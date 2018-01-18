#ifndef MTLX_TO_A_INTERFACE_H
#define MTLX_TO_A_INTERFACE_H

#include <ai.h>

// The MaterialX To Arnold library's interface for the Arnold procedural

namespace MaterialXToArnold
{

void Parameters(AtList* params, AtNodeEntry* nentry);
int ProceduralInit(const AtNode* node, void** user_ptr);
int ProceduralCleanup(const AtNode* node, void* user_ptr);
int ProceduralNumNodes(const AtNode* node, void* user_ptr);
AtNode* ProceduralGetNode(const AtNode* node, void* user_ptr, int i);

} // namespce MaterialXToArnold

#endif // MTLX_TO_A_INTERFACE_H
