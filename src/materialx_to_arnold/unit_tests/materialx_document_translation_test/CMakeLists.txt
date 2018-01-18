set(TARGET_NAME materialx_document_translation_test)

#include(DebugPrintCMakeVars)
#include(DebugPrintEnvVars)

include_directories(
    PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}
    PRIVATE ${MATERIALX_INCLUDE_DIRS}
    PRIVATE ${ARNOLD_INCLUDE_DIRS}
    PRIVATE ${MATERIALX_TO_ARNOLD_INCLUDE_DIR}
    PRIVATE ${GMock_INCLUDE_DIR}
)

add_executable(
    ${TARGET_NAME}
    mock_arnold_facade.h
    mock_materialx_facade.h
    materialx_document_translation_test.cpp
    main.cpp
)

# Add compile definitions to the procedural target
target_compile_definitions(
    ${TARGET_NAME}
    PRIVATE -DPROCEDURAL_NAME="${PROCEDURAL_TARGET_NAME}"
    PRIVATE -DPROCEDURAL_VERSION="${PROJECT_VERSION}"
)

target_link_libraries(
    ${TARGET_NAME}
    ${MATERIALX_TO_ARNOLD_LIB_TARGET_NAME}
    Threads::Threads
    ${GMock_LIBRARIES}
)

add_test(NAME ${TARGET_NAME}
         COMMAND ${TARGET_NAME})

unset(TARGET_NAME)
