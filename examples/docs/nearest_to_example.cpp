#include "spatula/kdtree.hpp"
#include <iostream>
#include <string>
#include <vector>
#include <random>
#include <algorithm>

using point = std::vector<int>;

// define how to print a point
namespace std {
ostream & operator<<(ostream & os, point const & p)
{
    std::string sep = "";
    os << "(";
    for (size_t i = 0; i < std::size(p); i++) {
        os << sep << p[i];
        sep = ", ";
    }
    os << ")";
    return os;
}
}

// create a random set of points to use for the kdtree
std::vector<point> random_points(size_t N)
{
    // set up random generator
    static std::random_device rd;
    static std::mt19937 rng{rd()};
    std::uniform_int_distribution<> dist(0, 100);

    // create the points
    std::vector<point> points;
    points.reserve(N);  // reserve space as an optimization

    // using c++'s functional interface, so write a lambda for a single point
    auto random_point = [&dist]() { return point{dist(rng), dist(rng)}; };
    // and pass it as a generator function
    std::generate_n(std::back_inserter(points), N, random_point);
    return points;
}

int main()
{
    // create a random k-d tree
    namespace sp = spatula;
    auto const points = random_points(10);
    sp::kdtree index(points);

    std::cout << "generated points:";
    for (auto const & p : points) {
        std::cout << std::endl << p;
    }
    std::cout << std::endl << std::endl;

    // find the nearest single point to p
    {
        auto const p = random_points(1);
        auto const q = index.nearest_to(p.front());
        std::cout << "q size: " << q.size() << std::endl;
        std::cout << "closest to " << p.front() << ": "
                  << q.front() << std::endl << std::endl;
    }
    // find the three nearest points to p
    {
        // similarly here: 3 < 10 so there will always be exactly three points
        auto const p = random_points(1);
        auto const Q = index.nearest_to(p.front(), 3);
        std::cout << "Q size: " << Q.size() << std::endl;
        std::cout << "closest to " << p.front() << ": "
                  << Q[0] << ", " << Q[1] << ", " << Q[2]
                  << std::endl << std::endl;
    }
    // find the nearest 20 points to p
    {
        // here we can't use structured bindings because there are less points
        // in the tree than the amount of points specified
        auto const p = random_points(1);
        auto const Q = index.nearest_to(p.front(), 20);

        std::cout << "Q size: " << Q.size() << std::endl;
        std::cout << "closest to " << p.front() << ":";
        for (point const & q : Q) {
            std::cout << std::endl << "  " << q;
        }
        std::cout << std::endl;
    }
}
