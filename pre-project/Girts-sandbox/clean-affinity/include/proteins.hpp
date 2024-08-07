#ifndef CLEAN_AFFINITY_PROTEINS_HPP
#define CLEAN_AFFINITY_PROTEINS_HPP

#include <compact.hpp>
#include <residue.hpp>

// Tool function to generate new IDs independently per 'Channel'
int getNewID(int channel = 0);

/// \brief Class for Proteins: Structure in 3D + additional list of residues and their positions in space \ingroup Prot
/// Philisophy: A struct3D should be continuous. We want to use discontinuous proteins as well. So wm
/// Note that the struct3D class doesn't know/keep the position of each successive point in space, only all occupied positions,
/// therefore, the storage of residues (vector 'points') will be used to store each residue position instead.
/// There is no restriction on the size of a protein. It also becomes possible to use this class without conventional 'structure'
/// (defined by a sequence of moves), but just a list of residues in space (start with an empty structure and add AAs one by one)
struct superProtein {
    /// \brief A protein is mainly a list of residues, but it can also store a structure together.
    struct3D* structure;

//    superProtein();
    ~superProtein();
    /// \brief Creates a struct3D from an absolute sequence/starting point, and prepare the list of residues for each position as type 'Undefined Yet' with ID their position in the structure \ingroup Prot
    superProtein(const string &absoluteSequence, int initialPos = -1);
    /// \brief Copy a struct3D and extends it by creating the list of residues at each position, a 'UndefinedYet' with ID their position in the structure  \ingroup Prot
    superProtein(const struct3D& source);
    /// \brief Copies an existing protein \ingroup Prot
    superProtein (const superProtein& toCopy);

    /// \brief A unique new ID is generated each time a protein is created. \ingroup Prot
    int ID;
    /// \brief Storage of each residue in memory, (on top of inherited struct3D fields) \ingroup Prot
    vector<residue> points;



    /// \brief Number of stored residues. This is one more than the size of the structure (defined as number of bonds) \ingroup Prot
    int size();
    /// \brief Says if a position is free (not occupied) \ingroup Prot
    bool isFree(int idPosition);

    /// \brief  \ingroup Prot
    void push_back(AA newAA, int IDnewPos);

    /// \brief  \ingroup Prot

    void push_back(residue &toAddToTail);

    /// \brief Access a residue \ingroup Prot
    residue operator[](int _IDresidue);
    /// \brief First residue \ingroup Prot
    residue* begin();
    /// \brief Last residue \ingroup Prot
    residue* end();
    /// \brief Browse through the residues to get AA sequence in that order. Adds + when jumps.  \ingroup Prot
    string getAAseq();
    /// \brief Function to set the type of each AA in a protein \ingroup Prot
    void setAAs(string seqAAs);
    /// \brief Checks that the residues IDs are contiguous and that there is no gap in the structure sequence.
    bool contiguous();

protected:
    // Tool function, called by the constructors: recreates the list of residues and their position from the underlying struct3D structure
    void createPoints();
};
#endif //CLEAN_AFFINITY_PROTEINS_HPP
