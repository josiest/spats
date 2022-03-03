---
layout: default
title: directions
nav_order: 4
has_children: true
---

Defined in `<spatula/math/directions.hpp>`

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

# named directions

# ranged enums
