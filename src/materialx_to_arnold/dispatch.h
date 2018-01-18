#ifndef MTLX_TO_A_DISPATCH_H
#define MTLX_TO_A_DISPATCH_H

#include <vector>

#include <ai.h>
#include <MaterialXCore/Element.h>

namespace MaterialXToArnold
{

void Dispatch(const AtNode* proc_node,
              const MaterialX::ElementPtr elem,
              std::vector<AtNode*>& nodes);

} // namespce MaterialXToArnold

#endif // MTLX_TO_A_DISPATCH_H
