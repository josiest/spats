#pragma once

#include <Eigen/Dense>
#include <tuple>
#include <cstddef>

//
// tuple size
//

template<typename Field>
struct std::tuple_size<Eigen::Matrix<Field, 2, 1>> {
    static constexpr const std::size_t value = 2;
};

template<typename Field>
struct std::tuple_size<Eigen::Matrix<Field, 3, 1>> {
    static constexpr const std::size_t value = 3;
};

template<typename Field>
struct std::tuple_size<Eigen::Matrix<Field, 4, 1>> {
    static constexpr const std::size_t value = 4;
};

//
// tuple element types
//

template<std::size_t i, typename Field>
    requires (i < 2)
struct std::tuple_element<i, Eigen::Matrix<Field, 2, 1>> {
    using type = typename std::add_const<Field>::type;
};

template<std::size_t i, typename Field>
    requires (i < 3)
struct std::tuple_element<i, Eigen::Matrix<Field, 3, 1>> {
    using type = typename std::add_const<Field>::type;
};

template<std::size_t i, typename Field>
    requires (i < 4)
struct std::tuple_element<i, Eigen::Matrix<Field, 4, 1>> {
    using type = typename std::add_const<Field>::type;
};
