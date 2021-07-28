#include "spatula.hpp"
#include <vector>
#include <iostream>
#include <string>

// define some useful aliases
namespace sp = spatula;
using point = std::vector<int>;

// define how to print a vector
#ifndef DEBUG
namespace std {
template<typename T>
ostream & operator<<(ostream & os, vector<T> const & v)
{
    string sep = "";
    os << "{";
    for (auto const & e : v) {
        os << sep << e;
        sep = ", ";
    }
    os << "}";
    return os;
}
}
#endif

int main()
{
    point const origin{0, 0};

    // create the point set to be used for the k-d tree
    std::vector<point> points{point{0, 0}, point{0, 1}, point{1, 0}};

    // create tree from iterators
    // note: we need to specify the type because C++ doesn't know to deduce the
    //  underlying type from iterators
    sp::kdtree<point> tree1(points.begin(), points.end());
    std::cout << "closest to origin: " << tree1.nearest_to(origin) << std::endl;

    // on the other hand, the type can be deduced from a vector
    sp::kdtree tree2(points);
    std::cout << "closest to origin: " << tree2.nearest_to(origin, 3) << std::endl;

    // alternatively, you can also construct from an initializer list
    sp::kdtree<point> tree3 = {point{1, 2}, point{1, -1}, point{5, 6}};
    std::cout << "closest to origin: " << tree3.nearest_to(origin, 3) << std::endl;
}
