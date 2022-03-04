---
layout: default
title: sp::scalar_field
parent: vectors
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
    requires <a href="has_component.html">sp::has_x_component</a>&lt;Vector>
struct scalar_field&lt;Vector>;

// get the scalar field type of an indexable vector
template&lt;class Vector>
    requires <a href="has_component.html">sp::has_i_component</a>&lt;Vector> and (not <a href="has_component.html">sp::has_x_component</a>&lt;Vector>)
struct scalar_field&lt;Vector>;
</pre>
