#include "Node.h"

bool Node::isUsed(const Node &node, std::unordered_set<Node, Node::HashFunction>& usedNodes) {
    return usedNodes.find(node) != usedNodes.end();
}

Node::Node() : parent(nullptr), depth(0), gPrice(0) {
}

Node::Node(const vector &v) : parent(nullptr), depth(0), mat(v), gPrice(0) {
}

bool Node::operator == (const Node &node) const {
    return std::equal(mat.begin(), mat.end(), node.mat.begin());
}

Node& Node::operator=(const Node &node) {
    mat = node.mat;
    depth = node.depth;
    parent = node.parent;
    return *this;
}

std::vector<Node *>& Node::makeChilds(std::unordered_set<Node, Node::HashFunction>& usedNodes) {
    int zeroI, zeroJ;
    for (int i = 0; i < mat.size(); ++i) {
        for (int j = 0; j < mat.size(); ++j) {
            if (mat[i][j] == 0) {
                zeroI = i;
                zeroJ = j;
                break;
            }
        }
    }

    if (zeroI != 0) { // двигаем верхнюю вниз
        makeChild(zeroI, zeroJ, -1, 0, usedNodes);
    }
    if (zeroI != mat.size() - 1) { // двигаем нижнюю вверх
        makeChild(zeroI, zeroJ, 1, 0, usedNodes);
    }
    if (zeroJ != 0) { // двигаем левую вправо
        makeChild(zeroI, zeroJ, 0, -1, usedNodes);
    }
    if (zeroJ != mat.size() - 1) { // двигаем правую влево
        makeChild(zeroI, zeroJ, 0, 1, usedNodes);
    }
    return childs;
}

void Node::makeChild (int zeroI, int zeroJ, int iDiff, int jDiff, std::unordered_set<Node, Node::HashFunction>& usedNodes) {
    vector newMat = mat;
    int valueForSwap = newMat[zeroI + iDiff][zeroJ + jDiff];
    std::swap(newMat[zeroI][zeroJ], newMat[zeroI + iDiff][zeroJ + jDiff]);
    Node *newNode = new Node(newMat);
    if (isUsed(*newNode, usedNodes)) {
        duplicatedNodes.push_back(*newNode);
        delete newNode;
        return;
    } //

    newNode->parent = this;
    newNode->depth = depth + 1;
    newNode->gPrice = gPrice + valueForSwap;
    usedNodes.insert(*newNode);
    childs.push_back(newNode);
}

Node::~Node() {
    for (auto child : childs) {
        delete child;
    }
}

int Node::getDepth() const {
    return depth;
}

std::vector<Node *> Node::getChilds() {
    return childs;
}

vector &Node::getMat() {
    return mat;
}

std::ostream &operator<<(std::ostream &os, const Node &node) {
    for (auto &m: node.mat) {
        os << m << "\n";
    }
    os << "\n";
    return os;
}

Node *Node::getParent() const {
    return parent;
}

int Node::getH1Price() const {
    return h1Price;
}

void Node::setH1Price(int h1Price) {
    Node::h1Price = h1Price;
}

int Node::getH2Price() const {
    return h2Price;
}

void Node::setH2Price(int h2Price) {
    Node::h2Price = h2Price;
}

int Node::getGPrice() const {
    return gPrice;
}

void Node::setGPrice(int gPrice) {
    Node::gPrice = gPrice;
}

std::ostream &operator<<(std::ostream &os, const std::vector<int>& v) {
    for (auto &m: v) {
        os << " " << m << " ";
    }
    return os;
}