---
layout: default
title: sp::semivector
parent: vectors
---

## `sp::semivector`

---

<pre>
template&lt;class Vector>
concept sp::semivector2 = <a href="https://en.cppreference.com/w/cpp/concepts/semiregular">std::semiregular</a>&lt;Vector> and
                          <a href="field_constructible.html">sp::field_2d_constructible</a>&lt;Vector> and
                          <a href="is_numeric.html">sp::is_2d_numeric</a>&lt;Vector>;

template&lt;class Vector>
concept sp::semivector3 = <a href="https://en.cppreference.com/w/cpp/concepts/semiregular">std::semiregular</a>&lt;Vector> and
                          <a href="field_constructible.html">sp::field_3d_constructible</a>&lt;Vector> and
                          <a href="is_numeric.html">sp::is_3d_numeric</a>&lt;Vector>;

template&lt;class Vector>
concept sp::semivector = sp::semivector2&lt;Vector> or
                         sp::semivector3&lt;Vector>;
</pre>

---

### Semantic Requirements

