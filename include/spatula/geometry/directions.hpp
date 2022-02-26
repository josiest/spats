#pragma once

// type constraints
#include <type_traits>
#include "spatula/geometry/vectors.hpp"

// data types and data structures
#include <cstdint>
#include <cstddef>
#include <array>

/** The cardinal directions. */
namespace sp::cardinal { enum direction_name { north, east, south, west, size }; }

namespace sp {

/** An enum with sequential values defined from [0, Enum::size). */
template<class Enum>
concept ranged_enum = std::is_enum_v<Enum> and requires { Enum::size; };

/** Convert a ranged_enum to a unit-vector. */
template<numeric Vector, ranged_enum Enum>
struct direction_as {
    Vector operator()(Enum direction) const;
};

template<numeric2d Vector>
struct direction_as<Vector, cardinal::direction_name>{
    Vector operator()(cardinal::direction_name dir) const
    {
        static std::array<Vector, cardinal::direction_name::size> directions{
            /* north */ Vector(0, 1), /* east */ Vector(1, 0),
            /* south */ Vector(0, -1), /* west */ Vector(-1, 0)
        };
        return directions[dir];

    }
};
}