#include <ai.h>

#include "interface.h" // MaterialX to Arnold library interface

namespace MtlXToA = MaterialXToArnold;

extern const AtNodeMethods* MaterialXMtd;
AI_PROCEDURAL_NODE_EXPORT_METHODS(MaterialXMtd);

node_parameters
{
    return MtlXToA::Parameters(params, nentry);
}

// This is the first MaterialX procedural method called. It performs all
// initialization required for the procedural. It creates new nodes based on the
// MaterialX file provided as a parameters to the node. A pointer to each new
// node created is added to the nodes is tracked in the user data so that each
// can be returned in order from the procedural_get_node method.
procedural_init
{
    // TODO: Enforce one and only one MaterialX procedrual.

    // Try to translate the MaterialX document specified in the parameters of
    // the procedural node. The ProceduralInit function will return true on
    // success and false otherwise.
    return MtlXToA::ProceduralInit(node, user_ptr);
}

procedural_cleanup
{
    return MtlXToA::ProceduralCleanup(node, user_ptr);
}

procedural_num_nodes
{
    return MtlXToA::ProceduralNumNodes(node, user_ptr);
}
  
procedural_get_node
{
    return MtlXToA::ProceduralGetNode(node, user_ptr, i);
}

node_loader
{
    if (i>0)
      return false;

    node->methods      = MaterialXMtd;
    node->output_type  = AI_TYPE_NONE;
    node->name         = PROCEDURAL_NAME;
    node->node_type    = AI_NODE_SHAPE_PROCEDURAL;
    strcpy(node->version, AI_VERSION);

    return true;
}
