#pragma once

// type constraints
#include <type_traits>
#include <concepts>
#include <ranges>

// data structures and algorithms
#include <algorithm>
#include <utility>

namespace sp {

namespace ranges = std::ranges;

/** A basic POD spatial type of 2 dimensions.
 *
 * A vector2 type must satisfy the following requirements
 * - default and copy constructible, and constructible from two numeric values
 * - has public numeric members x and y with the same type
 * 
 * Useful for working with c-types that haven't defined vector operations.
 */
template<class Vector>
concept basic_vector2 = std::default_initializable<Vector> and
                        std::copy_constructible<Vector> and
                        requires(Vector p) {

    // -- member requirements --
    // Vector has an x member that's numeric
    p.x and std::is_arithmetic_v<std::remove_reference_t<decltype(p.x)>>;
    // Vector has a y member with the same type as x
    p.y and std::same_as<decltype(p.x), decltype(p.y)>;

    // -- constructor requirements --
    // Vector is constructable from two numeric values
    Vector(p.x, p.y);
};

/** Addition for basic vector2 types. */
template<basic_vector2 Vector>
Vector vector2_add(Vector const & u, Vector const & v)
{
    return Vector(u.x + v.x, u.y + v.y);
}

/** Equality for basic vector2 types. */
template<basic_vector2 Vector>
bool vector2_equals(Vector const & u, Vector const & v)
{
    return u.x == v.x and u.y == v.y;
}

/** Order vectors by their fields. */
template<basic_vector2 Vector>
bool comparing_x2(Vector const & u, Vector const & v)
{
    return u.x < v.x;
}
template<basic_vector2 Vector>
bool comparing_y2(Vector const & u, Vector const & v)
{
    return u.y < v.y;
}

/** Generate the bounding corners of a set of vectors.
 * 
 * Return
 *   A pair of vectors (lower-left, upper-right), representing the bounding
 *   corners of the input points.
 * 
 * Parameters
 *   points - the input points to find the boundary of
 */
template<ranges::input_range Range>
    requires basic_vector2<ranges::range_value_t<Range>>
auto bounding_corners2(Range && points)
{
    using Vector = ranges::range_value_t<Range>;

    // find the points with the least and greatest x and y coordinates
    auto const &[xmin, xmax] = ranges::minmax(points, comparing_x2);
    auto const &[ymin, ymax] = ranges::minmax(points, comparing_y2);

    return std::make_pair(Vector(xmin.x, ymin.y), Vector(xmax.x, ymax.y));
}

/** A vector type of 2 dimensions.
 * 
 * A vector2 type must satisfy the following requirements
 * - basic_vector2 requirements
 * - equality comparable
 * - closed under addition
 */
template<class Vector>
concept vector2 = basic_vector2<Vector> and
                  std::equality_comparable<Vector> and
                  requires(Vector p) {
    // vectors must be closed under additon
    { p + p } -> std::same_as<Vector>;
};
}