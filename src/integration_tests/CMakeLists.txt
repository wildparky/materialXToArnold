# Enable testing for current directory and below. Note that ctest expects to
# find a test file in the build directory root. Therefore, this command should
# be in the source directory root. This adds another build target, which is
# test for Makefile generators, or RUN_TESTS for integrated development
# environments (like Visual Studio). From that point on, we can use the
# ADD_TEST command to add tests to the project.
enable_testing()

#include(DebugPrintCMakeVars)
#include(DebugPrintEnvVars)

find_package(Threads REQUIRED) # Required by GTest/GMock
find_package(GTest 1.8 REQUIRED) # For integration tests

add_executable(simple_surface_test
    simple_surface_test.h
    simple_surface_test.cpp
    main.cpp
)

set(ocio_config_file_path  ${CMAKE_CURRENT_SOURCE_DIR}/aces_1.0.3/config.ocio)
set(mtlx_file_name simple_surface.mtlx)

configure_file(${mtlx_file_name} COPYONLY)

target_compile_definitions(
    simple_surface_test
    PRIVATE -DPROCEDURAL_NAME="${PROCEDURAL_TARGET_NAME}"
    PRIVATE -DPLUGIN_DIR_PATH="${PROCEDURAL_INSTALL_PREFIX}"
    PRIVATE -DOCIO_CONFIG_FILE_PATH="${ocio_config_file_path}"
    PRIVATE -DMTLX_DIR_PATH="${CMAKE_CURRENT_SOURCE_DIR}"
    PRIVATE -DMTLX_FILE_NAME="${mtlx_file_name}"
)

unset(mtlx_file_name)
unset(ocio_config_file_path)

target_include_directories(
    simple_surface_test
    PRIVATE ${GTEST_INCLUDE_DIRS}
    PRIVATE ${ARNOLD_INCLUDE_DIRS}
    PRIVATE ${MATERIALX_TO_ARNOLD_INCLUDE_DIR}
)

target_link_libraries(
    simple_surface_test
    ${ARNOLD_LIBRARIES}
    ${MATERIALX_CORE_LIBRARIES}
    ${MATERIALX_FORMAT_LIBRARIES}
    GTest::GTest # if found; adds Thread::Thread automatically
)

add_test(NAME simple_surface_test
         COMMAND simple_surface_test)
