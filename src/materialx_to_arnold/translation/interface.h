#ifndef MTLX_TO_A_TRANSLATION_INTERFACE_H
#define MTLX_TO_A_TRANSLATION_INTERFACE_H

#include "configuration.h"
// #include "arnold_facade.h"
#include "materialx/facade.h"
// #include "materialx_document_translation.h"
#include "translation/translator.h"


namespace MaterialXToArnold
{

template<typename AFT,     // Arnold Facade
         typename MFT>     // MaterialX Facade
void Translate(const AFT& af,
               const MFT& mf,
               Configuration& config,
               typename AFT::AtNodeTDeleterFncPtrT node_deleter)
{
    Translator<AFT, MFT> t {af, mf, config, node_deleter};
    t.Translate();




//    DocumentTranslator<AFT,
//                       MFT,
//                       Document<AFT, MFT>,
//                       ColorManagementTranslator> dt (af, mf, procedural_node,
//                                                      procedural_node_name,
//                                                      config, user_data);
//    dt.Translate();
//
//     ColorManagementSystem cms;
//
//
//     TranslateColorManagementSystem<AFT, MFT>(
//                 af, doc, NodeDeleter, config, user_data);

//    //for (MaterialX::ElementPtr child : doc->getChildren())
//    //{
//    //    // Dispatch(procedural_node, child, nodes);
//    //}
}


} // namespce MaterialXToArnold

#endif // MTLX_TO_A_TRANSLATION_INTERFACE_H
