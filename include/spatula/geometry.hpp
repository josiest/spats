#ifndef SPATULA_GEOMETRY_HPP
#define SPATULA_GEOMETRY_HPP

#include <type_traits>
#include <stdexcept>
#include <iterator>
#include <cmath>

namespace spatula {

/**
 * Compute the squared distance between two points under the L2 norm
 *
 * @param a one of the two points to find the distance between
 * @param b the other of the two points to find the distance between
 *
 * @throws std::invalid_argument    if a and b size don't match
 *
 * @return  the L2 squared distance between a and b
 */
template<class point>
auto L2(point const & a, point const & b)

    -> typename std::decay<decltype(a[0])>::type
{
    // can't compute the distance between points in different dimensions
    if (std::size(a) != std::size(b)) {
        throw std::invalid_argument{"points must be the same dimension!"};
    }
    // alias the underlying type for the point
    using num_t = typename std::decay<decltype(a[0])>::type;

    // compute the sum of the squares of the difference
    num_t dist = 0;
    for (size_t i = 0; i < std::size(a); i++) {
        num_t const e = a[i]-b[i];
        dist += e*e;
    }
    return dist;
}

/**
 * Compute the squared distance between two points under the L1 norm
 *
 * @param a one of the two points to find the distance between
 * @param b the other of the two points to find the distance between
 *
 * @throws std::invalid_argument    if a and b size don't match
 *
 * @return  the L1 distance between a and b
 */
template<class point>
auto L1(point const & a, point const & b)

    -> typename std::decay<decltype(a[0])>::type

{
    // can't compute the distance between points in different dimensions
    if (std::size(a) != std::size(b)) {
        throw std::invalid_argument{"points must be the same dimension!"};
    }
    // alias the underlying type for the point
    using num_t = typename std::decay<decltype(a[0])>::type;

    // compute the sum of the absolute values of the difference
    num_t dist = 0;
    for (size_t i = 0; i < std::size(a); i++) {
        num_t const e = a[i]-b[i];
        dist += std::abs(e);
    }
    return dist;
}
}

#endif
