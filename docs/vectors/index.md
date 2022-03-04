---
layout: default
title: vectors
nav_order: 3
has_children: true
---

# vector concepts and contraints

## `sp::vector`

---

<pre>
template&lt;class Vector>
concept sp::vector2 = <a href="https://en.cppreference.com/w/cpp/concepts/regular">std::regular</a>&lt;Vector> and
                      <a href="#spfield_constructible">sp::field_2d_constructible</a>&lt;Vector> and
                      <a href="#spis_numeric">sp::is_2d_numeric</a>&lt;Vector> and
                      <a href="#sphas_vector_closure">sp::has_vector_closure</a>&lt;Vector>;

template&lt;class Vector>
concept sp::vector3 = <a href="https://en.cppreference.com/w/cpp/concepts/regular">std::regular</a>&lt;Vector> and
                      <a href="#spfield_constructible">sp::field_3d_constructible</a>&lt;Vector> and
                      <a href="#spis_numeric">sp::is_3d_numeric</a>&lt;Vector> and
                      <a href="#sphas_vector_closure">sp::has_vector_closure</a>&lt;Vector>;

template&lt;class Vector>
concept sp::vector = sp::vector2&lt;Vector> or sp::vector3&lt;Vector>;
</pre>

---

### Semantic Requirements

---

## `sp::semivector`

---

<pre>
template&lt;class Vector>
concept sp::semivector2 = <a href="https://en.cppreference.com/w/cpp/concepts/semiregular">std::semiregular</a>&lt;Vector> and
                          <a href="#spfield_constructible">sp::field_2d_constructible</a>&lt;Vector> and
                          <a href="#spis_numeric">sp::is_2d_numeric</a>&lt;Vector>;

template&lt;class Vector>
concept sp::semivector3 = <a href="https://en.cppreference.com/w/cpp/concepts/semiregular">std::semiregular</a>&lt;Vector> and
                          <a href="#spfield_constructible">sp::field_3d_constructible</a>&lt;Vector> and
                          <a href="#spis_numeric">sp::is_3d_numeric</a>&lt;Vector>;

template&lt;class Vector>
concept sp::semivector = sp::semivector2&lt;Vector> or
                         sp::semivector3&lt;Vector>;
</pre>

---

### Semantic Requirements

---

## `sp::scalar_field`

---

<pre>
template&lt;class Vector>
struct sp::scalar_field;
</pre>

---

Determine the underlying scalar field type of a vector.

### Member types


<code>type</code> - the type of the scalar field

### Helper variable template
<pre>

template&lt;class Vector>
using sp::scalar_field_t = sp::scalar_field&lt;Vector>::type;
</pre>

### Standard specializations
<pre>

// get the scalar field type of a vector with an x component
template&lt;class Vector>
    requires <a href="#sphas_component">sp::has_x_component</a>&lt;Vector>
struct scalar_field&lt;Vector>;

// get the scalar field type of an indexable vector
template&lt;class Vector>
    requires <a href="#sphas_component">sp::has_i_component</a>&lt;Vector> and (not <a href="#sphas_component">sp::has_x_component</a>&lt;Vector>)
struct scalar_field&lt;Vector>;
</pre>

---

## `sp::has_vector_closure`

---

<pre>
template&lt;class Vector>
bool constexpr sp::has_vector_closure = /* see below */;
</pre>

---

An atomic constraint that a class has operators defined for vector addition,
subtraction and scalar multiplication, and that each of these operations are
closed (each operation returns an instance of the same vector type as those in
the operands).

### Possible implementation
<pre>

template&lt;class Vector>
bool constexpr sp::has_vector_closure =
requires(Vector a, Vector b, <a href="#spscalar_field">sp::scalar_field_t</a>&lt;Vector> c) {
    { a + b } -> <a href="https://en.cppreference.com/w/cpp/concepts/same_as">std::same_as</a>&lt;Vector>;
    { a - b } -> <a href="https://en.cppreference.com/w/cpp/concepts/same_as">std::same_as</a>&lt;Vector>;
    { c * a } -> <a href="https://en.cppreference.com/w/cpp/concepts/same_as">std::same_as</a>&lt;Vector>;

    { a += b } -> <a href="https://en.cppreference.com/w/cpp/concepts/same_as">std::same_as</a>&lt;Vector&>;
    { a -= b } -> <a href="https://en.cppreference.com/w/cpp/concepts/same_as">std::same_as</a>&lt;Vector&>;
    { a *= c } -> <a href="https://en.cppreference.com/w/cpp/concepts/same_as">std::same_as</a>&lt;Vector&>;
};
</pre>

# component constraints

## `sp::has_component`

---

<pre>
template&lt;class Vector>
bool constexpr sp::has_x_component = /* see below */;

template&lt;class Vector>
bool constexpr sp::has_y_component = /* see below */;

template&lt;class Vector>
bool constexpr sp::has_z_component = /* see below */;

template&lt;class Vector>
bool constexpr sp::has_i_component = /* see below */;
</pre>

---

### Possible implementations

<pre>

template&lt;class Vector>
bool constexpr sp::has_x_component = requires(Vector v) {
    <a href="#sphas_field_closure">sp::has_field_closure</a>&lt;delctype(v.x)>;
};

