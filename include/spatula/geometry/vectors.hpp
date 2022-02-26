#pragma once

// type constraints
#include <type_traits>
#include <concepts>
#include <ranges>

// data structures and algorithms
#include <algorithm>
#include <utility>
#include <cstddef>
#include <array>

namespace sp {

namespace ranges = std::ranges;

//
// Components
//

/** A data type with a numeric x field. */
template<class Vector>
concept with_x_component = requires(Vector v) {
    v.x and std::is_arithmetic_v<std::remove_reference_t<decltype(v.x)>>;
};

/** A data type with a numeric y field. */
template<class Vector>
concept with_y_component = requires(Vector v) {
    v.y and std::is_arithmetic_v<std::remove_reference_t<decltype(v.y)>>;
};

/** A data type with a numeric z field. */
template<class Vector>
concept with_z_component = requires(Vector v) {
    v.z and std::is_arithmetic_v<std::remove_reference_t<decltype(v.z)>>;
};

/** A data type with arbitrary numeric fields. */
template<class Vector>
concept with_i_component = requires(Vector v, std::size_t i) {
    v[i] and std::is_arithmetic_v<std::remove_reference_t<decltype(v[i])>>;
};

//
// Numeric Types
//

/** A data type with two numeric dimensions.
 *
 * Requirements
 *  - constructible from two numeric values
 *  - has x and y components of the same type
 */
template<class Vector>
concept numeric2d =
    with_x_component<Vector> and with_y_component<Vector> and
requires(Vector v) {
    std::same_as<decltype(v.x), decltype(v.y)>;
    Vector(v.x, v.y);
};

/** A data type with three numeric dimensions.
 *
 * Requirements
 *  - constructible from two numeric values
 *  - has x, y, and z components of the same type
 */
template<class Vector>
concept numeric3d =
    with_x_component<Vector> and with_y_component<Vector> and
    with_z_component<Vector> and
requires(Vector v) {
    std::same_as<decltype(v.x), decltype(v.y)>;
    std::same_as<decltype(v.x), decltype(v.z)>;
    Vector(v.x, v.y, v.z);
};

/** A data type with arbitrary numeric dimensions.
 * 
 * Requirements
 * - has a numeric ith component
 * - can be queried for size with std::size
 */
template<class Vector>
concept numericNd =
    with_i_component<Vector> and
requires(Vector v) {
    std::size(v);
};

/** A general numeric type.
 * 
 * Requirements
 *  - numeric2d or numeric3d or numericNd
 */
template<class Vector>
concept numeric = numeric2d<Vector> or numeric3d<Vector> or numericNd<Vector>;

//
// Field type
//

/** Get the underlying field type of a vector type. */
template<class Vector> struct field;

template<with_x_component Vector>
struct field<Vector> {
    using type = std::remove_reference_t<decltype(std::declval<Vector>().x)>;
};
// it's possible that a vector type may support operator[] and have an x field
// so in order to avoid ambiguity, we must specify for operator[] and not x field
template<class Vector>
    requires with_i_component<Vector> and (not with_x_component<Vector>)
struct field<Vector> {
    using type = std::remove_reference_t<
        decltype(std::declval<Vector>()[std::declval<std::size_t>()])
    >;
};

template<class Vector>
requires with_x_component<Vector> or with_i_component<Vector>
using field_t = typename field<Vector>::type;

//
// Vector types
//

/** A basic "plain old" vector.
 *
 * Requirements
 * - semiregular and numeric
 * 
 * Useful for working with c-types that haven't defined vector operations.
 */
template<class Vector>
concept semi_vector = std::semiregular<Vector> and numeric<Vector>;
template<class Vector>
concept semi_vector2 = std::semiregular<Vector> and numeric2d<Vector>;
template<class Vector>
concept semi_vector3 = std::semiregular<Vector> and numeric3d<Vector>;
template<class Vector>
concept semi_vectorNd = std::semiregular<Vector> and numericNd<Vector>;

/** A type that satisfies vector closure requirements
 * 
 * Requirements
 * - closed under addition, subtraction and multiplication
 */
template<class Vector>
concept vector_closure =
    (with_x_component<Vector> or with_i_component<Vector>) and
requires(Vector v, field_t<Vector> c) {
    { v + v } -> std::same_as<Vector>;
    { v - v } -> std::same_as<Vector>;
    { c * v } -> std::same_as<Vector>;
};

/** A complete vector type.
 * 
 * Requirements
 * - regular and numeric
 * - closed under addition, subtraction and multiplication
 */
template<class Vector>
concept vector = std::regular<Vector> and numeric<Vector> and
                 vector_closure<Vector>;

template<class Vector>
concept vector2 = std::regular<Vector> and numeric2d<Vector> and
                  vector_closure<Vector>;

template<class Vector>
concept vector3 = std::regular<Vector> and numeric3d<Vector> and
                  vector_closure<Vector>;

template<class Vector>
concept vectorNd = std::regular<Vector> and numericNd<Vector> and
                   vector_closure<Vector>;


// TODO: move to separate file

//
// Math Utilities
//

//
// Ordering
//

/** Order vectors by their fields. */
template<with_x_component Vector>
bool least_x(Vector const & u, Vector const & v)
{
    return u.x < v.x;
}
template<with_y_component Vector>
bool least_y(Vector const & u, Vector const & v)
{
    return u.y < v.y;
}
template<with_z_component Vector>
bool least_z(Vector const & u, Vector const & v)
{
    return u.z < v.z;
}
template<std::size_t i, with_i_component Vector>
bool least_by_field(Vector const & u, Vector const & v)
{
    return u[i] < v[i];
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
    requires semi_vector2<ranges::range_value_t<Range>>

auto bounding_corners2d(Range && points)
{
    using Vector = ranges::range_value_t<Range>;

    // find the points with the least and greatest x and y coordinates
    auto const &[xmin, xmax] = ranges::minmax(points, least_x);
    auto const &[ymin, ymax] = ranges::minmax(points, least_y);

    return std::make_pair(Vector(xmin.x, ymin.y), Vector(xmax.x, ymax.y));
}

}