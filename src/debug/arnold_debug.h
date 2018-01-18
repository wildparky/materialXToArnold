#ifndef MTLX_TO_A_ARNOLD_DEBUG_H
#define MTLX_TO_A_ARNOLD_DEBUG_H

#include <sstream>
#include <ai.h>

namespace ArnoldDebug
{

void UserParameters(std::ostringstream& os,
                    const AtNode* node,
                    const char* name,
                    const unsigned int indent,
                    unsigned int& n);

void Parameter(std::ostringstream& os,
               const AtNode* node,
               const char* name,
               const AtNodeEntry* nentry,
               const int index,
               const unsigned int indent);

void Parameters(std::ostringstream& os,
                const AtNode* node,
                const char* name,
                const AtNodeEntry* nentry,
                const int num_params,
                const unsigned int indent);

void Parameters(std::ostringstream& os,
                const AtNode* node,
                const char* name,
                const AtNodeEntry* nentry,
                const unsigned int indent);

void Node(std::ostringstream& os,
          const AtNode* node,
          const unsigned int indent);

void Nodes(std::ostringstream& os,
           const unsigned int node_mask = AI_NODE_ALL,
           const char* node_name_regex = nullptr,
           const unsigned int indent = 4);

} // namespace ArnoldDebug

#endif // MTLX_TO_A_ARNOLD_DEBUG_H
