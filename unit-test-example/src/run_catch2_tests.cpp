#include <catch2.h>
#include <lattice.h>
#include <vector>

using namespace std;

void testPosition(int id, int expectedPosX, int expectedPosY, int expectedPosZ, int expectedID) {
    vector<int> pos = lattice::positionFromID(id);
    REQUIRE(pos[0] == expectedPosX);
    REQUIRE(pos[1] == expectedPosY);
    REQUIRE(pos[2] == expectedPosZ);
    int actualID = lattice::idFromPosisition(pos);
    REQUIRE(actualID == expectedID);
}

void testNeighbor(int id, const vector<int>& expectedNeighbors) {
    vector<int> neighbors = lattice::idNeighbors(id);
    REQUIRE(neighbors == expectedNeighbors);
}

/**
 * Test the lattice class with Catch2.
 */
TEST_CASE("Lattice tests", "[lattice]") {
    SECTION("Position tests") {
        testPosition(0, 0, 0, 0, 0);
        testPosition(15, 15, 0, 0, 15);
        testPosition(200, 8, 3, 0, 200);
        testPosition(1000, 40, 15, 0, 1000);
        testPosition(15000, 24, 42, 3, 15000);
    }
    SECTION("Neighbor tests") {
        testNeighbor(15000, {15001, 14999, 15064, 14936, 19096, 10904});
        testNeighbor(15250, {15251, 15249, 15314, 15186, 19346, 11154});
        testNeighbor(18500, {18501, 18499, 18564, 18436, 22596, 14404});
    }
}