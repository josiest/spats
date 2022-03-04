---
layout: default
title: sp::has_component
parent: vectors
---

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
    <a href="has_field_closure.html">sp::has_field_closure</a>&lt;delctype(v.x)>;
};

template&lt;class Vector>
bool constexpr sp::has_y_component = requires(Vector v) {
    <a href="has_field_closure.html">sp::has_field_closure</a>&lt;delctype(v.y)>;
};

template&lt;class Vector>
bool constexpr sp::has_z_component = requires(Vector v) {
    <a href="has_field_closure.html">sp::has_field_closure</a>&lt;delctype(v.z)>;
};

template&lt;class Vector>
bool constexpr sp::has_i_component = requires(Vector v, <a href="https://en.cppreference.com/w/cpp/types/size_t">std::size_t</a> i) {
    <a href="has_field_closure.html">sp::has_field_closure</a>&lt;delctype(v[i])>;
};
</pre>

