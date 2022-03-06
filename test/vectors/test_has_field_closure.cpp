#include <catch2/catch.hpp>
#include "spatula/vectors.hpp"
#include <cstdint>
#include <complex>
#include <string>
#include <vector>

using namespace sp;

struct my_field {
    my_field & operator+=(my_field const & other) { return *this; }
    my_field & operator-=(my_field const & other) { return *this; }
    my_field & operator*=(my_field const & other) { return *this; }
    my_field & operator/=(my_field const & other) { return *this; }
};
my_field operator+(my_field const & a, my_field const & b)
{ return my_field(a); }
my_field operator-(my_field const & a, my_field const & b)
{ return my_field(a); }
my_field operator*(my_field const & a, my_field const & b)
{ return my_field(a); }
my_field operator/(my_field const & a, my_field const & b)
{ return my_field(a); }

struct nonfield {
};

TEST_CASE("signed integral types", "[has_field_closure]")
{
    REQUIRE(has_field_closure<std::int8_t>);
    REQUIRE(has_field_closure<std::int16_t>);
    REQUIRE(has_field_closure<std::int32_t>);
    REQUIRE(has_field_closure<std::int64_t>);
}

TEST_CASE("unsigned integral types", "[has_field_closure]")
{
    REQUIRE(has_field_closure<std::uint8_t>);
    REQUIRE(has_field_closure<std::uint16_t>);
    REQUIRE(has_field_closure<std::uint32_t>);
    REQUIRE(has_field_closure<std::uint64_t>);
}

TEST_CASE("floating point types", "[has_field_closure]")
{
    REQUIRE(has_field_closure<float>);
    REQUIRE(has_field_closure<double>);
    REQUIRE(has_field_closure<long double>);
}

TEST_CASE("compound types", "[has_field_closure]")
{
    REQUIRE(has_field_closure<std::complex<float>>);
    REQUIRE(has_field_closure<std::complex<double>>);
    REQUIRE(has_field_closure<std::complex<long double>>);
    REQUIRE(has_field_closure<my_field>);
}

TEST_CASE("non fields", "[has_field_closure]")
{
    REQUIRE(not has_field_closure<std::string>);
    REQUIRE(not has_field_closure<std::vector<double>>);
    REQUIRE(not has_field_closure<nonfield>);
}
