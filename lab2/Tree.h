#pragma once
#include "Node.h"
#include <queue>
#include <stack>
#include <algorithm>

class Tree {
private:
    Node* root;
    Node* endNode;
    bool nodeFound;
    std::unordered_set<Node, Node::HashFunction> usedNodes;

    int stepCount;
    size_t capacity;
public:
    Tree();

    Node* getStartNode();
    void setStartNode(vector&& startState);
    Node* getEndNode();
    void setEndNode(vector&& endState);
    int getStepCount() const;
    size_t getCapacity() const;

    int h1(Node* node);
    int h2(Node* node);
    int g(Node* node);

    void dfs(Node* node, bool h1_h2);

    ~Tree();

    static void bds(Tree& start, Tree& goal, bool h1_h2);
    static void findPath(Node &curNode, Tree& tree, bool order);
    static void showParentInfo(Node& parent, bool firstStrategy, bool h1_h2);
};



