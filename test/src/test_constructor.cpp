#include <gtest/gtest.h>

#include "spatula/kdtree.hpp"

#include <vector>
#include <stdexcept>

TEST(KDTreeConstructorTest, InconsistentDimensions)
{
    using point = std::vector<int>;
    using kdtree = spatula::kdtree<point>;

    std::vector<point> points;
    points.push_back(point{0, 2});
    points.push_back(point{1, -23, 3});
    points.push_back(point{-2, 1});

    EXPECT_THROW(kdtree(points.begin(), points.end()), std::invalid_argument);
}
