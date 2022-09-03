---
layout: default
title: sp::has_2d_component
parent: components
grand_parent: vectors
---

# `sp::has_2d_component`

---

<pre>
template&lt;class Vector>
bool constexpr has_y_component = requires(Vector v) {
    <a href="../has_field_closure.html">sp::has_field_closure</a>&lt;decltype(v.y)>;
};
template&lt;class Vector>
bool constexpr has_Y_component = requires(Vector v) {
    <a href="../has_field_closure.html">sp::has_field_closure</a>&lt;decltype(v.Y)>;
};
template&lt;class Vector>
bool constexpr has_2d_component = requires(Vector v) {
    sp::has_y_component&lt;Vector> or sp::has_Y_component&lt;Vector> or
    <a href="">sp::has_nd_component</a>&lt;Vector, 1>;
};
</pre>

---

Determine if a type has a 2-dimensional component. This can be in the form of an
`y` member-field, an `Y` member-field, or a `1`st element. The type of the
2-dimensional component must have field closure.

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
              << "SDL_Point has an y-component: "
              << sp::has_y_component&lt;<a href="https://wiki.libsdl.org/SDL_Point">SDL_Point</a>> << "\n"
              << "SDL_Point has an Y-component: "
              << sp::has_Y_component&lt;<a href="https://wiki.libsdl.org/SDL_Point">SDL_Point</a>> << "\n"
              << "SDL_Point has a 2d-component: "
              << sp::has_2d_component&lt;<a href="https://wiki.libsdl.org/SDL_Point">SDL_Point</a>> << "\n\n";

    std::cout << "=== Eigen::Vector2i ===\n"
              << "Eigen::Vector2i has an y-component: "
              << sp::has_y_component&lt;<a href="">Eigen::Vector2i</a>> << "\n"
              << "Eigen::Vector2i has an Y-component: "
              << sp::has_Y_component&lt;<a href="">Eigen::Vector2i</a>> << "\n"
              << "Eigen::Vector2i has a 2d-component: "
              << sp::has_2d_component&lt;<a href="">Eigen::Vector2i</a>> << "\n";

    // output:

    // === SDL_Point ===
    // SDL_Point has an y-component: true
    // SDL_Point has an Y-component: false
    // SDL_Point has a 2d-component: true
    // 
    // === Eigen::Vector2i ===
    // Eigen::Vector2i has an y-component: false
    // Eigen::Vector2i has an Y-component: false
    // Eigen::Vector2i has a 2d-component: true
}
</pre>
