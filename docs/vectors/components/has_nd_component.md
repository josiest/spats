---
layout: default
title: sp::has_nd_component
parent: components
grand_parent: vectors
---

# `sp::has_nd_component`

---

<pre>
template&lt;class Vector, <a href="">std::size_t</a> i>
struct dimension_query { /* see below. */ };
</pre>

## Member fields

## Standard specializations

## Helper template

<pre>
template&lt;class Vector, <a href="">std::size_t</a> i>
constexpr bool has_nd_component = dimension_query&lt;Vector, i>::value;
</pre>
