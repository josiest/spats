---
layout: default
title: sp::has_3d_component
parent: components
grand_parent: vectors
---

# `sp::has_3d_component`

---

<pre>
template&lt;class Vector>
bool constexpr has_z_component = requires(Vector v) {
    <a href="../has_field_closure.html">sp::has_field_closure</a>&lt;decltype(v.z)>;
};
template&lt;class Vector>
bool constexpr has_Z_component = requires(Vector v) {
    <a href="../has_field_closure.html">sp::has_field_closure</a>&lt;decltype(v.Z)>;
};
template&lt;class Vector>
bool constexpr has_3d_component = requires(Vector v) {
    sp::has_z_component&lt;Vector> or sp::has_Z_component&lt;Vector> or
    <a href="">sp::has_nd_component</a>&lt;Vector, 2>;
};
</pre>

---

Determine if a type has a 3-dimensional component. This can be in the form of an
`z` member-field, an `Z` member-field, or a `2`nd element. The type of the
3-dimensional component must have field closure.

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

    std::cout << "=== glm::vec3 ===\n"
              << "glm::vec3 has a z-component: "
              << sp::has_z_component&lt;<a href="">glm::vec3</a>> << "\n"
              << "glm::vec3 has an Z-component: "
              << sp::has_Z_component&lt;<a href="">glm::vec3</a>> << "\n"
              << "glm::vec3 has a 3d-component: "
              << sp::has_3d_component&lt;<a href="">glm::vec3</a>> << "\n\n";

    std::cout << "=== Eigen::Vector3f ===\n"
              << "Eigen::Vector3f has an z-component: "
              << sp::has_z_component&lt;<a href="">Eigen::Vector3f</a>> << "\n"
              << "Eigen::Vector3f has an Z-component: "
              << sp::has_Z_component&lt;<a href="">Eigen::Vector3f</a>> << "\n"
              << "Eigen::Vector3f has a 3d-component: "
              << sp::has_3d_component&lt;<a href="">Eigen::Vector3f</a>> << "\n";

    // output:

    // === glm::vec3 ===
    // glm::vec3 has an z-component: true
    // glm::vec3 has an Z-component: false
    // glm::vec3 has a 3d-component: true
    // 
    // === Eigen::Vector3f ===
    // Eigen::Vector3f has an z-component: false
    // Eigen::Vector3f has an Z-component: false
    // Eigen::Vector3f has a 3d-component: true
}
</pre>
