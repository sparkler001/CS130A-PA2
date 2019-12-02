#include "GraphHelper.h"
#include "FeatureGraph.h"
#include "GraphAnalyzer.h"
#include <algorithm>
#include <queue>
#include <utility>
#include <iostream>
#include <stdio.h>

#define INF 9999

using namespace std;


void GraphAnalyzer::insert(Node n) {
    G.insert(n);
    // TODO Adjust calculations for ratio of open triangles and topKtriangles
};

void GraphAnalyzer::insert(Edge e) {
    G.insert(e);
    // TODO Adjust calculations for ratio of open triangles and topKtriangles
};

// n is the sizeOfNodes
// return the largest shorest path total weight for the start node
int GraphAnalyzer::DijkstraSearch(int startNode) {
    vector<vector<int> > weight_map = G.getNodesPathMap();
    int n = G.getNumberOfNodes();

    int cost[n][n], distance[n], pred[n];
    int visited[n], count, mindistance, nextnode, i, j;
    for (i = 0; i < n; i++)
        for (j = 0; j < n; j++)
            if (weight_map[i][j] == 0)
                cost[i][j] = INF;
            else
                cost[i][j] = weight_map[i][j];
    for (i = 0; i < n; i++) {
        distance[i] = cost[startNode][i];
        pred[i] = startNode;
        visited[i] = 0;
    }
    distance[startNode] = 0;
    visited[startNode] = 1;
    count = 1;
    while (count < n - 1) {
        mindistance = INF;
        for (i = 0; i < n; i++)
            if (distance[i] < mindistance && !visited[i]) {
                mindistance = distance[i];
                nextnode = i;
            }
        visited[nextnode] = 1;
        for (i = 0; i < n; i++)
            if (!visited[i])
                if (mindistance + cost[nextnode][i] < distance[i]) {
                    distance[i] = mindistance + cost[nextnode][i];
                    pred[i] = nextnode;
                }
        count++;
    }
    int result = 0;
    for (i = 0; i < n; i++)
        if (i != startNode) {
            //  cout<<"\nDistance of node"<<i<<"="<<distance[i]<<endl;
            if (result < distance[i] && distance[i] < INF) result = distance[i];

            //  cout<<"\nPath="<<i;
            j = i;
            do {
                j = pred[j];
                // cout<<"<-"<<j;
            } while (j != startNode);
        }

    return result;
}

// return the largest smallest path total weight in the graph
int GraphAnalyzer::diameter() {
    int max = 0;

    for(int i=0;i<G.getNumberOfNodes();i++){

        if(DijkstraSearch(i) > max)     max = DijkstraSearch(i);
    }

    return max;
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

    //if top k numbers is larger than the numbers of neighbors
    if(k > neigbors.size())     k = neigbors.size();

    priority_queue<pair<int, int> > priorityQueue;

    //calculate the weight of total feature of every neighbor and put each of them into the priority queue
    for(int eachNode = 0; eachNode < neigbors.size(); eachNode++) {
        int weight = 0;
        for (int eachFeature = 0; eachFeature < w.size(); eachFeature++) {
            int weight = 0;
            weight += neigbors[eachNode].features[eachFeature] * w[eachFeature];
//            pair<int, int> temp (weight, neibors[eachNode].id);
//            priorityQueue.push(make_pair(weight, neigbors[eachNode].id));
        }

        priorityQueue.push(make_pair(weight, neigbors[eachNode].id));
    }

    //find k times the largest weight, store them into the result and pop it
    for(int eachNode = 0; eachNode < k; eachNode++){
        pair<int, int> top = priorityQueue.top();

        result.push_back(top.second);
        priorityQueue.pop();
    }

    return result;
};


int GraphAnalyzer::topNonNeighbor(int nodeID, vector<float> w) {
    int result;

    vector<Node> nonNeigbors = G.nonNeigbors(nodeID);

    // if this node connect to all other node, return -1
    if(nonNeigbors.empty())     return -1;

    priority_queue<pair<int, int> > priorityQueue;

    //calculate the weight of total feature of every neighbor and put each of them into the priority queue
    for(int eachNode = 0; eachNode < nonNeigbors.size(); eachNode++) {
        int weight = 0;
        for (int eachFeature = 0; eachFeature < w.size(); eachFeature++) {
            int weight = 0;
            weight += nonNeigbors[eachNode].features[eachFeature] * w[eachFeature];
        }

        priorityQueue.push(make_pair(weight, nonNeigbors[eachNode].id));
    }

    //find the largest weight, store them into the result and pop it
    pair<int, int> top = priorityQueue.top();

    result = top.second;
    return result;
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
//    vector<int> a = ga.DijkstraSearch(0);
//
//    for(vector<int>::iterator nodeIt = a.begin(); nodeIt != a.end(); nodeIt++){
//        cout << *nodeIt << endl;
//    }
//
//    cout << "------" << endl;
//    cout << ga.topNonNeighbor(600, weight) << endl;
//
//
//    return 0;
//}
