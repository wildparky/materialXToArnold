#include "gtest/gtest.h"
#include "gmock/gmock.h"

#include "constants.h"
#include "configuration.h"
#include "exceptions.h"
#include "arnold/utility.h"

#include "mock_arnold_facade.h"

using namespace ::testing;

using MAF = MockArnoldFacade;

using namespace MaterialXToArnold;

// ----------------------------------------------
// NodeLookUpByName
// ----------------------------------------------

class Arnold_Utility_NodeLookUpByName: public Test
{
public:
    MAF mock_af {};
    const MAF::AtStringT arbitrary_name {"dnerbng_hhsdhf"};
};

TEST_F(Arnold_Utility_NodeLookUpByName,
       NoThrowWhenNodePtrIsNotNull)
{
    // ---------------------------------------------------------------
    // Arrange / Given / Setup
    MAF::AtNodeT mock_node {};
    MAF::AtNodeT* mock_node_ptr {&mock_node};

    ON_CALL(mock_af,
            AiNodeLookUpByName(arbitrary_name, nullptr))
            .WillByDefault(Return(mock_node_ptr));

    EXPECT_CALL(mock_af, AiNodeLookUpByName(arbitrary_name, _))
        .Times(AtLeast(1));

    // ---------------------------------------------------------------
    // Act / When / Exercise
    // ---------------------------------------------------------------
    // Assert / Then / Verify
    ASSERT_NO_THROW(NodeLookUpByName<MAF>(mock_af, arbitrary_name));
}

TEST_F(Arnold_Utility_NodeLookUpByName,
       ThrowsWhenNodePtrIsNull)
{
    // ---------------------------------------------------------------
    // Arrange / Given / Setup
    ON_CALL(mock_af,
            AiNodeLookUpByName(arbitrary_name, nullptr))
            .WillByDefault(Return(nullptr));

    EXPECT_CALL(mock_af, AiNodeLookUpByName(arbitrary_name, _))
        .Times(AtLeast(1));

    // ---------------------------------------------------------------
    // Act / When / Exercise
    // ---------------------------------------------------------------
    // Assert / Then / Verify
    ASSERT_THROW(NodeLookUpByName<MAF>(mock_af, arbitrary_name),
                 MaterialXToArnold::RuntimeError);

}

// ----------------------------------------------
// ArnoldBuiltinParam
// ----------------------------------------------

class Arnold_Utility_GetArnoldBuiltinParamName: public Test
{
public:
    MAF mock_af {};
    MAF::AtNodeT mock_node {};
    MAF::AtNodeT* mock_node_ptr {&mock_node};
    MAF::AtNodeEntryT mock_node_entry {};
    MAF::AtNodeEntryT* mock_node_entry_ptr {&mock_node_entry};
    const MAF::AtStringT arbitrary_node_name  {"dfbvg_asdf"};
    const ArnoldBuiltinParamNameIndex arb_idx
        {kOptionsColorManagerParamNameIndex};
};

TEST_F(Arnold_Utility_GetArnoldBuiltinParamName,
       ReturnsCorrectParamName)
{
    // ---------------------------------------------------------------
    // Arrange / Given / Setup
    const MAF::AtStringT actual_node_entry_name
        {kArnoldBuiltinNodeEntryNamesUsed[arb_idx]};

    const char* parameter_name_result {nullptr};

    ON_CALL(mock_af,
            AiNodeGetNodeEntry(mock_node_ptr))
            .WillByDefault(Return(mock_node_entry_ptr));

    EXPECT_CALL(mock_af, AiNodeGetNodeEntry(mock_node_ptr))
        .Times(AtLeast(1));

    ON_CALL(mock_af,
            AiNodeEntryGetNameAtString(mock_node_entry_ptr))
            .WillByDefault(Return(actual_node_entry_name));

    EXPECT_CALL(mock_af, AiNodeEntryGetNameAtString(mock_node_entry_ptr))
        .Times(AtLeast(1));

    // ---------------------------------------------------------------
    // Act / When / Exercise
    GetArnoldBuiltinParamName<MAF>(mock_af, arbitrary_node_name,
                                   arb_idx, mock_node_ptr,
                                   &parameter_name_result);

    // ---------------------------------------------------------------
    // Assert / Then / Verify
    ASSERT_EQ(parameter_name_result,
              kArnoldBuiltinParamNameIndex[arb_idx]);
}

