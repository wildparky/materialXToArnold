
# The following function is to test whether or not a variable was set on the
# command line. Recall from the CMake Command Line:
#
# -D <var>:<type>=<value>: Create a cmake cache entry.
#
# When cmake is first run in an empty build tree, it creates a CMakeCache.txt
# file and populates it with customizable settings for the project. This option
# may be used to specify a setting that takes priority over the project's
# default value. The option may be repeated for as many cache entries as
# desired.
#
# When a cmake cache entry is set on the command line, cmake sets its help
# (a.k.a. doc) string. As of this writing, that string is:
#
# "No help, variable specified on the command line."
#
# For a number of cmake cache entries, one may like to set a default 
# (different from the one set by CMake) when that cmake cache entry was not
# set on the command line. This function allows you to do that by testing the
# the help/doc string. It is wrapped in a function just in case it ever
# changes and because we may use it a number of times.
function(VARIABLE_SET_ON_COMMAND_LINE var_name result_name)
    get_property(help_str CACHE "${var_name}" PROPERTY HELPSTRING)
    string(COMPARE EQUAL "${help_str}"
        "No help, variable specified on the command line." result)
    set ("${result_name}" ${result} PARENT_SCOPE)
endfunction()

# Force sets a cache variable when it has not been given on the command line.
function(FORCE_SET_CACHE_VARIABLE_WHEN_NOT_ON_COMMAND_LINE var_name val typ str)
    VARIABLE_SET_ON_COMMAND_LINE("${var_name}" on_cmd_ln)
    if(NOT on_cmd_ln)
        set("${var_name}" "${val}" CACHE "${typ}" "${str}" FORCE)
    endif()
endfunction()
