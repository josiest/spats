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
    // Later we use the x and y components that are garunteed to exist

    Vector const v = std::accumulate(ranges::begin(points),
                                     ranges::end(points), Vector(0, 0));
    std::cout << "(" << v.x << ", " << v.y << ")\n";
}

int main()
{
    std::vector<sf::Vector2i> points{
        sf::Vector2i(1, 2), sf::Vector2i(3, 4), sf::Vector2i(5, 6)
    };
    printsum(points); // (9, 12)
}
```

## "plain old" vectors

# vector components

## partial ordering

# field concepts

