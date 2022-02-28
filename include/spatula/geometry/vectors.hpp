#pragma once

// type constraints
#include <type_traits>
#include <concepts>
#include <ranges>

// data types and algorithms
#include <cstddef>
#include <utility>
#include <algorithm>

namespace sp {

/** An atomic constraint for field operations. */
template<class Field>
constexpr bool has_field_closure =
    std::is_same_v<decltype(std::declval<Field>() +
                            std::declVal<Field>()), Field> and

    std::is_same_v<decltype(std::declval<Field>() -
                            std::declVal<Field>()), Field> and

    std::is_same_v<decltype(std::declval<Field>() *
                            std::declVal<Field>()), Field> and

    std::is_same_v<decltype(std::declval<Field>() /
                            std::declVal<Field>()), Field>;
};

/** A type that models the field axioms.
 * 
 * Semantic Requirements:
 * 
 * Adapted from https://mathworld.wolfram.com/FieldAxioms.html:
 * 
 * name             | addition          | multiplication
 * ----------------------------------------------------------------
 * associativity    | (a+b)+c=a+(b+c)   | (a*b)*c=a*(b*c)
 * commutativity    | a+b=b+a           | a*b=b*a
 * distributivity   | a(b+c)=a*b+a*c    | (a+b)*c=a*c+b*c
 * identity         | a+0=a=0+a         | a*1=a=1*a
 * inverses         | a-a=0             | a/a=1 if a!=0
*/
template<class Field>
concept field = std::regular<Field> and has_field_closure<Field>;

namespace ranges = std::ranges;

//
// Atomic component constraints
//

/** Require a type to have specific components subset to a field. */
template<class Vector>
constexpr bool has_x_component = has_field_closure<
    std::remove_reference_t<decltype(std::declval<Vector>().x)>
>;
template<class Vector>
constexpr bool has_y_component = has_field_closure<
    std::remove_reference_t<decltype(std::declval<Vector>().y)>
>;
template<class Vector>
constexpr bool has_z_component = has_field_closure<
    std::remove_reference_t<decltype(std::declval<Vector>().z)>
>;
template<class Vector>
constexpr bool has_i_component = has_field_closure<std::remove_reference_t<
    decltype(std::declval<Vector>()[std::declval<std::size_t>()])
>>;

//
// Field type-deduction
//

/** The scalar field type of a vector. */
template<class Vector> struct scalar_field;

template<class Vector>
    requires has_x_component<Vector>
struct scalar_field<Vector> {
    using type = std::remove_reference_t<decltype(std::declval<Vector>().x)>;
};
// it's possible that a vector type may support operator[] and have an x field
// so in order to avoid ambiguity, we must specify for operator[] and not x field
template<class Vector>
    requires has_i_component<Vector> and (not has_x_component<Vector>)
struct scalar_field<Vector> {
    using type = std::remove_reference_t<
        decltype(std::declval<Vector>()[std::declval<std::size_t>()])
    >;
};

template<class Vector>
using scalar_field_t = typename scalar_field<Vector>::type;

//
// Atomic numeric-type constraints
//

/** A numeric data type.
 * 
 * Syntactic Requirements:
 *   A numeric data type is an atomic constraint that requires a type to have a
 *   set of uniformly-typed components with field closure.
 */
template<class Vector>
constexpr bool is_2d_numeric =
    has_x_component<Vector> and has_y_component<Vector> and
    std::is_same_v<scalar_field_t<Vector>, decltype(std::declval<Vector>().x)> and
    std::is_same_v<scalar_field_t<Vector>, decltype(std::declval<Vector>().y)>;

template<class Vector>
constexpr bool is_3d_numeric =
    has_x_component<Vector> and has_y_component<Vector> and
    has_z_component<Vector> and

    std::is_same_v<scalar_field_t<Vector>, decltype(std::declval<Vector>().x)> and
    std::is_same_v<scalar_field_t<Vector>, decltype(std::declval<Vector>().y)> and
    std::is_same_v<scalar_field_t<Vector>, decltype(std::declval<Vector>().z)>;
};
 
template<class Vector>
constexpr bool is_numeric = is_2d_numeric<Vector> or is_3d_numeric<Vector>;

//
// Constructible concepts
//

