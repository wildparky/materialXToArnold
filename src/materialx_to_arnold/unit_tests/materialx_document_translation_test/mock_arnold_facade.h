#ifndef MOCK_ARNOLD_FACADE_H
#define MOCK_ARNOLD_FACADE_H

#include "gtest/gtest.h"
#include "gmock/gmock.h"

class MockArnoldFacade
{
public:
    class AtNode {};
    using AtNodeT = AtNode;
    using AtStringT = std::string;

    MOCK_CONST_METHOD8(AiMsgDebug, void(const char* file,
                                        const int line,
                                        const char* func,
                                        const char* format,
                                        const int doc_major,
                                        const int doc_minor,
                                        const int lib_major,
                                        const int lib_minor));

    MOCK_CONST_METHOD4(AiMsgDebug, void(const char* file,
                                        const int line,
                                        const char* func,
                                        const char* format));

};

#endif // MOCK_ARNOLD_FACADE_H
