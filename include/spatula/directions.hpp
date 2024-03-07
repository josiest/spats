#pragma once

// type constraints
#include <type_traits>
#include "spatula/vectors.hpp"

// data types and data structures
#include <cstdint>
#include <cstddef>
#include <array>

/** The cardinal directions. */
namespace sp::cardinal { enum direction_name { north, east, south, west }; }
namespace sp::flat_hex{
enum direction_name { north, northeast, southeast, south, southwest, northwest };
}
namespace sp::pointed_hex{
enum direction_name{ northeast, east, southeast, southwest, west, northwest };
}

namespace sp {

/** The amount of values defined by an enum type. */
template<class Enum>
    requires std::is_enum_v<Enum>
struct enum_size {
    static constexpr std::size_t value = 0;
};

template<class Enum>
    requires std::is_enum_v<Enum>
static constexpr std::size_t enum_size_v = enum_size<Enum>::value;

template<>
struct enum_size<cardinal::direction_name> {
    static constexpr std::size_t value = 4;
};

/** An enum with sequential values defined from [0, enum_size_v<Enum>). */
template<class Enum>
concept ranged_enum = std::is_enum_v<Enum> and requires { enum_size_v<Enum>; };

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
        std::uint32_t constexpr N = enum_size_v<cardinal::direction_name>;
        static std::array<Vector, N> directions{
            /* north */ Vector(0, 1), /* east */ Vector(1, 0),
            /* south */ Vector(0, -1), /* west */ Vector(-1, 0)
        };
        return directions[dir];
    }
};
}
