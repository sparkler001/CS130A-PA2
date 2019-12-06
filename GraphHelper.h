#ifndef HELPER_H
#define HELPER_H

#include <vector>
using namespace std;

struct Node {
    // NOTE: Do not edit node struct
    int id;
    vector<float> features;
    
    Node(int id, vector<float> features): id(id), features(features) {}
    Node(const Node &n2) { id = n2.id; features=n2.features;}
};


struct Edge {
    // NOTE: Do not edit Edge struct
    int IdA, IdB, weight;
    
    Edge(int IdA, int IdB, int weight): IdA(IdA), IdB(IdB), weight(weight) {}
};


class Triangle {
    // TODO make a Triangle class with appropriate fields and methods

public:

    Triangle() {
        IdA = -1;
        IdB = -1;
        IdC = -1;
        openTriangle = false;
        totalWeight = -1;
    }

    Triangle(int IdA, int IdB, int IdC, bool isOpenTriangle, int totalWeight):
        IdA(IdA), IdB(IdB), IdC(IdC), openTriangle(isOpenTriangle), totalWeight(totalWeight) {}

    bool isOpenTriangle() { return this->openTriangle; };

    int getFirstNode() { return IdA; };

    int getSecondNode() { return IdB; };

    int getThirdNode() { return IdC; };

    int getTotalWeight() const { return totalWeight; };

    // Operator overloading for storage in priority queue
    // returns true iff t2 is greater than t1.
    //
    // Note: Must be trans itive
    //      This means if t1<t2 and t2<t3 than t1< t3

//    bool operator < (Triangle other) {
//        return totalWeight <= other.totalWeight;
//    };

    bool operator = (Triangle other) {
        return ((IdA == other.IdA) && (IdB == other.IdB) && (IdC == other.IdC));
    };
private:
    int IdA;
    int IdB;
    int IdC;
    bool openTriangle;
    int totalWeight;
};

//struct CompareWeight {
//    bool operator < (Triangle const &t1, Triangle const &t2) {
//        return t1.getTotalWeight() <= t2.getTotalWeight();
//    }
//};

bool operator < (Triangle t1, Triangle t2);
//{
//    return t1.getTotalWeight() <= t2.getTotalWeight();
//}


//bool operator = (Triangle const &other) {
//    return ((IdA == other.IdA) && (IdB == other.IdB) && (IdC == other.IdC));
//}

#endif

    




    
