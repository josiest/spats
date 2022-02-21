#pragma once

// data structures
#include <unordered_set>

// type constraints
#include <type_traits>
#include <concepts>

namespace sp {

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
    p.y and std::is_same_v<decltype(p.x), decltype(p.y)>;

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