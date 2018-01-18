#include "interface.h"

#include <stdexcept>
#include <vector>

#include <ai.h>

#include "implementation.h"

namespace MaterialXToArnold
{

void Parameters(AtList* params, AtNodeEntry* nentry)
{
    ParametersImpl(params, nentry);
}

int ProceduralInit(const AtNode* node, void** user_ptr)
{
    return ProceduralInitImpl(node, user_ptr);
}

int ProceduralCleanup(const AtNode* node, void* user_ptr)
{
    return ProceduralCleanupImpl(node, user_ptr);
}

int ProceduralNumNodes(const AtNode* node, void* user_ptr)
{
    return ProceduralNumNodesImpl(node, user_ptr);
}

AtNode* ProceduralGetNode(const AtNode* node, void* user_ptr, int i)
{
    return ProceduralGetNodeImpl(node, user_ptr, i);
}

} // namespce MaterialXToArnold
