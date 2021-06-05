# This file is indended to be included in end-user CMakeLists.txt
# include(/path/to/Filelists.cmake)
# It assumes the variable TRPL_DIR is defined pointing to the
# root path of tripple sources.
#
# This file is NOT designed (on purpose) to be used as cmake
# subdir via add_subdirectory()
# The intention is to provide greater flexibility to users to
# create their own targets using the *_SRCS variables.

set(TRPL_VERSION_MAJOR    "0")
set(TRPL_VERSION_MINOR    "1")
set(TRPL_VERSION_REVISION "0")
# TRPL_VERSION_RC is set to TRPL_RC_RELEASE for official releases
# TRPL_VERSION_RC is set to TRPL_RC_DEVELOPMENT for Git versions
# Numbers 1..31 are reserved for release candidates
set(TRPL_VERSION_RC       "TRPL_RC_RELEASE")

if ("${TRPL_VERSION_RC}" STREQUAL "TRPL_RC_RELEASE")
	set(TRPL_VERSION_STRING
		"${TRPL_VERSION_MAJOR}.${TRPL_VERSION_MINOR}.${TRPL_VERSION_REVISION}"
    )
elseif ("${TRPL_VERSION_RC}" STREQUAL "TRPL_RC_DEVELOPMENT")
	set(TRPL_VERSION_STRING
		"${TRPL_VERSION_MAJOR}.${TRPL_VERSION_MINOR}.${TRPL_VERSION_REVISION}.dev"
    )
else ("${TRPL_VERSION_RC}" STREQUAL "TRPL_RC_RELEASE")
	set(TRPL_VERSION_STRING
		"${TRPL_VERSION_MAJOR}.${TRPL_VERSION_MINOR}.${TRPL_VERSION_REVISION}.rc${TRPL_VERSION_RC}"
    )
endif ("${TRPL_VERSION_RC}" STREQUAL "TRPL_RC_RELEASE")

# The minimum set of files needed for tripple.
set(trplcore_SRCS
	${TRPL_DIR}/src/core/msg_handler.c
)

set(trpluapi_SRCS
	${TRPL_DIR}/src/uapi/uapi_rpl.c
)

# APIFILES: The files which implement the sequential and socket APIs.
set(trplpapi_SRCS
	${TRPL_DIR}/src/papi/papi_icmp6.c
)

# All TRPL files without apps
set(trplall_SRCS
    ${trplcore_SRCS}
    ${trpluapi_SRCS}
    ${trplpapi_SRCS}
)

# Generate include/init.h (version info)
configure_file(${TRPL_DIR}/src/include/init.h.cmake.in ${TRPL_DIR}/src/include/init.h)

# Documentation
#set(DOXYGEN_DIR ${TRPL_DIR}/doc/doxygen)
#set(DOXYGEN_OUTPUT_DIR output)
#set(DOXYGEN_IN  ${TRPL_DIR}/doc/doxygen/trpl.Doxyfile.cmake.in)
#set(DOXYGEN_OUT ${TRPL_DIR}/doc/doxygen/trpl.Doxyfile)
#configure_file(${DOXYGEN_IN} ${DOXYGEN_OUT})

#find_package(Doxygen_TODO)
#if (DOXYGEN_FOUND)
#    message("Doxygen build started")

#    add_custom_target(trpldocs
#        COMMAND ${CMAKE_COMMAND} -E remove_directory ${DOXYGEN_DIR}/${DOXYGEN_OUTPUT_DIR}/html
#        COMMAND ${DOXYGEN_EXECUTABLE} ${DOXYGEN_OUT}
#        WORKING_DIRECTORY ${DOXYGEN_DIR}
#        COMMENT "Generating API documentation with Doxygen"
#        VERBATIM)
#else (DOXYGEN_FOUND)
#    message("Doxygen needs to be installed to generate the doxygen documentation")
#endif (DOXYGEN_FOUND)

# Tripple library
add_library(rplcore ${trplall_SRCS})
include_directories(include src/include)
target_compile_options(rplcore PRIVATE ${TRPL_COMPILER_FLAGS})
target_compile_definitions(rplcore PRIVATE ${TRPL_DEFINITIONS})
target_include_directories(rplcore PRIVATE ${TRPL_INCLUDE_DIRS})
