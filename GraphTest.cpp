#include "GraphHelper.h"
#include "FeatureGraph.h"
#include "GraphAnalyzer.h"
#include <map>
#include <iostream>
#include <vector>
using namespace std;

int main() {

    vector<Node> nodes  {
       Node(1, vector<float> { 10, 10}),
       Node(2,vector<float> { 20, 20}),
       Node(3, vector<float> { 30, 30}),
       Node(4, vector<float> { 40, 40}) };

    vector<Edge> edges {Edge(1,2, 10), Edge(2, 3, 9), Edge(3, 4, 1), Edge(1, 3, 5)};

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
    FeatureGraph graph = FeatureGraph(4, d, nodes, edges);
    cout<<"23"<<endl;
    GraphAnalyzer analyzer = GraphAnalyzer(graph);


/*    cout << analyzer.diameter() << "\n";

    cout << analyzer.openClosedTriangleRatio() << "\n";

    cout << analyzer.topKOpenTriangles(2) << "\n";
*/
    cout<<"33"<<endl;
    int newNodeID = 5;
    vector<float> newFeatures {3, 3};
    Node newNode = Node(newNodeID, newFeatures);
    cout<<"37"<<endl;
    analyzer.insert(newNode);
    analyzer.insert(Edge(4, 5, 32));

    cout<<"41"<<endl;
    vector<float> weights{.5, .5};
    cout<<"43"<<endl;
    vector<int> neighbors = analyzer.topKNeighbors(2, 2, weights);
    cout<<"45"<<endl;
    for(auto i = neighbors.begin(); i != neighbors.end(); ++i)
        cout << *i << ",";
    cout << "\n";

    /*cout << analyzer.topNonNeighbor(2, weights) << "\n";

    cout << analyzer.jacardIndexOfTopKNeighborhoods(1, 2, 2, weights);
    */
    return 0;
}
