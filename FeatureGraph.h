#ifndef FEATURE_H
#define FEATURE_H


#include <string>
#include <vector>
#include <map>
#include "GraphHelper.h"
#include <iostream>


using namespace std;



class FeatureGraph {

public:
    // TODO add necessary private fields


    // Constructor
    //
    // N: The number of nodes
    // d: the size of the skill vectors of all nodes
    // nodes: vector of nodes to insert
    // edges: vector of edges to insert
    FeatureGraph(int N, int d, vector<Node> nodes, vector<Edge> edges);


    //Insert node with given ID and feature vectors
    void insert(Node node);

    // insert given edge
    // May assume nodes in edge are already present
    void insert(Edge edge);

    // return whether this id is found in the feature graph
    bool find(int id);

    // return all the neigbors with this id
    vector<Node> neigbors(int id);

    // return all none neigbors with this id
    vector<Node> nonNeigbors(int id);

    vector<vector<int> > newMatrix(int numberOfNodes, vector<Edge> edges);

    vector<vector<int> > newPathMatrix(int numberOfNodes, vector<Edge> edges);

    int getNodeIndex(int nodeId);

    void printMatrix();

    void printPathMatrix();

    int getNumberOfNodes(){ return numberOfNodes; }

    vector<vector<int> > getNodesPathMap(){ return nodesPathMap; }
private:
    int numberOfNodes;
    int sizeOfSkill;
    vector<Node> allNodes;
    vector<Edge> allEdges;
    vector<vector<int> > nodesMap;
    vector<vector<int> > nodesPathMap;
};

//int main(){
//    vector<Edge> edges;
//    vector<Node> nodes;
//    vector<float> feature;
//    feature.push_back(10);
//    for(int i = 0; i < 10; i++){
//        struct Edge e1(i*100, i*100+100, 10);
//        edges.push_back(e1);
//        struct Node n1(i*100, feature);
//
//        nodes.push_back(n1);
//    }
//    struct Node n1(10*100, feature);
//    nodes.push_back(n1);
//
//    for(vector<Edge>::iterator edgeIt = edges.begin(); edgeIt != edges.end(); edgeIt++){
//        cout << "edge is connected "<< edgeIt->IdA << " and " << edgeIt->IdB << endl;
//    }
//
//    for(vector<Node>::iterator nodeIt = nodes.begin(); nodeIt != nodes.end(); nodeIt++){
//        cout << "node id is " << nodeIt->id << endl;
//    }
//
//    cout << "-----" << endl;
//
//    FeatureGraph fg1(11, 1, nodes, edges);
//
//    fg1.printMatrix();
//
//    struct Edge e1(600, 100, 10);
//    fg1.insert(e1);
//
//    cout << "-----" << endl;
//    fg1.printMatrix();
//
////    cout << fg1.find(1000) << endl;
//
//    vector<Node> neigbor = fg1.nonNeigbors(600);
//
//    for(vector<Node>::iterator nodeIt = neigbor.begin(); nodeIt != neigbor.end(); nodeIt++){
//        cout << nodeIt->id << endl;
//    }
//
//    fg1.printPathMatrix();
//
//    return 0;
//}

#endif
