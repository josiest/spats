#include <spatula/vectors.hpp>
#include <string>
#include <iostream>

using namespace std::string_literals;

template<sp::semivector3 Vector>
auto dot(Vector const & a, Vector const & b)
{
    return sp::get_x(a) * sp::get_x(b) +
           sp::get_y(a) * sp::get_y(b) +
           sp::get_z(a) * sp::get_z(b);
}

template<sp::semivector3 Vector>
auto cross(Vector const & a, Vector const & b)
{
    return Vector{sp::get_y(a) * sp::get_z(b) - sp::get_z(a) * sp::get_y(b),
                  sp::get_z(a) * sp::get_x(b) - sp::get_x(a) * sp::get_z(b),
                  sp::get_x(a) * sp::get_y(b) - sp::get_y(a) * sp::get_x(b)};
}

int main()
{
    std::cout << "dot(\"foo\", \"bar\") = " << dot("foo"s, "bar"s) << "\n"
                 "cross(\"foo\", \"bar\") = " << cross("foo"s, "bar"s) << "\n";
}
