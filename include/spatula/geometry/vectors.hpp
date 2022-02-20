#pragma once

// data structures
#include <unordered_set>

// type constraints
#include <type_traits>
#include <concepts>

namespace spatula {

/** A spatial type of 2 dimensions.
 * 
 * A vector2 type must satisfy the following requirements
 * - copy constructible, and constructible from two numeric values
 * - has public numeric members x and y with the same type
 *
 * From these requirements, the following operations have been defined
 * - equality, hashing, addition
 */
template<class Vector>
concept vector2 = requires(Vector p) {

    // -- member requirements --
    // Vector has an x member that's numeric
    p.x and std::is_arithmetic_v<std::remove_reference_t<decltype(p.x)>>;
    // Vector has a y member with the same type as x
    p.y and std::is_same_v<decltype(p.x), decltype(p.y)>;

    // -- constructor requirements --
    // Vector is constructable from two numeric values
    Vector(p.x, p.y);
    std::copy_constructible<Vector>;
};

template<vector2 VectorA, vector2 VectorB>
VectorA operator+(VectorA const & a, VectorB const & b)
{
    return VectorA(a.x+b.x, a.y+b.y);
}

bool operator==(vector2 auto const & lhs, vector2 auto const & rhs)
{
    return lhs.x == rhs.x and lhs.y == rhs.y;
}
}

namespace std {
template<spatula::vector2 Vector>
struct hash<Vector> {
    
    size_t operator()(Vector const & p) const
    {
        using Field = std::decay_t<decltype(p.x)>;
        hash<Field> field_hash;
        return field_hash(p.x) ^ (field_hash(p.y) << 1);
    }
};
}

namespace spatula {

/** An unordered set of vector2 objects. */
template<vector2 Vector>
using pointset = std::unordered_set<Vector>;
}