#include <iostream>
#include <random>

#include "spatula/directions.hpp"

using cardinal = sp::cardinal::direction_name;
using flat_hex = sp::flat_hex::direction_name;
using pointed_hex = sp::pointed_hex::direction_name;

using direction_distribution = std::uniform_int_distribution<std::uint32_t>;

struct Vec2 {
    int x, y;
};

int main()
{
    std::random_device seed{};
    std::mt19937 rng{seed()};

    direction_distribution cardinal_step(0, sp::enum_size_v<cardinal>);
    direction_distribution flat_step(0, sp::enum_size_v<flat_hex>);
    direction_distribution pointed_step(0, sp::enum_size_v<pointed_hex>);

    constexpr std::size_t N = 5;

    std::cout << "random cardinal steps:\n";
    for (int i = 0; i < N; ++i) {
        const auto dir = static_cast<cardinal>(cardinal_step(rng));
        const auto step = sp::direction_as<Vec2>(dir);
        std::cout << "(" << step.x << ", " << step.y << ")\n";
    }

    std::cout << "\nrandom flat hex steps:\n";
    for (int i = 0; i < N; ++i) {
        const auto dir = static_cast<flat_hex>(flat_step(rng));
        const auto step = sp::direction_as<Vec2>(dir);
        std::cout << "(" << step.x << ", " << step.y << ")\n";
    }

    std::cout << "\nrandom pointed hex steps:\n";
    for (int i = 0; i < N; ++i) {
        const auto dir = static_cast<pointed_hex>(pointed_step(rng));
        const auto step = sp::direction_as<Vec2>(dir);
        std::cout << "(" << step.x << ", " << step.y << ")\n";
    }
    return EXIT_SUCCESS;
}