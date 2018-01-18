#include "gtest/gtest.h"
#include "gmock/gmock.h"

#include "constants.h"
#include "configuration.h"
#include "exceptions.h"
#include "arnold/procedural.h"

#include "mock_arnold_facade.h"

using namespace ::testing;

using MAF = MockArnoldFacade;

using namespace MaterialXToArnold;

class ArnoldProceduralParametersTest: public Test
{
public:
    ArnoldProceduralParametersTest() :
        mock_af{},
        mock_node{},
        mock_node_ptr{&mock_node} {}


    MAF mock_af;
    const typename MAF::AtNodeT mock_node;
    const typename MAF::AtNodeT* mock_node_ptr;
};

TEST_F(ArnoldProceduralParametersTest,
     ReadAllProceduralNodeParameters_VerifyAllParametersWereRead)
{
    // ---------------------------------------------------------------
    // Arrange / Given / Setup

    uint8_t arbitrary_byte  {7};                            // AI_TYPE_BYTE
    int arbitary_int {4};                                   // AI_TYPE_INT
    unsigned int arbitary_uint {45};                        // AI_TYPE_UINT
    bool arbitrary_bool {false};                            // AI_TYPE_BOOLEAN
    float arbitrary_flt {10.234f};                          // AI_TYPE_FLOAT
    MAF::AtRGBT arbitrary_rgb { };                          // AI_TYPE_RGB
    MAF::AtRGBAT arbitrary_rgba { };                        // AI_TYPE_RGBA
    MAF::AtVectorT arbitrary_vec { };                       // AI_TYPE_VECTOR
    MAF::AtVector2T arbitrary_vec2 { };                     // AI_TYPE_VECTOR2
    const char* arbitrary_non_empty_str {"nsdf_ngljkrbb"};  // AI_TYPE_STRING
    void* arbitrary_ptr {nullptr};                          // AI_TYPE_POINTER
    MAF::AtArrayT arbitrary_array { };                      // AI_TYPE_ARRAY
    MAF::AtMatrixT arbitrary_matrix { };                    // AI_TYPE_MATRIX

    for(uint8_t ptype = 0; ptype <= AI_TYPE_CLOSURE; ptype++)
    {
        switch(ptype)
        {
            case AI_TYPE_BYTE:
            {
                for(uint16_t idx = 0; idx < kNumOfAllParams; idx++)
                {
                    if(kParamType[idx] == AI_TYPE_BYTE)
                    {
                        ON_CALL(mock_af,
                                AiNodeGetByte(mock_node_ptr, kParamNames[idx]))
                                .WillByDefault(Return(arbitrary_byte));
                    }
                }
                EXPECT_CALL(mock_af, AiNodeGetByte(mock_node_ptr, _))
                    .Times(Exactly(kNumOfParams[ptype]));
                break;
            }
            case AI_TYPE_ENUM:
            {
                break;
            }
            case AI_TYPE_INT:
            {
                for(uint16_t idx = 0; idx < kNumOfAllParams; idx++)
                {
                    if(kParamType[idx] == AI_TYPE_INT ||
                       kParamType[idx] == AI_TYPE_ENUM)
                    {
                        ON_CALL(mock_af,
                                AiNodeGetInt(mock_node_ptr, kParamNames[idx]))
                                .WillByDefault(Return(arbitary_int));
                    }
                }
                EXPECT_CALL(mock_af, AiNodeGetInt(mock_node_ptr, _))
                    .Times(Exactly(kNumOfParams[AI_TYPE_INT] +
                                   kNumOfParams[AI_TYPE_ENUM]));
                break;
            }
            case AI_TYPE_UINT:
            {
                for(uint16_t idx = 0; idx < kNumOfAllParams; idx++)
                {
                    if(kParamType[idx] == AI_TYPE_UINT)
                    {
                        ON_CALL(mock_af,
                                AiNodeGetUInt(mock_node_ptr, kParamNames[idx]))
                                .WillByDefault(Return(arbitary_uint));
                    }
                }
                EXPECT_CALL(mock_af, AiNodeGetUInt(mock_node_ptr, _))
                    .Times(Exactly(kNumOfParams[ptype]));
                break;
            }
            case AI_TYPE_BOOLEAN:
            {
                for(uint16_t idx = 0; idx < kNumOfAllParams; idx++)
                {
                    if(kParamType[idx] == AI_TYPE_BOOLEAN)
                    {
                        ON_CALL(mock_af,
                                AiNodeGetBool(mock_node_ptr, kParamNames[idx]))
                                .WillByDefault(Return(arbitrary_bool));
                    }
                }
                EXPECT_CALL(mock_af, AiNodeGetBool(mock_node_ptr, _))
                    .Times(Exactly(kNumOfParams[ptype]));
                break;
            }
            case AI_TYPE_FLOAT:
            {
                for(uint16_t idx = 0; idx < kNumOfAllParams; idx++)
                {
                    if(kParamType[idx] == AI_TYPE_FLOAT)
                    {
                        ON_CALL(mock_af,
                                AiNodeGetFlt(mock_node_ptr, kParamNames[idx]))
                                .WillByDefault(Return(arbitrary_flt));
                    }
                }
                EXPECT_CALL(mock_af, AiNodeGetFlt(mock_node_ptr, _))
                    .Times(Exactly(kNumOfParams[ptype]));
                break;
            }
            case AI_TYPE_RGB:
            {
                for(uint16_t idx = 0; idx < kNumOfAllParams; idx++)
                {
                    if(kParamType[idx] == AI_TYPE_RGB)
                    {
                        ON_CALL(mock_af,
                                AiNodeGetRGB(mock_node_ptr, kParamNames[idx]))
                                .WillByDefault(Return(arbitrary_rgb));
                    }
                }
                EXPECT_CALL(mock_af, AiNodeGetRGB(mock_node_ptr, _))
                    .Times(Exactly(kNumOfParams[ptype]));
                break;
            }
            case AI_TYPE_RGBA:
            {
                for(uint16_t idx = 0; idx < kNumOfAllParams; idx++)
                {
                    if(kParamType[idx] == AI_TYPE_RGBA)
                    {
                        ON_CALL(mock_af,
                                AiNodeGetRGBA(mock_node_ptr, kParamNames[idx]))
                                .WillByDefault(Return(arbitrary_rgba));
                    }
                }
                EXPECT_CALL(mock_af, AiNodeGetRGBA(mock_node_ptr, _))
                    .Times(Exactly(kNumOfParams[ptype]));
                break;
            }
            case AI_TYPE_VECTOR:
            {
                for(uint16_t idx = 0; idx < kNumOfAllParams; idx++)
                {
                    if(kParamType[idx] == AI_TYPE_VECTOR)
                    {
                        ON_CALL(mock_af,
                                AiNodeGetVec(mock_node_ptr, kParamNames[idx]))
                                .WillByDefault(Return(arbitrary_vec));
                    }
                }
                EXPECT_CALL(mock_af, AiNodeGetVec(mock_node_ptr, _))
                    .Times(Exactly(kNumOfParams[ptype]));
                break;
            }
            case AI_TYPE_VECTOR2:
            {
                for(uint16_t idx = 0; idx < kNumOfAllParams; idx++)
                {
                    if(kParamType[idx] == AI_TYPE_VECTOR)
                    {
                        ON_CALL(mock_af,
                                AiNodeGetVec2(mock_node_ptr, kParamNames[idx]))
                                .WillByDefault(Return(arbitrary_vec2));
                    }
                }
                EXPECT_CALL(mock_af, AiNodeGetVec2(mock_node_ptr, _))
                    .Times(Exactly(kNumOfParams[ptype]));
                break;
            }
            case AI_TYPE_STRING:
            {
                for(uint16_t idx = 0; idx < kNumOfAllParams; idx++)
                {
                    if(kParamType[idx] == AI_TYPE_STRING)
                    {
                        ON_CALL(mock_af,
                                AiNodeGetStr(mock_node_ptr, kParamNames[idx]))
                                .WillByDefault(Return(arbitrary_non_empty_str));
                    }
                }
                EXPECT_CALL(mock_af, AiNodeGetStr(mock_node_ptr, _))
                    .Times(Exactly(kNumOfParams[ptype]));
                break;
            }
            case AI_TYPE_POINTER:
            {
                // Do AI_TYPE_NODE and AI_TYPE_POINTER
                for(uint16_t idx = 0; idx < kNumOfAllParams; idx++)
                {
                    if(kParamType[idx] == AI_TYPE_POINTER ||
                       kParamType[idx] == AI_TYPE_NODE)
                    {
                        ON_CALL(mock_af,
                                AiNodeGetPtr(mock_node_ptr, kParamNames[idx]))
                                .WillByDefault(Return(arbitrary_ptr));
                    }
                }
                EXPECT_CALL(mock_af, AiNodeGetPtr(mock_node_ptr, _))
                    .Times(Exactly(kNumOfParams[AI_TYPE_POINTER] +
                                   kNumOfParams[AI_TYPE_NODE]));
                break;
            }
            case AI_TYPE_ARRAY:
            {
                for(uint16_t idx = 0; idx < kNumOfAllParams; idx++)
                {
                    if(kParamType[idx] == AI_TYPE_ARRAY)
                    {
                        ON_CALL(mock_af,
                                AiNodeGetArray(mock_node_ptr, kParamNames[idx]))
                                .WillByDefault(Return(arbitrary_array));
                    }
                }
                EXPECT_CALL(mock_af, AiNodeGetArray(mock_node_ptr, _))
                    .Times(Exactly(kNumOfParams[ptype]));
                break;
            }
            case AI_TYPE_MATRIX:
            {
                for(uint16_t idx = 0; idx < kNumOfAllParams; idx++)
                {
                    if(kParamType[idx] == AI_TYPE_MATRIX)
                    {
                        ON_CALL(mock_af,
                                AiNodeGetMatrix(mock_node_ptr,
                                                kParamNames[idx]))
                                .WillByDefault(Return(arbitrary_matrix));
                    }
                }
                EXPECT_CALL(mock_af, AiNodeGetMatrix(mock_node_ptr, _))
                    .Times(Exactly(kNumOfParams[ptype]));
                break;
            }
            default:
                break;
        }
    }

    // ---------------------------------------------------------------
    // Act / When / Exercise
    ASSERT_NO_THROW(ReadAllProceduralNodeParameters(mock_af, mock_node_ptr));


    // ---------------------------------------------------------------
    // Assert / Then / Verify (Implicit for GMock)
}

TEST_F(ArnoldProceduralParametersTest,
       ReadAllProceduralNodeParameters_ThrowsWhenMtlxFileNameIsEmptyStr)
{
    // ---------------------------------------------------------------
    // Arrange / Given / Setup
    const char* empty {""};

    ON_CALL(mock_af,
            AiNodeGetStr(mock_node_ptr, kParamNames[kMtlxFileNameParamIndex]))
            .WillByDefault(Return(empty));

    EXPECT_CALL(mock_af, AiNodeGetStr(mock_node_ptr, _))
        .Times(AtLeast(1));

    // ---------------------------------------------------------------
    // Act / When / Exercise
    ASSERT_THROW(ReadAllProceduralNodeParameters(mock_af, mock_node_ptr),
                 MaterialXToArnold::ValueError);

    // ---------------------------------------------------------------
    // Assert / Then / Verify (Implicit for GMock)
}



