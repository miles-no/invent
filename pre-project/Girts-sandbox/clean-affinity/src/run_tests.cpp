#include <cppunit.hpp>
#include <lattice.hpp>
#include <vector>

using namespace std;

/**
 * Test the lattice class
 */
class LatticeTests : public Cppunit {
    void testPositions() {
//        cout << "Testing the lattice class" << endl;
//        cout << "predefined sizes : " << XWidth << "," << YWidth << "," << ZWidth << endl;
//        vector<int> toTest = {0, 15, 200, 1000, 15000};
//        for (unsigned int i = 0; i < toTest.size(); ++i) {
//            cout << "positionFromID\t" << toTest[i] << "->"
//                 << printVector(lattice::positionFromID(toTest[i]))
//                 << " -> " << lattice::idFromPosisition(lattice::positionFromID(toTest[i])) << endl;
//        }

        testPosition(0, 0, 0, 0, 0);
        testPosition(15, 15, 0, 0, 15);
        testPosition(200, 8, 3, 0, 200);
        testPosition(1000, 40, 15, 0, 1000);
        testPosition(15000, 24, 42, 3, 15000);
    }

    void testPosition(int id, int expectedPosX, int expectedPosY, int expectedPosZ, int expectedID) {
        vector<int> pos = lattice::positionFromID(id);
        CHECKT(pos[0] == expectedPosX);
        CHECKT(pos[1] == expectedPosY);
        CHECKT(pos[2] == expectedPosZ);
        int actualID = lattice::idFromPosisition(pos);
        CHECKT(actualID == expectedID);
    }

    void testNeighbors() {
        testNeighbor(15000, {15001, 14999, 15064, 14936, 19096, 10904});
        testNeighbor(15250, {15251, 15249, 15314, 15186, 19346, 11154});
        testNeighbor(18500, {18501, 18499, 18564, 18436, 22596, 14404});
//        cout << "Neighbors " << endl;
//        // Note: don't use neighbors from border values, will become negative ...
//        vector<int> toTest = {15000, 15250, 18500};
//        for (unsigned int i = 0; i < toTest.size(); ++i) {
//            cout << "Neighbors for " << toTest[i] << ": "
//                 << printVector(lattice::positionFromID(toTest[i])) << endl;
//            vector<int> idNeigh = lattice::idNeighbors(toTest[i]);
//            for (unsigned int j = 0; j < idNeigh.size(); ++j) {
//                cout << "   ... " << idNeigh[j] << ": "
//                     << printVector(lattice::positionFromID(idNeigh[j])) << endl;
//            }
//        }
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
    int result = latticeTests.run();
    return result;
}