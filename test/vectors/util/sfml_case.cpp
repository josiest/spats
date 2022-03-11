TEST_CASE("get-${x}-component:SFML:Vector${N}",
          "[get_component][SFML][${x}-component][${N}D]") {

    sf::Vector${N}i v1${ivecstr};
    sf::Vector${N}f v2${fvecstr};

    REQUIRE(get_${x}(v1) == ${ivec_x});
    REQUIRE(std::abs(get_${x}(v2)-(${fvec_x})) < 0.001f);
}
