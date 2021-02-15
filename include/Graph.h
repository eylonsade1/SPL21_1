#ifndef GRAPH_H_
#define GRAPH_H_

#include <vector>
using namespace std;
class Graph{
public:
    Graph(std::vector<std::vector<int>> matrix);

    void infectNode(int nodeInd);
    void carryNode(int nodeInd);
    bool isInfected(int nodeInd);
    bool isCarry(int nodeInd);

    std::vector<int> getVector(int i) const;
    int getInfected();
    vector<int>* getCarry();
    void emptyCarry();
    void disconnect(int);
    virtual ~Graph();


private:
    vector<vector<int>> edges;
    vector<int> infected; //red
    vector<int> carry;  //yellow

};

#endif