#include <string>
#include <vector>
#include "FeatureGraph.h"
//#include "GraphHelper.h"
#include <iostream>
#include <algorithm>
#include <queue>

#define INF 9999

using namespace std;

bool operator < (Triangle t1, Triangle t2) {
    return t1.getTotalWeight() <= t2.getTotalWeight();
}

FeatureGraph::FeatureGraph(int N, int d, vector<Node> nodes, vector<Edge> edges) {
    this->numberOfNodes = N;
    this->sizeOfSkill   = d;

    for (int i=0; i<nodes.size();i++) {
        this->allNodes.push_back(nodes[i]);
//        cout << allNodes[i].id << endl;
    }

//    for (int i=0; i<allNodes.size();i++) {
//        cout << "node id is " << allNodes[i].id << endl;
//    }

    for (int i=0; i<edges.size(); i++) {
        this->allEdges.push_back(edges[i]);
    }

//    for (int i=0; i<allEdges.size();i++) {
//        cout << "edge is connected "<< allEdges[i].IdA << " and " << allEdges[i].IdB << endl;
//    }

    this->nodesMap = newMatrix(numberOfNodes, allEdges);
    this->nodesPathMap = newPathMatrix(numberOfNodes, allEdges);

    numberOfOpenTriangles = 0;
    numberOfClosedTriangles = 0;
    findTriangles();
};

void FeatureGraph::insert(Node node){
    //check if node has already been stored in graph
    if(find(node.id)){
        return;
    }

    this->numberOfNodes++;
    this->allNodes.push_back(node);

    //create a new column and row in the matrix
    //is there more convenient way to regenerate the whole matrix?
    this->nodesMap = newMatrix(numberOfNodes, allEdges);
    this->nodesPathMap = newPathMatrix(numberOfNodes, allEdges);
};

void FeatureGraph::insert(Edge edge){
    this->allEdges.push_back(edge);

    this->nodesMap = newMatrix(numberOfNodes, allEdges);
    this->nodesPathMap = newPathMatrix(numberOfNodes, allEdges);
//    findTriangles();
    findTriangles(edge.IdA);
    findTriangles(edge.IdB);
};

bool FeatureGraph::find(int id){
    for(vector<Node>::iterator nodeIt = allNodes.begin(); nodeIt != allNodes.end(); nodeIt++){
        if(nodeIt->id == id) return true;
//        cout << "node id is " << nodeIt->id << endl;
    }

    return false;
}

int FeatureGraph::getNodeIndex(int nodeId){
    for (int i=0; i<allNodes.size();i++) {
        if(this->allNodes[i].id == nodeId) return i;
    }

    return -1;
}

// return all nodes that connect to this input node
vector<Node> FeatureGraph::neigbors(int id){
    vector<Node> result;

    // if there is no id, return null
    if(!find(id)) return result;

    // find all nodes' id that have relation with given node's id
    for(int i = 0; i < numberOfNodes; i++){
        int index = getNodeIndex(id);
        if(this->nodesMap[index][i] == 1){

            // check if the edge contains the available node
            for(int eachNode = 0; eachNode < numberOfNodes; eachNode++){
                if(this->allNodes[eachNode].id == allNodes[i].id)  result.push_back(allNodes[i]);
            }
        }
    }

    return result;
}

// return all nodes that not connect to this input node
vector<Node> FeatureGraph::nonNeigbors(int id){
    vector<Node> result;

    // if there is no id, return null
    if(!find(id)) return result;

    //find all nodes' id that have relation with given node's id
    for(int i = 0; i < numberOfNodes; i++){
        int index = getNodeIndex(id);
        if(this->nodesPathMap[index][i] == INF){

            // check if the edge contains the available node
            for(int eachNode = 0; eachNode < numberOfNodes; eachNode++){
                if(this->allNodes[eachNode].id == allNodes[i].id)  {
                    result.push_back(allNodes[i]);
                }
            }
        }
    }

    return result;
}

//create a matrix that shows the relationship between nodes, 1 if these nodes are related, 0 if they are not
vector<vector<int> > FeatureGraph::newMatrix(int numberOfNodes, vector<Edge> edges){
    //create a matrix and set a matrix with all 0
    vector<vector<int> > matrix;
    for(int row = 0; row < numberOfNodes; row++){
        vector<int> temp;
        for(int column = 0; column < numberOfNodes; column++){
            temp.push_back(0);
        }
        matrix.push_back(temp);
    }

//    cout << "--" << endl;
    //go through every edge in edges and change the relationship matrix to 1 in these two nodes
    for(vector<Edge>::iterator edgeIt = edges.begin(); edgeIt != edges.end(); edgeIt++){
//            cout << "1" << endl;
            int idA = getNodeIndex(edgeIt->IdA);
            int idB = getNodeIndex(edgeIt->IdB);
//            cout << "2" << endl;

            if(idA == -1 || idB == -1){
                cout << "This " << edgeIt->IdA << " or " << edgeIt->IdB << " does not exist in map! " << endl;
                return matrix;
            }

            matrix[idA][idB] = 1;
            matrix[idB][idA] = 1;
    }

    return matrix;
}

void FeatureGraph::printMatrix(){
    for(int row = 0; row < this->numberOfNodes; row++){
        for(int column = 0; column < this->numberOfNodes; column++){
            cout << this->nodesMap[row][column];
//            cout << " ";
        }
        cout << endl;
    }
}

