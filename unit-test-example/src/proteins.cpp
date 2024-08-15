#include "proteins.h"
#include "compact.h"
#include <iostream>
#include "lattice.h"

using namespace std;

// the important storage inside the structure is occupiedPositions.
// Girts: commented out, because the struct3D constructor is marked as "bad start state"
//superProtein::superProtein() {
//    structure = new struct3D(); // note: never ever copy an external pointer into structure because the destructor would delete the external pointer then.
//    ID = getNewID();
//    points.clear();
//}

superProtein::~superProtein(){
    //cout << "Deleting " << structure << " Prot of size " << this->size() << endl; //print(*this) << endl;

    // I still don't understand why this creates a segfault when calling:
    if(structure) delete structure; // for instance if say superProtein p1, then p1 = p2, p1 will be destroyed. might have mo structure?
}

int getNewID(int channel){
    static vector<int> cpt = vector<int>(1, -1);
    if(channel < 0) return -1;
    if(channel >= (int) cpt.size()){
        cpt.resize(channel+1, -1); // hope it fills -1 to only the new positions
    }
    return ++cpt[channel];
}

superProtein::superProtein(const struct3D& source){
    //cout << "Copy called" << endl;
    structure = new struct3D(source);
    ID = getNewID();
    createPoints();
}

superProtein::superProtein(const string &absoluteSequence, int initialPos) {
    structure = new struct3D(absoluteSequence, UnDefined, (initialPos == -1) ? lattice::centralPosition() : initialPos);
    ID = getNewID();
    createPoints();
    // reconstitutes the structure point by point. This is redundant with the struct3D constructor (sorry!)
    // I wanted to keep the struct3D constructor as simple as possible for computations of millions of structures
    // where we don't really care about the order of positions, just the starting and ending ones.
}

// creates points from the structure to the list of residues points[]
void superProtein::createPoints(){
    if(structure == nullptr) {cerr << "superProtein::createPoints, structure = NULL" << endl; return;}
    int cptIDresidue = 0;
    points.clear();
    points.push_back(residue(structure->startingPosition, cptIDresidue));
    vector<int> currentPos = lattice::positionFromID(structure->startingPosition);
    if(structure->sequence.size() == 0) return;     // this is fine, no need to raise an error.

    cptIDresidue++;
    moveDirection currentDir = (moveDirection) charMoveToInt(structure->sequence[0]);
    moveDirection currentYaxis = initialYaxis((moveDirection) charMoveToInt(structure->sequence[0]));
    vector<int> actualMove = moveVector(currentDir);
    currentPos[0] += actualMove[0];
    currentPos[1] += actualMove[1];
    currentPos[2] += actualMove[2];
    int IDcurrentPos = lattice::idFromPosisition(currentPos);
    points.push_back(residue(IDcurrentPos, cptIDresidue));
    cptIDresidue++;

    for(int i = 1; i < (int) structure->sequence.size(); ++i){
        std::pair<moveDirection, moveDirection> next = nextAbsoluteMove(currentDir, currentYaxis, (moveDirection) charMoveToInt(structure->sequence[i]));
        currentDir = next.first;
        currentYaxis = next.second;
        vector<int> actualMove = moveVector(currentDir);
        currentPos[0] += actualMove[0];
        currentPos[1] += actualMove[1];
        currentPos[2] += actualMove[2];
        IDcurrentPos = lattice::idFromPosisition(currentPos);
        points.push_back(residue(IDcurrentPos, cptIDresidue));
        cptIDresidue++;
    }
}


int superProtein::size(){
    return points.size();
}
