#include "../include/Tree.h"
#include <vector>
#include <iostream>
#include <algorithm>
#include "../include/Graph.h"
#include "../include/Session.h"
using namespace std;

Tree::Tree(int rootLabel):node (rootLabel), children(), depth(0){};

void Tree::addChild(const Tree& child){
    children.push_back(child.clone());
}

Tree *Tree::createTree(const Session &session, int rootLabel) {
    Graph g = session.getGraph();
    TreeType treeType = session.getTreeType();
    vector<int> vec = g.getVector(rootLabel);
    vector<int> allEdges(vec.size());
    fill_n(allEdges.begin(),allEdges.size(),0);
    allEdges[rootLabel] = 1;
    Tree *tree= nullptr;
    if (treeType == Cycle)
        tree = new CycleTree(rootLabel, session.cycleNum());
    else if (treeType == MaxRank)
        tree =  new MaxRankTree(rootLabel);
    else
        tree = new RootTree(rootLabel);

    int edgesNum = vec.size();
    vector<Tree*> depths;
    depths.push_back(tree);
    Tree *firstTree = tree;
            vector<vector<int>> edges = {vec};
            vector<vector<int>> sons;
            int de = 0;
            for (int j = 0; j < edgesNum ; j++) {

                for (vector<int> v: edges) {
                    int sonCounter = 0;
                    tree = depths.front();
                    depths.erase(depths.begin());
                    tree->depth = de;

                    for (int i = 0; i < edgesNum; i++) {
                        if (v[i] == 1 && allEdges[i] != 1) {
                            if (treeType == Cycle)
                                tree->addChild(CycleTree(i, session.cycleNum()));
                            else if (treeType == MaxRank)
                                tree->addChild(MaxRankTree(i));
                            else
                                tree->addChild( RootTree(i));

                            depths.push_back(tree->getChild(sonCounter));
                            sons.push_back(g.getVector(i));
                            allEdges[i] = 1;
                            sonCounter++;
                        }

                    }

                }

                if (sons.empty())
                    break;

                edges = sons;
                sons.clear();
                de++;
            }
    return firstTree;
}

int Tree::getRoot() { return node;}

int Tree::childrenSize() { return children.size(); }

Tree *Tree::getChild(int inPlace) { return children[inPlace];}

CycleTree::CycleTree(int rootLabel, int currCycle): Tree(rootLabel), currCycle(currCycle) {};

int CycleTree::traceTree() {
    Tree *t = this;
    for(int i = 0; i < currCycle; i++){
        if(t->childrenSize() == 0)
            return t->getRoot();
        t = t -> getChild(0);
    }
    return t->getRoot();
}

MaxRankTree::MaxRankTree(int rootLabel) : Tree(rootLabel) {
};

int MaxRankTree::traceTree() {

    int maxRank = -1;
    vector<Tree*> allTrees;

    allTrees.push_back(this);
    int size = this->childrenSize();
    for (int i = 0 ; i < size ; i++) {
        allTrees.push_back(this->getChild(i));
    }
    size = allTrees.size(); //the size of the vector
    for (int index =1 ; index < size ; index++) {
        int size2 = allTrees[index]->childrenSize(); //the size of the children
        for (int i =0; i < size2; i++) {
            allTrees.push_back(allTrees[index]->getChild(i));
        }
        size = allTrees.size();
    }

    Tree* maxRankedTree;
    for (int i = 0 ;i < size ; i++) {
        if (allTrees[i]->childrenSize() > maxRank) {
            maxRank = allTrees[i]->childrenSize();
            maxRankedTree = allTrees[i];
        }
        else if(allTrees[i]->childrenSize() == maxRank) {
            if (maxRankedTree -> getDepth() > allTrees[i]->getDepth()) {
                maxRank = allTrees[i]->childrenSize();
                maxRankedTree = allTrees[i];
            }
        }
    }
    return maxRankedTree->getRoot();
}

RootTree::RootTree(int rootLabel) : Tree(rootLabel) {}

int RootTree::traceTree() { return getRoot();}

int Tree::getDepth() { return this->depth;}

Tree::~Tree() {

    for(auto &child : children){
        if(child !=nullptr) {
            delete child;
            child = nullptr;
        }
    }
    children.clear();
}

Tree &Tree::operator=(const Tree &other) {
    node = other.node;
    depth = other.depth;
    if(!children.empty()){
        for (auto t : children) {
                delete t;
        }
    }
    children =other.children;
    return *this;
}

Tree::Tree(const Tree &tree): node(tree.node),children(), depth(tree.depth) {

   for(auto child: tree.children){
       addChild(*child);
   }
}


Tree *MaxRankTree::clone() const {
    return new MaxRankTree(*this);
}




Tree *RootTree::clone() const{
    return new RootTree(*this);
}


Tree *CycleTree::clone() const{
    return new CycleTree(*this);
}