/** A type that's constructible from a sequence of field values.
 * 
 * Semantic Requirements:
 * 
 * - A field_constructible type models a data type with public uniformly-typed
 *   members that can be directly initialized through a constructor.
 * 
 * - The type's members have a semantically defined order, which corresponds to
 *   the order of the constructor's parameters.
 * 
 * Example:
 *     struct point { int x, y; };
 *     static_assert<field_2d_constructible<point>>;
 * 
 *   The point class models field_2d_constructible because all of its members
 *   (x and y) have the same type, and the default constructor assigns them in
 *   the standard order of x before y.
 * 
 *   Note, a type such as `struct yfirst_point { int y, x; };` still models
 *   field_2d_constructible if the context it's used in orders y before x.
 *   However, the original point type would not model field_2d_constructible for
 *   this context because the programmer expects point(1, 2) to assign 1 to the
 *   y member and 2 to the x member.
 */
template<class Vector>
concept field_2d_constructible = std::constructible_from<
    Vector, scalar_field_t<Vector>, scalar_field_t<Vector>
>;

template<class Vector>
concept field_3d_constructible = std::constrictible_from<
    Vector, scalar_field_t<Vector>, scalar_field_t<Vector>,
            scalar_field_t<Vector>
>;

template<class Vector>
concept field_constructible = field_2d_constructible<Vector> or
                              field_3d_constructible<Vector>;

//
// Vector concepts
//

/** A basic "plain old" vector.
 * 
 * Useful for working with c-types that haven't defined vector operations.
 */
template<class Vector>
concept semivector2 = std::semiregular<Vector> and
                      field_2d_constructible<Vector> and is_2d_numeric<Vector>;
template<class Vector>
concept semivector3 = std::semiregular<Vector> and
                      field_3d_constructible<Vector> and is_3d_numeric<Vector>;
template<class Vector>
concept semivector = semivector2<Vector> or semivector3<Vector>;

/** An atomic contraint for vector operations. */
template<class Vector>
constexpr bool has_vector_closure =
    std::is_same_v<decltype(std::declval<Vector>() +
                            std::declval<Vector>()), Vector> and

    std::is_same_v<decltype(std::declval<Vector>() -
                            std::declval<Vector>()), Vector> and

    std::is_same_v<decltype(std::declval<scalar_field_t<Vector>>() *
                            std::declval<Vector>()), Vector>;

/** A complete vector type.
 * 
 * Semantic Requirements:
 * 
 * for two n-dimensional vectors a and b of the form
 *  v = (v[1], v[2], ..., v[n])
 * and an element c of their scalar field
 * 
 * - a + b = (a[1] + b[1], a[2] + b[2], ..., a[n] + b[n])
 * - a - b = (a[1] - b[1], a[2] - b[2], ..., a[n] - b[n])
 * - c * a = (c * a[1], c * a[2], ..., c * a[3])
 */
template<class Vector>
concept vector2 = std::regular<Vector> and field_2d_constructible<Vector> and
                  is_2d_numeric<Vector> and has_vector_closure<Vector>;
template<class Vector>
concept vector3 = std::regular<Vector> and field_3d_constructible<Vector> and
                  is_3d_numeric<Vector> and has_vector_closure<Vector>;
template<class Vector>
concept vector = vector2<Vector> or vector3<Vector>;

//
// Math Utilities
//

//
// Ordering
//

/** Order vectors by their components. */
template<class Vector>
    requires has_x_component<Vector> and
             std::totally_ordered<scalar_field_t<Vector>>
bool least_x(Vector const & u, Vector const & v)
{
    return u.x < v.x;
}
template<class Vector>
    requires has_y_component<Vector> and
             std::totally_ordered<scalar_field_t<Vector>>
bool least_y(Vector const & u, Vector const & v)
{
    return u.y < v.y;
}
template<class Vector>
    requires has_z_component<Vector> and
             std::totally_ordered<scalar_field_t<Vector>>
bool least_z(Vector const & u, Vector const & v)
{
    return u.z < v.z;
}
template<std::size_t i, class Vector>
    requires has_i_component<Vector> and
             std::totally_ordered<scalar_field_t<Vector>>
bool least_by_component(Vector const & u, Vector const & v)
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
    requires semivector2<ranges::range_value_t<Range>> and
             std::totally_ordered<scalar_field_t<ranges::range_value_t>>

auto bounding_corners2d(Range && points)
{
    using Vector = ranges::range_value_t<Range>;

    // find the points with the least and greatest x and y coordinates
    auto const &[xmin, xmax] = ranges::minmax(points, least_x);
    auto const &[ymin, ymax] = ranges::minmax(points, least_y);

    return std::make_pair(Vector(xmin.x, ymin.y), Vector(xmax.x, ymax.y));
}

}