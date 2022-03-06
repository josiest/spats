#include <catch2/catch.hpp>
#include "spatula/vectors.hpp"
#include <cstdint>
#include <complex>
#include <string>
#include <vector>

using namespace sp;

struct my_field2 {
    my_field2 & operator+=(my_field2 const & other) { return *this; }
    my_field2 & operator-=(my_field2 const & other) { return *this; }
    my_field2 & operator*=(my_field2 const & other) { return *this; }
    my_field2 & operator/=(my_field2 const & other) { return *this; }
};
my_field2 operator+(my_field2 const & a, my_field2 const & b)
{ return my_field2(a); }
my_field2 operator-(my_field2 const & a, my_field2 const & b)
{ return my_field2(a); }
my_field2 operator*(my_field2 const & a, my_field2 const & b)
{ return my_field2(a); }
my_field2 operator/(my_field2 const & a, my_field2 const & b)
{ return my_field2(a); }

struct nonfield2 {
};

TEST_CASE("field: signed integral types", "[field]")
{
    REQUIRE(field<std::int8_t>);
    REQUIRE(field<std::int16_t>);
    REQUIRE(field<std::int32_t>);
    REQUIRE(field<std::int64_t>);
}

TEST_CASE("field: unsigned integral types", "[field]")
{
    REQUIRE(field<std::uint8_t>);
    REQUIRE(field<std::uint16_t>);
    REQUIRE(field<std::uint32_t>);
    REQUIRE(field<std::uint64_t>);
}

TEST_CASE("field: floating point types", "[field]")
{
    REQUIRE(field<float>);
    REQUIRE(field<double>);
    REQUIRE(field<long double>);
}

TEST_CASE("field: compound types", "[field]")
{
    REQUIRE(field<std::complex<float>>);
    REQUIRE(field<std::complex<double>>);
    REQUIRE(field<std::complex<long double>>);
}

TEST_CASE("field: non fields", "[field]")
{
    REQUIRE(not field<std::string>);
    REQUIRE(not field<std::vector<double>>);
    REQUIRE(not field<nonfield2>);
    REQUIRE(not field<my_field2>);
}
