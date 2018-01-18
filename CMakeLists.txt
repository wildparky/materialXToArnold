cmake_minimum_required(VERSION 3.1 FATAL_ERROR)

cmake_policy(SET CMP0048 NEW) # Use VERSION with project conmand (CMake 3.0+)
project(rspMaterialXArnold VERSION 0.0.1 LANGUAGES CXX)

# Append this project's cmake modules dir to module path to get its modules
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/Modules/")

include(ForceSetCacheVariableWhenNotOnCommandLine)
FORCE_SET_CACHE_VARIABLE_WHEN_NOT_ON_COMMAND_LINE(
    CMAKE_BUILD_TYPE "Debug" STRING "Choose the type of build, options are:
    None(CMAKE_CXX_FLAGS or CMAKE_C_FLAGS used) Debug Release RelWithDebInfo
    MinSizeRel."
)
FORCE_SET_CACHE_VARIABLE_WHEN_NOT_ON_COMMAND_LINE(
    CMAKE_VERBOSE_MAKEFILE TRUE BOOL "If this value is on, makefiles will be
    generated without the .SILENT directive, and all commands will be echoed
    to the console during the make.  This is useful for debugging only. With
    Visual Studio IDE projects all commands are done without /nologo."
)

set(CMAKE_CXX_STANDARD 11)

add_subdirectory(src)

