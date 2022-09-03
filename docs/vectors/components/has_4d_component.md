---
layout: default
title: sp::has_4d_component
parent: components
grand_parent: vectors
---

# `sp::has_4d_component`

---

<pre>
template&lt;class Vector>
bool constexpr has_w_component = requires(Vector v) {
    <a href="../has_field_closure.html">sp::has_field_closure</a>&lt;decltype(v.w)>;
};
template&lt;class Vector>
bool constexpr has_W_component = requires(Vector v) {
    <a href="../has_field_closure.html">sp::has_field_closure</a>&lt;decltype(v.W)>;
};
template&lt;class Vector>
bool constexpr has_4d_component = requires(Vector v) {
    sp::has_w_component&lt;Vector> or sp::has_W_component&lt;Vector> or
    <a href="">sp::has_nd_component</a>&lt;Vector, 3>;
};
</pre>

---

Determine if a type has a 3-dimensional component. This can be in the form of an
`w` member-field, an `W` member-field, or a `3`rd element. The type of the
4-dimensional component must have field closure.

## Examples

<pre>
#include &lt;iostream>
#include &lt;iomanip>

#include &lt;glm/glm.hpp>
#include &lt;Eigen/Dense>
#include &lt;spatula_extensions/Eigen>

int main()
{
    std::cout << std::boolalpha;

    std::cout << "=== glm::vec4 ===\n"
              << "glm::vec3 has a w-component: "
              << sp::has_w_component&lt;<a href="">glm::vec4</a>> << "\n"
              << "glm::vec4 has an W-component: "
              << sp::has_W_component&lt;<a href="">glm::vec4</a>> << "\n"
              << "glm::vec4 has a 4d-component: "
              << sp::has_4d_component&lt;<a href="">glm::vec4</a>> << "\n\n";

    std::cout << "=== Eigen::Vector4f ===\n"
              << "Eigen::Vector4f has an w-component: "
              << sp::has_w_component&lt;<a href="">Eigen::Vector4f</a>> << "\n"
              << "Eigen::Vector4f has an W-component: "
              << sp::has_W_component&lt;<a href="">Eigen::Vector4f</a>> << "\n"
              << "Eigen::Vector4f has a 4d-component: "
              << sp::has_4d_component&lt;<a href="">Eigen::Vector4f</a>> << "\n";

    // output:

    // === glm::vec4 ===
    // glm::vec4 has an w-component: true
    // glm::vec4 has an W-component: false
    // glm::vec4 has a 4d-component: true
    // 
    // === Eigen::Vector4f ===
    // Eigen::Vector4f has an w-component: false
    // Eigen::Vector4f has an W-component: false
    // Eigen::Vector4f has a 4d-component: true
}
</pre>
