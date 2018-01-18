#ifndef MTLX_TO_A_TRANSLATION_DOCUMENT_CMS_H
#define MTLX_TO_A_TRANSLATION_DOCUMENT_CMS_H

#include <iostream>
#include <tuple>
#include <memory>
#include <functional>
#include <sstream>
#include <assert.h>
#include <cxxabi.h>

#include "macros.h"
#include "exceptions.h"
#include "configuration.h"
#include "operating_system/constants.h"
#include "arnold/constants/interface.h"
#include "operating_system/facade.h"
#include "arnold/utility.h"
#include "materialx/facade.h"

namespace MaterialXToArnold
{

template<typename AFT,  // Arnold Facade Type
         typename MFT,  // MaterialX Facade Type
         typename OSFT>   // Operating System Facade Type
class ColorManagementSystem
{
public:

    ColorManagementSystem(const AFT& arnold_facade,
                          const MFT& materialx_facade,
                          Configuration& config,
                          typename AFT::AtNodeTDeleterFncPtrT node_deleter,
                          const typename MFT::DocumentPtrT& doc):
        af_ (arnold_facade),
        mf_ (materialx_facade),
        config_ (config),
        node_deleter_ (node_deleter),
        doc_ (doc) {}

    void Default(typename AFT::AtNodeT* options_node,
                 const char* options_color_manager_param_name)
    {
        // TODO: Use the Arnold facade here
        // Set the default built-in color manager to be used, which will use
        // 'sRGB' (working) and 'linear' (rendering) spaces
        AiNodeSetPtr(options_node, options_color_manager_param_name, nullptr);
        // Set the default working color space to linear, which will result in
        // the values being used as-is.
        config_.working_color_space_ = "linear";
        MSG_INFO(af_, "No docuemt level color management "
               "system is specified in the MaterialX file %s. Using Arnold's"
               "default built-in color manager and a default working color "
               "space of linear with linear rendering. All values will "
               "be presumed to be used as-is.",  doc_->getSourceUri().c_str());
    }

    void OpenColorIO(typename AFT::AtNodeT* options_node,
                     const char* options_color_manager_param_name)
    {
        // Get the color managment config file path (from MaterialX Doc or env)
        std::string cms_config_file_path {""};
        GetOpenColorIOConfigFilePathStr(cms_config_file_path);

        // Fall back on Arnold's default CMS when there is an empty or missing
        // OCIO config file
        if (cms_config_file_path.empty())
        {
            MSG_WARNING(af_, "Falling back on the Arnold default color "
                        "management system as no OpenColorIO config file was "
                        "found - empty or missing file paths on both the "
                        "attribute cmsconfig in the MaterialX file \"%s\" and "
                        "the \"OCIO\" environment variable.",
                        doc_->getSourceUri().c_str());
            Default(options_node, options_color_manager_param_name);
            return;
        }

        // Create an Arnold color manager OCIO node to validate the OCIO config
        // file Upon success, a new pointer to the color manager OCIO node will
        // be added to the user data.
        bool success = CreateArnoldColorManagerOpenColorIONode(options_node,
                    options_color_manager_param_name, cms_config_file_path);

        // Fall back on Arnold's default CMS when OCIO config file is invalid
        if (!success)
        {
            MSG_WARNING(af_, "Falling back on the Arnold default color "
                        "management system as \"%s\" is not a valid OCIO "
                        "config file.", cms_config_file_path.c_str());

            Default(options_node, options_color_manager_param_name);
            return;
        }
    }

private:

    bool HasColorSpace(
            const typename AFT::AtNodeTUniquePtrT& color_manager_ocio_node,
            const std::string& color_space)
    {
        if (color_space.empty()) {return false;}

        // TODO: Use the Arnold facade here
        // Check the default color space attribute string value against the
        // list of color space strings in the color manager node (family should
        // be the empty string as we want all color spaces).
        int nspaces =
                AiColorManagerGetNumColorSpaces(color_manager_ocio_node.get());
        for (int i = 0; i < nspaces; i++)
        {
            typename AFT::AtStringT name =
                    AiColorManagerGetColorSpaceNameByIndex(
                        color_manager_ocio_node.get(), i);
            if (color_space == std::string(name.c_str()))
            {
                return true;
            }
        }
        return false;
    }

    void GetOpenColorIOConfigFilePathStr(std::string& color_management_config)
    {
        color_management_config = doc_->getColorManagementConfig();
        if (color_management_config.empty())
        {
            MSG_INFO(af_, "The OpenColorIO config file path (given by the "
                     "attribute cmsconfig) in the MaterialX file \"%s\" is "
                     "missing or empty.", doc_->getSourceUri().c_str());

            // When the color management config file path is the empty string we
            // will try to read it instead from the 'OCIO' environment variable,
            // like most applications, including Arnold, do.
            // https://support.solidangle.com/display/A5NodeRef/color+managers

            MSG_INFO(af_, "Attempting to get the OCIO config file path from "
                     "the \"%s\" environment variable ...",
                     kOpenColorInputOutputEnvVarName);

            OSFT os {};
            const char* result = os.getenv(kOpenColorInputOutputEnvVarName);
            if (result == nullptr)
            {
                MSG_WARNING(af_, "No \"%s\" environment variable found.",
                            result, kOpenColorInputOutputEnvVarName);
                color_management_config = "";
            }
            else
            {
                MSG_INFO(af_, "Found the string \"%s\" in the \"%s\" "
                         "environment variable.", result,
                         kOpenColorInputOutputEnvVarName);
                color_management_config = result;
            }
        }
    }

