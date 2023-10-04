#pragma once
#include "Node.h"
#include <queue>
#include <stack>

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

    void dfs(Node* node);
    static void bds(Tree& start, Tree& goal);
    static std::vector<Node*> getVectorChilds(Tree& parentTree, const std::vector<Node*>& parents) ;
        ~Tree();
    static void findPath(Node &curNode, Tree& tree, bool order);

    int getStepCount() const;

    static void showParentInfo(Node& parent);

    size_t getCapacity() const;
};