template&lt;class Vector>
bool constexpr sp::has_y_component = requires(Vector v) {
    <a href="#sphas_field_closure">sp::has_field_closure</a>&lt;delctype(v.y)>;
};

template&lt;class Vector>
bool constexpr sp::has_z_component = requires(Vector v) {
    <a href="#sphas_field_closure">sp::has_field_closure</a>&lt;delctype(v.z)>;
};

template&lt;class Vector>
bool constexpr sp::has_i_component = requires(Vector v, <a href="https://en.cppreference.com/w/cpp/types/size_t">std::size_t</a> i) {
    <a href="#sphas_field_closure">sp::has_field_closure</a>&lt;delctype(v[i])>;
};
</pre>

# field concepts and constraints

## `sp::field`

---

<pre>
template&lt;class Field>
concept sp::field = <a href="https://en.cppreference.com/w/cpp/concepts/regular">std::regular</a>&lt;Field> and <a href="#sphas_field_closure">sp::has_field_closure</a>&lt;Field>;
</pre>

---

### Semantic requirements

---

## `sp::has_field_closure`

---

<pre>
template&lt;class Field>
bool constexpr sp::has_field_closure = /* see below */;
</pre>

---

### Possible implementation
<pre>

template&lt;typename Field>
bool constexpr sp::has_field_closure = requires(Field a, Field b) {
    { a + b } -> <a href="https://en.cppreference.com/w/cpp/concepts/same_as">std::same_as</a>&lt;Field>;
    { a - b } -> <a href="https://en.cppreference.com/w/cpp/concepts/same_as">std::same_as</a>&lt;Field>;
    { a * b } -> <a href="https://en.cppreference.com/w/cpp/concepts/same_as">std::same_as</a>&lt;Field>;
    { a / b } -> <a href="https://en.cppreference.com/w/cpp/concepts/same_as">std::same_as</a>&lt;Field>;

    { a += b } -> <a href="https://en.cppreference.com/w/cpp/concepts/same_as">std::same_as</a>&lt;Field&>;
    { a -= b } -> <a href="https://en.cppreference.com/w/cpp/concepts/same_as">std::same_as</a>&lt;Field&>;
    { a *= b } -> <a href="https://en.cppreference.com/w/cpp/concepts/same_as">std::same_as</a>&lt;Field&>;
    { a /= b } -> <a href="https://en.cppreference.com/w/cpp/concepts/same_as">std::same_as</a>&lt;Field&>;
};
</pre>

# numeric constraints

## `sp::is_numeric`

---

<pre>
template&lt;class Vector>
bool constexpr sp::is_2d_numeric = /* see below */;

template&lt;class Vector>
bool constexpr sp::is_2d_numeric = /* see below */;

template&lt;class Vector>
bool constexpr sp::is_numeric = sp::is_2d_numeric&lt;Vector> or
                                sp::is_3d_numeric&lt;Vector>;
</pre>

---

### Possible implementation

<pre>

template&lt;class Vector>
bool constexpr sp::is_2d_numeric =
    <a href="#sphas_component">sp::has_x_component</a>&lt;Vector> and <a href="#sphas_component">sp::has_y_component</a>&lt;Vector> and
requires(Vector v) {
    { v.x } -> <a href="https://en.cppreference.com/w/cpp/concepts/same_as">std::same_as</a>&lt;<a href="#spscalar_field">sp::scalar_field_t</a>&lt;Vector>>;
    { v.y } -> <a href="https://en.cppreference.com/w/cpp/concepts/same_as">std::same_as</a>&lt;<a href="#spscalar_field">sp::scalar_field_t</a>&lt;Vector>>;
};

template&lt;class Vector>
bool constexpr sp::is_3d_numeric =
    sp::is_2d_numeric&lt;Vector> and <a href="#sphas_component">sp::has_z_component</a>&lt;Vector> and
requires(Vector v) {
    { v.z } -> <a href="https://en.cppreference.com/w/cpp/concepts/same_as">std::same_as</a>&lt;<a href="#spscalar_field">sp::scalar_field_t</a>&lt;Vector>>;
};
</pre>

# constructible concepts

## `sp::field_constructible`

---

<pre>
template&lt;class Vector>
concept sp::field_2d_constructible = <a href="https://en.cppreference.com/w/cpp/concepts/constructible_from">std::constructible_from</a>&lt;
    Vector, <a href="#spscalar_field">sp::scalar_field_t</a>&lt;Vector>, <a href="#spscalar_field">sp::scalar_field_t</a>&lt;Vector>
>;

template&lt;class Vector>
concept sp::field_3d_constructible = <a href="https://en.cppreference.com/w/cpp/concepts/constructible_from">std::constructible_from</a>&lt;
    Vector, <a href="#spscalar_field">sp::scalar_field_t</a>&lt;Vector>, <a href="#spscalar_field">sp::scalar_field_t</a>&lt;Vector>,
            <a href="#spscalar_field">sp::scalar_field_t</a>&lt;Vector>
>;

template&lt;class Vector>
concept sp::field_constructible = sp::field_2d_constructible&lt;Vector> or
                                  sp::field_3d_constructible&lt;Vector>;
</pre>

---

### Semantic requirements
