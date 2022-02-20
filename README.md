# spatula

A simple header-only library for algorithms and datastructures for spatial data

## Example Usage

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

## Requirements

- compiler for C++20 or later