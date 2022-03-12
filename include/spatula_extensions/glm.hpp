#pragma once

#include <glm/glm.hpp>
#include <tuple>
#include <cstddef>

template<>
struct std::tuple_size<glm::vec2> {
    static constexpr std::size_t value = 2;
};

template<>
struct std::tuple_size<glm::vec3> {
    static constexpr std::size_t value = 3;
};

template<>
struct std::tuple_size<glm::vec4> {
    static constexpr std::size_t value = 4;
};

template<>
struct std::tuple_size<glm::dvec2> {
    static constexpr std::size_t value = 2;
};

template<>
struct std::tuple_size<glm::dvec3> {
    static constexpr std::size_t value = 3;
};

template<>
struct std::tuple_size<glm::dvec4> {
    static constexpr std::size_t value = 4;
};

template<>
struct std::tuple_size<glm::ivec2> {
    static constexpr std::size_t value = 2;
};

template<>
struct std::tuple_size<glm::ivec3> {
    static constexpr std::size_t value = 3;
};

template<>
struct std::tuple_size<glm::ivec4> {
    static constexpr std::size_t value = 4;
};

template<>
struct std::tuple_size<glm::uvec2> {
    static constexpr std::size_t value = 2;
};

template<>
struct std::tuple_size<glm::uvec3> {
    static constexpr std::size_t value = 3;
};

template<>
struct std::tuple_size<glm::uvec4> {
    static constexpr std::size_t value = 4;
};
