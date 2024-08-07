#define CATCH_CONFIG_MAIN
#include "catch2.hpp"
#include "factorial.hpp"

TEST_CASE("Factorial tests", "[factorial]") {
    REQUIRE(factorial(1) == 1);
    REQUIRE(factorial(2) == 2);
    REQUIRE(factorial(3) == 6);
    REQUIRE(factorial(10) == 3628800);
    REQUIRE(factorial(0) == 1);
}
