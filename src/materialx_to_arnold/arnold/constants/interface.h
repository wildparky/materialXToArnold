#ifndef MTLX_TO_A_CONSTANTS_ARNOLD_INTERFACE_H
#define MTLX_TO_A_CONSTANTS_ARNOLD_INTERFACE_H

#include <cstdint>

namespace MaterialXToArnold
{

// Constants to be used with the Arnold interface in the MaterialX to Arnold
// library and procedural node. Organizing the Arnold built-in node entry names
// and the Arnold built-in node parameter names below allows for both easy
// using and sanity checking that they exist.

// ====================================================================
// Arnold Built-in Node Entry Names
// ====================================================================
enum ArnoldBuiltinNodeEntryNameIndex {
    kOptionsNodeEntryNameIndex               = 0,
    kColorManagerOcioNodeEntryNameIndex      = 1,
    kNumOfArnoldBuiltinNodeEntryNamesUsed    = 2
};

const char* const
kArnoldBuiltinNodeEntryNamesUsed[kNumOfArnoldBuiltinNodeEntryNamesUsed]
{
    "options",
    "color_manager_ocio"
};

const char* const   kOptionsNodeEntryName = \
        kArnoldBuiltinNodeEntryNamesUsed[kOptionsNodeEntryNameIndex];

const char* const   kColorManagerOcioNodeEntryName = \
        kArnoldBuiltinNodeEntryNamesUsed[kColorManagerOcioNodeEntryNameIndex];


// ====================================================================
// Arnold Built-in Parameter Names
// ====================================================================
enum ArnoldBuiltinParamNameIndex {
    kOptionsColorManagerParamNameIndex  = 0,
    kNumArnoldBuiltinParamNamesUsed     = 1
};

const char* const
kArnoldBuiltinParamNameIndex[kNumArnoldBuiltinParamNamesUsed]
{
    "color_manager"
};

const
ArnoldBuiltinNodeEntryNameIndex
kArnoldBuiltinParamNameToNodeIndex[kNumArnoldBuiltinParamNamesUsed]
{
    kOptionsNodeEntryNameIndex // color_manager
};

} // namespce MaterialXToArnold

#endif // MTLX_TO_A_CONSTANTS_ARNOLD_INTERFACE_H
