#include "cppunit.hpp"
#include "factorial.hpp"

class FactorialTests: public Cppunit {
    void test_list() {
        CHECK(factorial(1), 1);
        CHECKT(factorial(2) == 2);
        CHECKT(factorial(3) == 6);
        CHECKT(factorial(10) == 3628800);
        CHECKT(factorial(0) == 1);
    }
};

int main(int argc, char *argv[]) {
    return (new FactorialTests())->run();
}