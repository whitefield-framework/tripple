cmake_minimum_required(VERSION 3.7)

project(tripple)

set(TRPL_DIR ${CMAKE_CURRENT_SOURCE_DIR})
include(src/Filelists.cmake)

# Package generation
set(CPACK_SOURCE_GENERATOR "ZIP")
set(CPACK_SOURCE_PACKAGE_DESCRIPTION_SUMMARY "Tripple: An RPL implementation")
set(CPACK_PACKAGE_VERSION_MAJOR "${TRPL_VERSION_MAJOR}")
set(CPACK_PACKAGE_VERSION_MINOR "${TRPL_VERSION_MINOR}")
set(CPACK_PACKAGE_VERSION_PATCH "${TRPL_VERSION_REVISION}")
set(CPACK_SOURCE_IGNORE_FILES "/build/;${CPACK_SOURCE_IGNORE_FILES};.git")
set(CPACK_SOURCE_PACKAGE_FILE_NAME "trpl-${TRPL_VERSION_MAJOR}.${TRPL_VERSION_MINOR}.${TRPL_VERSION_REVISION}")
include(CPack)

# Target for package generation
add_custom_target(dist COMMAND ${CMAKE_MAKE_PROGRAM} package_source)
# add_dependencies(dist lwipdocs)
