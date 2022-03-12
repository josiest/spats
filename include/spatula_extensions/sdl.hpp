#pragma once

#include <SDL2/SDL.h>
#include <tuple>
#include <cstddef>

//
// tuple size
//

template<>
struct std::tuple_size<SDL_Point> {
    static constexpr const std::size_t value = 2;
};

template<>
struct std::tuple_size<SDL_Rect> {
    static constexpr const std::size_t value = 4;
};

template<>
struct std::tuple_size<SDL_Color> {
    static constexpr const std::size_t value = 4;
};

//
// tuple element types
//

template<std::size_t i>
    requires (i < 2)
struct std::tuple_element<i, SDL_Point> {
    using type = typename std::add_const<int>::type;
};

template<std::size_t i>
    requires (i < 4)
struct std::tuple_element<i, SDL_Rect> {
    using type = typename std::add_const<int>::type;
};

template<std::size_t i>
    requires (i < 4)
struct std::tuple_element<i, SDL_Color> {
    using type = typename std::add_const<Uint8>::type;
};
