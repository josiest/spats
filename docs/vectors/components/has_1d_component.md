---
layout: default
title: sp::has_1d_component
parent: components
grand_parent: vectors
---

# `sp::has_1d_component`

---

<pre>
template&lt;class Vector>
bool constexpr has_x_component = requires(Vector v) {
    <a href="../has_field_closure.html">sp::has_field_closure</a>&lt;decltype(v.x)>;
};
template&lt;class Vector>
bool constexpr has_X_component = requires(Vector v) {
    <a href="../has_field_closure.html">sp::has_field_closure</a>&lt;decltype(v.X)>;
};
template&lt;class Vector>
bool constexpr has_1d_component = requires(Vector v) {
    sp::has_x_component&lt;Vector> or sp::has_X_component&lt;Vector> or
    <a href="">sp::has_nd_component</a>&lt;Vector, 0>;
};
</pre>

---

Determine if a type has a 1-dimensional component. This can be in the form of an
`x` member-field, an `X` member-field, or a `0`th element. The type of the
1-dimensional component must have field closure.

## Examples

<pre>
#include &lt;iostream>
#include &lt;iomanip>

#include &lt;SDL2/SDL.h>
#include &lt;Eigen/Dense>
#include &lt;spatula_extensions/Eigen>

int main()
{
    std::cout << std::boolalpha;

    std::cout << "=== SDL_Point ===\n"
              << "SDL_Point has an x-component: "
              << sp::has_x_component&lt;<a href="https://wiki.libsdl.org/SDL_Point">SDL_Point</a>> << "\n"
              << "SDL_Point has an X-component: "
              << sp::has_X_component&lt;<a href="https://wiki.libsdl.org/SDL_Point">SDL_Point</a>> << "\n"
              << "SDL_Point has a 1d-component: "
              << sp::has_1d_component&lt;<a href="https://wiki.libsdl.org/SDL_Point">SDL_Point</a>> << "\n\n";

    std::cout << "=== Eigen::Vector2i ===\n"
              << "Eigen::Vector2i has an x-component: "
              << sp::has_x_component&lt;<a href="">Eigen::Vector2i</a>> << "\n"
              << "Eigen::Vector2i has an X-component: "
              << sp::has_X_component&lt;<a href="">Eigen::Vector2i</a>> << "\n"
              << "Eigen::Vector2i has a 1d-component: "
              << sp::has_1d_component&lt;<a href="">Eigen::Vector2i</a>> << "\n";

    // output:

    // === SDL_Point ===
    // SDL_Point has an x-component: true
    // SDL_Point has an X-component: false
    // SDL_Point has a 1d-component: true
    // 
    // === Eigen::Vector2i ===
    // Eigen::Vector2i has an x-component: false
    // Eigen::Vector2i has an X-component: false
    // Eigen::Vector2i has a 1d-component: true
}
</pre>
