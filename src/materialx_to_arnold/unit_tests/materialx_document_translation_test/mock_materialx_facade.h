#ifndef MOCK_MATERIALX_FACADE_H
#define MOCK_MATERIALX_FACADE_H

#include <tuple>
#include <utility>
#include <memory>

#include "gtest/gtest.h"
#include "gmock/gmock.h"

class Document
{
public:
    MOCK_CONST_METHOD0(getVersionIntegers, std::pair<int, int>());
};

class MockMaterialXFacade
{
public:
    using DocumentPtrT = std::shared_ptr<::Document>;
    MOCK_CONST_METHOD0(getVersionIntegers, std::tuple<int, int, int>());
};



#endif // MOCK_MATERIALX_FACADE_H
