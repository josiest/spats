#pragma once

// type constraints
#include <type_traits>
#include "spatula/geometry/vectors.hpp"

// data types and data structures
#include <cstdint>
#include <cstddef>
#include <array>

/** The cardinal directions. */
namespace sp::cardinal { enum direction_name { north, east, south, west }; }

namespace sp {

/** The amount of values defined by an enum type. */
template<class Enum>
    requires std::is_enum_v<Enum>
struct enum_size;

template<class Enum>
    requires std::is_enum_v<Enum>
using enum_size_v = enum_size<Enum>::value;

template<>
struct enum_size<cardinal::direction_name> { using value = 4; };

/** An enum with sequential values defined from [0, enum_size_v<Enum>). */
template<class Enum>
concept ranged_enum = std::is_enum_v<Enum> and
                      std::convertible_to<enum_size_v<Enum>, std::size_t>;

/** Convert a ranged_enum to a unit-vector. */
template<ranged_enum Enum, class Vector>
struct enum_to_vector {
    Vector operator()(Enum direction) const;
};
template<class Vector, ranged_enum Enum>
Vector direction_as(Enum direction)
{
    return enum_to_vector<Enum, Vector>{}(direction);
}

template<field_2d_constructible Vector>
    requires std::constructible_from<scalar_field_t<Vector>, int>

struct enum_to_vector<cardinal::direction_name, Vector>{
    Vector operator()(cardinal::direction_name dir) const
    {
        std::uint32_t const N = enum_size_v<cardinal::direction_name>;
        static std::array<Vector, N> directions{
            /* north */ Vector(0, 1), /* east */ Vector(1, 0),
            /* south */ Vector(0, -1), /* west */ Vector(-1, 0)
        };
        return directions[dir];
    }
};
}