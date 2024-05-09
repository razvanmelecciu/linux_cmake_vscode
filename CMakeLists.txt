cmake_minimum_required(VERSION 3.11)
project(main_app VERSION 1.0.0)
configure_file(config.h.in config.h)

set(SECTION_SEPARATOR "----------------------------------------------------------")
message(STATUS ${SECTION_SEPARATOR})
message(STATUS "!!!!! Processing CmakeLists.txt path: "${CMAKE_CURRENT_SOURCE_DIR})
message(STATUS ${SECTION_SEPARATOR})

# add_subdirectory(test)
include_directories(src)

# Dinamically download content using CMake's FetchContent - In this case fmt
# include(FetchContent)

# FetchContent_Declare(fmt
#  GIT_REPOSITORY https://github.com/fmtlib/fmt.git
#  GIT_TAG master
#)
# FetchContent_MakeAvailable(fmt)

# Set variables
#set(GCC_CUSTOM_COMPILE_FLAGS "-fprofile-arcs -ftest-coverage -fcoroutines")
#set(GCC_CUSTOM_LINK_FLAGS    "-lgcov")
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

set(Boost_USE_STATIC_LIBS OFF) 
set(Boost_USE_MULTITHREADED ON)  
set(Boost_USE_STATIC_RUNTIME OFF)
set(PRINT_ALL_CMAKE_VARS False)

# Add path to additional modules
list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/modules")

# Output paths
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

# Options for definitions
add_definitions(-DBOOST_LOG_DYN_LINK)

# Find packages
find_package(Threads)
find_package(Boost COMPONENTS log)
find_package(TBB)
find_package(OpenMP)
find_package(fmt CONFIG REQUIRED)
find_package(SFML COMPONENTS graphics audio REQUIRED)

# Debug messages
if(PRINT_ALL_CMAKE_VARS)
message(STATUS ${SECTION_SEPARATOR})
message(STATUS "Printing variables")
    get_cmake_property(_variableNames VARIABLES)
    list (SORT _variableNames)
    foreach (_variableName ${_variableNames})
        message(STATUS "${_variableName}=${${_variableName}}")
    endforeach()
endif()

# Debug messages
message(STATUS ${SECTION_SEPARATOR})
message(STATUS "Used C++ Compiler: "${CMAKE_CXX_COMPILER})
message(STATUS "CMAKE_CURRENT_SOURCE_DIR: " ${CMAKE_CURRENT_SOURCE_DIR})
message(STATUS "CMAKE_MODULE_PATH: " ${CMAKE_MODULE_PATH})
message(STATUS "C++ Standard: " ${CMAKE_CXX_STANDARD})
if(Boost_FOUND)
    message(STATUS "Boost Version: " ${Boost_VERSION})
endif()
if(TBB_FOUND)
    message(STATUS "TBB Version: " ${TBB_VERSION_MAJOR} ${TBB_VERSION.MINOR})
    message(STATUS "TBB Interface Version: " ${TBB_INTERFACE_VERSION})
endif()
if(OpenMP_FOUND)
    message(STATUS "OpenMP Spec Date: " ${OpenMP_CXX_SPEC_DATE})
    message(STATUS "OpenMP C++ Flags: " ${OpenMP_CXX_FLAGS})
endif()
if(fmt_FOUND)
    message(STATUS "Fmt Version: " ${fmt_VERSION})
endif()
if(SFML_FOUND)
    message(STATUS "SFML Version: " ${SFML_VERSION})
endif()
message(STATUS ${SECTION_SEPARATOR})

# Custom compiler flags for different compiler vendors
if (CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
    message(STATUS "Appending custom compiler flags for Clang")
    set(CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} -frelaxed-template-template-args")
    if (CMAKE_BUILD_TYPE STREQUAL "Debug")
        message(STATUS "Adding flags for Debug")
        set(CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} -O0 -g")
    endif()
elseif(CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
    message(STATUS "Appending custom compiler flags for GNU")
    if (CMAKE_BUILD_TYPE STREQUAL "Debug")
        message(STATUS "Adding flags for Debug")
        set(CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} -O0 -g")
    endif()
endif()

# Append custom compile flags
if (CUSTOM_COMPILER_FLAGS)
    message(STATUS "Custom compiler (e.g. g++) Flags: " ${CUSTOM_COMPILER_FLAGS})
    set(CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} ${CUSTOM_COMPILER_FLAGS}")    
endif()
message(STATUS "Compiler Flags: " ${CMAKE_CXX_FLAGS})
if (CUSTOM_LINKER_FLAGS)
    message(STATUS "Custom  linker (e.g. ld) Flags: " ${CUSTOM_LINKER_FLAGS})
    set(CMAKE_EXE_LINKER_FLAGS  "${CMAKE_EXE_LINKER_FLAGS} ${CUSTOM_LINKER_FLAGS}")
endif()
message(STATUS "Linker Flags: " ${CMAKE_EXE_LINKER_FLAGS})

# Compile and assemble into a target
add_executable(main_app main_launch.cpp)
target_link_libraries(main_app Threads::Threads)
if(Boost_FOUND)
    message(STATUS "Adding support for Boost libraries...")
    include_directories(${Boost_INCLUDE_DIRS})
    target_link_libraries(main_app Boost::log)
endif()
if(TBB_FOUND)
    message(STATUS "Adding support for TBB libraries...")
    target_link_libraries(main_app tbb)
endif()
if(OpenMP_FOUND)
    message(STATUS "Adding support for OpenMP libraries...")
    target_link_libraries(main_app OpenMP::OpenMP_CXX)
endif()
if(fmt_FOUND)
    message(STATUS "Adding support for Fmt libraries...")
    target_link_libraries(main_app fmt::fmt)
endif()
if(SFML_FOUND)
    message(STATUS "Adding support for SFML libraries...")
    target_link_libraries(main_app sfml-graphics sfml-audio)
endif()

target_include_directories(main_app PUBLIC "${PROJECT_BINARY_DIR}")

# Log output paths
message(STATUS ${SECTION_SEPARATOR})
message(STATUS "Binaries Output path - Archive: " ${CMAKE_ARCHIVE_OUTPUT_DIRECTORY})
message(STATUS "Binaries Output path - Library: " ${CMAKE_LIBRARY_OUTPUT_DIRECTORY})
message(STATUS "Binaries Output path - Runtime: " ${CMAKE_RUNTIME_OUTPUT_DIRECTORY})
message(STATUS ${SECTION_SEPARATOR})

message(STATUS ${SECTION_SEPARATOR})
message(STATUS "!!!!! Finished CmakeLists.txt path: "${CMAKE_CURRENT_SOURCE_DIR})
message(STATUS ${SECTION_SEPARATOR})