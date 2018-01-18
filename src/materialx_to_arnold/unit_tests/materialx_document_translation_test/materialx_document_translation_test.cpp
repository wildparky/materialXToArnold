#include <cstdint>
#include <tuple>
#include <utility>
#include <memory>
#include <string>

#include "gtest/gtest.h"
#include "gmock/gmock.h"

#include "constants.h"
#include "configuration.h"
#include "exceptions.h"

#include "mock_arnold_facade.h"
#include "mock_materialx_facade.h"

using namespace ::testing;

using MAF = MockArnoldFacade;
using MMF = MockMaterialXFacade;

using namespace MaterialXToArnold;

class MaterialXDocumentTranslationTest: public ::testing::Test
{
public:
    MaterialXDocumentTranslationTest() :
        mock_af {},
        mock_mxf {},
        mock_node {},
        mock_node_ptr {&mock_node},
        mock_doc {new ::Document()} {}


    MAF mock_af;
    MMF mock_mxf{};
    const typename MAF::AtNodeT mock_node;
    const typename MAF::AtNodeT* mock_node_ptr;
    typename MMF::DocumentPtrT mock_doc{};
};

//TEST_F(MaterialXDocumentTranslationTest,
//       CheckVersions_DocMajGreaterThanLibMaj_Throws)
//{
//    // Arrange / Given / Setup
//    std::pair<int, int> doc_version {2, 0};
//    std::tuple<int, int, int> lib_version {1, 35, 0};

//    ON_CALL((*mock_doc), getVersionIntegers())
//            .WillByDefault(Return(doc_version));
//    EXPECT_CALL((*mock_doc), getVersionIntegers())
//        .Times(AtLeast(1));

//    ON_CALL(mock_mxf, getVersionIntegers())
//            .WillByDefault(Return(lib_version));
//    EXPECT_CALL(mock_mxf, getVersionIntegers())
//        .Times(AtLeast(1));

//     // Act / When / Exercise
//     ASSERT_THROW(CheckVersions(mock_af, mock_mxf, mock_doc),
//                  IncompatibleVersionsError);

//    // Assert / Then / Verify (Implicit for GMock)
//}

//TEST_F(MaterialXDocumentTranslationTest,
//       CheckVersions_DocMajLessThanLibMaj_NoThrows)
//{
//    // Arrange / Given / Setup
//    std::pair<int, int> doc_version {0, 90};
//    std::tuple<int, int, int> lib_version {1, 35, 0};

//    ON_CALL((*mock_doc), getVersionIntegers())
//            .WillByDefault(Return(doc_version));
//    EXPECT_CALL((*mock_doc), getVersionIntegers())
//        .Times(AtLeast(1));

//    ON_CALL(mock_mxf, getVersionIntegers())
//            .WillByDefault(Return(lib_version));
//    EXPECT_CALL(mock_mxf, getVersionIntegers())
//        .Times(AtLeast(1));

//     // Act / When / Exercise
//     ASSERT_NO_THROW(CheckVersions(mock_af, mock_mxf, mock_doc));

//    // Assert / Then / Verify (Implicit for GMock)
//}

//TEST_F(MaterialXDocumentTranslationTest,
//       CheckVersions_DocMajEqualToLibMajAndDocMinGreaterThanLibMin_Throws)
//{
//    // Arrange / Given / Setup
//    std::pair<int, int> doc_version {1, 90};
//    std::tuple<int, int, int> lib_version {1, 35, 0};

//    ON_CALL((*mock_doc), getVersionIntegers())
//            .WillByDefault(Return(doc_version));
//    EXPECT_CALL((*mock_doc), getVersionIntegers())
//        .Times(AtLeast(1));

//    ON_CALL(mock_mxf, getVersionIntegers())
//            .WillByDefault(Return(lib_version));
//    EXPECT_CALL(mock_mxf, getVersionIntegers())
//        .Times(AtLeast(1));

//     // Act / When / Exercise
//     ASSERT_THROW(CheckVersions(mock_af, mock_mxf, mock_doc),
//                  IncompatibleVersionsError);

//    // Assert / Then / Verify (Implicit for GMock)
//}

//TEST_F(MaterialXDocumentTranslationTest,
//       CheckVersions_DocMajEqualToLibMajAndDocMinLessThanLibMin_NoThrows)
//{
//    // Arrange / Given / Setup
//    std::pair<int, int> doc_version {1, 20};
//    std::tuple<int, int, int> lib_version {1, 35, 0};

//    ON_CALL((*mock_doc), getVersionIntegers())
//            .WillByDefault(Return(doc_version));
//    EXPECT_CALL((*mock_doc), getVersionIntegers())
//        .Times(AtLeast(1));

//    ON_CALL(mock_mxf, getVersionIntegers())
//            .WillByDefault(Return(lib_version));
//    EXPECT_CALL(mock_mxf, getVersionIntegers())
//        .Times(AtLeast(1));

//     // Act / When / Exercise
//     ASSERT_NO_THROW(CheckVersions(mock_af, mock_mxf, mock_doc));

//    // Assert / Then / Verify (Implicit for GMock)
//}

//TEST_F(MaterialXDocumentTranslationTest,
//       CheckVersions_DocMajEqualToLibMajAndDocMinEqualToLibMin_NoThrows)
//{
//    // Arrange / Given / Setup
//    std::pair<int, int> doc_version {1, 35};
//    std::tuple<int, int, int> lib_version {1, 35, 0};

//    ON_CALL((*mock_doc), getVersionIntegers())
//            .WillByDefault(Return(doc_version));
//    EXPECT_CALL((*mock_doc), getVersionIntegers())
//        .Times(AtLeast(1));

//    ON_CALL(mock_mxf, getVersionIntegers())
//            .WillByDefault(Return(lib_version));
//    EXPECT_CALL(mock_mxf, getVersionIntegers())
//        .Times(AtLeast(1));

//     // Act / When / Exercise
//     ASSERT_NO_THROW(CheckVersions(mock_af, mock_mxf, mock_doc));

//    // Assert / Then / Verify (Implicit for GMock)
//}

//TEST_F(MaterialXDocumentTranslationTest,
//      ColorManagementSystem_)
//{
//    // Arrange / Given / Setup
//    std::pair<int, int> doc_version {1, 35};
//    std::tuple<int, int, int> lib_version {1, 35, 0};

//    ON_CALL((*mock_doc), getVersionIntegers())
//            .WillByDefault(Return(doc_version));
//    EXPECT_CALL((*mock_doc), getVersionIntegers())
//        .Times(AtLeast(1));

//    ON_CALL(mock_mxf, getVersionIntegers())
//            .WillByDefault(Return(lib_version));
//    EXPECT_CALL(mock_mxf, getVersionIntegers())
//        .Times(AtLeast(1));

//     // Act / When / Exercise
//     ASSERT_NO_THROW(CheckVersions(mock_af, mock_mxf, mock_doc));

//    // Assert / Then / Verify (Implicit for GMock)
//}



























