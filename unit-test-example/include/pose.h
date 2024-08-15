#ifndef CLEAN_AFFINITY_POSE_HPP
#define CLEAN_AFFINITY_POSE_HPP

#include <string>

using namespace std;

/**
 * Structure to store the results of the affinity calculation.
 */
struct pose {
    pose(int _startPos, double _affInteract, double _totalAff, string _structure, string _interactionCode) :
            startPos(_startPos), affInteract(_affInteract), totalAff(_totalAff), structure(_structure),
            interactionCode(_interactionCode) {}

    int startPos;
    double affInteract;
    double totalAff;
    string structure;
    string interactionCode;

    //string print();
};

#endif //CLEAN_AFFINITY_POSE_HPP
