#include "dispatch.h"

#include <vector>

#include <ai.h>
#include <MaterialXCore/Element.h>
#include <MaterialXCore/Geom.h>
#include <MaterialXCore/Util.h>
#include <MaterialXCore/Look.h>
#include <MaterialXCore/Material.h>
#include <MaterialXCore/Node.h>

#include "mtrace.h"
#include "demangle.h"

namespace MaterialXToArnold
{

void Dispatch(const AtNode* proc_node,
              const MaterialX::ElementPtr elem,
              std::vector<AtNode*>& nodes)
{
    // TODO: Avoid potentially-evaluated-expression warning

    MTRACE(AiMsgDebug, "Dispatching element %s (Type Name: %s, Category: %s, "
           "Depth: %d) ... ",
           elem->asString().c_str(),
           demangle(typeid(*elem).name()).c_str(),
           elem->getCategory().c_str(),
           elem->traverseTree().getElementDepth());

    if(elem->isA<MaterialX::Collection>())
    {
        // Base: Element
        //
        // A collection element within a Document.
        // ss << "Collection";
    }
    // Skipping Document and ObservedDocument
    else if(elem->isA<MaterialX::GenericElement>())
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
    else if(elem->isA<MaterialX::CollectionAdd>())
    {
        // Base: Element|GeomElement
        //
        // A collection add element within a Collection.
        // ss << "CollectionAdd";
    }
    else if(elem->isA<MaterialX::CollectionRemove>())
    {
        // Base: Element|GeomElement
        //
        // A collection remove element within a Collection.
        // ss << "CollectionRemove";
    }
    else if(elem->isA<MaterialX::GeomInfo>())
    {
        // Base: Element|GeomElement
        //
        // A geometry info element within a Document.
        // ss << "GeomInfo";
    }
    else if(elem->isA<MaterialX::MaterialAssign>())
    {
        // Base: Element|GeomElement
        //
        // A material assignment element within a Look.
        // ss << "MaterialAssign";
    }
    else if(elem->isA<MaterialX::PropertySetAssign>())
    {
        // Base: Element|GeomElement
        //
        // A property set assignment element within a Look.
        // ss << "PropertySetAssign";
    }
    else if(elem->isA<MaterialX::Visibility>())
    {
        // Base: Element|GeomElement
        //
        // A visibility element within a Look. A Visibility describes the
        // visibility relationship between two geometries or geometric
        // collections.
        // ss << "Visibility";
    }
    // End Element|GeomElement subclasses
    else if(elem->isA<MaterialX::Look>())
    {
        // Base: Element
        //
        // A look element within a Document.
        // ss << "Look";
    }
    else if(elem->isA<MaterialX::LookInherit>())
    {
        // Base: Element
        //
        // A look inheritance element within a Look.
        // ss << "LookInherit";
    }
    else if(elem->isA<MaterialX::Material>())
    {
        // Base: Element
        //
        // A Material instantiates one or more shader nodes with a specific
        // set of data bindings.
        // ss << "Material";
    }
    else if(elem->isA<MaterialX::MaterialInherit>())
    {
        // Base: Element
        //
        // A material inheritance element within a Material.
        // ss << "MaterialInherit";
    }
    else if(elem->isA<MaterialX::NodeGraph>())
    {
        // Base: Element
        //
        // A node graph element within a Document.
        // ss << "NodeGraph";
    }
    else if(elem->isA<MaterialX::PropertySet>())
    {
        // Base: Element
        //
        // A property set element within a Document.
        // ss << "PropertySet";
    }
    else if(elem->isA<MaterialX::ShaderRef>())
    {
        // Base: Element
        //
        // A ShaderRef instantiates a shader NodeDef within the context of a
        // Material.
        // ss << "ShaderRef";
    }
    else if(elem->isA<MaterialX::TypeDef>())
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
    else if(elem->isA<MaterialX::Implementation>())
    {
        // Base: Element|TypedElement|InterfaceElement
        //
        // An Implementation is used to associate external source code with a
        // specific NodeDef, providing a definition for the node that may eiher
        // be universal or restricted to a specific target.
        // ss << "Implementation";
    }
    else if(elem->isA<MaterialX::Node>())
    {
        // Base: Element|TypedElement|InterfaceElement
        //
        // A Node represents an instance of a NodeDef within a graph, and its
        // Parameter and Input elements apply specific values and connections
        // to that instance.
        // ss << "Node";
    }
    else if(elem->isA<MaterialX::NodeDef>())
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
    else if(elem->isA<MaterialX::BindInput>())
    {
        // Base: Element|TypedElement|ValueElement
        //
        // A BindInput binds spatially-varying data to an Input of a shader NodeDef
        // within the scope of a material.
        // ss << "BindInput";
    }
    else if(elem->isA<MaterialX::BindParam>())
    {
        // Base: Element|TypedElement|ValueElement
        //
        // A BindParam binds uniform data to a Parameter of a shader NodeDef within
        // the scope of a Material.
        // ss << "BindParam";
    }
    else if(elem->isA<MaterialX::GeomAttr>())
    {
        // Base: Element|TypedElement|ValueElement
        //
        // A geometry attribute element within a GeomInfo.
        // ss << "GeoAttr";
    }
    else if(elem->isA<MaterialX::Override>())
    {
        // Base: Element|TypedElement|ValueElement
        //
        // An Override modifies the uniform value of a public Parameter or Input
        // within the scope of a Material.
        // ss << "Override";
    }
    else if(elem->isA<MaterialX::Parameter>())
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
    else if(elem->isA<MaterialX::Input>())
    {
        // Base: Element|TypedElement|ValueElement|PortElement
        //
        // An Input holds either a uniform value or a connection to a
        // spatially-varying Output, either of which may be modified within
        // the scope of a Material.
        // ss << "Input";
    }
    else if(elem->isA<MaterialX::Output>())
    {
        // Base: Element|TypedElement|ValueElement|PortElement
        //
        // A spatially-varying output element within a NodeGraph
        // ss << "Output";
    }
    // End Element|TypedElement|ValueElement|PortElement subclasses
    else if(elem->isA<MaterialX::Property>())
    {
        // Base: Element|TypedElement|ValueElement
        //
        // A property element within a PropertySet.
        // ss << "Property";
    }
    else if(elem->isA<MaterialX::PropertyAssign>())
    {
        // Base: Element|TypedElement|ValueElement
        //
        // A property assignment element within a Look.
        // ss << "PropertyAssign";
    }
    // End Element|TypedElement|ValueElement subclasses
    // End Element|TypedElement subclasses
    else
    {
        MTRACE(AiMsgError, "Skipping MaterialX element with name "
               "\"%s\" as it has an unsupported MaterialX type of %s",
               elem->getName().c_str(), demangle(typeid(*elem).name()).c_str());
    }




//    const std::vector<std::string>& attr_names = elem->getAttributeNames();
//    for(std::string name : attr_names)
//    {
//        MTRACE(AiMsgDebug, proc_node, "Attribute name %s", name.c_str());
//    }

    // AtNode *points_node = AiNode("points", "test", proc_node);
    // nodes.push_back(points_node);

}

} // namespce MaterialXToArnold
