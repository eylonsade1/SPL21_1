#ifndef TREE_H_
#define TREE_H_

#include "../include/Session.h"
#include <vector>

class Session;

class Tree{
public:
    Tree(int rootLabel);
    void addChild(const Tree& child);
    int getRoot();
    int childrenSize();
    Tree* getChild(int inPlace);
    Tree &operator= (const Tree &other);
    virtual ~Tree();
    static Tree* createTree(const Session& session, int rootLabel);
    virtual int traceTree()=0;
    virtual Tree *clone() const=0;
    int getDepth();
    Tree (const Tree& tree);



protected:
    int node;
    std::vector<Tree*> children;
private:
    int depth;

};

class CycleTree: public Tree{
public:
    CycleTree(int rootLabel, int currCycle);
    virtual int traceTree();

    virtual Tree *clone() const;

private:
    int currCycle;


};

class MaxRankTree: public Tree{
public:
    MaxRankTree(int rootLabel);


    virtual int traceTree();
    virtual Tree *clone() const;



};

class RootTree: public Tree{
public:
    RootTree(int rootLabel);
    virtual int traceTree();

    virtual Tree *clone() const;



};

#endif
