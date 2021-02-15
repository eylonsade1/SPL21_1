#include "../include/Session.h"
#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include "../include/Graph.h"
#include "../include/Tree.h"
#include "../include/json.hpp"
#include "../include/Agent.h"

using json = nlohmann::json;
using namespace std;


Session::Session(const string &path) : g({}), treeType(), agents(),cycle(0) {
    ifstream i(path);
    json j;
    i >> j;
    g = Graph(j["graph"]);
    for (auto &elem: j["agents"]) {
        Agent *newAgent;
        if (elem[0] == "V") {
            newAgent = new Virus(elem[1]);
            g.carryNode(elem[1]);
        } else
            newAgent = new ContactTracer();
        agents.push_back(newAgent);
    }

    if (j["tree"] == "M")
        treeType = MaxRank;
    if (j["tree"] == "C")
        treeType = Cycle;
    if (j["tree"] == "R")
        treeType= Root;
}

const int Session::cycleNum() const {
    return cycle;
}

void Session::simulate() {
    while (!terminate()) {
        for (auto &elem : agents)
            elem->act(*this);
        vector<int> *vCarry = g.getCarry();
        for (int v: *vCarry) {
            if (!g.isInfected(v)) {
                addAgent(Virus(v));
            }
        }
        cycle++;
    }

    vector<vector<int>> finalGraph;
    int size = g.getVector(0).size();
    vector<int> finalInfected;
    for (int i = 0; i < size; i++) {
        finalGraph.push_back(g.getVector(i));
        if (g.isInfected(i))
            finalInfected.push_back(i);
    }
    json j;
    j["graph"] = finalGraph;
    j["infected"] = finalInfected;
    ofstream i("./output.json");
    i << j;
}

void Session::addAgent(const Agent &agent) {
    agents.push_back(agent.clone());
}

void Session::setGraph(const Graph &graph) {
    g = graph;
}

const Graph Session::getGraph() const {
    return g;
}


TreeType Session::getTreeType() const {
    return treeType;
}

void Session::enqueueInfected(int edge) {
    g.infectNode(edge);
}

int Session::dequeueInfected() {
    return g.getInfected();
}

bool Session::terminate() {
    vector<int> *check = g.getCarry();
    for (int i: *check) {
        if (!g.isInfected(i))
            return false;
    }
    return true;
}

Session::~Session() {

    for(auto &agent : agents) {
        if (agent != nullptr)
            delete agent;
        agent = nullptr;
    }
        agents.clear();
}




