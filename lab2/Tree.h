#pragma once
#include "Node.h"
#include <queue>
#include <stack>
#include <algorithm>
#include <map>

class Tree {
private:
    Node* root;
    Node* endNode;
    bool nodeFound;
    std::unordered_set<Node, Node::HashFunction> usedNodes;
    std::multimap<int, std::pair<Node, bool>> map;

    int stepCount;
    size_t capacity;
public:
    Tree();

    void aStar(bool h1_h2, Node& node);
    void addToMap(Node& node, bool h1_h2);

    Node* getStartNode();
    void setStartNode(vector&& startState);
    Node* getEndNode();
    void setEndNode(vector&& endState);
    int getStepCount() const;
    size_t getCapacity() const;

    int h1(Node* node);
    int h2(Node* node);
    int g(Node* node);
    int f(Node& node, bool h1_h2);

    ~Tree();
};



