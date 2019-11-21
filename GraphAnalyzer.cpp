#include "GraphHelper.h"
#include "FeatureGraph.h"
#include "GraphAnalyzer.h"
#include <algorithm>
#include <queue>
#include <utility>
#include <iostream>

using namespace std;


void GraphAnalyzer::insert(Node n) {
    G.insert(n);
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
    vector<int> result;

    vector<Node> neigbors = G.neigbors(nodeID);

    if(k > neigbors.size())     k = neigbors.size();

    priority_queue<pair<int, int> > priorityQueue;
//    cout<<"A45"<<endl;
    //calculate the weight of total feature of every neighbor and put each of them into the priority queue
    for(int eachNode = 0; eachNode < neigbors.size(); eachNode++) {
        int weight = 0;
        for (int eachFeature = 0; eachFeature < w.size(); eachFeature++) {
//            int weight = 0;
            weight += neigbors[eachNode].features[eachFeature] * w[eachFeature];
//            pair<int, int> temp (weight, neibors[eachNode].id);
//            priorityQueue.push(make_pair(weight, neigbors[eachNode].id));
        }
        priorityQueue.push(make_pair(weight, neigbors[eachNode].id));
//        cout<<priorityQueue.top()<<endl;
    }
//    cout<<"A57"<<endl;
    //find k times the largest weight, store them into the result and pop it
    for(int eachNode = 0; eachNode < k; eachNode++){
        pair<int, int> top = priorityQueue.top();
//        cout << top.first << "  "<< top.second <<endl;
        result.push_back(top.second);
        priorityQueue.pop();
    }
//    cout<<"A64"<<endl;
//    cout<<result[0]<<endl;
//    cout<<result[1]<<endl;
//    cout<<result[2]<<endl;
//    cout<<result[3]<<endl;
//    cout<<result[4]<<endl;
//    cout<<result[5]<<endl;
    return result;

};


int GraphAnalyzer::topNonNeighbor(int nodeID, vector<float> w) {
    //TODO
    return 1;
};


float GraphAnalyzer::jacardIndexOfTopKNeighborhoods(int nodeAID, int nodeBiID, int k, vector<float> w) {
    //TODO
    return 0;
};

//int main(){
//    vector<Edge> edges;
//    vector<Node> nodes;
//    vector<float> feature;
//    feature.push_back(10);
//    feature.push_back(10);
//
//    for(int i = 0; i < 10; i++){
//        struct Edge e1(i*100, i*100+100, 10);
//        edges.push_back(e1);
//        struct Node n1(i*100, feature);
//
//        nodes.push_back(n1);
//    }
//
//    struct Node n1(10*100, feature);
//    nodes.push_back(n1);
//
//    FeatureGraph fg1(11, 1, nodes, edges);
////    cout << "3" << endl;
//    fg1.printMatrix();
//
//    struct Edge e1(600, 100, 10);
//    fg1.insert(e1);
//
//    cout << "-----" << endl;
//    fg1.printMatrix();
//
//
//    vector<Node> neigbor = fg1.neigbors(600);
//
//    for(vector<Node>::iterator nodeIt = neigbor.begin(); nodeIt != neigbor.end(); nodeIt++){
//        cout << nodeIt->id << endl;
//    }
//
//    GraphAnalyzer ga(fg1);
//
//    vector<float> weight;
//    weight.push_back(5);
//    vector<int> result;
//    result = ga.topKNeighbors(600, 2, weight);
//
//    for(vector<int>::iterator nodeIt = result.begin(); nodeIt != result.end(); nodeIt++){
//        cout << *nodeIt << endl;
//    }
//
//    return 0;
//}
