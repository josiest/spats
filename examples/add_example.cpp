#include <iostream>
#include <spatula/geometry.hpp>
#include <glm/glm.hpp>

template<sp::vector2 Vector>
Vector add2(Vector const & v)
{
    return v + Vector(2, 2);
}

namespace std {
ostream & operator<<(ostream & os, glm::ivec2 const & v)
{
    os << "(" << v.x << ", " << v.y << ")";
    return os;
}
}

int main()
{
    glm::ivec2 const a{1, 2};
    glm::ivec2 const b = add2(a);
    std::cout << "b: " << b << std::endl; // (3, 4)
}