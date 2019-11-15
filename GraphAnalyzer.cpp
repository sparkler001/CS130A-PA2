#include "GraphHelper.h"
#include "FeatureGraph.h"
#include "GraphAnalyzer.h"

using namespace std;


void GraphAnalyzer::insert(int nodeID, vector<float> features) {
    G.insert(nodeID, features);
    // TODO Adjust calculations for ratio of open triangles and topKtriangles
};

void GraphAnalyzer::insert(Edge e) {
    G.insert(e);
    // TODO Adjust calculations for ratio of open triangles and topKtriangles
};

int GraphAnalyzer::diameter() {
    //TODO
    return 2;
};


float GraphAnalyzer::openClosedTriangleRatio() {
    //TODO
    return .5;
};

string GraphAnalyzer::topKOpenTriangles(int k) {
    //TODO
    return "2,3,4";
};


vector<int> GraphAnalyzer::topKNeighbors(int nodeID, int k,  vector<float> w) {
    //TODO
    return vector<int> {3};
};


int GraphAnalyzer::topNonNeighbor(int nodeID, vector<float> w) {
    //TODO
    return 1;
};


float GraphAnalyzer::jacardIndexOfTopKNeighborhoods(int nodeA, int nodeB, int k, vector<float> w) {
    //TODO
    return 0;
};



