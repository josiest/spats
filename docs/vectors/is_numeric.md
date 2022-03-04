---
layout: default
title: sp::is_numeric
parent: vectors
---

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
    <a href="has_component.html">sp::has_x_component</a>&lt;Vector> and <a href="has_component.html">sp::has_y_component</a>&lt;Vector> and
requires(Vector v) {
    { v.x } -> <a href="https://en.cppreference.com/w/cpp/concepts/same_as">std::same_as</a>&lt;<a href="scalar_field.html">sp::scalar_field_t</a>&lt;Vector>>;
    { v.y } -> <a href="https://en.cppreference.com/w/cpp/concepts/same_as">std::same_as</a>&lt;<a href="scalar_field.html">sp::scalar_field_t</a>&lt;Vector>>;
};

template&lt;class Vector>
bool constexpr sp::is_3d_numeric =
    sp::is_2d_numeric&lt;Vector> and <a href="has_component.html">sp::has_z_component</a>&lt;Vector> and
requires(Vector v) {
    { v.z } -> <a href="https://en.cppreference.com/w/cpp/concepts/same_as">std::same_as</a>&lt;<a href="scalar_field.html">sp::scalar_field_t</a>&lt;Vector>>;
};
</pre>

