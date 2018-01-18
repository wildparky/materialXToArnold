#ifndef MOCK_ARNOLD_FACADE_H
#define MOCK_ARNOLD_FACADE_H

#include "gtest/gtest.h"
#include "gmock/gmock.h"

class MockArnoldFacade
{
public:
    struct AtNode {};
    using AtNodeT = AtNode;
    struct AtNodeEntry {};
    using AtNodeEntryT = AtNodeEntry;
    using AtStringT = std::string;

    struct AtRGB
    {
       float r, g, b;
    };
    using AtRGBT = AtRGB;

    struct AtRGBA
    {
       float r, g, b, a;
    };
    using AtRGBAT = AtRGBA;

    struct AtVector
    {
       float x, y, z;
    };
    using AtVectorT = AtVector;

    struct AtVector2
    {
       float x, y;
    };
    using AtVector2T = AtVector2;

    class AtArray {};
    using AtArrayT = AtArray;

    struct AtMatrix {

       float data[4][4];
    };
    using AtMatrixT = AtMatrix;

    // -----------------------------------------------------------
    // AtNode API ai_nodes.h
    // -----------------------------------------------------------

    // AtNode Methods

    MOCK_CONST_METHOD2(AiNodeLookUpByName, AtNodeT*(const AtStringT name,
                                                    const AtNodeT* parent));

    MOCK_CONST_METHOD1(AiNodeGetName, const char*(const AtNodeT* node));

    MOCK_CONST_METHOD1(AiNodeGetNodeEntry,
                       const AtNodeEntryT*(const AtNodeT* node));

    // Parameter Readers

    MOCK_CONST_METHOD2(AiNodeGetByte, uint8_t(const AtNodeT* node,
                                              const AtStringT param));

    MOCK_CONST_METHOD2(AiNodeGetInt, int(const AtNodeT* node,
                                         const AtStringT param));

    MOCK_CONST_METHOD2(AiNodeGetUInt, unsigned int(const AtNodeT* node,
                                                   const AtStringT param));

    MOCK_CONST_METHOD2(AiNodeGetBool, bool(const AtNodeT* node,
                                           const AtStringT param));

    MOCK_CONST_METHOD2(AiNodeGetFlt, float(const AtNodeT* node,
                                           const AtStringT param));

    MOCK_CONST_METHOD2(AiNodeGetRGB, AtRGBT(const AtNodeT* node,
                                            const AtStringT param));

    MOCK_CONST_METHOD2(AiNodeGetRGBA, AtRGBAT(const AtNodeT* node,
                                              const AtStringT param));

    MOCK_CONST_METHOD2(AiNodeGetVec, AtVectorT(const AtNodeT* node,
                                               const AtStringT param));

    MOCK_CONST_METHOD2(AiNodeGetVec2, AtVector2T(const AtNodeT* node,
                                                 const AtStringT param));

    MOCK_CONST_METHOD2(AiNodeGetStr, AtStringT(const AtNodeT* node,
                                               const AtStringT param));

    MOCK_CONST_METHOD2(AiNodeGetPtr, void*(const AtNodeT* node,
                                           const AtStringT param));

    MOCK_CONST_METHOD2(AiNodeGetArray, AtArrayT(const AtNodeT* node,
                                                const AtStringT param));

    MOCK_CONST_METHOD2(AiNodeGetMatrix, AtMatrixT(const AtNodeT* node,
                                                  const AtStringT param));

    // -----------------------------------------------------------
    // AtNodeEntry API (ai_node_entry.h)
    // -----------------------------------------------------------

    // AtNodeEntry Methods
    MOCK_CONST_METHOD1(AiNodeEntryGetNameAtString,
                       AtStringT(const AtNodeEntryT* nentry));
};

#endif // MOCK_ARNOLD_FACADE_H
