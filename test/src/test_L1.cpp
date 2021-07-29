#include <gtest/gtest.h>
#include "spatula/geometry.hpp"

#include "util.hpp"
#include <vector>

#include <cstdlib>
#include <stdexcept>

namespace sp = spatula;

TEST(L1Test, BetweenOrigin)
{
    using point = std::vector<int>;
    constexpr auto dist = sp::L1<point>;

    point const a{0, 0};
    point const b{0, 0};
    EXPECT_EQ(dist(a, b), 0);
}

TEST(L1Test, BetweenOriginCustomPoint)
{
    using point = Vector2i;
    constexpr auto dist = sp::L1<point>;

    point const a{0, 0};
    point const b{0, 0};
    EXPECT_EQ(dist(a, b), 0);
}

TEST(L1Test, BetweenRandomIntVecAndOrigin)
{
    using point = Vector2i;
    constexpr auto dist = sp::L1<point>;

    point const a{0, 0};
    point const b{-2, -14};
    EXPECT_EQ(dist(a, b), 16);
}

TEST(L1Test, BetweenRandomRealVecAndOrigin)
{
    using point = std::vector<double>;
    constexpr auto dist = sp::L1<point>;

    point const a{0.05, -0.16, 0.21};
    point const b{0, 0, 0};
    EXPECT_LT(std::abs(dist(a, b) - 0.42), 0.01);
}

TEST(L1Test, BetweenRandomRealPoints)
{
    using point = std::vector<float>;
    constexpr auto dist = sp::L1<point>;

    
    point const a{-278.8, 109.5, 327.5, -60.48, -89.56};
    point const b{-77.01, -333.2, -122.6, 256.2, -140.9};
    EXPECT_LT(std::abs(dist(a, b) - 1463), 1);
}

TEST(L1Test, BetweenIncompatibleDimensions)
{
    using point = std::vector<double>;
    constexpr auto dist = sp::L1<point>;

    point const a{-1, -2};
    point const b{-3, -4, -5};
    EXPECT_THROW(dist(a, b), std::invalid_argument);
}
