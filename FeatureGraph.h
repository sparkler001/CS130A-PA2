#ifndef FEATURE_H
#define FEATURE_H


#include <string>
#include <vector>
#include <map>
#include "GraphHelper.h"


using namespace std;



class FeatureGraph {

public:
    // TODO add necessary private fields


    // Constructor
    // 
    // N: The number of nodes
    // nodeIds: the ids of nodes as integers
    // d: the sizee of the skill vectors of all nodes
    // nodeIDtoSkillsMap: a map form the nodeID to their skiils vector
    FeatureGraph(int N, vector<int> nodeIDs, vector<Edge> edges, int d, map<int, vector<float>> nodeIDToSkillsMap);


    //Insert node with given ID and feature vectors
    void insert(int nodeID, vector<float> feautres);

    // insert given edge
    // May assume nodes in edge are already present
    void insert(Edge edge);


};  

#endif
