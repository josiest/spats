---
layout: default
title: sp::vector
parent: vectors
---

## `sp::vector`

---

<pre>
template&lt;class Vector>
concept sp::vector2 = <a href="https://en.cppreference.com/w/cpp/concepts/regular">std::regular</a>&lt;Vector> and
                      <a href="field_constructible.html">sp::field_2d_constructible</a>&lt;Vector> and
                      <a href="is_numeric.html">sp::is_2d_numeric</a>&lt;Vector> and
                      <a href="has_vector_closure.html">sp::has_vector_closure</a>&lt;Vector>;

template&lt;class Vector>
concept sp::vector3 = <a href="https://en.cppreference.com/w/cpp/concepts/regular">std::regular</a>&lt;Vector> and
                      <a href="field_constructible.html">sp::field_3d_constructible</a>&lt;Vector> and
                      <a href="is_numeric.html">sp::is_3d_numeric</a>&lt;Vector> and
                      <a href="has_vector_closure.html">sp::has_vector_closure</a>&lt;Vector>;

template&lt;class Vector>
concept sp::vector = sp::vector2&lt;Vector> or sp::vector3&lt;Vector>;
</pre>

---

### Semantic Requirements

