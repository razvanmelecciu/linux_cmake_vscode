
cmake_minimum_required(VERSION 3.5)
project(main_app VERSION 1.0.0)
configure_file(config.h.in config.h)

# Variables
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(BOOST_VER 1.58.0)

set(Boost_USE_STATIC_LIBS OFF) 
set(Boost_USE_MULTITHREADED ON)  
set(Boost_USE_STATIC_RUNTIME OFF) 

# Options for definitions
add_definitions(-DBOOST_LOG_DYN_LINK)

# Find packages
find_package(Threads REQUIRED)
find_package(Boost ${BOOST_VER} COMPONENTS log)

# Compile and assemble into a target
if(Boost_FOUND)
    include_directories(${Boost_INCLUDE_DIRS}) 
    add_executable(main_app main_launch.cpp)
    target_link_libraries(main_app Threads::Threads Boost::log)
    target_include_directories(main_app PUBLIC "${PROJECT_BINARY_DIR}")
endif()