    bool CreateArnoldColorManagerOpenColorIONode(
            typename AFT::AtNodeT* options_node,
            const char* options_color_manager_param_name,
            const std::string& cms_config_file_path)
    {
        // Get a unique name for the color manager ocio node
        const typename AFT::AtStringT
                start_str {"color_manager_ocio_materialx"};
        const typename AFT::AtStringT color_manager_ocio_node_name =
                MakeUniqueNodeName(af_, start_str);

        // Create an Arnold OCIO color manager node in order to validate config
        // and the default color space. The unique pointer will call deleter
        // when the pointer goes out of scope to destroy the node unless its
        // ownership is passed (to the user_data).
        typename AFT::AtNodeTDeleterBindT deleter = std::bind(node_deleter_,
                                                 std::placeholders::_1, af_);
        typename AFT::AtNodeTUniquePtrT color_manager_ocio_node {
            af_.AiNode(typename AFT::AtStringT(kColorManagerOcioNodeEntryName),
                      color_manager_ocio_node_name), deleter};

        // TODO: Use the Arnold facade here
        // Set the color manager ocio config file to validate it
        AiNodeSetStr(color_manager_ocio_node.get(), "config",
                     cms_config_file_path.c_str());

        // TODO: Use the Arnold facade here
        // AiColorManagerGetNumColorSpaces will be 0 when the color manager ocio
        // node failed to read the OCIO config file on its config parameter.
        if (AiColorManagerGetNumColorSpaces(color_manager_ocio_node.get()) == 0)
        {
            return false;
        }

        MSG_INFO(af_, "The OCIO config file \"%s\" is valid according to a "
                 "newly created and connected Arnold OCIO color manager node "
                 "(of type \"%s\") with name \"%s\".",
                 cms_config_file_path.c_str(), kColorManagerOcioNodeEntryName,
                 color_manager_ocio_node_name.c_str());

        // Try to set the default color space
        WorkingColorSpace(color_manager_ocio_node);

        // Set the newly created color manager ocio node to be the active color
        // manager for the scene (set options node's color_manager parameter to
        // point to the node) and transfer ownership of the unique pointer for
        // it to the user data.
        AiNodeSetPtr(options_node, options_color_manager_param_name,
                     color_manager_ocio_node.get());

        typename AFT::UserDataT* user_data =
                static_cast<typename AFT::UserDataT*>(config_.user_data_ptr_);
        user_data->push_back(color_manager_ocio_node.release());
        assert(color_manager_ocio_node.get() == nullptr &&
               "a released unique pointer should be NULL");
        return true;
    }

    // The MaterialX Document's Working Color Space.
    //
    // The working color space of a MaterialX document is defined by the
    // colorspace attribute of its root <materialx> element, and it is strongly
    // recommended that all <materialx> elements define a specific colorspace
    // if they wish to use a color-managed workflow rather than relying on a
    // default colorspace
    //
    // The color space of individual color image files and values may be defined
    // via a colorspace attribute in a parameter which defines a filename or
    // value. Color images and values in spaces other than the working space are
    // expected to be transformed by the application into the working space
    // before computations are performed.
    //
    // (the color space that input
    // was created in). This color space should be used when one is not provided
    // in MaterialX elements. If not specified, the should default to the
    // rendering color space in order to make sure the values are used as-is.
    void WorkingColorSpace(
            const typename AFT::AtNodeTUniquePtrT& color_manager_ocio_node)
    {
        // Get the working color space from the MaterialX doc
        std::string working_color_space = doc_->getColorSpace();

        // Check whether the working color space from the MaterialX doc is one
        // that is in the OCIO config file
        if (HasColorSpace(color_manager_ocio_node, working_color_space))
        {
            // TODO: Use the Arnold facade here
            // Set color_space_linear on the color manager ocio node. The
            // parameter color_space_linear is the default linear color space
            // that Arnold will use as its rendering color space.
            const typename AFT::AtStringT wcs {working_color_space.c_str()};
            // TODO: Put me in constants
            const typename AFT::AtStringT pname {"color_space_linear"};
            AiNodeSetStr(color_manager_ocio_node.get(), pname, wcs);

        }
        else
        {
            const typename AFT::AtStringT pname {"color_space_linear"};
            typename AFT::AtStringT wcs =
                    AiNodeGetStr(color_manager_ocio_node.get(), pname);
            MSG_WARNING(af_, "The working color space \"%s\" given in the "
                        "colorspace attribute of the root MaterialX element "
                        "is not one in theOpenColorIO configuration file "
                        "(defaulting to." "\"%s\"",
                        working_color_space.c_str(), wcs.c_str());
        }
    }


private:
    const AFT& af_; // Arnold Facade
    const MFT& mf_; // MaterialX Facade
    Configuration& config_;
    typename AFT::AtNodeTDeleterFncPtrT node_deleter_;
    const typename MFT::DocumentPtrT& doc_; // MaterialX document

};

} // namespce MaterialXToArnold

#endif // MTLX_TO_A_TRANSLATION_DOCUMENT_CMS_H
