---
layout: default
title: sp::has_i_component
parent: components
grand_parent: vectors
---

# `sp::has_i_component`

---

<pre>
template&lt;class Vector>
constexpr bool has_i_component = requires(Vector v) {
    has_field_closure<decltype(v[i])>;
};
</pre>
