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

    // find all open triangles for one node
    void findTriangles(int nodeId);

    // find all open triangles for all nodes
    void findTriangles();

    // add an open triangle in open triangles' list
    // if it is open triangle, add it, if not, return
    // if this triangle is already exists, just return
    void addOpenTriangles(Triangle t1);

    // add an closed triangle in open triangles' list
    // if it is closed triangle, add it, if not, return
    // if this triangle is already exists, just return
    void addClosedTriangles(Triangle t1);

    int getNumberOfNodes(){ return numberOfNodes; }

    vector<vector<int> > getNodesPathMap(){ return nodesPathMap; }

    vector<Triangle> getOpenTriangles(){ return openTriangles; }

    float getNumberOfOpenTriangles(){ return numberOfOpenTriangles; }

    vector<Triangle> getClosedTriangles(){ return closedTriangles; }

    float getNumberOfClosedTriangles(){ return numberOfClosedTriangles; }
private:
    int numberOfNodes;
    int sizeOfSkill;
    vector<Node> allNodes;
    vector<Edge> allEdges;
    vector<vector<int> > nodesMap;
    vector<vector<int> > nodesPathMap;
    vector<Triangle> openTriangles;
    float numberOfOpenTriangles;
    vector<Triangle> closedTriangles;
    float numberOfClosedTriangles;
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
//    fg1.findTriangles(100);
//
//    vector<Triangle> t1 = fg1.getOpenTriangles();
//    for(vector<Triangle>::iterator nodeIt = t1.begin(); nodeIt != t1.end(); nodeIt++){
//        cout << "this triangle " << nodeIt->getFirstNode() << ", " << nodeIt->getSecondNode() << ", " << nodeIt->getThirdNode() << " is an open triangle!" << endl;
//    }
//
//    return 0;
//}

#endif
