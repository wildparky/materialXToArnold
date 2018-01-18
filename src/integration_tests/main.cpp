#include "gtest/gtest.h"

#include <string>
#include <iostream>
#include <stdlib.h>

// github.com/google/googletest/blob/master/googletest/docs/AdvancedGuide.md
//
// Just as you can do set-up and tear-down at the test level and the test case
// level, you can also do it at the test program level. Here's how.
//
// First, you subclass the ::testing::Environment class to define a test
// environment, which knows how to set-up and tear-down:



const char* const kOpenColorIOEnvVarName {"OCIO"};

class MyEnvironment : public ::testing::Environment
{
public:
    MyEnvironment() {}

    virtual ~MyEnvironment() {}

    // Override this to define how to set up the environment.
    virtual void SetUp()
    {
        // std::cout << "Setup" << std::endl;
        setenv(kOpenColorIOEnvVarName, OCIO_CONFIG_FILE_PATH, 1);
    }

    // Override this to define how to tear down the environment.
    virtual void TearDown()
    {
        // std::cout << "TearDown" << std::endl;
    }

};

int main(int argc, char **argv)
{
    MyEnvironment* env = new MyEnvironment();
    ::testing::AddGlobalTestEnvironment(env);
    ::testing::InitGoogleTest(&argc, argv);
    int ret = RUN_ALL_TESTS();
    return ret;
}
