#include <iostream>
#include <thread>
#include <chrono>
#include <filesystem>

#include <vector>
#include <random>
#include <algorithm>
#include <execution>

#include "main_launch.hpp"
#include "config.h"

void printDuration(std::chrono::steady_clock::time_point start,
                   std::chrono::steady_clock::time_point end,
                   const char *message)
{
    auto diff = end - start;
    LOG("%s: %d (ms)") %message %std::chrono::duration<double, std::milli>(diff).count();
}

template<typename T>
void test(const T &policy, const std::vector<double> &data, 
          const int repeat, const char *message) 
{
    for(int i = 0; i < repeat; ++i) 
    {
        std::vector<double> curr_data(data);

        const auto start = std::chrono::steady_clock::now();
        std::sort(policy, curr_data.begin(), curr_data.end());
        const auto end = std::chrono::steady_clock::now();
        printDuration(start, end, message);
    }
}

void doTBBTest()
{
    LOG("Running Parallel STL test");
    // Test samples and repeat factor
    constexpr size_t samples{5'000'000};
    constexpr int repeat{10};

    // Fill a vector with samples numbers
    std::random_device rd;
    std::mt19937_64 mre(rd());
    std::uniform_real_distribution<double> urd(0.0, 1.0);

    std::vector<double> data(samples);
    for (auto &e : data)
    {
        e = urd(mre);
    }

    // Sort data using different execution policies
    LOG("Running with sequential execution policy");
    test(std::execution::seq, data, repeat, "Elapsed time");

    LOG("Parallel with sequential execution policy");
    test(std::execution::par, data, repeat, "Elapsed time");
}

int main(int argc, char** argv)
{
    /*LOG("Main app version %s, Boost version %d.%d.%d") %PROJECT_VER 
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

    doTBBTest();*/

    sf::RenderWindow window(sf::VideoMode(200, 200), "SFML works!");
    sf::CircleShape shape(100.f);
    shape.setFillColor(sf::Color::Green);

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear();
        window.draw(shape);
        window.display();
    }

    return 0;
}