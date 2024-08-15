#include <cppunit.h>
#include <lattice.h>
#include <vector>

using namespace std;

/**
 * Test the lattice class with CppUnit.
 */
class LatticeTests : public Cppunit {
    void testPositions() {
        testPosition(0, 0, 0, 0, 0);
        testPosition(15, 15, 0, 0, 15);
        testPosition(200, 8, 3, 0, 200);
        testPosition(1000, 40, 15, 0, 1000);
        testPosition(15000, 24, 42, 3, 15000);
    }

    void testPosition(int id, int expectedPosX, int expectedPosY, int expectedPosZ, int expectedID) {
        vector<int> pos = lattice::positionFromID(id);
        CHECK(pos[0], expectedPosX);
        CHECK(pos[1], expectedPosY);
        CHECK(pos[2], expectedPosZ);
        int actualID = lattice::idFromPosisition(pos);
        CHECK(actualID, expectedID);
    }

    void testNeighbors() {
        testNeighbor(15000, {15001, 14999, 15064, 14936, 19096, 10904});
        testNeighbor(15250, {15251, 15249, 15314, 15186, 19346, 11154});
        testNeighbor(18500, {18501, 18499, 18564, 18436, 22596, 14404});
    }

    void testNeighbor(int id, const vector<int>& expectedNeighbors) {
        vector<int> neighbors = lattice::idNeighbors(id);
        CHECKT(neighbors == expectedNeighbors);
    }

    void test_list() {
        testPositions();
        testNeighbors();
    }
};

int main() {
    LatticeTests latticeTests;
    return latticeTests.run();
}