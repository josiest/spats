#pragma once

#include <vector>
#include <stdexcept>
#include <iostream>
#include <string>
#include <boost/functional/hash.hpp>

namespace std {
template<typename num_t>
inline ostream & operator<<(ostream & os, vector<num_t> const & v)
{
    string sep = "";
    os << "(";
    for (auto e : v) {
        os << sep << e;
        sep = ", ";
    }
    os << ")";
    return os;
}
}

struct Vector2i {
    int x, y;
    inline int & operator[](size_t i) {
        switch (i) {
        case 0:
            return x;
        case 1:
            return y;
        default:
            throw std::out_of_range{"index must be at most 1"};
        }
    }
    inline int const & operator[](size_t i) const {
        switch (i) {
        case 0:
            return x;
        case 1:
            return y;
        default:
            throw std::out_of_range{"index must be at most 1"};
        }
    }
    inline constexpr size_t size() const noexcept { return 2; }
};
inline bool operator==(Vector2i const & lhs, Vector2i const & rhs)
{
    return lhs.x == rhs.x && lhs.y == rhs.y;
}
namespace std
{
template<> struct hash<Vector2i>
{
    std::size_t operator()(Vector2i const & v) const noexcept
    {
        std::size_t seed = 0;
        boost::hash_combine(seed, v.x);
        boost::hash_combine(seed, v.y);
        return seed;
    }
};
inline ostream & operator<<(ostream & os, Vector2i const & v)
{
    os << "(" << v.x << ", " << v.y << ")";
    return os;
}
}

struct Vector3d {
    double x, y, z;
    inline double & operator[](size_t i)
    {
        switch (i) {
        case 0:
            return x;
        case 1:
            return y;
        case 2:
            return z;
        default:
            throw std::out_of_range{"index must be at most 2"};
        }
    }
    inline double const & operator[](size_t i) const
    {
        switch (i) {
        case 0:
            return x;
        case 1:
            return y;
        case 2:
            return z;
        default:
            throw std::out_of_range{"index must be at most 2"};
        }
    }
    inline constexpr size_t size() const noexcept { return 3; }
};
inline bool operator==(Vector3d const & lhs, Vector3d const & rhs)
{
    return lhs.x == rhs.x && lhs.y == rhs.y && lhs.z == rhs.z;
}
namespace std
{
template<> struct hash<Vector3d>
{
    std::size_t operator()(Vector3d const & v) const noexcept
    {
        std::size_t seed = 0;
        boost::hash_combine(seed, v.x);
        boost::hash_combine(seed, v.y);
        boost::hash_combine(seed, v.z);
        return seed;
    }
};
inline ostream & operator<<(ostream & os, Vector3d const & v)
{
    os << "(" << v.x << ", " << v.y << ", " << v.z << ")";
    return os;
}
}

