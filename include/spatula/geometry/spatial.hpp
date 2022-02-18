#pragma once

// data structures
#include <unordered_set>

// type constraints
#include <type_traits>
#include <concepts>

namespace spatula {

/** A spatial type of 2 dimensions.
 * 
 * A spatial2 type must satisfy the following requirements
 * - copy constructible, and constructible from two numeric values
 * - has public numeric members x and y with the same type
 *
 * From these requirements, the following operations have been defined
 * - equality, hashing, addition
 */
template<class Point>
concept spatial2 = requires(Point p) {

    // -- member requirements --
    // Point has an x member that's numeric
    p.x and std::is_arithmetic_v<std::remove_reference_t<decltype(p.x)>>;
    // Point has a y member with the same type as x
    p.y and std::is_same_v<decltype(p.x), decltype(p.y)>;

    // -- constructor requirements --
    // Point is constructable from two numeric values
    Point(p.x, p.y);
    std::copy_constructible<Point>;
};

template<spatial2 PointA, spatial2 PointB>
PointA operator+(PointA const & a, PointB const & b)
{
    return PointA(a.x+b.x, a.y+b.y);
}

bool operator==(spatial2 auto const & lhs, spatial2 auto const & rhs)
{
    return lhs.x == rhs.x and lhs.y == rhs.y;
}
}

namespace std {
template<spatula::spatial2 Point>
struct hash<Point> {
    
    size_t operator()(Point const & p) const
    {
        return p.x ^ (p.y << 1);
    }
};
}

namespace spatula {

/** An unordered set of spatial2 objects. */
template<spatial2 Point>
using pointset = std::unordered_set<Point>;
}