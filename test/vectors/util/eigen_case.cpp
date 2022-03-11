TEST_CASE("get-${x}-component:Eigen:Vector${N}",
          "[get_component][Eigen][${x}-component][${N}D]") {

    Eigen::Vector${N}i v1${ivecstr};
    Eigen::Vector${N}f v2${fvecstr};
    Eigen::Vector${N}d v3${dvecstr};

    REQUIRE(get_${x}(v1) == ${ivec_x});
    REQUIRE(std::abs(get_${x}(v2)-(${fvec_x})) < 0.001f);
    REQUIRE(std::abs(get_${x}(v3)-(${dvec_x})) < 0.000000001);
}
