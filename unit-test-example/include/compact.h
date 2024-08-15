#ifndef CLEAN_AFFINITY_COMPACT_H
#define CLEAN_AFFINITY_COMPACT_H

#include <string>
#include <set>

using namespace std;

enum moveDirection{Straight, Right, Left, Up, Down, Backwards, UnDefined};


/// \brief Class to generate 3D structures in memory from a string of moves in space, and to manipulate them (rotation, fusion) \ingroup StructManip
struct struct3D{

    /// \brief Main function: Building a 3D structure from an absolute sequence of moves, and from an initial position in space. \ingroup StructManip
    /// \param AbsoluteSequence   String of moves that may start with B
    /// \param IDinitposition     Starting position in space of the structure (as a single integer number).
    ///                           Using -1 by default leads to use the center of the lattice. Use lattice::idFromPosisition(x,y,z) to specify a position
    /// \param initYAxis          By default (use Undefined), the observer coordinates is predefined to be (Ox, Oy) before the first move, and the coordinate
    /// after the first move is given by the initialYaxis() function. It is possible to define an alternative observer coordinates
    /// by giving another yAxis after first move (i.e. after the first move, the xAxis of the observer will still be the direction of first move).
    struct3D(string AbsoluteSequence, moveDirection initYAxis = UnDefined, int IDinitposition = -1);

    /// \brief Create a structure from an existing one \ingroup StructManip
    struct3D(const struct3D &toCopy);
    // do not recommend to use this constructor, it puts a bad starting position by default.
    // Girts: commented out, because the struct3D constructor is marked as "bad start state"
    //struct3D();
    //~struct3D(){}//{std::cout << "Delete" << &occupiedPositions << endl;}

    // Containers, created automatically:
    /// \brief Lattice integer code for the starting position of the structure in 3D
    int startingPosition;
    /// \brief Absolute sequence of moves
    string sequence;
    /// \brief Decomposition of each step direction in space (i.e. not relative to the previous move, just as translation in 3D)
    /// this notation is helpful when performing rotations of structures: the singlemoves can be rotated easily, then the sequence is updated.
    string separatedSingleMoves;
    /// \brief List of observer coordinates (yAxis) after each move. Used mainly for checking consistency.
    string listYAxis;
    /// \brief Position in space of the last point of the structure (integer encoding, see lattice)
    int endingPosition;
    /// \brief Set of occupied positions in space by this structure. Useful for collision check
    set<int> occupiedPositions;
    /// \brief During construction of the structure, this flag says whether the protein is self-colliding or not.
    bool properlyFolded;

    /// \brief Function to elongate a structure by one absolute direction in space (not relative to anything that happened to the structure before)
    /// the function will find what was the equivalent 'relative move' to add to the tail of the structure to extend in the same direction. \ingroup StructManip
    bool pushBackAbsoluteMove(moveDirection d);
};

string printVector(vector<int> v);
string printVector(vector<double> v);
string printVector(vector<size_t> v);
string printVector(vector<string> v);

vector<int> moveVector(moveDirection dir);

int charMoveToInt(char c);  // same as outputing moveDirection. Casts might be necessary.
/// \brief Conversions for printing: Char code for each move.  \ingroup BasicMoves
char intToMoveChar(moveDirection m);
char intToMoveChar(int m);

moveDirection initialYaxis(moveDirection dir);

/// \brief Main function: moving the observer, from a current direction (Ox) and a current yaxis (Oy) according to the wished RELATIVE next move.
/// \param previous Current direction of observer (previous X axis)
/// \param yaxis Current Y axis of observer.
/// \param nextToTranslate Next move (relative to observer)
/// \return the new x axis and y axis after moving, as a pair. \image html dox/Compact1-ListMoves.png  \ingroup BasicMoves
std::pair<moveDirection, moveDirection> nextAbsoluteMove(moveDirection previous, moveDirection yaxis, moveDirection nextToTranslate);

/// \brief vectorial product between vectors  \ingroup BasicMoves
vector<int> vectorialProduct(vector<int> x, vector<int> y);
/// \brief vectorial product between directions  \ingroup BasicMoves
moveDirection vectorialProduct(moveDirection x, moveDirection y);


#endif //CLEAN_AFFINITY_COMPACT_H
