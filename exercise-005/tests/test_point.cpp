#include <catch2/catch_test_macros.hpp>
#include "../../exercise-004/point.cpp"

TEST_CASE("Point: Konstruktoren") {
    SECTION("Init mit Werten") {
        Point p{2, 3};
        REQUIRE(p.x == 2);
        REQUIRE(p.y == 3);
    }
    SECTION("Default-Konstruktor") {
        Point p;
        REQUIRE(p.x == 0);
        REQUIRE(p.y == 0);
    }
}

TEST_CASE("Point: move verschiebt relativ") {
    Point p{1, 1};
    p.move(2, -3);
    REQUIRE(p.x == 3);
    REQUIRE(p.y == -2);
}