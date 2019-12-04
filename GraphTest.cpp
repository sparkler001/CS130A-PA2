#include "GraphHelper.h"
#include "FeatureGraph.h"
#include "GraphAnalyzer.h"
#include <map>
#include <iostream>
#include <vector>
#include <queue>
#include <utility>
#include <algorithm>
#include <stdio.h>
#include <string>
using namespace std;

int main() {

    vector<Node> nodes {
       Node(1, vector<float> { 10, 10}),
       Node(2,vector<float> { 20, 20}),
       Node(3, vector<float> { 30, 30}),
       Node(4, vector<float> { 40, 40}),
       Node(8, vector<float> { 33, 34}),
       Node(11, vector<float> { 53, 54})
    };

    vector<Edge> edges {Edge(1,2, 10), Edge(2, 3, 9), Edge(3, 4, 1), Edge(1, 3, 5), Edge(2, 8, 5), Edge(2, 11, 5), Edge(2, 4, 5), Edge(1,11, 10)};
//    vector<Edge> edges {Edge(1,2, 10), Edge(2, 3, 9), Edge(3, 4, 1), Edge(2, 8, 5)};

    int numberOfNodes = 6;
    int d = 2;
    vector<int> a;
    a.push_back(1);
    vector<int> b;
    b=a;
    cout<<b[0]<<endl;
    a.push_back(2);
    b=a;
    cout<<b[1]<<endl;
    cout<<"good21"<<endl;
    FeatureGraph graph = FeatureGraph(numberOfNodes, d, nodes, edges);
    cout<<"23"<<endl;
    GraphAnalyzer analyzer = GraphAnalyzer(graph);
//    analyzer.G.printPathMatrix();


    cout << analyzer.diameter() << "\n";

    cout << analyzer.openClosedTriangleRatio() << "\n";

    cout << analyzer.topKOpenTriangles(2) << "\n";

    cout<<"33"<<endl;
    int newNodeID = 5;
    vector<float> newFeatures {3, 3};
    Node newNode = Node(newNodeID, newFeatures);
    cout<<"37"<<endl;
    analyzer.insert(newNode);
    analyzer.insert(Edge(4, 5, 32));

    cout << "-----" << endl;
    cout<<"41"<<endl;
    vector<float> weights{.5, .5};
    cout<<"43"<<endl;
    vector<int> neighbors = analyzer.topKNeighbors(2, 2, weights);
    cout<<"45"<<endl;
    for(auto i = neighbors.begin(); i != neighbors.end(); ++i)
        cout << *i << ",";
    cout << "\n";

    cout << "-----" << endl;
    analyzer.insert(Edge(2, 5, 32));
    cout << "top neighbor for node 2 is: "<< analyzer.topNonNeighbor(2, weights) << "\n";

    cout << analyzer.jacardIndexOfTopKNeighborhoods(1, 2, 2, weights) << endl;

    cout << analyzer.topKOpenTriangles(4) << "\n";

    priority_queue<pair<int, int> > priorityQueue;
    priorityQueue.push(make_pair(100, 10));
    priorityQueue.push(make_pair(110, 11));
    priorityQueue.push(make_pair(110, 11));

    cout << priorityQueue.top().second << endl;
    priorityQueue.pop();
    cout << priorityQueue.top().second << endl;

    return 0;
}
