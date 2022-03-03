---
layout: default
title: sp::ranged_enum
parent: directions
---

## `sp::ranged_enum`

---

<pre>
template&lt;class Enum>
concept sp::ranged_enum = <a href="https://en.cppreference.com/w/cpp/types/is_enum">std::is_enum_v</a>&lt;Enum> and
                          <a href="https://en.cppreference.com/w/cpp/concepts/convertible_to">std::convertible_to</a>&lt;<a href="#spenum_size">sp::enum_size_v</a>&lt;Enum>, <a href="https://en.cppreference.com/w/cpp/types/size_t">std::size_t</a>>;
</pre>

---

### Semantic requirements

An enum with sequential underlying values defined on the interval
[0, [`sp::enum_size_v<Enum>`](#spenum_size)).

---

## `sp::enum_size`

---

<pre>
template&lt;class Enum> requires <a href="https://en.cppreference.com/w/cpp/types/is_enum">std::is_enum_v</a>&lt;Enum>
struct enum_size;
</pre>

---

Determine the number of elements an enum type defines.

### Member fields
<code><a href="https://en.cppreference.com/w/cpp/types/size_t">std::size_t</a> value</code> - the number of enum values
### Helper variable template
<pre>
template&lt;class Enum> requires <a href="https://en.cppreference.com/w/cpp/types/is_enum">std::is_enum_v</a>&lt;Enum>
using enum_size_v = enum_size&lt;Enum>::value;
</pre>