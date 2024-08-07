#ifndef CLEAN_AFFINITY_RESIDUE_HPP
#define CLEAN_AFFINITY_RESIDUE_HPP

//Note: This enum should follow the same order as the values of interaction in the matrix !!!
/// \brief Each AA has an integer ID, or UndefinedYet \ingroup Prot
enum AA{Cys, Met, Phe, Ile, Leu, Val, Trp, Tyr, Ala, Gly, Thr, Ser, Asn, Gln, Asp, Glu, His, Arg, Lys, Pro, UndefinedYet, NB_AAs};

struct residue {
    /// \brief Basic constructor for a residue. By default, the AA is undefined, and only the position in space matters \ingroup Prot
    residue(int _IDposition, int _IDresidue = -1, AA _TypeResidue = UndefinedYet)
            : IDposition(_IDposition), IDresidue(_IDresidue), TypeResidue(_TypeResidue) {}

    /// \brief Copies a Residue \ingroup Prot
    residue(const residue &toCopy) : IDposition(toCopy.IDposition), IDresidue(toCopy.IDresidue), TypeResidue(toCopy.TypeResidue) {}
    /// \brief Position in space in the lattice \ingroup Prot
    int IDposition;
    /// \brief An ID that can be given to the residue. By default it can be the position inside a protein : 1,2,3,4, ..., N, but can also be changed. This is not used for any algorithms, so can be user-defined.
    int IDresidue;
    /// \brief The type of residue, see enum AA above (or UndefinedYet) \ingroup Prot
    AA TypeResidue;
};

#endif //CLEAN_AFFINITY_RESIDUE_HPP
