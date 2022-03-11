TEST_CASE("get-${x}-component:glm:vec${N}",
          "[get_component][glm][${x}-component][${N}D]") {

    glm::ivec${N} v1${ivecstr};
    glm::uvec${N} v2${uvecstr};
    glm::vec${N} v3${fvecstr};
    glm::dvec${N} v4${dvecstr};

    REQUIRE(get_${x}(v1) == ${ivec_x});
    REQUIRE(get_${x}(v2) == ${uvec_x});
    REQUIRE(std::abs(get_${x}(v3)-(${fvec_x})) < 0.001f);
    REQUIRE(std::abs(get_${x}(v4)-(${dvec_x})) < 0.000000001);
}
