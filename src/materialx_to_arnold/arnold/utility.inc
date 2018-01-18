#ifndef MTLX_TO_A_ARNOLD_UTILITY_INC
#define MTLX_TO_A_ARNOLD_UTILITY_INC

#include <iostream>
#include <limits>
#include <string>
#include <sstream>

#include <ai.h>

#include "arnold/constants/interface.h"
#include "arnold/facade.h"
#include "exceptions.h"

namespace MaterialXToArnold
{

// -----------------------------------------------------------
// Arnold Utility Functions
// -----------------------------------------------------------

// A node look up by name function that throws when it does not find a node
// with the given name.
template<typename AFT>     // Arnold Facade Type
typename AFT::AtNodeT*
NodeLookUpByName(const AFT& af,
                 const typename AFT::AtStringT name,
                 const typename AFT::AtNodeT* parent = nullptr)
{
    // Look up node -- node will be a pointer to a node whose "name" parameter
    // matches the given name string, or NULL if there are no nodes with that
    // name
    typename AFT::AtNodeT* node = af.AiNodeLookUpByName(name, parent);
    if(node == nullptr)
    {
        std::stringstream ss;
        ss << "Detected a missing node that should exist with the name " <<
              name.c_str();
        throw RuntimeError(__FILE__, __LINE__, ss.str());
    }
    return node;
}

template<typename AFT>     // Arnold Facade Type
void GetArnoldBuiltinParamName(const AFT& af,
                               const typename AFT::AtStringT& node_name,
                               const ArnoldBuiltinParamNameIndex i,
                               const typename AFT::AtNodeT* node,
                               const char** parameter_name)
{
    // Get expected node type name
    ArnoldBuiltinNodeEntryNameIndex idx {kArnoldBuiltinParamNameToNodeIndex[i]};
    const char* node_entry_name {kArnoldBuiltinNodeEntryNamesUsed[idx]};
    typename AFT::AtStringT expected_node_entry_name {node_entry_name};

    // Get actual node type name
    const typename AFT::AtNodeEntryT* nentry = af.AiNodeGetNodeEntry(node);
    typename AFT::AtStringT actual_node_entry_name =
            af.AiNodeEntryGetNameAtString(nentry);

    if(expected_node_entry_name != actual_node_entry_name)
    {
        std::stringstream ss;
        ss << "A node with name " << node_name.c_str() << " has a type " <<
              actual_node_entry_name.c_str() << " instead of the expected " <<
              expected_node_entry_name.c_str();
        throw RuntimeError(__FILE__, __LINE__, ss.str());
    }

    *parameter_name = kArnoldBuiltinParamNameIndex[i];
}

// Get the Arnold Built-in node and parameter name for the given node name
// and parameter name index, throws when missing
template<typename AFT>     // Arnold Facade Type
void ArnoldBuiltin(const AFT& af,
                   const typename AFT::AtStringT& name,
                   const ArnoldBuiltinParamNameIndex i,
                   typename AFT::AtNodeT* node,
                   const char** parameter_name)
{
    node = NodeLookUpByName<AFT>(af, name);
    GetArnoldBuiltinParamName<AFT>(af, name, i, node, parameter_name);
}

template<typename AFT>     // Arnold Facade Type
typename AFT::AtStringT MakeUniqueNodeName(const AFT& af,
                                           const typename AFT::AtStringT& name)
{
    typename AFT::AtNodeT* node = af.AiNodeLookUpByName(name, nullptr);
    if(node == nullptr) return name;

    for(int i = 1; i < std::numeric_limits<int>::max(); i++)
    {
        std::string ustr = std::string(name.c_str()) + std::to_string(i);
        typename AFT::AtStringT uname {ustr.c_str()};
        node = af.AiNodeLookUpByName(uname, nullptr);
        if(node == nullptr) return uname;
    }
    throw RuntimeError(__FILE__, __LINE__, "Excessive tries at making a unique"
                       "node name detected.");
}

} // namespace MaterialXToArnold

#endif // MTLX_TO_A_ARNOLD_UTILITY_INC
