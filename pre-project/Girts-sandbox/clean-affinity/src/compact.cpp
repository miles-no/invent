#include "compact.hpp"
#include <iostream>
#include <sstream>
#include "lattice.hpp"
#include <map>

using namespace std;

// Internal functions and constants
#define Nb_Moves_Relative 5
#define Nb_Moves_Absolute 6
std::map<int, std::pair<moveDirection, moveDirection> > movementMap();
int combinedID(moveDirection previous, moveDirection yaxis, moveDirection nextToTranslate);
int norm2(vector<int> toTest);



struct3D::struct3D(string AbsoluteSequence, moveDirection initYAxis, int IDinitposition)
        : sequence(AbsoluteSequence), properlyFolded(true){

    //cerr << "S3D constructor" << AbsoluteSequence << " x=" << IDinitposition << " initY=" << intToMoveChar(initYAxis) << endl;

    //cout << "struct3D constructor " << AbsoluteSequence << endl;
    if(IDinitposition == -1) IDinitposition = lattice::centralPosition();
    startingPosition = IDinitposition;
    int cptIDresidue = 0;
    vector<int> currentPos = lattice::positionFromID(IDinitposition);
    if(!lattice::testPos(currentPos)) {
        cerr << "ERR: struct3D(" << sequence << ", pos=" << IDinitposition << ", protein going out of bounds at residue " << cptIDresidue  << ", pos=" << currentPos[0] << "," << currentPos[1] << "," << currentPos[2] << ". Suggestions : change starting point of the protein, or change X/Y/ZWidth" << endl;
        properlyFolded = false;
    } // leaving area is an exclusion criterion

    // even if the proteins is 1 residue (empty moves), puts the initial points in.
    //§§§§§points.push_back(residue(IDinitposition, cptIDresidue));
    occupiedPositions.insert(IDinitposition);
    if(sequence.size() == 0) return;
    cptIDresidue++;

    // First move. Note: here, take the initial axis. Would have been similar to start by straight and follow a decision, but in case of Backwards, it doesn't work.

    moveDirection currentDir = (moveDirection) charMoveToInt(sequence[0]);
    moveDirection currentYaxis = initialYaxis((moveDirection) charMoveToInt(sequence[0]));
    if(initYAxis != UnDefined){ // note:backwards also possible.
        currentYaxis = initYAxis;
        if(vectorialProduct(currentDir, currentYaxis) == UnDefined){
            cerr << "ERR: Struct3d(" << sequence << "), the initial direction : " << intToMoveChar(currentDir) << " is not compatible (not perpendicular) with the requested Y axis : " << intToMoveChar(initYAxis) << " : prod=" << intToMoveChar(vectorialProduct(currentDir, currentYaxis)) << endl;
        }
    }
    vector<int> actualMove = moveVector(currentDir);
    currentPos[0] += actualMove[0];
    currentPos[1] += actualMove[1];
    currentPos[2] += actualMove[2];
    // No need for folding checking yet.
    int IDcurrentPos = lattice::idFromPosisition(currentPos);
    //§§§§§points.push_back(residue(IDcurrentPos, cptIDresidue));
    listYAxis.push_back(intToMoveChar(currentYaxis));
    separatedSingleMoves.push_back(intToMoveChar(currentDir));
    occupiedPositions.insert(IDcurrentPos);
    cptIDresidue++;


    for(size_t i = 1; i < sequence.size(); ++i){
        std::pair<moveDirection, moveDirection> next = nextAbsoluteMove(currentDir, currentYaxis, (moveDirection) charMoveToInt(sequence[i]));
        //cout << "Current Pos " << printVector(currentPos) << "\tCurrentDir/Yaxis= " << intToMoveChar(currentDir) << "," << intToMoveChar(currentYaxis);
        //cout << " -> " << sequence[i] << " -> next direction/Yaxis = " << intToMoveChar(next.first) << "," << intToMoveChar(next.second);
        //if(next.first == UnDefined) cerr << "ERR: struct3D(), couldn't find the next move for " << intToMoveChar(currentDir) << ", " << intToMoveChar(currentYaxis) << endl;
        currentDir = next.first;
        currentYaxis = next.second;
        listYAxis.push_back(intToMoveChar(next.second));
        separatedSingleMoves.push_back(intToMoveChar(next.first));
        vector<int> actualMove = moveVector(currentDir);
        currentPos[0] += actualMove[0];
        currentPos[1] += actualMove[1];
        currentPos[2] += actualMove[2];
        //cout << "\tNewPos= " << printVector(currentPos) << endl;
        if(!lattice::testPos(currentPos)) {
            cerr << "ERR: struct3D(" << sequence << ", pos=" << IDinitposition << ", protein going out of bounds at residue " << cptIDresidue  << ", pos=" << currentPos[0] << "," << currentPos[1] << "," << currentPos[2] << ". Suggestions : change starting point of the protein, or change X/Y/ZWidth" << endl;
            properlyFolded = false;
        } // leaving area is an exclusion criterion
        IDcurrentPos = lattice::idFromPosisition(currentPos);
        //§§§§§points.push_back(residue(IDcurrentPos, cptIDresidue));
        properlyFolded = properlyFolded && ((occupiedPositions.find(IDcurrentPos)) == occupiedPositions.end());
        occupiedPositions.insert(IDcurrentPos);
        cptIDresidue++;
    }

    endingPosition = IDcurrentPos;
}

