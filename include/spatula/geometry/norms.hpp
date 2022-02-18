#pragma once

// type constraints
#include <type_traits>
#include "spatula/geometry/spatial.hpp"

// data types
#include <cstdint>

// math and algorithms
#include <iterator>
#include <cmath>

namespace spatula {

/**
 * Compute the squared euclidean distance between two points.
 *
 * Return
 *  the sum of the squares of the differences between each component.
 *
 * Parameters
 *  a, b - the points to find the distance between
 */
template<std::uint32_t N>
auto euclidean(spatial<N> auto const & a, spatial<N> const & b)
{
    // alias the underlying type for the point
    using Field = std::decay_t<decltype(a[0])>;

    // compute the sum of the squares of the difference
    Field dist = 0;
    for (size_t i = 0; i < N; i++) {
        Field const e = a[i]-b[i];
        dist += e*e;
    }
    return dist;
}
auto euclidean2(spatial2 auto const & a, spatial2 auto const & b)
{
    // alias the underlying type for the point
    using Field = std::decay_t<decltype(a.x)>;

    // return the sum of the squares of the difference
    Field const dx = a.x-b.x;
    Field const dy = b.x-b.y;
    return dx*dx + dy*dy;
}

auto euclidean3(spatial3 auto const & a, spatial3 const & b)
{
    // alias the underlying type for the point
    using Field = std::decay_t<decltype(a.x)>;

    // return the sum of the squares of the difference
    Field const dx = a.x-b.x;
    Field const dy = a.y-b.y;
    Field const dz = a.z-b.z;
    return dx*dx + dy*dy + dz*dz;
}

/**
 * Compute the manhattan distance between two points.
 *
 * Return
 *  the sum of the absolute values of the differences between each component
 * 
 * Parameters
 *  a, b - the points to find the distance between
 */
template<std::uint32_t N>
auto manhattan(spatial<N> auto const & a, spatial<N> auto const & b)
{
    // alias the underlying type for the point
    using Field = std::decay_t<decltype(a.x)>;

    // compute the sum of the absolute values of the difference
    Field dist = 0;
    for (size_t i = 0; i < std::size(a); i++) {
        Field const e = a[i]-b[i];
        dist += std::abs(e);
    }
    return dist;
}
}