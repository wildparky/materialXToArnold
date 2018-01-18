#include "simple_surface_test.h"

#include <cstdint>
#include <sstream>
#include <memory>

#include "arnold/constants/procedural.h"
// #include "arnold_debug.h"

#include <ai.h>

#ifndef PLUGIN_DIR_PATH
#error "Must provide -DPLUGIN_DIR_PATH value while compiling this file."
#endif

#ifndef PROCEDURAL_NAME
#error "Must provide -DPROCEDURAL_NAME value while compiling this file."
#endif

using namespace MaterialXToArnold;

SimpleSurfaceTest::SimpleSurfaceTest() {};

SimpleSurfaceTest::~SimpleSurfaceTest() {};

void SimpleSurfaceTest::SetUp() {

    AiBegin();

    std::unique_ptr<AtNode*> ptr;

    // Color Manager
    AtNode* color_manager_node = AiNode("color_manager_ocio");
    AiNodeSetStr(color_manager_node, "config", OCIO_CONFIG_FILE_PATH);

    // Options
    // AiMsgSetConsoleFlags(AI_LOG_DEBUG | AI_LOG_INFO | AI_LOG_WARNINGS |
    //                      AI_LOG_ERRORS);

    // AiMsgSetConsoleFlags(AI_LOG_WARNINGS | AI_LOG_ERRORS);
    AiMsgSetConsoleFlags(AI_LOG_ALL);


    AtNode* options = AiUniverseGetOptions();
    AiNodeSetBool(options, "skip_license_check", true);
    AiNodeSetPtr(options, "color_manager", color_manager_node);

    // AiNodeLink(color_manager_node, "color_manager", options);

    AiLoadPlugins(PLUGIN_DIR_PATH);

    //const char* filename = "/home/rheniser/untitled.0001.ass";
    //AiASSLoad(filename, AI_NODE_ALL);

    // MaterialX Procedural
    AtNode* mtlx_proc_node = AiNode(AtString(PROCEDURAL_NAME),
                                    AtString("materialx_test"),
                                    NULL);

    AiNodeSetStr(mtlx_proc_node,
                 kParamNames[kMtlxFileNameParamIndex],
                 MTLX_FILE_NAME);

    AiNodeSetStr(mtlx_proc_node,
                 kParamNames[kSearchPathParamIndex],
                 MTLX_DIR_PATH);





//    std::ostringstream os;
//    arnold::debug::Nodes(os, AI_NODE_ALL);
//    std::cout << os.str() << std::flush;
};

void SimpleSurfaceTest::TearDown() {
    AiEnd();
};

TEST_F(SimpleSurfaceTest, ByDefaultBazTrueIsTrue) {

    AiASSWrite("/dev/null",
               AI_NODE_ALL,
               true,        // open_procs
               false);      // binary

    EXPECT_TRUE(true==true);
    // EXPECT_EQ(true, true);
}

//TEST_F(SimpleSurfaceTest, ByDefaultBazFalseIsFalse) {
//    EXPECT_EQ(false, false);
//}

//TEST_F(SimpleSurfaceTest, SometimesBazFalseIsTrue) {
//    EXPECT_EQ(false, true);
//}