struct3D::struct3D(const struct3D &toCopy)
// 2019-11-04 originally, this constructor would recreate the full structure, it allowed to check consistency. But this takes too much time so now just copying all the content.
//: struct3D(toCopy.sequence, (toCopy.listYAxis.size() > 0) ? (moveDirection) charMoveToInt(toCopy.listYAxis[0]) : UnDefined, toCopy.startingPosition)
{
    startingPosition = toCopy.startingPosition;
    sequence = toCopy.sequence;
    separatedSingleMoves = toCopy.separatedSingleMoves;
    listYAxis = toCopy.listYAxis;
    endingPosition = toCopy.endingPosition;
    occupiedPositions = set<int>(toCopy.occupiedPositions);
    //cerr << &occupiedPositions << " VS " << &toCopy.occupiedPositions << endl;

    properlyFolded = toCopy.properlyFolded;
}

string printVector(vector<string> v){
    //cerr << "Fin" << v.size() << endl;
    stringstream res;
    for(unsigned int i = 0; i < v.size(); ++i){
        res << i << "\t" << v[i] << endl;
    }
    //cerr << res.str() << endl;
    return res.str();
}

string printVector(vector<int> v){
    stringstream res;
    for(unsigned int i = 0; i < v.size(); ++i){
        if(i > 0) res << "\t";
        res << v[i];
    }
    return res.str();
}

string printVector(vector<double> v){
    stringstream res;
    for(unsigned int i = 0; i < v.size(); ++i){
        if(i > 0) res << "\t";
        res << v[i];
    }
    return res.str();
}

string printVector(vector<size_t> v){
    stringstream res;
    for(unsigned int i = 0; i < v.size(); ++i){
        if(i > 0) res << "\t";
        res << v[i];
    }
    return res.str();
}

vector<int> moveVector(moveDirection dir){
    vector<int> res(3,0);
    switch(dir){
        case Right:     {res[1] = -1; break;}
        case Left:      {res[1] = +1; break;}
        case Up:        {res[2] = +1; break;}
        case Down:      {res[2] = -1; break;}
        case Straight:  {res[0] = +1; break;}
        case Backwards: {res[0] = -1; break;}
        case UnDefined:  {/*cerr << "ERR: moveVector(UnDefined) is not an allowed direction" << endl This error always happens during init */ break;}
    }
    return res;
}

moveDirection moveID(vector<int> v){
    if(v.size() != 3) cerr << "ERR: moveID, vector with wrong length" << endl;
    if((abs(v[0]) + abs(v[1]) + abs(v[2])) != 1) cerr << "ERR: moveID, vector is not a unit direction " << v[0] << "," << v[1] << "," << v[2] << endl;
    if(v[1] == -1) return Right;
    if(v[1] == +1) return Left;
    if(v[2] == +1) return Up;
    if(v[2] == -1) return Down;
    if(v[0] == +1) return Straight;
    if(v[0] == -1) return Backwards;
    cerr << "ERR: moveID, move unknown : " << v[0] << "," << v[1] << "," << v[2] << endl;
    return UnDefined;
}


