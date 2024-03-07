#include <spatula/vectors.hpp>
#include <iostream>
#include <array>

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
    // will not compile because strings are not numeric:
    // std::cout << "dot(\"foo\", \"bar\") = " << dot("foo"s, "bar"s) << "\n"
    //              "cross(\"foo\", \"bar\") = " << cross("foo"s, "bar"s) << "\n";

    constexpr std::array a{1, 2, 3};
    constexpr std::array b{3, 2, 1};
    const auto c = cross(a, b);
    std::cout << "dot([1, 2, 3], [3, 2, 1]) = " << dot(a, b) << "\n"
              << "cross([1, 2, 3], [3, 2, 1]) = ["
              << c[0] << ", " << c[1] << ", " << c[2] << "]\n";
}
