#include "materialx/facade.h"

#include <tuple>

#include <MaterialXCore/Document.h>
#include <MaterialXFormat/XmlIo.h>

namespace MaterialXToArnold
{

MaterialXFacade::DocumentPtrT MaterialXFacade::createDocument() const
{
    return MaterialX::createDocument();
}

std::tuple<int, int, int> MaterialXFacade::getVersionIntegers() const
{
    return MaterialX::getVersionIntegers();
}

void MaterialXFacade::readFromXmlFile(MaterialXFacade::DocumentPtrT doc,
                                      const std::string& filename,
                                      const std::string& searchPath,
                                      bool readXIncludes) const
{
    MaterialX::readFromXmlFile(doc, filename, searchPath, readXIncludes);
}


} // namespce MaterialXToArnold

