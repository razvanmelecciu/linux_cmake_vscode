cmake_minimum_required(VERSION 3.5)
project(main_app VERSION 1.0.0)
configure_file(config.h.in config.h)

# Set variables
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(BOOST_VER 1.58.0)

set(Boost_USE_STATIC_LIBS OFF) 
set(Boost_USE_MULTITHREADED ON)  
set(Boost_USE_STATIC_RUNTIME OFF) 

# Add path to additional modules
list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/modules")

# Output paths
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

# Options for definitions
add_definitions(-DBOOST_LOG_DYN_LINK)

# Find packages
find_package(Threads REQUIRED)
find_package(Boost ${BOOST_VER} COMPONENTS log)
find_package(TBB REQUIRED)

# Debug messages
message(STATUS "-----------------------------")
message(STATUS "CMAKE_CURRENT_SOURCE_DIR: " ${CMAKE_CURRENT_SOURCE_DIR})
message(STATUS "CMAKE_MODULE_PATH: " ${CMAKE_MODULE_PATH})
message(STATUS "C++ Standard: " ${CMAKE_CXX_STANDARD})
if(Boost_FOUND)
    message(STATUS "Boost Version: " ${BOOST_VER})
endif()
if(TBB_FOUND)
    message(STATUS "TBB Version: " ${TBB_VERSION_MAJOR} ${TBB_VERSION.MINOR})
    message(STATUS "TBB Interface Version: " ${TBB_INTERFACE_VERSION})
endif()
message(STATUS "-----------------------------")

# Compile and assemble into a target
if(Boost_FOUND AND TBB_FOUND)
    include_directories(${Boost_INCLUDE_DIRS})
    add_executable(main_app main_launch.cpp)
    target_link_libraries(main_app Threads::Threads Boost::log tbb)
    target_include_directories(main_app PUBLIC "${PROJECT_BINARY_DIR}")
endif()

