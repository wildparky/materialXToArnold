#ifndef MTLX_TO_A_MATERIALX_FACADE_H
#define MTLX_TO_A_MATERIALX_FACADE_H

#include <utility>
#include <string>

#include <MaterialXCore/Util.h>
#include <MaterialXCore/Document.h>
#include <MaterialXFormat/XmlIo.h>

namespace MaterialXToArnold
{

class MaterialXFacade
{
public:
    using CollectionT = MaterialX::Collection;
    using DocumentT = MaterialX::Document;
    using ElementT = MaterialX::Element;
    using GenericElementT = MaterialX::GenericElement;
    using CollectionAddT = MaterialX::CollectionAdd;
    using CollectionRemoveT = MaterialX::CollectionRemove;
    using GeomInfoT = MaterialX::GeomInfo;
    using MaterialAssignT = MaterialX::MaterialAssign;
    using PropertySetAssignT = MaterialX::PropertySetAssign;
    using VisibilityT = MaterialX::Visibility;
    using LookT = MaterialX::Look;
    using LookInheritT = MaterialX::LookInherit;
    using MaterialT = MaterialX::Material;
    using MaterialInheritT = MaterialX::MaterialInherit;
    using NodeGraphT = MaterialX::NodeGraph;
    using PropertySetT = MaterialX::PropertySet;
    using ShaderRefT = MaterialX::ShaderRef;
    using TypeDefT = MaterialX::TypeDef;
    using ImplementationT = MaterialX::Implementation;
    using NodeT = MaterialX::Node;
    using NodeDefT = MaterialX::NodeDef;
    using BindInputT = MaterialX::BindInput;
    using BindParamT = MaterialX::BindParam;
    using GeomAttrT = MaterialX::GeomAttr;
    using OverrideT = MaterialX::Override;
    using ParameterT = MaterialX::Parameter;
    using InputT = MaterialX::Input;
    using OutputT = MaterialX::Output;
    using PropertyT = MaterialX::Property;
    using PropertyAssignT = MaterialX::PropertyAssign;

    using DocumentPtrT = MaterialX::DocumentPtr;
    using ElementPtrT = MaterialX::ElementPtr;

    // using DocumentPtrT = std::shared_ptr<MaterialX::Document>;

    DocumentPtrT createDocument() const;

    std::tuple<int, int, int> getVersionIntegers() const;

    void readFromXmlFile(
            DocumentPtrT doc,
            const std::string& filename,
            const std::string& searchPath = MaterialX::EMPTY_STRING,
            bool readXIncludes = true) const;

};

} // namespace MaterialXToArnold

#endif // MTLX_TO_A_MATERIALX_FACADE_H
