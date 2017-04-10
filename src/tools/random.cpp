#include <ctime>
#include <random>
#include <chrono>

#include "random.hpp"

namespace tools
{

float random(float from, float to)
{
    static std::mt19937 gen(std::chrono::system_clock::now().time_since_epoch().count());
    std::uniform_real_distribution<> dist(from, to);
    return dist(gen);
}

}
