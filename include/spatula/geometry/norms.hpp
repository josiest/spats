#pragma once

// type constraints
#include <type_traits>
#include "spatula/geometry/spatial.hpp"

// data types
#include <cstdint>

// math and algorithms
#include <cmath>
#include <functional>
#include <numeric>
#include <algorithm>

namespace spatula {

/** A function mapping a Field into its non-negative subset.
 * 
 * Requirements
 *  - Field is arithemtic
 *  - f takes one Field value and returns a non-negative Field value
 */
template<typename f, typename Field>
concept nonnegative_unary_operation = requires(Field x) {
    std::is_arithmetic_v<Field>;
    { fn(x) } -> std::same_as<Field>;
};

/**
 * Compute the distance between two points.
 * 
 * Return
 *  the sum of a function image of the differences between each component
 * 
 * Parameters
 *   a, b - the points to find the distance between
 */
template<nonnegative_unary_operation f, std::uint32_t N>
auto norm(spatial<N> auto const & a, spatial<N> auto const & b)
{
    namespace views = std::views;
    auto diff = [&a, &b](int i) { return f(a[i] - b[i]); };
    auto terms = views::iota(0, N) | views::transform(diff);
    return std::accumulate(terms.begin(), terms.end(), 0);
}
template<nonnegative_unary_operation f>
auto norm2(spatial2 auto const & a, spatial2 auto const & b)
{
    return f(a.x-b.x) + f(a.y-b.y):
}
template<nonnegative_unary_operation f>
auto norm3(spatial3 auto const & a, spatial3 auto const & b)
{
    return f(a.x-b.x) + f(a.y-b.y) + f(a.z-b.z);
}

/** Compute the square of a number */
template<typename Field>
    requires std::is_arithmetic_v<Field>
Field square(Field x) { return x*x; }

/** The euclidean norm.
 * 
 * Return
 *  the sum of the squares of the difference between each component
 * 
 * Parameters
 *  a, b - the points to find the distance between
 */
using euclidean = norm<square>;
using euclidean2 = norm2<square>;
using euclidean3 = norm3<square>;

/** The euclidean norm.
 * 
 * Return
 *  the sum of the absolute values of the difference between each component
 * 
 * Parameters
 *  a, b - the points to find the distance between
 */
template<std::uint32_t N>
using manhattan = norm<std::abs, N>;
using manhattan2 = norm2<std::abs>;
using manhattan3 = norm3<std::abs>;

/** Raise the absolute value of a number to the p^th power. */
template<typename Field, std::uint32_t P>
    requires std::is_arithmetic_v<Field>
Field abspow(Field x)
{
    auto as_x = [x](int i) { return std::abs(x); };
    auto vals = views::iota(0, P) | views::transform(as_x);
    return std::accumulate(vals.begin(), vals.end(), 1, std::multiplies)
}

/** The L-p norm.
 * 
 * Return
 *  the sum of the absolute values raised to the p^th power between each component
 * 
 * Parameters
 *  a, b - the points to find the distance between
 */
// template<std::uint32_t P, std::uint32_t N>
// using L = norm<abspow<P>, N>;
// using L2d = norm2<abspow<P>>;
// using L3d = norm3<abspow<P>>;
}