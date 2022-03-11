#include <catch2/catch.hpp>
#include "spatula/vectors.hpp"

#include <SDL2/SDL.h>
#include <SFML/System.hpp>
#include <glm/vec2.hpp>
#include <glm/vec3.hpp>
#include <glm/vec4.hpp>
#include <Eigen/Dense>
#include <spatula_extensions/eigen.hpp>

#include <vector>
#include <string>

#include <cmath>

using namespace sp;

TEST_CASE("get-x-component:SDL", "[get_component][SDL][x-component][2D]") {
    SDL_Point points[] = {
        {0, 0}, {1, 2}, {-12, -3}, {1304, -1982}, {-802920, 29318}
    };
    REQUIRE(get_x(points[0]) == 0);
    REQUIRE(get_x(points[1]) == 1);
    REQUIRE(get_x(points[2]) == -12);
    REQUIRE(get_x(points[3]) == 1304);
    REQUIRE(get_x(points[4]) == -802920);
}

TEST_CASE("get-y-component:SDL", "[get_component][SDL][y-component][2D]") {
    SDL_Point points[] = {
        {-132, 201031}, {0, 0}, {213, 123}, {90293, -1293}, {-12, -2}
    };
    REQUIRE(get_y(points[0]) == 201031);
    REQUIRE(get_y(points[1]) == 0);
    REQUIRE(get_y(points[2]) == 123);
    REQUIRE(get_y(points[3]) == -1293);
    REQUIRE(get_y(points[4]) == -2);
}

TEST_CASE("get-x-component:SFML:Vector2",
          "[get_component][SFML][x-component][2D]") {

    sf::Vector2i v1{139, 79};
    sf::Vector2f v2{191.993, -45.886};

    REQUIRE(get_x(v1) == 139);
    REQUIRE(std::abs(get_x(v2)-(191.993)) < 0.001f);
}


TEST_CASE("get-y-component:SFML:Vector2",
          "[get_component][SFML][y-component][2D]") {

    sf::Vector2i v1{-497, -424};
    sf::Vector2f v2{82.424, 128.926};

    REQUIRE(get_y(v1) == -424);
    REQUIRE(std::abs(get_y(v2)-(128.926)) < 0.001f);
}


TEST_CASE("get-x-component:SFML:Vector3",
          "[get_component][SFML][x-component][3D]") {

    sf::Vector3i v1{34, 425, -292};
    sf::Vector3f v2{-150.912, -92.02, 118.632};

    REQUIRE(get_x(v1) == 34);
    REQUIRE(std::abs(get_x(v2)-(-150.912)) < 0.001f);
}


TEST_CASE("get-y-component:SFML:Vector3",
          "[get_component][SFML][y-component][3D]") {

    sf::Vector3i v1{231, 135, 9};
    sf::Vector3f v2{-103.076, -132.276, -31.937};

    REQUIRE(get_y(v1) == 135);
    REQUIRE(std::abs(get_y(v2)-(-132.276)) < 0.001f);
}


TEST_CASE("get-z-component:SFML:Vector3",
          "[get_component][SFML][z-component][3D]") {

    sf::Vector3i v1{352, 492, 137};
    sf::Vector3f v2{-7.11, 52.727, 18.383};

    REQUIRE(get_z(v1) == 137);
    REQUIRE(std::abs(get_z(v2)-(18.383)) < 0.001f);
}

TEST_CASE("get-x-component:glm:vec2",
          "[get_component][glm][x-component][2D]") {

    glm::ivec2 v1{506, -281};
    glm::uvec2 v2{431, 72};
    glm::vec2 v3{123.634, 46.896};
    glm::dvec2 v4{117.257328241, -128.010158947};

    REQUIRE(get_x(v1) == 506);
    REQUIRE(get_x(v2) == 431);
    REQUIRE(std::abs(get_x(v3)-(123.634)) < 0.001f);
    REQUIRE(std::abs(get_x(v4)-(117.257328241)) < 0.000000001);
}


TEST_CASE("get-y-component:glm:vec2",
          "[get_component][glm][y-component][2D]") {

    glm::ivec2 v1{48, 144};
    glm::uvec2 v2{245, 5};
    glm::vec2 v3{-141.22, 63.105};
    glm::dvec2 v4{-80.151155146, -198.778732169};

    REQUIRE(get_y(v1) == 144);
    REQUIRE(get_y(v2) == 5);
    REQUIRE(std::abs(get_y(v3)-(63.105)) < 0.001f);
    REQUIRE(std::abs(get_y(v4)-(-198.778732169)) < 0.000000001);
}


