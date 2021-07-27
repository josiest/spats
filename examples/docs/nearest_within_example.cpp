#include "spatula/kdtree.hpp"
#include <iostream>
#include <string>
#include <vector>
#include <random>
#include <algorithm>

namespace sp = spatula;
using point = std::vector<double>;

// define how to print a vector
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

// create a random set of points to use for the kdtree
std::vector<point> random_points(size_t N)
{
    // set up random generator
    static std::random_device rd;
    static std::mt19937 rng{rd()};
    std::uniform_real_distribution<> dist(-50, 50);

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
    auto const points = random_points(5);
    auto const P = random_points(1);
    auto const p = P.front();
    std::cout << "generated points: " << points << std::endl;

    sp::kdtree index(points);

    // find the single nearest point to p within 50 units
    std::cout << "closest to " << p << ": "
              << index.nearest_within(p, 50.0) << std::endl;

    // find the three nearest points to p within 100 units
    std::cout << "3 closest to " << p << ": "
              << index.nearest_within(p, 100.0, 3) << std::endl;

    // find the nearest 20 points to p within 0.5 units
    std::cout << "20 closest to " << p << ": "
              << index.nearest_within(p, 0.5, 20) << std::endl;

    // find the three nearest points to p using the L1 norm within 50 units
    std::cout << "3 L1-closest to " << p << ": "
              << index.nearest_within(p, 50.0, 3, sp::L1) << std::endl;
}