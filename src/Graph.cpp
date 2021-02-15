#include "../include/Graph.h"
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;


Graph::Graph(vector<vector<int>> matrix): edges(matrix), infected(), carry() {};

void Graph::infectNode(int nodeInd){
    infected.push_back(nodeInd);
}
//inserts a new edge to the carry vector
void Graph::carryNode(int nodeInd){
    carry.push_back(nodeInd);
}

//checks if the node is red
bool Graph::isInfected(int nodeInd){
    if(find(infected.begin(), infected.end(),  nodeInd) != infected.end())
        return true;
    else
        return false;
}

//checks if the node is yellow
bool Graph::isCarry(int nodeInd){
    if(find(carry.begin(), carry.end(),  nodeInd) != carry.end())
        return true;
    else
        return false;
}

//edges for ContactTracer to handle
int Graph:: getInfected(){
    int inf = infected.front();
    infected.erase(infected.begin());
    return inf;
};

//returns the carry vector
vector<int> *Graph::getCarry(){
    return &carry;
};

//returns the vector representing a specific edge in the graph
vector<int> Graph::getVector(int i) const {
    return edges[i];

}

//emptys the carry vector
void Graph::emptyCarry() {
    carry.clear();
}


void Graph::disconnect(int index) {
    fill_n(edges[index].begin(),edges[index].size(),0);
    int len = edges.size();
    for (int i = 0; i < len ; i++){
        edges[i][index] = 0;
    }
}

Graph::~Graph() {
    edges.clear();
    infected.clear();
    carry.clear();
}