TEST_CASE("get-x-component:glm:vec3",
          "[get_component][glm][x-component][3D]") {

    glm::ivec3 v1{-214, -78, -428};
    glm::uvec3 v2{302, 160, 84};
    glm::vec3 v3{-161.017, 180.344, -17.013};
    glm::dvec3 v4{-61.575280948, -144.05264325, 67.752950049};

    REQUIRE(get_x(v1) == -214);
    REQUIRE(get_x(v2) == 302);
    REQUIRE(std::abs(get_x(v3)-(-161.017)) < 0.001f);
    REQUIRE(std::abs(get_x(v4)-(-61.575280948)) < 0.000000001);
}


TEST_CASE("get-y-component:glm:vec3",
          "[get_component][glm][y-component][3D]") {

    glm::ivec3 v1{-308, -382, -3};
    glm::uvec3 v2{987, 718, 349};
    glm::vec3 v3{-26.507, -88.923, 43.661};
    glm::dvec3 v4{59.018942774, -18.545242682, 174.725346227};

    REQUIRE(get_y(v1) == -382);
    REQUIRE(get_y(v2) == 718);
    REQUIRE(std::abs(get_y(v3)-(-88.923)) < 0.001f);
    REQUIRE(std::abs(get_y(v4)-(-18.545242682)) < 0.000000001);
}


TEST_CASE("get-z-component:glm:vec3",
          "[get_component][glm][z-component][3D]") {

    glm::ivec3 v1{394, 480, -152};
    glm::uvec3 v2{543, 883, 752};
    glm::vec3 v3{-163.434, -25.002, -45.242};
    glm::dvec3 v4{141.876156454, -86.309305674, 185.952659437};

    REQUIRE(get_z(v1) == -152);
    REQUIRE(get_z(v2) == 752);
    REQUIRE(std::abs(get_z(v3)-(-45.242)) < 0.001f);
    REQUIRE(std::abs(get_z(v4)-(185.952659437)) < 0.000000001);
}


TEST_CASE("get-x-component:glm:vec4",
          "[get_component][glm][x-component][4D]") {

    glm::ivec4 v1{489, 158, -420, -155};
    glm::uvec4 v2{648, 918, 660, 339};
    glm::vec4 v3{188.414, -189.35, 170.647, -148.846};
    glm::dvec4 v4{64.64113486, 13.02307201, -31.461906864, 181.570732635};

    REQUIRE(get_x(v1) == 489);
    REQUIRE(get_x(v2) == 648);
    REQUIRE(std::abs(get_x(v3)-(188.414)) < 0.001f);
    REQUIRE(std::abs(get_x(v4)-(64.64113486)) < 0.000000001);
}


TEST_CASE("get-y-component:glm:vec4",
          "[get_component][glm][y-component][4D]") {

    glm::ivec4 v1{100, 145, -306, -224};
    glm::uvec4 v2{952, 987, 497, 315};
    glm::vec4 v3{-34.044, -176.042, 171.26, -194.96};
    glm::dvec4 v4{-114.941396239, 131.039751875, 193.950648706, 24.365400049};

    REQUIRE(get_y(v1) == 145);
    REQUIRE(get_y(v2) == 987);
    REQUIRE(std::abs(get_y(v3)-(-176.042)) < 0.001f);
    REQUIRE(std::abs(get_y(v4)-(131.039751875)) < 0.000000001);
}


TEST_CASE("get-z-component:glm:vec4",
          "[get_component][glm][z-component][4D]") {

    glm::ivec4 v1{230, 13, -201, -178};
    glm::uvec4 v2{847, 39, 856, 601};
    glm::vec4 v3{-157.872, 18.41, 195.857, 199.467};
    glm::dvec4 v4{80.436054535, 82.624766256, -134.077016859, -188.96129855};

    REQUIRE(get_z(v1) == -201);
    REQUIRE(get_z(v2) == 856);
    REQUIRE(std::abs(get_z(v3)-(195.857)) < 0.001f);
    REQUIRE(std::abs(get_z(v4)-(-134.077016859)) < 0.000000001);
}


TEST_CASE("get-w-component:glm:vec4",
          "[get_component][glm][w-component][4D]") {

    glm::ivec4 v1{-114, 127, -483, 64};
    glm::uvec4 v2{449, 597, 528, 969};
    glm::vec4 v3{-173.646, -191.755, -166.435, -83.942};
    glm::dvec4 v4{146.604857233, -184.949293132, 142.750842472, 35.922946805};

    REQUIRE(get_w(v1) == 64);
    REQUIRE(get_w(v2) == 969);
    REQUIRE(std::abs(get_w(v3)-(-83.942)) < 0.001f);
    REQUIRE(std::abs(get_w(v4)-(35.922946805)) < 0.000000001);
}

TEST_CASE("get-x-component:Eigen:Vector2",
          "[get_component][Eigen][x-component][2D]") {

    Eigen::Vector2i v1{-323, -419};
    Eigen::Vector2f v2{-126.329, 34.431};
    Eigen::Vector2d v3{-52.6735703, -122.706620738};

    REQUIRE(get_x(v1) == -323);
    REQUIRE(std::abs(get_x(v2)-(-126.329)) < 0.001f);
    REQUIRE(std::abs(get_x(v3)-(-52.6735703)) < 0.000000001);
}

