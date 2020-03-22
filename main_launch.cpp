#include <iostream>
#include <thread>
#include <chrono>

#include "main_launch.hpp"
#include "config.h"

int main(int argc, char** argv)
{
    LOG("Main app version %s, Boost version %d.%d.%d") %PROJECT_VER 
                                                       %BOOST_VER_MAJOR 
                                                       %BOOST_VER_MINOR 
                                                       %BOOST_VER_PATCH;
    return 0;
}