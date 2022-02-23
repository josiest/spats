# spatula

A simple header-only library for manipulating spatial data of arbitrary types.

# Example Usage

One of the useful features of spatula are the spatial data concepts. These allow
you to use operations like addition on arbitrary 
```cpp
#include <spatula/geometry.hpp>
namespace sp = spatula;

template<sp::vector2 Vector>
Vector add2(Vector const & v)
{
    // addition has been defined for vector2 types
    return v + Vector(2, 2);
}

// since the point type satisfies the vector2 requirements,
// we can give it to a function that uses the addition operator
// even though we didn't explicitly define addition for the point type
struct point { int x; int y; };
int main()
{
    point a{1, 2};
    point b = add2(a);
}
```

# Installation

## Requirements

- compiler for C++20 or later

## Installation Instructions

```sh
mkdir build
cd build
cmake ..
sudo cmake --install .
```

If you're on windows, you can run `cmake --install .` on an adminstrator
shell instead of running the last command.

# Documentation

## Overview

- [geometry/vectors](#geometryvectorshpp)
    - [`concept basic_vector2`](#concept-basic_vector2)
    - [`concept vector2`](#concept_vector2)
    - [`bounding_corners2(points)`](#bounding_corners2points)
    - [comparing vectors](#comparing-vectors)
- [geometry/directions](#geometrydirectionshpp)
    - [`concept ranged_enum`](#concept-ranged_enum)
    - [`enum cardinal::direction_name`](#enum-cardinaldirection_name)
    - [`direction_as(dir)`](#direction_asdir)`

# geometry/vectors.hpp

## concept basic_vector2
A basic POD spatial type of 2 dimensions.

### Requirements
- default and copy constructible, and constructible from two numeric values
- has public numeric members x and y with the same type

### Signature
```cpp
template<class Vector>
concept basic_vector2 = std::default_initializable<Vector> and
                        std::copy_constructible<Vector> and
                        requires(Vector p) {

    p.x and std::is_arithmetic_v<std::remove_reference_t<decltype(p.x)>>;
    p.y and std::is_same_v<decltype(p.x), decltype(p.y)>;
    Vector(p.x, p.y);
};
```

### Examples

```cpp
#include <spatula/geometry.hpp>
#include <SDL.h>

template<sp::basic_vector2 Vector>
Vector add2(Vector const & p)
{
    return Vector(p.x + 2, p.y + 2);
}

// ...

SDL_Point const p(1, 2);
SDL_Point const q = add2(p); // (3, 4)
```

## concept vector2
A vector type of 2 dimensions.

### Requirements
- basic_vector2 requirements
- equality comparable
- closed under addition

### Signature
```cpp
template<class Vector>
concept vector2 = basic_vector2<Vector> and
                  std::equality_comparable<Vector> and
                  requires(Vector p) { { p + p } -> std::same_as<Vector>; };
```

### Examples

```cpp
#include <spatula/geometry.hpp>
#include <glm/glm.hpp>

template<sp::vector2 Vector>
Vector add2(Vector const & p)
{
    return p + Vector(2, 2);
}

// ...

glm::ivec2 const p(1, 2);
glm::ivec2 const q = add2(p); // (3, 4)
```

## bounding_corners2(points)

### Signature
```cpp
template<ranges::input_range Range>
    requires basic_vector2<ranges::range_value_t<Range>>
auto bounding_corners2(Range && points);
```

### Return
A pair of vectors (lower-left, upper-right), representing the bounding corners
of the input points.

### Parameters
- `points` the input points to find the boundary of

## comparing vectors
Compare vectors by their components.

```cpp
// compare u < v by their x-components
template<basic_vector2 Vector>
bool comparing_x2(Vector const & u, Vector const & v);
// comapre u < v by their y components
template<basic_vector2 Vector>
bool comparing_y2(Vector const & u, Vector const & v);
```

# geometry/directions.hpp

## concept ranged_enum
An enum with sequential values defined from [0, Enum::size).

### Signature
```cpp
template<class Enum>
concept ranged_enum = std::is_enum_v<Enum> and requires { Enum::size; };
```

### Requirements
- must be an enum type
- must have a `size` value

## enum cardinal::direction_name
The cardinal directions

### Members
- `cardinal::north`
- `cardinal::east`
- `cardinal::south`
- `cardinal::west`
- `cardinal::size`

## direction_as(dir)
Convert a direction as `ranged_enum` to a unit-vector

### Signature
```cpp
template<basic_vector2 Vector, ranged_enum Direction>
Vector const & direction_as(Direction dir);
```

### Return
A unit-vector representing the input direction

### Parameters
dir - the direction to represent

### Examples
```cpp
namespace cardinal = sp::cardinal;
sp::direction_as<SDL_Point, cardinal::direction_name> to_vector;
auto const & north = to_vector(cardinal::north);
```