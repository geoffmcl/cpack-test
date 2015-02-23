# Testing CPack
# CMakeLists.txt, generated gencmake.pl, on 2015/02/20 20:14:17
# from : http://www.cmake.org/Wiki/CMake/CPackExample
cmake_minimum_required( VERSION 2.8.8 )

# CMakeScripts or use the ones that come by default with CMake.
# set(CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/CMakeModules ${CMAKE_MODULE_PATH})

project( test-cpack )

# The version number.
set( test-cpack_MAJOR 3 )
set( test-cpack_MINOR 0 )
set( test-cpack_POINT 0 )
set( LIBUTIL_VERSION "${test-cpack_MAJOR}.${test-cpack_MINOR}.${test-cpack_POINT}" )

# Allow developer to select is Dynamic or static library built
set( LIB_TYPE STATIC )  # set default static
option( BUILD_SHARED_LIB "Set OFF to build static Library" ON )

if(CMAKE_COMPILER_IS_GNUCXX)
    set( WARNING_FLAGS -Wall )
endif(CMAKE_COMPILER_IS_GNUCXX)

if (CMAKE_CXX_COMPILER_ID STREQUAL "Clang") 
   set( WARNING_FLAGS "-Wall -Wno-overloaded-virtual" )
endif() 

if(WIN32 AND MSVC)
    # turn off various warnings - none needed in this compile
    set(WARNING_FLAGS "${WARNING_FLAGS} /wd4996")
    # foreach(warning 4244 4251 4267 4275 4290 4786 4305)
    #     set(WARNING_FLAGS "${WARNING_FLAGS} /wd${warning}")
    # endforeach(warning)
    set( MSVC_FLAGS "-DNOMINMAX -D_USE_MATH_DEFINES -D_CRT_SECURE_NO_WARNINGS -D_SCL_SECURE_NO_WARNINGS -D__CRT_NONSTDC_NO_WARNINGS" )
    # if (${MSVC_VERSION} EQUAL 1600)
    #    set( MSVC_LD_FLAGS "/FORCE:MULTIPLE" )
    # endif (${MSVC_VERSION} EQUAL 1600)
    #set( NOMINMAX 1 )
    # to distinguish between debug and release libs
    set( CMAKE_DEBUG_POSTFIX "d" )
else()
    # items for unix
endif()

set( CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${WARNING_FLAGS} ${MSVC_FLAGS} -D_REENTRANT" )
set( CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${WARNING_FLAGS} ${MSVC_FLAGS} -D_REENTRANT" )
set( CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} ${MSVC_LD_FLAGS}" )

# configuration file, if needed
# configure_file( ${CMAKE_SOURCE_DIR}/config.h.cmake ${CMAKE_BINARY_DIR}/config.h )
# add_definitions( -DHAVE_CONFIG_H )
# include_directories( ${CMAKE_BINARY_DIR} )

if(BUILD_SHARED_LIB)
   set(LIB_TYPE SHARED)
   message(STATUS "*** Building DLL library ${LIB_TYPE}")
else()
   message(STATUS "*** Option BUILD_SHARED_LIB is OFF ${LIB_TYPE}")
   add_definitions( -DUTILS_LIB_STATIC )
endif()
#################################################
##### LIBRARY #####
#################################################
set(name test-utils)
set(dir src/lib)
include_directories( ${dir} )
set(${name}_SRCS
    ${dir}/sprtf.cxx
    )
set(${name}_HDRS
    ${dir}/sprtf.hxx
    )
add_library( ${name} ${LIB_TYPE} ${${name}_SRCS} ${${name}_HDRS} )
list( APPEND add_LIBS ${name} )
set_target_properties(${name} PROPERTIES COMPILE_FLAGS "-DBUILDING_UTIL_LIB")
set_target_properties(${name} PROPERTIES
    VERSION   ${LIBUTIL_VERSION}
    SOVERSION ${test-cpack_MAJOR}
    )
install(TARGETS ${name}
    RUNTIME DESTINATION bin
    LIBRARY DESTINATION lib
    ARCHIVE DESTINATION lib
    )
install(FILES ${${name}_HDRS} DESTINATION include)

#################################################
##### EXECUTABLE #####
#################################################
# test-app EXECUTABLE from [F:\Projects\test-cpack\src],
# have 1 C/C++ sources, 1 headers
set(name test-app)
set(dir src)
set(${name}_SRCS
    ${dir}/test-app.cxx
    )
set(${name}_HDRS
    ${dir}/test-app.hxx
    )
if (WIN32)
    list( APPEND ${name}_SRCS ${dir}/test-app.rc )
endif ()    
add_executable( ${name} ${${name}_SRCS} ${${name}_HDRS} )
if (add_LIBS)
    target_link_libraries( ${name} ${add_LIBS} )
endif ()
if (MSVC)
    set_target_properties( ${name} PROPERTIES DEBUG_POSTFIX d )
endif ()
# deal with install, if any...
install( TARGETS ${name} DESTINATION bin )
install(FILES ${${name}_HDRS} DESTINATION include)

if (WIN32)
    set(CPACK_GENERATOR "NSIS")
elseif ( ${CMAKE_SYSTEM_NAME} MATCHES "Darwin" )
    set(CPACK_GENERATOR "PackageMake")
else ()
    set(CPACK_GENERATOR "DEB")
    set(CPACK_SOURCE_GENERATOR "TGZ")
endif ()
set(CPACK_DEBIAN_PACKAGE_MAINTAINER "Geoff R. McLane") #required
set(CPACK_PACKAGE_VERSION "${test-cpack_MAJOR}.${test-cpack_MINOR}.${test-cpack_POINT}")
set(CPACK_PACKAGE_VERSION_MAJOR "${test-cpack_MAJOR}")
set(CPACK_PACKAGE_VERSION_MINOR "${test-cpack_MINOR}")
set(CPACK_PACKAGE_VERSION_PATCH "${test-cpack_POINT}")
set(CPACK_RESOURCE_FILE_LICENSE "${CMAKE_SOURCE_DIR}/LICENSE.txt")
set(CPACK_RESOURCE_FILE_README "${CMAKE_SOURCE_DIR}/README.md")
set(CPACK_RESOURCE_FILE_WELCOME "${CMAKE_SOURCE_DIR}/README.md")
set(CPACK_PACKAGE_DESCRIPTION_FILE "${CMAKE_SOURCE_DIR}/README.md")
set(CPACK_SOURCE_IGNORE_FILES "${CMAKE_SOURCE_DIR}/build/;${CMAKE_SOURCE_DIR}/.git/")

include(CPack)

# eof

