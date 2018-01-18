#ifndef MTLX_TO_A_TRANSLATION_DOCUMENT_TRANSLATOR_H
#define MTLX_TO_A_TRANSLATION_DOCUMENT_TRANSLATOR_H

#include <memory>
#include <functional>
#include <assert.h>

#include "macros.h"
#include "configuration.h"
#include "operating_system/constants.h"
#include "arnold/constants/interface.h"
#include "operating_system/facade.h"
#include "arnold/utility.h"

namespace MaterialXToArnold
{

template<typename AFT,     // Arnold Facade Type
         typename MFT,     // MaterialX Facade Type
         typename CMST>    // Color Management System Type
class DocumentTranslator
{
public:

    DocumentTranslator(const AFT& arnold_facade,
               const MFT& materialx_facade,
               Configuration& config,
               typename AFT::AtNodeTDeleterFncPtrT node_deleter,
               typename MFT::DocumentPtrT& doc):
        af_ (arnold_facade),
        mf_ (materialx_facade),
        config_ (config),
        node_deleter_ (node_deleter),
        doc_ (doc),
        cms_ (arnold_facade, materialx_facade, config, node_deleter, doc) {}

    void Translate()
    {

        // Get the options node and its color manager parameter name
        typename AFT::AtNodeT* options_node = nullptr;
        const char* options_color_manager_param_name = nullptr;
        const typename AFT::AtStringT node_name {"options"};
        ArnoldBuiltin<AFT>(af_, node_name, kOptionsColorManagerParamNameIndex,
                          options_node, &options_color_manager_param_name);

        // MaterialX
        // If a color management system (CMS) is specified using a cms attribute
        // in the top-level <materialx> element, the implementation will use that
        // CMS to handle all color transformations. If no CMS is specified, then
        // all values are presumed to be used as-is. One color management system
        // specifically supported by MaterialX is OpenColorIO.
        // Ref: MaterialX.v1.35.Final.pdf page 14

        config_.color_management_sysem_ = doc_->getColorManagementSystem();
        if (!config_.color_management_sysem_.compare("ocio"))
        {
            MSG_INFO(af_, "Found the supported color management system \"%s\" "
                     "specified in the MaterialX file \"%s\".",
                     config_.color_management_sysem_.c_str(),
                     doc_->getSourceUri().c_str());

            cms_.OpenColorIO(options_node, options_color_manager_param_name);
        }
        else if (config_.color_management_sysem_.empty())
        {
            MSG_INFO(af_, "Using Arnold's default color management system as none "
                     "(an empty string) was specified in the MaterialX file %s .",
                     config_.color_management_sysem_.c_str(),
                     doc_->getSourceUri().c_str());

            cms_.Default(options_node, options_color_manager_param_name);
        }
        else
        {
            std::stringstream msg;
            msg << "The color management system \"" <<
                   config_.color_management_sysem_ << "\" given in the " <<
                   "MaterialX file " << doc_->getSourceUri() << "is not supported.";
            throw UnsupportedError(__FILE__, __LINE__, msg.str());
        }

    }

private:
    const AFT& af_;     // Arnold Facade
    const MFT& mf_;     // MaterialX Facade
    Configuration& config_;
    typename AFT::AtNodeTDeleterFncPtrT node_deleter_;
    typename MFT::DocumentPtrT& doc_;
    CMST cms_;   // Color Managment System
};

} // namespce MaterialXToArnold

#endif // MTLX_TO_A_TRANSLATION_DOCUMENT_TRANSLATOR_H
