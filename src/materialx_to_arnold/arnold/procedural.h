#ifndef MTLX_TO_A_ARNOLD_PROCEDURAL_H
#define MTLX_TO_A_ARNOLD_PROCEDURAL_H

#include <cstdint>
#include <cstring>
#include <sstream>

#include <ai.h>

#include "constants.h"
#include "arnold/constants/procedural.h"
#include "exceptions.h"
#include "configuration.h"

namespace MaterialXToArnold
{

template<typename AFT>     // Arnold Facade
void InstallParameter(const AFT& af,
                      typename AFT::AtListT* params,
                      uint8_t idx)
{
    uint8_t ptype = kParamType[idx];
    const char* pn = kParamNames[idx];
    switch(ptype)
    {
        case AI_TYPE_BYTE:
        {
            af.AiNodeParamByte(params, -1, pn, kByteParamDefaultValues[idx]);
            break;
        }
        case AI_TYPE_INT:
        {
            af.AiNodeParamInt(params, -1, pn, kIntParamDefaultValues[idx]);
            break;
        }
        case AI_TYPE_UINT:
        {
            af.AiNodeParamUInt(params, -1, pn, kUIntParamDefaultValues[idx]);
            break;
        }
        case AI_TYPE_BOOLEAN:
        {
            af.AiNodeParamBool(params, -1, pn, kBoolParamDefaultValues[idx]);
            break;
        }
        case AI_TYPE_FLOAT:
        {
            af.AiNodeParamFlt(params, -1, pn, kFltParamDefaultValues[idx]);
            break;
        }
        case AI_TYPE_RGB:
        {
            af.AiNodeParamRGB(params, -1, pn,
                              kRGBParamDefaultValues[idx].r,
                              kRGBParamDefaultValues[idx].g,
                              kRGBParamDefaultValues[idx].b);
            break;
        }
        case AI_TYPE_RGBA:
        {
            af.AiNodeParamRGBA(params, -1, pn,
                               kRGBAParamDefaultValues[idx].r,
                               kRGBAParamDefaultValues[idx].g,
                               kRGBAParamDefaultValues[idx].b,
                               kRGBAParamDefaultValues[idx].a);
            break;
        }
        case AI_TYPE_VECTOR:
        {
            af.AiNodeParamVec(params, -1, pn,
                              kVecParamDefaultValues[idx].x,
                              kVecParamDefaultValues[idx].y,
                              kVecParamDefaultValues[idx].z);
            break;
        }
        case AI_TYPE_VECTOR2:
        {
            af.AiNodeParamVec2(params, -1, pn,
                               kVecParamDefaultValues[idx].x,
                               kVecParamDefaultValues[idx].y);
            break;
        }
        case AI_TYPE_STRING:
        {
            af.AiNodeParamStr(params, -1, pn, kStrParamDefaultValues[idx]);
            break;
        }
        case AI_TYPE_POINTER:
        {
            af.AiNodeParamPtr(params, -1, pn, kPtrParamDefaultValues[idx]);
            break;
        }
        case AI_TYPE_NODE:
        {
            af.AiNodeParamNode(params, -1, pn, kNodeParamDefaultValues[idx]);
            break;
        }
        case AI_TYPE_ARRAY:
        {
            af.AiNodeParamArray(params, -1, pn,
                                kArrayParamDefaultValues[idx]);
            break;
        }
        case AI_TYPE_MATRIX:
        {
            af.AiNodeParamMtx(params, -1, pn, kMtxParamDefaultValues[idx]);
            break;
        }
        case AI_TYPE_ENUM:
        {
            af.AiNodeParamEnum(params, -1, pn,
                               kEnumParamDefaultValues[idx],
                               kEnumTypeParamDefaultValues[idx]);
            break;
        }
        case AI_TYPE_CLOSURE:
        {
            // Closures do not have default values
            af.AiNodeParamClosure(params, -1, pn);
            break;
        }
        default:
            break;
    }

}
template<typename AFT>     // Arnold Facade
void AddMetaData(const AFT& af,
                 typename AFT::AtNodeEntryT* nentry,
                 uint8_t idx)
{
    af.AiMetaDataSetStr(nentry,
                        kParamNames[idx],
                        kDescriptionMetaDataName,
                        kParamDescriptionMetaData[idx]);
}

template<typename AFT>     // Arnold Facade
void InstallAllProceduralNodeParametersAndMetaData(
        const AFT& af,
        typename AFT::AtListT* params,
        typename AFT::AtNodeEntryT* nentry)
{
    // The MaterialX To Arnold Procedural Node's Parameter Names and Meta Data
    for(uint16_t idx = 0; idx < kNumOfAllParams; idx++)
    {
        InstallParameter(af, params, idx);
        AddMetaData(af, nentry, idx);
    }
}

template<typename AFT>     // Arnold Facade
Configuration ReadAllProceduralNodeParameters(
        const AFT& af,
        const typename AFT::AtNodeT* procedural_node)
{
    Configuration cfg {};
    cfg.procedural_node_name_ =  af.AiNodeGetName(procedural_node);
    const char* param_name = nullptr;
    uint16_t idx = 0;

    // Use static assert to catch unused parameters at compile time.

    // AI_TYPE_BYTE
    static_assert(kNumOfByteParams == 0, "Missing one or more AI_TYPE_BYTE"
                                         "parameter reads.");
    // AI_TYPE_INT
    static_assert(kNumOfIntParams == 0, "Missing one or more AI_TYPE_INT"
                                        "parameter reads.");
    // AI_TYPE_UINT
    static_assert(kNumOfUIntParams == 0, "Missing one or more AI_TYPE_UINT"
                                         "parameter reads.");
    // AI_TYPE_BOOLEAN
    static_assert(kNumOfBoolParams == 0, "Missing one or more AI_TYPE_BOOLEAN"
                                         "parameter reads.");
    // AI_TYPE_FLOAT
    static_assert(kNumOfFltParams == 0, "Missing one or more AI_TYPE_FLOAT"
                                        "parameter reads.");
    // AI_TYPE_RGB
    static_assert(kNumOfRGBParams == 0, "Missing one or more AI_TYPE_RGB"
                                        "parameter reads.");
    // AI_TYPE_RGBA
    static_assert(kNumOfRGBAParams == 0, "Missing one or more AI_TYPE_RGBA"
                                        "parameter reads.");
    // AI_TYPE_VECTOR
    static_assert(kNumOfVecParams == 0, "Missing one or more AI_TYPE_VECTOR"
                                           "parameter reads.");
    // AI_TYPE_VECTOR2
    static_assert(kNumOfVec2Params == 0, "Missing one or more AI_TYPE_VECTOR2"
                                         "parameter reads.");
    // AI_TYPE_STRING
    static_assert(kNumOfStrParams == 2, "Wrong number of expected "
                                         "AI_TYPE_STRING parameter reads.");
    using AtString = typename AFT::AtStringT;
    AtString str =
            af.AiNodeGetStr(procedural_node,
                           AtString(kParamNames[kMtlxFileNameParamIndex]));
    cfg.materialx_file_name_ = str.c_str();

    if(cfg.materialx_file_name_.empty())
    {
        std::stringstream ss;
        ss << "The parameter " << param_name <<
              " is an invalid empty string value.";
        throw ValueError(__FILE__, __LINE__, ss.str());
    }

    str = af.AiNodeGetStr(procedural_node,
                          AtString(kParamNames[kSearchPathParamIndex]));
    cfg.materialx_search_path_ = str.c_str();

    // AI_TYPE_POINTER
    static_assert(kNumOfPtrParams == 0, "Missing one or more AI_TYPE_POINTER"
                                        "parameter reads.");
    // AI_TYPE_NODE
    static_assert(kNumOfPtrParams == 0, "Missing one or more AI_TYPE_POINTER"
                                        "parameter reads.");
    // AI_TYPE_ARRAY
    static_assert(kNumOfArrayParams == 0, "Missing one or more AI_TYPE_ARRAY"
                                          "parameter reads.");
    // AI_TYPE_MATRIX
    static_assert(kNumOfMtxParams == 0, "Missing one or more AI_TYPE_MATRIX"
                                        "parameter reads.");
    // AI_TYPE_ENUM
    static_assert(kNumOfEnumParams == 0, "Missing one or more AI_TYPE_ENUM"
                                         "parameter reads.");
    // AI_TYPE_CLOSURE
    static_assert(kNumOfClosureParams == 0, "Missing one or more "
                                         "AI_TYPE_CLOSURE parameter reads.");

    return cfg;
}


} // namespce MaterialXToArnold

#endif // MTLX_TO_A_ARNOLD_PROCEDURAL_H
