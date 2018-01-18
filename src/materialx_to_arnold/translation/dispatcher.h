#ifndef MTLX_TO_A_TRANSLATION_DISPATCHER_H
#define MTLX_TO_A_TRANSLATION_DISPATCHER_H

#include "macros.h"
#include "exceptions.h"
#include "configuration.h"
#include "operating_system/constants.h"
#include "arnold/constants/interface.h"
#include "operating_system/facade.h"
#include "arnold/utility.h"
#include "materialx/facade.h"

#include "translation/demangle.h"
#include "translation/document/color_management_system.h"
#include "translation/document/translator.h"

namespace MaterialXToArnold
{

// Visitor pattern to do dynamic dispatching of MaterialX element translation

template<typename AFT,     // Arnold Facade Type
         typename MFT>     // MaterialX Facade Type
class Dispatcher
{

public:

    Dispatcher(const AFT& arnold_facade,
               const MFT& materialx_facade,
               Configuration& config,
               typename AFT::AtNodeTDeleterFncPtrT node_deleter):
        af_ (arnold_facade),
        mf_ (materialx_facade),
        config_ (config),
        node_deleter_ (node_deleter) {}


    void dispatch(typename MFT::ElementPtrT& elem) const
    {

        MSG_DEBUG(af_, "Dispatching element %s for translation (Type Name: %s, "
                  "Category: %s, Depth: %d) ... ",
                  elem->asString().c_str(),
                  DemangleType((*elem)).c_str(),
                  elem->getCategory().c_str(),
                  elem->traverseTree().getElementDepth());

        if(elem->template isA<typename MFT::CollectionT>())
        {
            // Base: Element
            //
            // A collection element within a Document.
            // ss << "Collection";
        }
        if(elem->template isA<typename MFT::DocumentT>())
        {
            // Base: Element
            //
            // A collection element within a Document.
            // ss << "Collection";

            typename MFT::DocumentPtrT doc =
                    elem->template asA<typename MFT::DocumentT>();

            using CMS = ColorManagementSystem<AFT, MFT, OperatingSystem>;
            DocumentTranslator<AFT, MFT, CMS>
                    dt {af_, mf_, config_, node_deleter_, doc};

            dt.Translate();

        }
        else if(elem->template isA<typename MFT::GenericElementT>())
        {
            // Base: Element
            //
            // A generic element subclass, for instantiating elements with
            // unrecognized categories.
            // ss << "GenericElement";
        }
        // Start Element|GeomElement subclasses
        //  GeomElement is the base class for geometric elements, which support
        //  bindings to geometries and geometric collections.
        else if(elem->template isA<typename MFT::CollectionAddT>())
        {
            // Base: Element|GeomElement
            //
            // A collection add element within a Collection.
            // ss << "CollectionAdd";
        }
        else if(elem->template isA<typename MFT::CollectionRemoveT>())
        {
            // Base: Element|GeomElement
            //
            // A collection remove element within a Collection.
            // ss << "CollectionRemove";
        }
        else if(elem->template isA<typename MFT::GeomInfoT>())
        {
            // Base: Element|GeomElement
            //
            // A geometry info element within a Document.
            // ss << "GeomInfo";
        }
        else if(elem->template isA<typename MFT::MaterialAssignT>())
        {
            // Base: Element|GeomElement
            //
            // A material assignment element within a Look.
            // ss << "MaterialAssign";
        }
        else if(elem->template isA<typename MFT::PropertySetAssignT>())
        {
            // Base: Element|GeomElement
            //
            // A property set assignment element within a Look.
            // ss << "PropertySetAssign";
        }
        else if(elem->template isA<typename MFT::VisibilityT>())
        {
            // Base: Element|GeomElement
            //
            // A visibility element within a Look. A Visibility describes the
            // visibility relationship between two geometries or geometric
            // collections.
            // ss << "Visibility";
        }
        // End Element|GeomElement subclasses
        else if(elem->template isA<typename MFT::LookT>())
        {
            // Base: Element
            //
            // A look element within a Document.
            // ss << "Look";
        }
        else if(elem->template isA<typename MFT::LookInheritT>())
        {
            // Base: Element
            //
            // A look inheritance element within a Look.
            // ss << "LookInherit";
        }
        else if(elem->template isA<typename MFT::MaterialT>())
        {
            // Base: Element
            //
            // A Material instantiates one or more shader nodes with a specific
            // set of data bindings.
            // ss << "Material";
        }
        else if(elem->template isA<typename MFT::MaterialInheritT>())
        {
            // Base: Element
            //
            // A material inheritance element within a Material.
            // ss << "MaterialInherit";
        }
        else if(elem->template isA<typename MFT::NodeGraphT>())
        {
            // Base: Element
            //
            // A node graph element within a Document.
            // ss << "NodeGraph";
        }
        else if(elem->template isA<typename MFT::PropertySetT>())
        {
            // Base: Element
            //
            // A property set element within a Document.
            // ss << "PropertySet";
        }
        else if(elem->template isA<typename MFT::ShaderRefT>())
        {
            // Base: Element
            //
            // A ShaderRef instantiates a shader NodeDef within the context of a
            // Material.
            // ss << "ShaderRef";
        }
        else if(elem->template isA<typename MFT::TypeDefT>())
        {
            // Base: Element
            //
            // A type definition element within a Document.
            // ss << "TypeDef";
        }
        // Start Element|TypedElement subclasses
        //  TypedElement is the base class for typed elements.
        //
        // Start Element|TypedElement|InterfaceElement subclasses
        //  InterfaceElement  is the base class for interface elements such as Node
        //  and NodeDef. An InterfaceElement supports a set of Parameter and Input
        //  elements, with an API for setting their values.
        else if(elem->template isA<typename MFT::ImplementationT>())
        {
            // Base: Element|TypedElement|InterfaceElement
            //
            // An Implementation is used to associate external source code with a
            // specific NodeDef, providing a definition for the node that may eiher
            // be universal or restricted to a specific target.
            // ss << "Implementation";
        }
        else if(elem->template isA<typename MFT::NodeT>())
        {
            // Base: Element|TypedElement|InterfaceElement
            //
            // A Node represents an instance of a NodeDef within a graph, and its
            // Parameter and Input elements apply specific values and connections
            // to that instance.
            // ss << "Node";
        }
        else if(elem->template isA<typename MFT::NodeDefT>())
        {
            // Base: Element|TypedElement|InterfaceElement
            //
            // A NodeDef provides the declaration of a node interface, which may
            // then be instantiated as a Node or a ShaderRef.
            // ss << "NodeDef";
        }
        // End Element|TypedElement|InterfaceElement subclasses
        //
        // Start Element|TypedElement|ValueElement subclasses
        //  The base class for elements that support typed values.
        else if(elem->template isA<typename MFT::BindInputT>())
        {
            // Base: Element|TypedElement|ValueElement
            //
            // A BindInput binds spatially-varying data to an Input of a shader NodeDef
            // within the scope of a material.
            // ss << "BindInput";
        }
        else if(elem->template isA<typename MFT::BindParamT>())
        {
            // Base: Element|TypedElement|ValueElement
            //
            // A BindParam binds uniform data to a Parameter of a shader NodeDef within
            // the scope of a Material.
            // ss << "BindParam";
        }
        else if(elem->template isA<typename MFT::GeomAttrT>())
        {
            // Base: Element|TypedElement|ValueElement
            //
            // A geometry attribute element within a GeomInfo.
            // ss << "GeoAttr";
        }
        else if(elem->template isA<typename MFT::OverrideT>())
        {
            // Base: Element|TypedElement|ValueElement
            //
            // An Override modifies the uniform value of a public Parameter or Input
            // within the scope of a Material.
            // ss << "Override";
        }
        else if(elem->template isA<typename MFT::ParameterT>())
        {
            // Base: Element|TypedElement|ValueElement
            //
            // A Parameter holds a single uniform value, which may be modified
            // within the scope of a Material.
            // ss << "Parameter";
        }
        // Start Element|TypedElement|ValueElement|PortElement subclasses
        //
        // Port elements support spatially-varying upstream connections to nodes
        else if(elem->template isA<typename MFT::InputT>())
        {
            // Base: Element|TypedElement|ValueElement|PortElement
            //
            // An Input holds either a uniform value or a connection to a
            // spatially-varying Output, either of which may be modified within
            // the scope of a Material.
            // ss << "Input";
        }
        else if(elem->template isA<typename MFT::OutputT>())
        {
            // Base: Element|TypedElement|ValueElement|PortElement
            //
            // A spatially-varying output element within a NodeGraph
            // ss << "Output";
        }
        // End Element|TypedElement|ValueElement|PortElement subclasses
        else if(elem->template isA<typename MFT::PropertyT>())
        {
            // Base: Element|TypedElement|ValueElement
            //
            // A property element within a PropertySet.
            // ss << "Property";
        }
        else if(elem->template isA<typename MFT::PropertyAssignT>())
        {
            // Base: Element|TypedElement|ValueElement
            //
            // A property assignment element within a Look.
            // ss << "PropertyAssign";
        }
        else
        {
            MSG_ERROR(af_, "Skipping MaterialX element with name "
                   "\"%s\" as it has an unsupported MaterialX type of %s",
                   elem->getName().c_str(),
                      DemangleType((*elem)).c_str());

        }
    }


private:


private:
    const AFT& af_; // Arnold Facade
    const MFT& mf_; // MaterialX Facade
    Configuration& config_;
    typename AFT::AtNodeTDeleterFncPtrT node_deleter_;

};

} // namespce MaterialXToArnold

#endif // MTLX_TO_A_TRANSLATION_DISPATCHER_H
