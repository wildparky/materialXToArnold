
set(PROCEDURAL_TARGET_NAME "materialx")

# Find the MaterialX, the Arnold SDK packages, and the Google Test Framework
find_package(MaterialX 1.35 REQUIRED)
find_package(Arnold 5 REQUIRED)

# TODO: Do we need this?
# Set the position independent code property on all targets
set(CMAKE_POSITION_INDEPENDENT_CODE ON)

# A static MaterialX to Arnold translation library
set(MATERIALX_TO_ARNOLD_LIB_TARGET_NAME "materialx_to_arnold")
set(MATERIALX_TO_ARNOLD_INCLUDE_DIR
    "${CMAKE_CURRENT_SOURCE_DIR}/${MATERIALX_TO_ARNOLD_LIB_TARGET_NAME}")
add_subdirectory(${MATERIALX_TO_ARNOLD_LIB_TARGET_NAME})

# Create a shared library target for the procedural (headers are added to make
# them show up in an IDE using CMake, i.e. QtCreator).
add_library(
    ${PROCEDURAL_TARGET_NAME} SHARED
    procedural.cpp
)
# No prefix for this shared library
set_target_properties(${PROCEDURAL_TARGET_NAME} PROPERTIES PREFIX "")

# Add compile definitions to the procedural target
target_compile_definitions(
    ${PROCEDURAL_TARGET_NAME}
    PRIVATE -DPROCEDURAL_NAME="${PROCEDURAL_TARGET_NAME}"
    PRIVATE -DPROCEDURAL_VERSION="${PROJECT_VERSION}"
)

target_include_directories(
    ${PROCEDURAL_TARGET_NAME}
    PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}
    PRIVATE ${MATERIALX_INCLUDE_DIR}
    PRIVATE ${ARNOLD_INCLUDE_DIRS}
    PRIVATE ${MATERIALX_TO_ARNOLD_INCLUDE_DIR}

)

# Link the procedural target to the libraries.
target_link_libraries(
    ${PROCEDURAL_TARGET_NAME}
    ${ARNOLD_LIBRARIES}
    ${MATERIALX_CORE_LIBRARIES}
    ${MATERIALX_FORMAT_LIBRARIES}
    ${MATERIALX_TO_ARNOLD_LIB_TARGET_NAME}
)

set(PROCEDURAL_INSTALL_PREFIX ${CMAKE_INSTALL_PREFIX}/lib)
install(
    TARGETS ${PROCEDURAL_TARGET_NAME}
    LIBRARY DESTINATION ${PROCEDURAL_INSTALL_PREFIX}
)




#include(DebugPrintCMakeVars)
#include(DebugPrintEnvVars)



















###################################################################################




# TODO: Add option here

add_subdirectory(integration_tests)
