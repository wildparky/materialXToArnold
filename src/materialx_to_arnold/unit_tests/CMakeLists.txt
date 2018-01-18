# Enable testing for current directory and below. Note that ctest expects to
# find a test file in the build directory root. Therefore, this command should
# be in the source directory root. This adds another build target, which is
# test for Makefile generators, or RUN_TESTS for integrated development
# environments (like Visual Studio). From that point on, we can use the
# ADD_TEST command to add tests to the project.
enable_testing()

configure_file(README COPYONLY)

find_package(Threads REQUIRED) # Required by GTest/GMock
find_package(GMock 1.8 REQUIRED)

# add_subdirectory(materialx_document_translation_test)
add_subdirectory(arnold)
