#include "Tree.h"

//#define STEP_BY_STEP
//#define A_STAR

Tree::Tree() :
    nodeFound(false)
{
    usedNodes.reserve(20000);

    root = nullptr;
    endNode = nullptr;
    stepCount = 0;
    capacity = 0;
}

void Tree::setStartNode(vector &&startState) {
    this->root = new Node(startState);
    usedNodes.insert(*root);
}

Node* Tree::getStartNode()
{
    return root;
}

Node* Tree::getEndNode()
{
    return endNode;
}

void Tree::setEndNode(vector &&endState)
{
    this->endNode = new Node(endState);
}

Tree::~Tree() {
    delete root;
    delete endNode;
}

int Tree::getStepCount() const {
    return stepCount;
}

size_t Tree::getCapacity() const {
    return capacity;
}

int Tree::h1(Node *node) {
    int ans = 0;

    for (int i = 0; i < node->getMat().size(); i++)
        for (int j = 0; j < node->getMat().size(); j++)
            if (node->getMat()[i][j] != endNode->getMat()[i][j] && node->getMat()[i][j] != 0)
                ans = ans + 1;
    node->setH1Price(ans);
    return ans;
}

int Tree::h2(Node *node) {
    int distance = 0;

    auto getIndexes = [this](int digit) {
        for (int i = 0; i < this->endNode->getMat().size(); ++i) {
            for (int j = 0; j < this->endNode->getMat().size(); ++j) {
                if (this->endNode->getMat()[i][j] == digit) {
                    return std::pair {i, j};
                }
            }
        }
    };

    for (int i = 0; i < node->getMat().size(); i++) {
        for (int j = 0; j < node->getMat().size(); j++) {
            if (node->getMat()[i][j] != 0) {
                std::pair currentDistance = getIndexes(node->getMat()[i][j]);
                distance += abs(currentDistance.first - i) + abs(currentDistance.second - j);
            }
        }
    }

    node->setH2Price(distance);
    return distance;
}

int Tree::g(Node *node) {
    return node->getGPrice();
}

void Tree::aStar(bool h1_h2, Node& node) {
#ifdef STEP_BY_STEP
    if(!map.empty()) {
        std::cout << "Nodes for unpacking: " << std::endl;
        for (int j = 0; j < map.begin()->second.first.getMat().size(); ++j) {
            for (auto element: map) {
                if(!element.second.second) {
                    std::cout << ((element.second.first).getMat())[j] << " ";
                }
            }
            std::cout << "\n";
        }

        std::cout << " ";
        for (auto element: map) {
            if(!element.second.second) {
                printf("g = %-3d   ", (element.second.first).getGPrice());
            }
        }
        std::cout << "\n ";
        for (auto element: map) {
            if(!element.second.second) {
                h1_h2 ? printf("h1 = %-2d   ", (element.second.first).getH1Price()) : printf("h2 = %-2d   ", (element.second.first).getH2Price());
            }
        }
        std::cout << "\n ";
    }
    std::cout << "Current node: " << std::endl;
    std::cout << node;
    printf(" g = %-3d   \n", (node).getGPrice());
    h1_h2 ? printf(" h1 = %-2d   ", (node).getH1Price()) : printf(" h2 = %-2d   ", (node).getH2Price());
#endif

    if(node == *endNode){
        std::cout << "Found node: \n" << node << "\n";
        std::cout << "Depth = " << node.getDepth() << "\n";
        nodeFound = true;
        return;
    }
    if(nodeFound) return;

#ifdef STEP_BY_STEP
    std::cout << "\nNode is not goal" << std::endl;
#endif

    if(node == *root)
    {
        addToMap(node, h1_h2);
    }
    stepCount++;
    auto& childs = node.makeChilds();

#ifdef STEP_BY_STEP
    std::cout << "\nChilds: " << std::endl;
    for (int j = 0; j < node.getMat().size(); ++j) {
        for (auto child : childs) {
            std::cout << (child->getMat())[j] << " ";
        }
        std::cout << "\n";
    }
#endif

    for (Node *child: childs) {
        addToMap(*child, h1_h2);
    }
    std::pair<const int, std::pair<Node, bool>> newNode = {f(node, h1_h2), {node, false}};
    std::find_if(
            map.begin(),
            map.end(),
            [newNode](const auto& mapObject)
            { return mapObject.second.first == newNode.second.first; })->second.second = true;

#ifdef STEP_BY_STEP
    std::cout << std::endl;
    std::cin.get();
#endif

    for(auto &curNode: map){
        if(!curNode.second.second){
            aStar(h1_h2, curNode.second.first);
            break;
        }
    }

}

void Tree::addToMap(Node &node, bool h1_h2) {
    capacity++;
    std::pair<const int, std::pair<Node, bool>> newNode = {f(node, h1_h2), {node, false}};
    auto it = std::find_if(
            map.begin(),
            map.end(),
            [node](const auto& mapObject) { return mapObject.second.first == node; });
    if(it != map.end()){
        if (it->second.first.getGPrice() > node.getGPrice()){
            map.erase(it);
            map.insert(newNode);
        }
    } else{
        map.insert(newNode);
    }
}

int Tree::f(Node &node, bool h1_h2) {
    return
#ifdef A_STAR
node.getGPrice() +
#endif
    (h1_h2 ? h1(&node) : h2(&node));
}

