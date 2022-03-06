---
layout: default
title: vectors
nav_order: 3
has_children: true
---

# vector concepts
If you've taken a class in linear algebra or multivarible calculus, you might
be fimiliar with the concept of a vector as an ordered set of numbers that
describe a point or displacement in space. If you've taken linear algebra,
you've also likely been exposed to a more formal definition of a vector [as an
element of a vector space](https://mathworld.wolfram.com/Vector.html). If
you're unfamiliar with the concept of a vector or a vector space, or could use
a refresher of their properties, 3blue1brown has some excellent videos on
[vectors](https://www.youtube.com/watch?v=fNk_zzaMoSs) and on
[vector spaces](https://www.youtube.com/watch?v=TgKwz5Ikpc8).

Fundamental vector operations like
[addition](https://mathworld.wolfram.com/VectorAddition.html) and
[scalar multiplication](https://mathworld.wolfram.com/ScalarMultiplication.html)
are extremely useful in the realm of computer science. In C++ alone there a
whole handful of widely used libraries that each define their own vector types.
This, of course, makes things a little complicated when you want to write
algorithms that can be used independent of the library that supplies the vector
class. The solution is to make your algorithms templated. With C++20, you can
go even further and constrain the template parameters to satisfy certain
requirements. The aim of the vectors library is to provide you with a set of
well defined concepts and type constraints for writing generic algorithms that
work with vectors.

In order to provide the most practical experience, spatula defines two vector
concepts. [`sp::vector`](vector.html) models a the complete vector we know from
linear algebra, while [`sp::semivector`](semivector.html) is a much more
generalized constraint that allows for plain data types that don't have
operator specializations.

## complete vectors

By "complete," I mean that a vector type models all conditions of an element in
a [vector space](https://mathworld.wolfram.com/VectorSpace.html). Most of the
conditions described from the linked page are not ones that can be enforced, so
we say that the [`sp::vector`](vector.html) _models_ a complete vector. The
main requirements that _can_ be enforced are closure under addition and scalar
multiplication. The [`sp::vector`](vector.html) concept enforces these
conditions, as well as some conditions that are more specific to programming,
like the order a variable is assigned on initialization.

With complete vectors, we can very easily do things that usually require
operators:

```cpp
#include <numeric>
#include <ranges>
#include <vector>

#include <spatula/vectors.hpp>
#include <SFML/System.hpp>

namespace ranges = std::ranges;

template<ranges::output_range Range>
    requires sp::vector2<ranges::range_value_t<Range>>
void printsum(Range && points)
{
    // in this function, std::accumulate implicitly uses Vector's + operator
    // and takes advantage of the field_2d_constructible concept.
    // Later we get the x and y components that are also guaranteed to exist

    Vector const v = std::accumulate(
        ranges::begin(points), ranges::end(points), Vector(0, 0));
    std::cout << "(" << sp::get_x(v) << ", " << sp::get_y(v) << ")\n";
}

int main()
{
    std::vector<sf::Vector2i> points{
        sf::Vector2i(1, 2), sf::Vector2i(3, 4), sf::Vector2i(5, 6)
    };
    printsum(points); // (9, 12)
}
```

### An incomplete list of compatible types
A number of existing libraries have vector types that already model complete
vectors:

- [`glm`](https://github.com/g-truc/glm/blob/master/manual.md)'s
  [vector types](https://glm.g-truc.net/0.9.2/api/a00155.html)
- [`SFML`](https://www.sfml-dev.org/index.php)'s
  [`sf::Vector2`](https://www.sfml-dev.org/documentation/2.5.1/classsf_1_1Vector2.php) and
  [`sf::Vector3`](https://www.sfml-dev.org/documentation/2.5.1/classsf_1_1Vector3.php) types
- [Unreal Engine](https://www.unrealengine.com/en-US/)'s
  [`FVector`](https://docs.unrealengine.com/4.26/en-US/API/Runtime/Core/Math/FVector) and
  [`FQuat`](https://docs.unrealengine.com/4.27/en-US/API/Runtime/Core/Math/FQuat/) types

#### Note:
- [`Eigen`](https://eigen.tuxfamily.org/index.php?title=Main_Page)'s
  [Vector types](https://eigen.tuxfamily.org/dox-devel/group__matrixtypedefs.html)
  are also
  [_almost_ compatible](https://eigen.tuxfamily.org/dox/group__TutorialMatrixArithmetic.html)
  with [`sp::vector`](vector.html), but they access components by index and not
  by name. spatula will also add support for this in the very nearby future.

## "plain old" vectors

It may be the case that the vector types that you're working with don't have
operators defined for them. Maybe you're working with a data type from a C
library like [SDL](https://www.libsdl.org/)'s
[`SDL_Point`](https://wiki.libsdl.org/SDL_Point), or have your own similarly
very basic spatial data type. Something like:

```c
struct point { int x, y; };
```

Types like these are often called
["plain old" or "passive" data types](https://en.wikipedia.org/wiki/Passive_data_structure) (POD or PDS).
The [`std::semiregular`](https://en.cppreference.com/w/cpp/concepts/semiregular)
concept models almost everything about a POD type, save for how it's
initialized, and how its members are accessed.

Because vectors are fairly specific structures, default initialization is
essentially uniform accross any vector type you might see, and there's very
little variation with how members are named. Because of this, spatula is able
to offer the [`sp::field_constructible`](field_constructible.html) and
[`sp::is_numeric`](is_numeric.html) constraints to more concretely specify
POD vector types.

Here's an example of using a [`sp::semivector`](semivector.html) concept to
define the dot product for an arbitrary 3d vector type:

```cpp
auto dot(sp::semivector3 auto const & a, sp::semivector3 auto const & b)
{
    return sp::get_x(a) * sp::get_x(b) +
           sp::get_y(a) * sp::get_y(b) +
           sp::get_z(a) * sp::get_z(b);
}
```

> **Note:** [`sp::semivector`](semivector.html) is a _superset_ of of
  [`sp::vector`](vector.html): all functions that work for
  [`sp::semivector`](semivector.html) will _also_ work for
  [`sp::vector`](vector.html).

Alternatively, you can also limit the vectors to have specifically named
components - but this will break compatibility with certain vector types:

```cpp
template<class Vector>
    // if it models semivector3 and has an x component, standards dictate that
    // it likely has y and z components as well
    require sp::semivector3<Vector> and sp::has_x_component<Vector>

auto dot(Vector const & a, Vector const & b)
{
    return a.x*b.x + a.y*b.y + a.z*b.z;
}
```

# vector components

## example: partial ordering

## specializing component getters

# field concepts

