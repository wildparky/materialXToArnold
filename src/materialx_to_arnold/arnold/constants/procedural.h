#ifndef MTLX_TO_A_CONSTANTS_ARNOLD_PROCEDURAL_H
#define MTLX_TO_A_CONSTANTS_ARNOLD_PROCEDURAL_H

#include <cstdint>
#include <ai.h>

namespace MaterialXToArnold
{

const char* const kDescriptionMetaDataName {"description"};

// ====================================================================
// Procedural Node
// ====================================================================
// The MaterialX To Arnold Procedural Node's Meta Data

const char* const kProceduralNodeDescriptionMetaData {
    "Translates to the Arnold renderer the MaterialX document in the file "
    "with the given name in the parameter mtlx_file_name along the search "
    "paths given in search_paths."
};

// ====================================================================
// Procedural Node Parameters
// ====================================================================

// The MaterialX To Arnold Procedural Node's Parameter Names and Meta Data

// Defining all these constants for the parameters here makes for better code
// (Once And Only Once) and easier unit tests.

const uint16_t kNumOfByteParams     {0};
const uint16_t kNumOfIntParams      {0};
const uint16_t kNumOfUIntParams     {0};
const uint16_t kNumOfBoolParams     {0};
const uint16_t kNumOfFltParams      {0};
const uint16_t kNumOfRGBParams      {0};
const uint16_t kNumOfRGBAParams     {0};
const uint16_t kNumOfVecParams      {0};
const uint16_t kNumOfVec2Params     {0};
const uint16_t kNumOfStrParams      {2};
const uint16_t kNumOfPtrParams      {0};
const uint16_t kNumOfNodeParams     {0};
const uint16_t kNumOfArrayParams    {0};
const uint16_t kNumOfMtxParams      {0};
const uint16_t kNumOfEnumParams     {0};
const uint16_t kNumOfClosureParams  {0};

const uint16_t kNumOfEnumTypeParams = kNumOfEnumParams;

const uint16_t kNumOfAllParams {
    kNumOfByteParams    +
    kNumOfIntParams     +
    kNumOfUIntParams    +
    kNumOfBoolParams    +
    kNumOfFltParams     +
    kNumOfRGBParams     +
    kNumOfRGBAParams    +
    kNumOfVecParams     +
    kNumOfVec2Params    +
    kNumOfStrParams     +
    kNumOfPtrParams     +
    kNumOfNodeParams    +
    kNumOfArrayParams   +
    kNumOfMtxParams     +
    kNumOfEnumParams    +
    kNumOfClosureParams
};

const uint16_t kNumOfParams[AI_TYPE_CLOSURE+1] {
    kNumOfByteParams,       //#define AI_TYPE_BYTE          0x00
    kNumOfIntParams,        //#define AI_TYPE_INT           0x01
    kNumOfUIntParams,       //#define AI_TYPE_UINT          0x02
    kNumOfBoolParams,       //#define AI_TYPE_BOOLEAN       0x03
    kNumOfFltParams,        //#define AI_TYPE_FLOAT         0x04
    kNumOfRGBParams,        //#define AI_TYPE_RGB           0x05
    kNumOfRGBAParams,       //#define AI_TYPE_RGBA          0x06
    kNumOfVecParams,        //#define AI_TYPE_VECTOR        0x07
    0,                      //#define AI_TYPE_POINT         0x08 // not in A5
    kNumOfVec2Params,       //#define AI_TYPE_VECTOR2       0x09
    kNumOfStrParams,        //#define AI_TYPE_STRING        0x0A
    kNumOfPtrParams,        //#define AI_TYPE_POINTER       0x0B
    kNumOfNodeParams,       //#define AI_TYPE_NODE          0x0C
    kNumOfArrayParams,      //#define AI_TYPE_ARRAY         0x0D
    kNumOfMtxParams,        //#define AI_TYPE_MATRIX        0x0E
    kNumOfEnumParams,       //#define AI_TYPE_ENUM          0x0F
    kNumOfClosureParams     //#define AI_TYPE_CLOSURE       0x10
};

// ----------------------------------------
// Index
enum ParamNameIndex {
    kMtlxFileNameParamIndex  = 0,
    kSearchPathParamIndex    = 1,
    kParamNameIndexSize
};

static_assert(kParamNameIndexSize == kNumOfAllParams, "tst" );

// ----------------------------------------
// Index to Param Name
const char* const kParamNames[kNumOfAllParams] {
    "mtlx_file_name",   // 0 MtlxFileNameParamIndex
    "search_paths"      // 1 SearchPathParamIndex
};

// ----------------------------------------
// Index to Param Type (see ai_params.h)
const uint8_t kParamType[kNumOfAllParams] {
    AI_TYPE_STRING,     // 0 MtlxFileNameParamIndex
    AI_TYPE_STRING,     // 1 SearchPathParamIndex
};

// ----------------------------------------
// Byte Param Default Value Array
const uint8_t kByteParamDefaultValues[kNumOfByteParams] {};

// ----------------------------------------
// Int Param Default Value Array
const int kIntParamDefaultValues [kNumOfIntParams] {};

// ----------------------------------------
// Unsigned Int Param Default Value Array
const unsigned int kUIntParamDefaultValues[kNumOfUIntParams] {};

// ----------------------------------------
// Boolean Param Default Value Array
const bool kBoolParamDefaultValues[kNumOfBoolParams] {};

// ----------------------------------------
// Float Param Default Value Array
const float kFltParamDefaultValues[kNumOfFltParams] {};

// ----------------------------------------
// RGB Param Default Value Array
const AtRGB kRGBParamDefaultValues[kNumOfRGBParams] {};

// ----------------------------------------
// RGBA Param Default Value Array
const AtRGBA kRGBAParamDefaultValues[kNumOfRGBAParams] {};

// ----------------------------------------
// Vector Param Default Value Array
const AtVector kVecParamDefaultValues[kNumOfVecParams] {};

// ----------------------------------------
// Vector2 Param Default Value Array
const AtVector2 kVec2ParamDefaultValues[kNumOfVec2Params] {};

// ----------------------------------------
// String Param Default Value Array
const char* const kStrParamDefaultValues[kNumOfStrParams] {
    "", // 0 MtlxFileNameParamIndex
    ""  // 1 SearchPathParamIndex
};

// ----------------------------------------
// Pointer Param Default Value Array
void* const kPtrParamDefaultValues[kNumOfPtrParams] {};

// ----------------------------------------
// AtNode Param Default Value Array
AtNode* const kNodeParamDefaultValues[kNumOfNodeParams] {};

// ----------------------------------------
// AtArray Param Default Value Array
AtArray* const kArrayParamDefaultValues[kNumOfArrayParams] {};

// ----------------------------------------
// AtMatrix Param Default Value Array
const AtMatrix kMtxParamDefaultValues[kNumOfMtxParams] {};

// ----------------------------------------
// Enum Param Default Value Array
const int kEnumParamDefaultValues[kNumOfEnumParams] {};

// ----------------------------------------
// AtEnum Param Default Value Array
const AtEnum kEnumTypeParamDefaultValues[kNumOfEnumTypeParams] {};

// AtClosure has not default value

// ----------------------------------------
// Index to Default Value Array Index
const uint16_t kParamDefaultValueIndices[kNumOfStrParams] {
    0,  // 0 MtlxFileNameParamIndex
    1   // 1 SearchPathParamIndex
};

// Closures do not have default values

// ----------------------------------------
// Oreder to Index
const uint16_t ParamNameOrder[kNumOfAllParams] {
    kSearchPathParamIndex,   // 0 MtlxFileNameParamIndex
    kMtlxFileNameParamIndex  // 1 SearchPathParamIndex
};

// ----------------------------------------
// Index to Parameter Description Meta Data
const char* const kParamDescriptionMetaData[kNumOfAllParams] {

    // 0 MtlxFileNameParamIndex
    "The file name of the MaterialX file",

    // 1 SearchPathParamIndex
    "A semicolon-separated sequence of directory paths, which will be applied "
    "in order when searching for the file name given in mtlx_file_name and its "
    "includes."
};

} // namespce MaterialXToArnold

#endif // MTLX_TO_A_CONSTANTS_ARNOLD_PROCEDURAL_H
