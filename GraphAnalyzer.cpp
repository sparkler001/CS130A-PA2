//#include "GraphHelper.h"
//#include "FeatureGraph.h"
#include "GraphAnalyzer.h"
#include <algorithm>
#include <queue>
#include <utility>
#include <iostream>
#include <stdio.h>
#include <string>

#define INF 9999

using namespace std;

GraphAnalyzer::GraphAnalyzer(FeatureGraph& G):G(G){
    for (int eachTriangle = 0; eachTriangle < G.getNumberOfOpenTriangles(); ++eachTriangle) {
        Triangle t1 = G.getOpenTriangles()[eachTriangle];
        Triangles.push(t1);
    }

    for (int eachTriangle = 0; eachTriangle < G.getNumberOfClosedTriangles(); ++eachTriangle) {
        Triangle t1 = G.getOpenTriangles()[eachTriangle];
        Triangles.push(t1);
    }

    // print all the triangles in the Triangles by its total weight from large to small, but pop all of them
//    for (int eachTriangle = 0; eachTriangle < G.getNumberOfOpenTriangles(); ++eachTriangle){
//        Triangle t1 = G.getOpenTriangles()[eachTriangle];
//        cout << "this triangle " << t1.getFirstNode() << ", " << t1.getSecondNode() << ", " << t1.getThirdNode()
//             << " is an open triangle! and its weight is " << t1.getTotalWeight() << " and its is a triangle "<< endl;
//        this->Triangles.pop();
//    }
}

void GraphAnalyzer::insert(Node n) {
    G.insert(n);
    // TODO Adjust calculations for ratio of open triangles and topKtriangles
};

void GraphAnalyzer::insert(Edge e) {
    int oldOpenTriangles = G.getNumberOfOpenTriangles();

    G.insert(e);
    // TODO Adjust calculations for ratio of open triangles and topKtriangles

    // there is no open triangles switch to closed
    if(oldOpenTriangles == G.getNumberOfOpenTriangles()) return;

    // pop the top and store them in temp triangle list until find there is a triangle switch from open to closed
    vector<Triangle> tempTriangles;
//    for()
}

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
            if (result < distance[i] && distance[i] < INF)  result = distance[i];

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
    if(G.getClosedTriangles().empty() && G.getNumberOfClosedTriangles() == 0) return -1;

    cout << " number of open triangles are " << G.getNumberOfOpenTriangles() << endl;
    cout << " number of closed triangles are " << G.getNumberOfClosedTriangles() << endl;
    return G.getNumberOfOpenTriangles() / G.getNumberOfClosedTriangles();
};

string GraphAnalyzer::topKOpenTriangles(int k) {
    if(k <= 0)  {
        cout << "invaild input! the input should be greater than 0!" << endl;
        return "";
    }

    if(G.getNumberOfOpenTriangles() == 0){
        cout << "there is no open triangles in this graph! " << endl;
        return "";
    }

    int numberOfTriangle = G.getNumberOfOpenTriangles();
    //if top k numbers is larger than the numbers of open triangles, change k to the total number of open triangles
    if(k > numberOfTriangle)    k = numberOfTriangle;

    string result;

    priority_queue<pair<int, string> > priorityQueue;

    for(int eachTriangle = 0; eachTriangle < numberOfTriangle; eachTriangle++){
        Triangle temp = G.getOpenTriangles()[eachTriangle];
        string tname = to_string(temp.getFirstNode()) + "," + to_string(temp.getSecondNode()) + "," + to_string(temp.getThirdNode());
        int weight = temp.getTotalWeight();

        priorityQueue.push(make_pair(weight, tname));
    }

    for (int eachTriangle = 0; eachTriangle < k-1; ++eachTriangle) {
        pair<int, string> top = priorityQueue.top();
        result += top.second + ";";
//        cout << priorityQueue.top().second << "has been added" << endl;
        priorityQueue.pop();
    }

    result += priorityQueue.top().second;

    return result;
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
//            int weight = 0;
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
    vector<Node> nonNeigbors = G.nonNeigbors(nodeID);

    // if this node connect to all other node, return -1
    if(nonNeigbors.empty())     return -1;

    priority_queue<pair<int, int> > priorityQueue;

    //calculate the weight of total feature of every neighbor and put each of them into the priority queue
    for(int eachNode = 0; eachNode < nonNeigbors.size(); eachNode++) {
        int weight = 0;
        for (int eachFeature = 0; eachFeature < w.size(); eachFeature++) {
//            int weight = 0;
            weight += nonNeigbors[eachNode].features[eachFeature] * w[eachFeature];
        }

        priorityQueue.push(make_pair(weight, nonNeigbors[eachNode].id));
    }

    //find the largest weight, store them into the result and pop it
    pair<int, int> top = priorityQueue.top();

    return top.second;
};

float GraphAnalyzer::jacardIndexOfTopKNeighborhoods(int nodeAID, int nodeBID, int k, vector<float> w) {
    if(k < 1)   return 0;

    vector<int> aNeigbor = topKNeighbors(nodeAID, k, w);
    vector<int> bNeigbor = topKNeighbors(nodeBID, k, w);
    float AandB = 0;
    float AorB = 2*k;

    for(int eachANode = 0; eachANode < k; eachANode++){
        int nodeId = aNeigbor[eachANode];

        for(int eachBNode = 0; eachBNode < k; eachBNode++){
               if(nodeId == bNeigbor[eachBNode]){
                   AandB++;
                   AorB--;
               }
        }
    }

    return AandB/AorB;
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
