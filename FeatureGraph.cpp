#include <string>
#include <vector>
#include "FeatureGraph.h"
#include "GraphHelper.h"
#include <iostream>

using namespace std;


FeatureGraph::FeatureGraph(int N, int d, vector<Node> nodes, vector<Edge> edges) {
    this->numberOfNodes = N;
    this->sizeOfSkill   = d;
    this->allNodes = nodes;
    this->allEdges = edges;
    this->nodesMap = newMatrix(numberOfNodes, allEdges);
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
};
    
void FeatureGraph::insert(Edge edge){
    this->allEdges.push_back(edge);

    this->nodesMap = newMatrix(numberOfNodes, allEdges);
};

bool FeatureGraph::find(int id){
    for(vector<Node>::iterator nodeIt = allNodes.begin(); nodeIt != allNodes.end(); nodeIt++){
        if(nodeIt->id == id) return true;
//        cout << "node id is " << nodeIt->id << endl;
    }

    return false;
}

vector<int> FeatureGraph::neigborsId(int id){
    vector<int> result;

    // if there is no id, return null
    if(!find(id)) return result;

    //find all nodes' id that have relation with given node's id
    for(int i = 0; i < numberOfNodes; i++){
        if(this->nodesMap[id][i] == 1){
            result.push_back(i);
        }
    }

    return result;
}

vector<Node> FeatureGraph::neigbors(int id){
    vector<Node> result;

    // if there is no id, return null
    if(!find(id)) return result;

    //find all nodes' id that have relation with given node's id
    for(int i = 0; i < numberOfNodes; i++){
        if(this->nodesMap[id][i] == 1){

            for(int eachNode = 0; eachNode < numberOfNodes; eachNode++){
                if(this->allNodes[eachNode].id == i)  result.push_back(allNodes[eachNode]);
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

    //go through every edge in edges and change the relationship matrix to 1 in these two nodes
    for(vector<Edge>::iterator edgeIt = edges.begin(); edgeIt != edges.end(); edgeIt++){
            matrix[edgeIt->IdA][edgeIt->IdB] = 1;
            matrix[edgeIt->IdB][edgeIt->IdA] = 1;
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