int charMoveToInt(char c){
    switch(c){
        case 'R': {return Right;}
        case 'L': {return Left;}
        case 'U': {return Up;}
        case 'D': {return Down;}
        case 'S': {return Straight;}
        case '-': {return UnDefined;}  // Actually, calling charMoveToInt('-') doesn't make much sense.
        case 'B': {return Backwards;}  // only for the first move of an absolute structure
        default:  {
            cerr << "ERR: Proteins Structures are supposed to only contain -,R,L,U,D and S, and not " << c << endl;
            return UnDefined;
        }
    }
}

char intToMoveChar(int m){
    switch((moveDirection) m){
        case Right: return 'R';
        case Left: return 'L';
        case Up: return 'U';
        case Down: return 'D';
        case Straight: return 'S';
        case UnDefined: return '-';
        case Backwards: return 'B';
    }
    return '?';
}

char intToMoveChar(moveDirection m){
    switch(m){
        case Right: return 'R';
        case Left: return 'L';
        case Up: return 'U';
        case Down: return 'D';
        case Straight: return 'S';
        case UnDefined: return '-';
        case Backwards: return 'B';
    }
    return '?';
}

// Default initial y axis. Defined as if the observer was following x with the y axis.
moveDirection initialYaxis(moveDirection dir){
    switch(dir){
        case Right: return Straight;
        case Left: return Backwards;
        case Up: return Left;
        case Down: return Left;     //case Down: return moveID(vectorialProduct(moveVector(Straight), moveVector(dir)));
        case Straight: return Left; // default
        case UnDefined: return UnDefined; // should raise error later maybe
        case Backwards: return Right; // default
    }
    return UnDefined;
}


// Main function to move along an absolute sequence, in space.
// returns 1/ next absolute direction and 2/ next y axis
std::pair<moveDirection, moveDirection> nextAbsoluteMove(moveDirection previous, moveDirection yaxis, moveDirection nextToTranslate){
    static std::map<int, std::pair<moveDirection, moveDirection> > decision = movementMap();

    int IDmove = combinedID(previous, yaxis, nextToTranslate);
    std::map<int, std::pair<moveDirection, moveDirection> >::iterator it = (decision.find(IDmove));
    if (it == decision.end()){
        cerr << "ERR: nextAbsoluteMove(" << intToMoveChar(previous) << "," << intToMoveChar(yaxis) << "," << intToMoveChar(nextToTranslate) << "), this movement is not authorized " << endl;
        return std::pair<moveDirection, moveDirection>(UnDefined, UnDefined);
    }
    std::pair<moveDirection, moveDirection> res = decision[IDmove]; // Can be improved to *it.reference
    //cout << res.first << "," << res.second << endl;
    // Note: in non debug mode, this function could be shorter.
    return res;
}

