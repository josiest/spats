# directions

Concepts and tools for working with spatial directions.

# How to work with directions

A direction, in layman's terms, is a concept that tells us how to turn our faces
or our bodies. In mathematical terms, we can say that a direction conceptually
corresponds to a finite set of unit vectors.

When we try to model this in C++, we should consider that different libraries
use different types to describe mathematical vectors, but we still want a way to
uniformly refer to a direction. Spatula's solution is to use enums to define a
direction, which can then be converted into a vector type:

```cpp
auto north = sp::direction_as<glm::ivec2>(sp::cardinal::north);
```

In the example above, the variable `north` is assigned a
[`glm::ivec2`](https://glm.g-truc.net/0.9.5/api/a00168.html#ga2ab812bd103527e2d6c62c2e2f5ee78f)
unit vector with the value `(0, 1)`. The function
[`sp::direction_as`](#Vector-direction_asdir) takes a direction enum, in this
case with the type
[`sp::cardinal::direction_name`](#enum-spcardinaldirection_name), and gives back
a unit vector with the specified type, that corresponds to the direction we gave
it.

The [`sp::direction_as`](#Vector-direction_asdir) function is designed to
provide users with the flexibility of choosing their own vector type, and even
[defining conversion functions](#struct-spenumtovector) for their own custom
direction types.

# direction conversions

## `sp::direction_as`
<pre>
<code><!-- language: lang-cpp -->template&lt;<a href="">sp::field_constructible</a> Vector, <a href="https://github.com/josiest/spatula/wiki/Directions#spranged_enum">sp::ranged_enum</a> Direction>
Vector sp::direction_as(Direction dir);
</code></pre>
Convert a direction from a `ranged_enum` to a unit vector

### Parameters
`dir` - the direction to convert to a vector

### Return
A unit vector representing the input direction

### Examples
```cpp
#include <SDL2/SDL.h>
auto const north = sp::direction_as<SDL_Point>(sp::cardinal::north);
```

## `sp::enum_to_vector`
<pre><code>template&lt;<a href="">sp::ranged_enum</a> Enum, class Vector></code>
struct enum_to_vector;
</pre>
A specializable template function object for converting a direction enum to a
vector.

### Member functions
- [`operator()`](#spenum_to_vectoroperator) - convert an enum to a unit vector

### Standard specializations

<pre>
<code>template&lt;<a href="">sp::field_2d_constructible</a> Vector>
    requires <a href="">std::construtible_from</a>&lt;<a href="">sp::scalar_field_t</a>&lt;Vector>, int>
sp::enum_to_vector<<a href="">sp::cardinal::direction_name</a>, Vector>;</code>
</pre>

## `sp::enum_to_vector::operator()`
<pre><code>Vector sp::enum_to_vector&lt;Enum, Vector>::operator()(Enum dir) const;</code>
</pre>

### Parameters
`dir` - the direction to convert to an enum

### Returns
A unit vector representing the input direction

# named directions

## `sp::cardinal::direction_name`
<pre><code>enum sp::cardinal::direction_name;</code></pre>
The cardinal directions

### Members
`sp::cardinal::north`  
`sp::cardinal::east`  
`sp::cardinal::south`  
`sp::cardinal::west`

# ranged enums

## `sp::ranged_enum`

<pre>
<code>template&lt;class Enum>
concept sp::ranged_enum = <a href="https://en.cppreference.com/w/cpp/types/is_enum">std::is_enum_v</a>&lt;Enum> and
                          <a href="https://en.cppreference.com/w/cpp/concepts/convertible_to">std::convertible_to</a>&lt;<a href="https://github.com/josiest/spatula/wiki/Directions#spenum_size">sp::enum_size_v</a>&lt;Enum>, <a href="https://en.cppreference.com/w/cpp/types/size_t">std::size_t</a>>;</code>
</pre>

### Semantic requirements

An enum with sequential underlying values defined on the interval
[0, [`sp::enum_size_v<Enum>`](#spenum_size)).

## `sp::enum_size`
<pre>
<code>template&lt;class Enum> requires <a href="https://en.cppreference.com/w/cpp/types/is_enum">std::is_enum_v</a>&lt;Enum>
struct enum_size;</code>
</pre>
Determine the number of elements an enum type defines.

### Member fields
- <code><a href="https://en.cppreference.com/w/cpp/types/size_t">std::size_t</a> value</code> - the number of enum values

### Helper variable template
<pre>
<code>template&lt;class Enum></code> requires <a href="https://en.cppreference.com/w/cpp/types/is_enum">std::is_enum_v</a>&lt;Enum>
using enum_size_v = enum_size&lt;Enum>::value;</code>
</pre>
