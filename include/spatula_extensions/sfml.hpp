#pragma once

#include <SFML/System.hpp>
#include <tuple>
#include <cstddef>

//
// tuple size
//

template<typename Field>
struct std::tuple_size<sf::Vector2<Field>> {
    static constexpr const std::size_t value = 2;
};

template<typename Field>
struct std::tuple_size<sf::Vector3<Field>> {
    static constexpr const std::size_t value = 3;
};

//
// tuple element types
//

template<std::size_t i, typename Field>
    requires (i < 2)
struct std::tuple_element<i, sf::Vector2<Field>> {
    using type = typename std::add_const<Field>::type;
};

template<std::size_t i, typename Field>
    requires (i < 3)
struct std::tuple_element<i, sf::Vector3<Field>> {
    using type = typename std::add_const<Field>::type;
};
