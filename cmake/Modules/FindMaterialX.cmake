# MaterialX finder module
# This module searches for a valid MaterialX instalation.
#
# Variables that will be defined:
# MATERIALX_FOUND             Defined if a Arnold installation has been detected
# MATERIALX_CORE_LIBRARY      Path to MaterialX Core library
# MATERIALX_FORMAT_LIBRARY    Path to MaterialX Format library
# MATERIALX_LIBRARIES         Path to MaterialX library
# MATERIALX_INCLUDE_DIR       Path to the include directory (for backward compatibility)
# MATERIALX_INCLUDE_DIRS      Path to the include directory
# MATERIALX_VERSION           Version of arnold

find_path(MATERIALX_INCLUDE_DIR MaterialXCore/Util.h
    PATHS $ENV{MATERIALX_ROOT}/include ${MATERIALX_ROOT}/include
    DOC "MaterialX include path")

find_library(MATERIALX_CORE_LIBRARY
    NAMES MaterialXCore
    PATHS $ENV{MATERIALX_ROOT}/lib ${MATERIALX_ROOT}/lib
    DOC "MaterialX Core library")

find_library(MATERIALX_FORMAT_LIBRARY
    NAMES MaterialXFormat
    PATHS $ENV{MATERIALX_ROOT}/lib ${MATERIALX_ROOT}/lib
    DOC "MaterialX Format library")

set(MATERIALX_INCLUDE_DIRS ${MATERIALX_INCLUDE_DIR})
set(MATERIALX_CORE_LIBRARIES ${MATERIALX_CORE_LIBRARY})
set(MATERIALX_FORMAT_LIBRARIES ${MATERIALX_FORMAT_LIBRARY})

include(FindPackageHandleStandardArgs)
find_package_handle_standard_args(MaterialX DEFAULT_MSG
    MATERIALX_CORE_LIBRARY MATERIALX_INCLUDE_DIR MATERIALX_FORMAT_LIBRARY)
