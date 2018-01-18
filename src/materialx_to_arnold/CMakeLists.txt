
# Create a shared library target for the procedural (some headers are added just
# to make them show up in an IDE using CMake, i.e. QtCreator).
add_library(
    ${MATERIALX_TO_ARNOLD_LIB_TARGET_NAME} STATIC
    arnold/constants/interface.h
    arnold/constants/procedural.h
    arnold/facade.cpp
    arnold/procedural.h
    arnold/utility.cpp
    arnold/utility.inc
    configuration.h
    constants.h
    exceptions.cpp
    implementation.cpp
    interface.cpp
    macros.h
    materialx/facade.cpp
    operating_system/constants.h
    operating_system/facade.cpp
    translation/demangle.cpp
    translation/dispatcher.h
    translation/document/color_management_system.h
    translation/document/translator.h
    translation/interface.h
    translation/translator.h
)

# Add compile definitions to the procedural target
target_compile_definitions(
    ${MATERIALX_TO_ARNOLD_LIB_TARGET_NAME}
    PRIVATE -DPROCEDURAL_NAME="${PROCEDURAL_TARGET_NAME}"
    PRIVATE -DPROCEDURAL_VERSION="${PROJECT_VERSION}"
)

# Specify include directories to use when compiling the procedural target
target_include_directories(
    ${MATERIALX_TO_ARNOLD_LIB_TARGET_NAME}
    PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}
    PRIVATE ${MATERIALX_INCLUDE_DIRS}
    PRIVATE ${ARNOLD_INCLUDE_DIRS}
    #PRIVATE ../debug
)

target_link_libraries(
    ${MATERIALX_TO_ARNOLD_LIB_TARGET_NAME}
    ${ARNOLD_LIBRARIES}
    ${MATERIALX_CORE_LIBRARIES}
    ${MATERIALX_FORMAT_LIBRARIES}
)

add_subdirectory(unit_tests)
