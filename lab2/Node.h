#pragma once
#include <iostream>
#include <vector>
#include <unordered_set>
#include <string>

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
    int gPrice, h1Price, h2Price;

public:
    int getH1Price() const;
    void setH1Price(int h1Price);
    int getH2Price() const;
    void setH2Price(int h2Price);
    int getGPrice() const;
    void setGPrice(int gPrice);

private:
    void makeChild (int zeroI, int zeroJ, int iDiff, int jDiff);

public:
    static bool isUsed(const Node& node, std::unordered_set<Node, Node::HashFunction>& usedNodes);
    std::vector<Node> duplicatedNodes;

    int getDepth() const;
    vector &getMat();
    Node *getParent() const;

    Node();
    explicit Node(const vector& v);
    bool operator == (const Node& node) const;
    Node& operator = (const Node& node);
    std::vector<Node*>& makeChilds(/*std::unordered_set<Node, Node::HashFunction>& usedNodes*/);
    std::vector<Node*> getChilds();
    friend std::ostream& operator << (std::ostream& os, const Node& node);

    ~Node();
};

std::ostream &operator<<(std::ostream &os, const std::vector<int>& v);

std::ostream &operator<<(std::ostream &os, const Node &node);