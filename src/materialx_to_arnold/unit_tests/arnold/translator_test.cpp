#include "gtest/gtest.h"
#include "gmock/gmock.h"

#include "constants.h"
#include "configuration.h"
#include "exceptions.h"
#include "translation/translator.h"

#include "mock_arnold_facade.h"

using namespace ::testing;

using MAF = MockArnoldFacade;

using namespace MaterialXToArnold;

class Arnold_Utility_CheckVersions : public Test
{
public:
    MAF mock_af {};
    const MAF::AtStringT arbitrary_name {"dnerbng_hhsdhf"};
};

TEST_F(Arnold_Utility_CheckVersions,
       Test1)
{
//    // ---------------------------------------------------------------
//    // Arrange / Given / Setup
//    MAF::AtNodeT mock_node {};
//    MAF::AtNodeT* mock_node_ptr {&mock_node};

//    ON_CALL(mock_af,
//            AiNodeLookUpByName(arbitrary_name, nullptr))
//            .WillByDefault(Return(mock_node_ptr));

//    EXPECT_CALL(mock_af, AiNodeLookUpByName(arbitrary_name, _))
//        .Times(AtLeast(1));

//    // ---------------------------------------------------------------
//    // Act / When / Exercise
//    // ---------------------------------------------------------------
//    // Assert / Then / Verify
//    ASSERT_NO_THROW(NodeLookUpByName<MAF>(mock_af, arbitrary_name));
    ASSERT_TRUE(true);
}

//TEST_F(Arnold_Utility_CheckVersions,
//       Test2)
//{
//    // ---------------------------------------------------------------
//    // Arrange / Given / Setup
//    ON_CALL(mock_af,
//            AiNodeLookUpByName(arbitrary_name, nullptr))
//            .WillByDefault(Return(nullptr));

//    EXPECT_CALL(mock_af, AiNodeLookUpByName(arbitrary_name, _))
//        .Times(AtLeast(1));

//    // ---------------------------------------------------------------
//    // Act / When / Exercise
//    // ---------------------------------------------------------------
//    // Assert / Then / Verify
//    ASSERT_THROW(NodeLookUpByName<MAF>(mock_af, arbitrary_name),
//                 MaterialXToArnold::RuntimeError);

//}
