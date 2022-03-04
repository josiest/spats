---
layout: default
title: sp::enum_size
parent: directions
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
