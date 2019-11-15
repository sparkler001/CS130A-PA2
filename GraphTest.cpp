#include "GraphHelper.h"
#include "FeatureGraph.h"
#include "GraphAnalyzer.h"
#include <map>
#include <iostream>
using namespace std;

int main() {

    vector<int> nodes{ 1, 2, 3, 4};
    
    vector<Edge> edges {Edge(1,2, 10), Edge(2, 3, 9), Edge(3, 4, 1), Edge(1, 3, 5)};
  
    int d = 2;

 
    map<int, vector<float>> nodeToFeatures = {
        {1, {10, 10}},
        {2, {20, 20}},
        {3, {30, 30}},
        {4, {40, 40}} };

    FeatureGraph graph = FeatureGraph(4, nodes, edges, d, nodeToFeatures);
    GraphAnalyzer analyzer = GraphAnalyzer(graph);


    cout << analyzer.diameter() << "\n";

    cout << analyzer.openClosedTriangleRatio() << "\n";

    cout << analyzer.topKOpenTriangles(2) << "\n";

    
    int newNode = 5;
    vector<float> newFeatures {3, 3};

    analyzer.insert(newNode, newFeatures);
    analyzer.insert(Edge(4, 5, 32));
    
    
    vector<float> weights{.5, .5};
    vector<int> neighbors = analyzer.topKNeighbors(2, 3, weights);
    
    for(auto i = neighbors.begin(); i != neighbors.end(); ++i)
        cout << *i << ",";
    cout << "\n";

    cout << analyzer.topNonNeighbor(2, weights) << "\n";

    cout << analyzer.jacardIndexOfTopKNeighborhoods(1, 2, 2, weights);
    return 0;
}
