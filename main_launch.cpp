#include <iostream>
#include <thread>
#include <chrono>
#include <filesystem>

#include "main_launch.hpp"
#include "config.h"

int main(int argc, char** argv)
{
    LOG("Main app version %s, Boost version %d.%d.%d") %PROJECT_VER 
                                                       %BOOST_VER_MAJOR 
                                                       %BOOST_VER_MINOR 
                                                       %BOOST_VER_PATCH;
    auto crtPath = std::filesystem::current_path();
    LOG("Current directory: %s") %crtPath;
    LOG("No. passed parameters: %d") %argc;
    for (auto i = 0; i < argc; ++i)
    {
        LOG("Param %d >> %s") %i %argv[i];
    }

    return 0;
}