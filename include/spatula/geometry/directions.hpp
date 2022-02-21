#pragma once

// type constraints
#include <type_traits>

// data structures and data types
#include "spatula/geometry/vectors.hpp"
#include <array>
#include <cstdint>
#include <cstddef>

// math
#include <random>

namespace sp {

/** An enum with sequential values defined from [0, Enum::size). */
template<typename Enum>
concept ranged_enum = std::is_enum_v<Enum> and requires { Enum::size; };

}

namespace sp::cardinal {

/** The cardinal directions. */
enum direction_name { north, east, south, west, size };

/** Get the vector associated with a cardinal direction. */
template<vector2 Vector>
Vector const &
direction_as(direction_name dir)
{
    static std::array<Vector, direction_name::size> directions{
        /* north */ Vector(0, 1), /* east */ Vector(1, 0),
        /* south */ Vector(0, -1), /* west */ Vector(-1, 0)
    };
    return directions[dir];
};

}