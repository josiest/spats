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
- [geometry/directions](#geometrydirectionshpp)
    - [`concept ranged_enum`](#concept-ranged_enum)
    - [`enum cardinal::direction_name`](#enum-cardinaldirection_name)
    - [`cardinal::direction_as(dir)`](#cardinaldirection_asdir)`

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

## cardinal::direction_as(dir)
The vector associated with a cardinal direction

### Signature
```cpp
template<basic_vector2 Vector>
Vector const &
direction_as(cardinal::direction_name dir);
```

### Return
A unit-vector representing the input direction

### Parameters
dir - the direction to represent

### Notes
Behavior is undefined when `dir == cardinal::direction_name::size`

### Examples
```cpp
using namespace sp::cardinal;
auto const & north = direction_as<SDL_Point>(direction_name::north);
```