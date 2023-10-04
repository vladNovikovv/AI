#pragma once
#include <iostream>
#include <vector>
#include <unordered_set>

typedef std::vector<std::vector<int>> vector;

class Node {
public:
    struct HashFunction {
        size_t operator()(const Node& node) const {
            std::string str;
            for (auto& s : node.mat) {
                for (auto& r : s) {
                    str += std::to_string(r);
                }
            }
            return std::hash<std::string>()(str);
        }
    };

private:
    vector mat;
    int depth;
    Node* parent;
    std::vector<Node*> childs;

    void makeChild (int zeroI, int zeroJ, int iDiff, int jDiff, std::unordered_set<Node, Node::HashFunction>& usedNodes);

public:
//    static std::unordered_set<Node, Node::HashFunction> usedNodes;
    static bool isUsed(const Node& node, std::unordered_set<Node, Node::HashFunction>& usedNodes);
    std::vector<Node> duplicatedNodes;

    int getDepth() const;
    vector &getMat();

    Node();
    explicit Node(const vector& v);
    bool operator == (const Node& node) const;
    Node& operator = (const Node& node);
    std::vector<Node*> makeChilds(std::unordered_set<Node, Node::HashFunction>& usedNodes);
    std::vector<Node*> getChilds();
    friend std::ostream& operator << (std::ostream& os, const Node& node);

    Node *getParent() const;

    ~Node();
};

std::ostream &operator<<(std::ostream &os, const std::vector<int>& v);

std::ostream &operator<<(std::ostream &os, const Node &node);