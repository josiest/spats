#include <iostream>
#include <array>
#include <string_view>

#include "spatula/directions.hpp"

struct Vec2 {
    int x, y;
};

using cardinal = sp::cardinal::direction_name;
constexpr std::array<std::string_view, sp::enum_size_v<cardinal>> cardinal_name{
    "north", "east", "south", "west"
};

using flat_hex = sp::flat_hex::direction_name;
constexpr std::array<std::string_view, sp::enum_size_v<flat_hex>> flat_hex_name{
    "north", "northeast", "southeast", "south", "southwest", "northwest"
};

using pointed_hex = sp::pointed_hex::direction_name;
constexpr std::array<std::string_view, sp::enum_size_v<pointed_hex>> pointed_hex_name{
    "northeast", "east", "southeast", "southwest", "west", "northwest"
};

int main()
{
    std::cout << "cardinal directions:\n";
    for (int i = 0; i < sp::enum_size_v<cardinal>; ++i) {
        const auto dir = sp::direction_as<Vec2>(static_cast<cardinal>(i));
        std::cout << cardinal_name[i] << ": (" << dir.x << ", " << dir.y << ")\n";
    }

    std::cout << "\nflat hex directions:\n";
    for (int i = 0; i < sp::enum_size_v<flat_hex>; ++i) {
        const auto dir = sp::direction_as<Vec2>(static_cast<flat_hex>(i));
        std::cout << flat_hex_name[i] << ": (" << dir.x << ", " << dir.y << ")\n";
    }

    std::cout << "\npointed hex directions:\n";
    for (int i = 0; i < sp::enum_size_v<pointed_hex>; ++i) {
        const auto dir = sp::direction_as<Vec2>(static_cast<pointed_hex>(i));
        std::cout << pointed_hex_name[i] << ": (" << dir.x << ", " << dir.y << ")\n";
    }
    return EXIT_SUCCESS;
}