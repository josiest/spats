# spatula

A simple header-only library for manipulating spatial data of arbitrary types.

# Example Usage

One of the useful features of spatula are the spatial data concepts. These allow
you to use operations like addition on arbitrary 
```cpp
#include <spatula/math.hpp>
#inlcude <glm/glm.hpp>
#include <SDL2/SDL.h>
#include <iostream>

auto dot(sp::semivector2 auto const & a, sp::semivector2 auto const & b)
{
    return a.x * b.x + a.y * b.y;
}

int main()
{
    glm::ivec2 const a(1, 2);
    SDL_Point const b(3, 4);
    std::cout << dot(a, b) << "\n"; // 11
}
```

# Installation

## Requirements

- compiler for C++20 or later
- cmake

## Installation Instructions

```sh
git clone https://github.com/josiest/spatula.git
cd spatula
mkdir build
cd build
cmake ..
sudo cmake --install .
```

If you're on windows, you can run `cmake --install .` on an adminstrator
shell instead of running the last command.

# Documentation

The documentation is [hosted here](https://josiest.github.io/spatula/)
