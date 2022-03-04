---
layout: default
title: sp::has_vector_closure
parent: vectors
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
requires(Vector a, Vector b, <a href="scalar_field.html">sp::scalar_field_t</a>&lt;Vector> c) {
    { a + b } -> <a href="https://en.cppreference.com/w/cpp/concepts/same_as">std::same_as</a>&lt;Vector>;
    { a - b } -> <a href="https://en.cppreference.com/w/cpp/concepts/same_as">std::same_as</a>&lt;Vector>;
    { c * a } -> <a href="https://en.cppreference.com/w/cpp/concepts/same_as">std::same_as</a>&lt;Vector>;

    { a += b } -> <a href="https://en.cppreference.com/w/cpp/concepts/same_as">std::same_as</a>&lt;Vector&>;
    { a -= b } -> <a href="https://en.cppreference.com/w/cpp/concepts/same_as">std::same_as</a>&lt;Vector&>;
    { a *= c } -> <a href="https://en.cppreference.com/w/cpp/concepts/same_as">std::same_as</a>&lt;Vector&>;
};
</pre>