// 2/ creates a 'movement map', where, for each combination, the next direction (Ox) and y axis (Oy) is pre-computed / stored
std::map<int, std::pair<moveDirection, moveDirection> > movementMap(){
    std::map<int, std::pair<moveDirection, moveDirection> > decision;

    // i is a current direction, including Backwards
    for(int i = 0; i <= Nb_Moves_Absolute; ++i){
        vector<int> currentX = moveVector( (moveDirection) i);
        //cout << " current " << intToMoveChar(i) << ":" << printVector(currentX) << endl;

        // j is a current Yaxis plane (including Backwards).
        for(int j = 0; j <= Nb_Moves_Absolute; ++j){
            vector<int> currentY = moveVector((moveDirection) j);
            vector<int> currentZ = vectorialProduct(currentX, currentY);


            // the yaxis vector has to be non-colinear !
            if(norm2(currentZ) != 0){

                //cout << "    ... current Y " << intToMoveChar(j) << ":" << printVector(currentY) << endl;
                //cout << "           => current Z " << intToMoveChar(moveID(currentZ)) << ":" << printVector(currentZ) << endl;

                // k is the next (relative) move.
                for(int k = 0; k < Nb_Moves_Relative; ++k){
                    vector<int> moveXYZ = moveVector( (moveDirection) k);
                    vector<int> moveInBase(3,0);
                    // the move 'X' means following currentX, 'Y' means follow current Y, etc
                    // new move, in XYZ basis
                    moveInBase[0] = moveXYZ[0] * currentX[0] + moveXYZ[1] * currentY[0] + moveXYZ[2] * currentZ[0];
                    moveInBase[1] = moveXYZ[0] * currentX[1] + moveXYZ[1] * currentY[1] + moveXYZ[2] * currentZ[1];
                    moveInBase[2] = moveXYZ[0] * currentX[2] + moveXYZ[1] * currentY[2] + moveXYZ[2] * currentZ[2];

                    // new Yaxis vector : if Straight, kept. if not, vectorial(prev, new)
                    vector<int> newY = currentY; // current Yaxix

                    // if left or right, keep same plane of walking, but needs to turn. => Zaxis vector kept, Y=N^newX
                    // this is a trick: instead of
                    if((k == Right) || (k == Left)){
                        newY = vectorialProduct(currentZ, moveInBase);
                    }

                    // if up or right, the plane is turned (like piloting a plane). Y is kept. The Zaxis vector is changed.
                    if((k == Up) || (k == Down)){
                        newY = currentY;
                    }

                    //cout << " Move " << intToMoveChar(k) << " results in : newDir " << intToMoveChar(moveID(moveInBase)) << " and new Yaxis: " << intToMoveChar(moveID(newY)) << endl;
                    decision[combinedID((moveDirection) i,(moveDirection) j,(moveDirection) k)] = std::pair<moveDirection, moveDirection> (moveID(moveInBase), (norm2(newY) == 0) ? UnDefined : moveID(newY) ); // moveID raises an error if gets a wrong vectror
                }
            }
        }
    }
    return decision;
}

// 1/ an ID is given to each combination (current observer direction (Ox), current observer y axis (Oy), and next relative move)
int combinedID(moveDirection previous, moveDirection yaxis, moveDirection nextToTranslate){
    return static_cast<int>(previous) * (Nb_Moves_Absolute + 1) * (Nb_Moves_Absolute + 1) +
           static_cast<int>(yaxis) * (Nb_Moves_Absolute + 1) +
           static_cast<int>(nextToTranslate);  // note: the +1's are in case someone puts UnDefined.
}

moveDirection vectorialProduct(moveDirection x, moveDirection y){
    // Pre-stores the result for all combinations of x and y into a map (static) when the function is called first.
    // Then, each further call is just an access to the map.
    static map<int, moveDirection> products;
    static bool loaded = false;
    if(!loaded){
        //cerr << "Loading vectorial product combinations" << endl;
        for(int i = 0; i < Nb_Moves_Absolute + 1; ++i){
            for(int j = 0; j < Nb_Moves_Absolute + 1; ++j){
                int comb = i + 100 * j;
                if((i == UnDefined) || (j == UnDefined)) products[comb] = UnDefined;
                else {
                    vector<int> z = vectorialProduct(moveVector(static_cast<moveDirection> (i)), moveVector(static_cast<moveDirection>(j)));
                    if(norm2(z) == 0) products[comb] = UnDefined;
                    else {
                        moveDirection mz = moveID(z);
                        products[comb] = mz;
                    }
                    //cerr << intToMoveChar(i) << " ^ " << intToMoveChar(j) << " = " << intToMoveChar(products[comb]) << endl;
                }
            }
        }
        loaded = true;
    }
    return products[static_cast<int>(x) + 100 * static_cast<int>(y)];
}

int norm2(vector<int> toTest){
    return toTest[0] * toTest[0] + toTest[1] * toTest[1] + toTest[2] * toTest[2];
}

vector<int> vectorialProduct(vector<int> x, vector<int> y){
    if((x.size() != 3) || (y.size() != 3)) cerr << "ERR: Vectorial product with bad sized vectors " << endl;
    vector<int> z(3,0);
    z[0] = x[1] * y[2] - y[1] * x[2];
    z[1] = - x[0] * y[2] + y[0] * x[2];
    z[2] = x[0] * y[1] - y[0] * x[1];
    return z;
}
