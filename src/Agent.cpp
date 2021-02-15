#include "../include/Agent.h"
#include <vector>
#include <algorithm>
#include "../include/Tree.h"
using namespace std;

Agent::Agent() {

}

Agent::~Agent() {}



ContactTracer::ContactTracer() {

}

ContactTracer *ContactTracer::clone() const {
    return new ContactTracer(*this);
}

void ContactTracer::act(Session &session) {
    int infected = -1;
    Graph g = session.getGraph();

    vector<int> *carry = g.getCarry();
    for(int i: *carry){
        if (g.isInfected(i)){
            infected = i;
            carry->erase(remove(carry->begin(), carry->end(), i), carry->end());
            break;
        }
    }

    if (infected == -1)
        return;

    Tree *tree  = Tree::createTree(session, infected);
    int actOn = tree -> traceTree();
    delete tree;
    tree = nullptr;
    g.disconnect(actOn);
    session.setGraph(g);


}

ContactTracer::~ContactTracer() {}

Virus::Virus(int nodeInd): nodeInd(nodeInd){};

void Virus::act(Session &session) {
    vector<int> neighbors = session.getGraph().getVector(this->nodeInd);
    Graph g = session.getGraph();
    if (!g.isInfected(this->nodeInd)){
        g.infectNode(this -> nodeInd);
        session.setGraph(g);
    }
    int len = neighbors.size();
    for (int i = 0; i < len ; i++){
        if (neighbors[i] == 1 && !g.isInfected(i) && !g.isCarry(i)){
            g.carryNode(i);
            session.setGraph(g);
            break;
        }
    }

}


Virus *Virus::clone() const{
    return new Virus(*this);
}

Virus::~Virus() {}