TEST_F(Arnold_Utility_GetArnoldBuiltinParamName,
       NoThrowWhenExpectedEqualsActualNodeEntryName)
{
    // ---------------------------------------------------------------
    // Arrange / Given / Setup
    const MAF::AtStringT actual_node_entry_name
        {kArnoldBuiltinNodeEntryNamesUsed[arb_idx]};

    const char* parameter_name_result {nullptr};

    ON_CALL(mock_af,
            AiNodeGetNodeEntry(mock_node_ptr))
            .WillByDefault(Return(mock_node_entry_ptr));

    EXPECT_CALL(mock_af, AiNodeGetNodeEntry(mock_node_ptr))
        .Times(AtLeast(1));

    ON_CALL(mock_af,
            AiNodeEntryGetNameAtString(mock_node_entry_ptr))
            .WillByDefault(Return(actual_node_entry_name));

    EXPECT_CALL(mock_af, AiNodeEntryGetNameAtString(mock_node_entry_ptr))
        .Times(AtLeast(1));

    // ---------------------------------------------------------------
    // Act / When / Exercise
    // ---------------------------------------------------------------
    // Assert / Then / Verify
    ASSERT_NO_THROW(GetArnoldBuiltinParamName<MAF>(mock_af, arbitrary_node_name,
                                                   arb_idx, mock_node_ptr,
                                                   &parameter_name_result));
}

TEST_F(Arnold_Utility_GetArnoldBuiltinParamName,
       ThrowWhenExpectedNotEqualActualNodeEntryName)
{
    // ---------------------------------------------------------------
    // Arrange / Given / Setup
    const MAF::AtStringT actual_node_entry_name {"sdfbnber_sadfdf"};

    const char* parameter_name_result {nullptr};

    ON_CALL(mock_af,
            AiNodeGetNodeEntry(mock_node_ptr))
            .WillByDefault(Return(mock_node_entry_ptr));

    EXPECT_CALL(mock_af, AiNodeGetNodeEntry(mock_node_ptr))
        .Times(AtLeast(1));

    ON_CALL(mock_af,
            AiNodeEntryGetNameAtString(mock_node_entry_ptr))
            .WillByDefault(Return(actual_node_entry_name));

    EXPECT_CALL(mock_af, AiNodeEntryGetNameAtString(mock_node_entry_ptr))
        .Times(AtLeast(1));

    // ---------------------------------------------------------------
    // Act / When / Exercise
    // ---------------------------------------------------------------
    // Assert / Then / Verify
    ASSERT_THROW(GetArnoldBuiltinParamName<MAF>(mock_af, arbitrary_node_name,
                                                arb_idx, mock_node_ptr,
                                                &parameter_name_result),
                 MaterialXToArnold::RuntimeError);
}

// ----------------------------------------------
// MakeUniqueNodeName
// ----------------------------------------------

class Arnold_Utility_MakeUniqueNodeName: public Test
{
public:
    MAF mock_af {};
    const MAF::AtStringT arbitrary_name {"wnxrbng_lhsdhf"};
    const MAF::AtStringT arbitrary_name1 {"wnxrbng_lhsdhf1"};
};

TEST_F(Arnold_Utility_MakeUniqueNodeName,
       ReturnsUniqueNodeNameWhenNoneExist)
{
    // ---------------------------------------------------------------
    // Arrange / Given / Setup
    ON_CALL(mock_af,
            AiNodeLookUpByName(arbitrary_name, nullptr))
            .WillByDefault(Return(nullptr));

    EXPECT_CALL(mock_af, AiNodeLookUpByName(arbitrary_name, _))
        .Times(AtLeast(1));

    // ---------------------------------------------------------------
    // Act / When / Exercise
    MAF::AtStringT name = MakeUniqueNodeName<MAF>(mock_af, arbitrary_name);

    // ---------------------------------------------------------------
    // Assert / Then / Verify
    ASSERT_EQ(arbitrary_name, name);
}

TEST_F(Arnold_Utility_MakeUniqueNodeName,
       ReturnsUniqueNodeNameWhenOneExist)
{
    // ---------------------------------------------------------------
    // Arrange / Given / Setup
    MAF::AtNodeT mock_node {};
    MAF::AtNodeT* mock_node_ptr {&mock_node};

    ON_CALL(mock_af,
            AiNodeLookUpByName(_, nullptr))
            .WillByDefault(Return(nullptr));

    ON_CALL(mock_af,
            AiNodeLookUpByName(arbitrary_name, nullptr))
            .WillByDefault(Return(mock_node_ptr));

    EXPECT_CALL(mock_af, AiNodeLookUpByName(_, _))
        .Times(AtLeast(2));

    // ---------------------------------------------------------------
    // Act / When / Exercise
    MAF::AtStringT name = MakeUniqueNodeName<MAF>(mock_af, arbitrary_name);

    // ---------------------------------------------------------------
    // Assert / Then / Verify
    ASSERT_EQ(arbitrary_name1, name);
}


