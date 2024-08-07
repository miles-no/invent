#include <cppunit.hpp>

class Struct3dTests: public Cppunit {
    void test_list() {
        CHECK(1, 2);
    }
};

int main() {
    Struct3dTests tests;
    return tests.run();
}