TEST_CASE("get-y-component:Eigen:Vector2",
          "[get_component][Eigen][y-component][2D]") {

    Eigen::Vector2i v1{-336, 141};
    Eigen::Vector2f v2{-96.81, 104.258};
    Eigen::Vector2d v3{166.203933633, -42.964165336};

    REQUIRE(get_y(v1) == 141);
    REQUIRE(std::abs(get_y(v2)-(104.258)) < 0.001f);
    REQUIRE(std::abs(get_y(v3)-(-42.964165336)) < 0.000000001);
}

TEST_CASE("get-x-component:Eigen:Vector3",
          "[get_component][Eigen][x-component][3D]") {

    Eigen::Vector3i v1{-103, 322, 361};
    Eigen::Vector3f v2{-59.881, 4.698, -56.365};
    Eigen::Vector3d v3{32.904075043, 59.567718179, -175.674152018};

    REQUIRE(get_x(v1) == -103);
    REQUIRE(std::abs(get_x(v2)-(-59.881)) < 0.001f);
    REQUIRE(std::abs(get_x(v3)-(32.904075043)) < 0.000000001);
}

TEST_CASE("get-y-component:Eigen:Vector3",
          "[get_component][Eigen][y-component][3D]") {

    Eigen::Vector3i v1{239, 28, -38};
    Eigen::Vector3f v2{193.657, 36.69, 5.387};
    Eigen::Vector3d v3{142.941076184, -127.239538643, 199.290927905};

    REQUIRE(get_y(v1) == 28);
    REQUIRE(std::abs(get_y(v2)-(36.69)) < 0.001f);
    REQUIRE(std::abs(get_y(v3)-(-127.239538643)) < 0.000000001);
}

TEST_CASE("get-z-component:Eigen:Vector3",
          "[get_component][Eigen][z-component][3D]") {

    Eigen::Vector3i v1{-381, -151, -188};
    Eigen::Vector3f v2{51.136, -78.125, -175.683};
    Eigen::Vector3d v3{-132.962282796, 25.524327517, 142.508097104};

    REQUIRE(get_z(v1) == -188);
    REQUIRE(std::abs(get_z(v2)-(-175.683)) < 0.001f);
    REQUIRE(std::abs(get_z(v3)-(142.508097104)) < 0.000000001);
}

TEST_CASE("get-x-component:Eigen:Vector4",
          "[get_component][Eigen][x-component][4D]") {

    Eigen::Vector4i v1{215, 396, 485, -462};
    Eigen::Vector4f v2{-33.26, 74.581, 93.177, -134.978};
    Eigen::Vector4d v3{34.843250203, 197.853018379, -32.809700429, 175.167994087};

    REQUIRE(get_x(v1) == 215);
    REQUIRE(std::abs(get_x(v2)-(-33.26)) < 0.001f);
    REQUIRE(std::abs(get_x(v3)-(34.843250203)) < 0.000000001);
}

TEST_CASE("get-y-component:Eigen:Vector4",
          "[get_component][Eigen][y-component][4D]") {

    Eigen::Vector4i v1{-195, 6, 444, 418};
    Eigen::Vector4f v2{-87.331, -49.295, -163.219, -24.731};
    Eigen::Vector4d v3{82.219613967, 68.134990682, 47.288059209, -193.222816507};

    REQUIRE(get_y(v1) == 6);
    REQUIRE(std::abs(get_y(v2)-(-49.295)) < 0.001f);
    REQUIRE(std::abs(get_y(v3)-(68.134990682)) < 0.000000001);
}

TEST_CASE("get-z-component:Eigen:Vector4",
          "[get_component][Eigen][z-component][4D]") {

    Eigen::Vector4i v1{-477, -12, 50, 495};
    Eigen::Vector4f v2{-113.444, 184.105, 181.774, 38.31};
    Eigen::Vector4d v3{103.993891681, -174.832994925, -6.836492297, 174.404977151};

    REQUIRE(get_z(v1) == 50);
    REQUIRE(std::abs(get_z(v2)-(181.774)) < 0.001f);
    REQUIRE(std::abs(get_z(v3)-(-6.836492297)) < 0.000000001);
}

TEST_CASE("get-w-component:Eigen:Vector4",
          "[get_component][Eigen][w-component][4D]") {

    Eigen::Vector4i v1{411, -56, 244, -303};
    Eigen::Vector4f v2{192.998, -75.761, 27.28, -108.01};
    Eigen::Vector4d v3{15.592886782, -152.594140398, 79.561179573, -178.964285323};

    REQUIRE(get_w(v1) == -303);
    REQUIRE(std::abs(get_w(v2)-(-108.01)) < 0.001f);
    REQUIRE(std::abs(get_w(v3)-(-178.964285323)) < 0.000000001);
}
