---
layout: default
title: direction_as
parent: directions
---

## `sp::direction_as`

---

<pre>
template&lt;<a href="vectors.html#spfield_constructible">sp::field_constructible</a> Vector, <a href="#spranged_enum">sp::ranged_enum</a> Direction>
Vector sp::direction_as(Direction dir);
</pre>

---

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

