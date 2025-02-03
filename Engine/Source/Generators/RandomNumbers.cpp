#include "RandomNumbers.h"
#include <random>
#include <chrono>

int TextureGenEngine::Random::RandInt(int min, int max)
{
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> dis(min, max);
    return dis(gen);
}
std::string TextureGenEngine::Random::UUID()
{
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> dis(0, 15);
    std::uniform_int_distribution<int> dis2(8, 11);

    auto now = std::chrono::system_clock::now();
    auto now_ms = std::chrono::time_point_cast<std::chrono::milliseconds>(now);
    auto epoch = now_ms.time_since_epoch();
    auto value = std::chrono::duration_cast<std::chrono::milliseconds>(epoch);
    long duration = value.count();

    std::stringstream ss;
    ss << std::hex << duration << "-";
    for (int i = 0; i < 4; i++)
    {
        ss << dis(gen);
    }
    ss << "-4"; // UUID version 4
    for (int i = 0; i < 3; i++)
    {
        ss << dis(gen);
    }
    ss << "-";
    ss << dis2(gen); // UUID variant
    for (int i = 0; i < 3; i++)
    {
        ss << dis(gen);
    }
    ss << "-";
    for (int i = 0; i < 12; i++)
    {
        ss << dis(gen);
    }

    return ss.str();
}