#include <iostream>
#include <spatula/geometry.hpp>
namespace sp = spatula;

template<sp::vector2 Vector>
Vector add2(Vector const & v)
{
    return v + Vector(2, 2);
}

struct point { int x; int y; };

namespace std {
ostream & operator<<(ostream & os, point const & p)
{
    os << "{" << p.x << ", " << p.y << "}";
    return os;
}
}

int main()
{
    point const a{1, 2};
    point const b = add2(a);
    std::cout << "a: " << a << std::endl;
    std::cout << "b: " << b << std::endl;
}