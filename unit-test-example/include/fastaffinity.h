#ifndef CLEAN_AFFINITY_FASTAFFINITY_H
#define CLEAN_AFFINITY_FASTAFFINITY_H

#include <map>
#include <set>
#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include <pose.h>
#include <proteins.h>

using namespace std;

class affinityOneLigand {
    // 2 - Pre-calculated list of structures (actually not the structures themselves, but their interaction profiles)
    // and stored / loaded into files
    vector<string> *interactions;
    vector<int> nbRepeats;
    vector<string> *selfInteractions;
    vector<int> nbSelfRepeats;

    // 1 - list of options requested
    string ligandSeq;
    string ligandAAseq;
    superProtein *ligand;
    int sizeReceptors;
    int minimalNInteract;
    int nInterCodes;
    int minNrSelfInteractions;
    int nFoldingCodes;
    double KT;
    string fileStructures;
    string fileSelfFoldings;
    bool modeUltraFast; // will only return best affinity, not the statistical

    // 4 - memory of the previously called affinities.
    map<string, double> knownBestAffinities;
    map<string, double> knownStatisticalAffinities;
    map<string, string> knownBestInteractions;

    // name of files corresponding to the parameters given in the constructor.
    string fStruct;
    string fAll;
    string fCompact;

public:
//    affinityOneLigand(string _ligandStructureSeq, string _ligandAAseq, int startPosition, int _sizeReceptors, int _minimalNInteract, int _minSelfFoldings, double _KT, vector<int> listForbiddenPositions = vector<int>());
//    affinityOneLigand(superProtein* _ligand, int _sizeReceptors, int _minimalNInteract, int _minSelfFoldings, double _KT, vector<int> listForbiddenPositions = vector<int>());
    affinityOneLigand(const affinityOneLigand &copy) {
        throw std::runtime_error("NO copy of affinityOneLigand accepted");
        //cerr << "NO copy of affinityOneLigand accepted" << endl;
    }

    void setUltraFast(bool v) { modeUltraFast = v; }

    // 3 - to be called for getting an affinity
    // returns both best and statistical energies.
    std::pair<double, double>
    affinity(string receptorAASeq, bool showStructures = false, vector<string> *returnBestStructures = nullptr,
             size_t nPoses = 0, vector<pose> *returnTopPoses = nullptr);

    // just simpler way, just returns the bestEnergy
    double
    bestAffinity(string receptorAASeq, bool showStructures = false, vector<string> *returnBestStructures = nullptr) {
        return affinity(receptorAASeq, showStructures, returnBestStructures).first;
    }

    // common function called by both constructors. I tried by one constructor to tall another, but it creates a duplicate struct instead and returns an uninstantiated one.
    void initialize(superProtein *_ligand, int _sizeReceptors, int _minimalNInteract, int _minSelfFoldings, double _KT,
                    vector<int> listForbiddenPositions = vector<int>());
};


#endif //CLEAN_AFFINITY_FASTAFFINITY_HPP
