---
layout: default
title: spatula
nav_order: 1
---

# What is spatula?

Spatula is a header only library that provides concepts for working with spatial
data types.

## Example Usage

```cpp
#include <spatula/math.hpp>
#include <glm/glm.hpp>
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

# Installing

### Requirements
- compiler for C++20 or later
- cmake >= 18.0

### Installation Instructions

```sh
git clone https://github.com/josiest/spatula.git
cd spatula
mkdir build
cd build
cmake ..
sudo cmake --install .
```

If you're on windows, you can run `cmake --install .` on an adminstrator shell
instead of running the last command.
