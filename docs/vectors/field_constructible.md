---
layout: default
title: sp::field_constructible
parent: vectors
---

## `sp::field_constructible`

---

<pre>
template&lt;class Vector>
concept sp::field_2d_constructible = <a href="https://en.cppreference.com/w/cpp/concepts/constructible_from">std::constructible_from</a>&lt;
    Vector, <a href="scalar_field.html">sp::scalar_field_t</a>&lt;Vector>, <a href="scalar_field.html">sp::scalar_field_t</a>&lt;Vector>
>;

template&lt;class Vector>
concept sp::field_3d_constructible = <a href="https://en.cppreference.com/w/cpp/concepts/constructible_from">std::constructible_from</a>&lt;
    Vector, <a href="scalar_field.html">sp::scalar_field_t</a>&lt;Vector>, <a href="scalar_field.html">sp::scalar_field_t</a>&lt;Vector>,
            <a href="scalar_field.html">sp::scalar_field_t</a>&lt;Vector>
>;

template&lt;class Vector>
concept sp::field_constructible = sp::field_2d_constructible&lt;Vector> or
                                  sp::field_3d_constructible&lt;Vector>;
</pre>

---

### Semantic requirements
