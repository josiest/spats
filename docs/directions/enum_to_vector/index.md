---
layout: default
title: enum_to_vector
parent: directions
has_children: true
---

## `sp::enum_to_vector`

---

<pre>
template&lt;<a href="directions/ranged_enum.html">sp::ranged_enum</a> Enum, class Vector>
struct enum_to_vector;
</pre>

---

A specializable template function object for converting a direction enum to a
vector.

### Member functions
- [`operator()`](operator_parens.html) - convert an enum to a unit vector

### Standard specializations

<pre>
// convert cardinal direction to a 2d vector
template&lt;<a href="vectors.html#spfield_constructible">sp::field_2d_constructible</a> Vector>
    requires <a href="https://en.cppreference.com/w/cpp/concepts/constructible_from">std::constructible_from</a>&lt;<a href="vectors.html#spscalar_field">sp::scalar_field_t</a>&lt;Vector>, int>
sp::enum_to_vector<<a href="directions/cardinal.html">sp::cardinal::direction_name</a>, Vector>;
</pre>