void FeatureGraph::printPathMatrix(){
    for(int row = 0; row < this->numberOfNodes; row++){
        for(int column = 0; column < this->numberOfNodes; column++){
            cout << this->nodesPathMap[row][column];
            cout << " ";
        }
        cout << endl;
    }
}

//create a matrix that shows the relationship between nodes, 1 if these nodes are related, 0 if they are not
vector<vector<int> > FeatureGraph::newPathMatrix(int numberOfNodes, vector<Edge> edges){
    //create a matrix and set a matrix with all 0
    vector<vector<int> > matrix;
    for(int row = 0; row < numberOfNodes; row++){
        vector<int> temp;
        for(int column = 0; column < numberOfNodes; column++){
            temp.push_back(INF);
        }
        temp[row] = 0;
        matrix.push_back(temp);
    }

    //go through every edge in edges and change the relationship matrix to the weight of their edges in these two nodes
    for(vector<Edge>::iterator edgeIt = edges.begin(); edgeIt != edges.end(); edgeIt++){
        int idA = getNodeIndex(edgeIt->IdA);
        int idB = getNodeIndex(edgeIt->IdB);

        if(idA == -1 || idB == -1){
            cout << "This " << edgeIt->IdA << " or " << edgeIt->IdB << " does not exist in map! " << endl;
            continue;
        }

        matrix[idA][idB] = edgeIt->weight;
        matrix[idB][idA] = edgeIt->weight;
    }

    return matrix;
}

// find the node and check if after the edge insertion, one of open triangle become closed triangle
void FeatureGraph::findTriangles(int nodeId){
    // if there is no id, just return
    if(!find(nodeId)) return;

    vector<Node> nodeNeighbors = neigbors(nodeId);
    for(int eachNode = 0; eachNode < nodeNeighbors.size(); eachNode++){
        int nodeAId = nodeNeighbors[eachNode].id;

        for(int nextNode = eachNode+1; nextNode < nodeNeighbors.size(); nextNode++){
            int nodeBId = nodeNeighbors[nextNode].id;

            int indexA = getNodeIndex(nodeAId);
            int indexB = getNodeIndex(nodeBId);

            // find the sequence of these three nodes by their id from the smallest to the largest
            priority_queue<int> priorityQueue;
            priorityQueue.push(nodeId);
            priorityQueue.push(nodeAId);
            priorityQueue.push(nodeBId);

            int nodeA = priorityQueue.top();
            priorityQueue.pop();
            int nodeB = priorityQueue.top();
            priorityQueue.pop();
            int nodeC = priorityQueue.top();
            priorityQueue.pop();

            // calculate the total weight of the triangle
            int node = getNodeIndex(nodeId);
            int totalWeight = nodesPathMap[node][indexA] + nodesPathMap[node][indexB];

            // find if this two neighbors have path, if they have, put them into closed triangle, else, put into open triagles
            // if there already exist the same triangle, skip it and continue
            if(this->nodesMap[indexA][indexB] == 1){

                totalWeight += nodesPathMap[indexA][indexB];
                Triangle closedTriangle(nodeC, nodeB, nodeA, false, totalWeight);
                addClosedTriangles(closedTriangle);

                // if it this is a open triangle, delete it in the open triangle
                for(int i = 0; i < numberOfOpenTriangles; i++){
                    if((openTriangles[i] = closedTriangle)){
                        this->openTriangles.erase(openTriangles.begin()+i);
                        numberOfOpenTriangles--;
                    }
                }
                continue;
            }

            Triangle openTriangle(nodeC, nodeB, nodeA, true, totalWeight);
            addOpenTriangles(openTriangle);
        }

    }

}

void FeatureGraph::findTriangles(){

    for(int eachNode = 0; eachNode < numberOfNodes; eachNode++){
        int nodeId = allNodes[eachNode].id;
        findTriangles(nodeId);
    }
}

void FeatureGraph::addOpenTriangles(Triangle t1){
    if(!t1.isOpenTriangle()){
        cout << "this triangle " << t1.getFirstNode() << ", " << t1.getSecondNode() << ", " << t1.getThirdNode() << " is not an open triangle!" << endl;
        return;
    }

    // check if t1 triangle is already in the open triangle lists
    for(vector<Triangle>::iterator triangle = openTriangles.begin(); triangle != openTriangles.end(); triangle++){
        if((t1 = *triangle))  return;
    }

    openTriangles.push_back(t1);
//    InsideTriangles.push(make_pair(t1.getTotalWeight(),t1));
    numberOfOpenTriangles++;
    cout << "this triangle " << t1.getFirstNode() << ", " << t1.getSecondNode() << ", " << t1.getThirdNode()
         << " is an open triangle! and its weight is " << t1.getTotalWeight() << endl;
}

void FeatureGraph::addClosedTriangles(Triangle t1){
    if(t1.isOpenTriangle()){
        cout << "this triangle " << t1.getFirstNode() << ", " << t1.getSecondNode() << ", " << t1.getThirdNode() << " is not a closed triangle!" << endl;
        return;
    }

    // check if t1 triangle is already in the open triangle lists
    for(vector<Triangle>::iterator triangle = closedTriangles.begin(); triangle != closedTriangles.end(); triangle++){
        if((t1 =(*triangle)))  return;
    }

    closedTriangles.push_back(t1);
//    InsideTriangles.push(make_pair(t1.getTotalWeight(),t1));
    numberOfClosedTriangles++;
    cout << "this triangle " << t1.getFirstNode() << ", " << t1.getSecondNode() << ", " << t1.getThirdNode()
         << " is a closed triangle and its weight is " << t1.getTotalWeight() << endl;
}