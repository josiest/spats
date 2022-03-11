#pragma once

#include "spatula/vectors.hpp"
#include <Eigen/Dense>
#include <cstddef>
#include <tuple>

template<sp::field Field>
struct std::tuple_size<Eigen::Matrix<Field, 2, 1>> {
    static constexpr const std::size_t value = 2;
};

template<sp::field Field>
struct std::tuple_size<Eigen::Matrix<Field, 3, 1>> {
    static constexpr const std::size_t value = 3;
};

template<sp::field Field>
struct std::tuple_size<Eigen::Matrix<Field, 4, 1>> {
    static constexpr const std::size_t value = 4;
};
