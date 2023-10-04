#include "Tree.h"

#define STEP_BY_STEP

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

void Tree::dfs(Node* node, bool h1_h2) {
    if (nodeFound) {
        return;
    }
    stepCount++;
    auto& childs = node->makeChilds(usedNodes);
    if (childs.size() == 1) {
        h1(childs.at(0));
        h2(childs.at(0));
    }
    std::sort(childs.begin(), childs.end(), [&](Node* l, Node* r){
        return g(l) + (h1_h2 ? h1(l) : h2(l)) < g(r) + (h1_h2 ? h1(r) : h2(r));
    });
#ifdef STEP_BY_STEP
    if(!nodeFound) {
        std::cout << "Current node isn't goal" << std::endl;
    }
    showParentInfo(*node, true, h1_h2);
#endif
    for (auto child : node->getChilds()) {
        if (*child == *endNode) {
            std::cout << "FIND!\n";
            std::cout << *child << "\n";
            nodeFound = true;
            capacity = usedNodes.size();
            break;
        }
        dfs(child, h1_h2);
    }
}

Tree::~Tree() {
    delete root;
    delete endNode;
}

void Tree::findPath(Node &curNode, Tree& tree, bool order) {
    std::stack<Node> stack;
    Node tmpNode = *(tree.usedNodes.find(curNode));
    while(!(tmpNode == *(tree.root))){
        tmpNode = *(tmpNode.getParent());
        stack.push(tmpNode);
        // Прямой вывод
        if(order){
            std::cout << tmpNode;
        }
    }
    // Обратный вывод
    if(!order){
        while(!stack.empty()){
            std::cout << stack.top();
            stack.pop();
        }
    }
}

void Tree::bds(Tree &start, Tree &goal, bool h1_h2) {
    if (*start.root == *goal.root) {
        return;
    }
    std::vector<Node*> startNodes, goalNodes, temp;
    startNodes.push_back(start.root);
    goalNodes.push_back(goal.root);
    while(true) {
        if (startNodes.size() == 1) {
            start.h1(startNodes.at(0));
            start.h2(startNodes.at(0));
        }else{
            std::sort(startNodes.begin(), startNodes.end(), [&](Node* l, Node* r){
                return start.g(l) + (h1_h2 ? start.h1(l) : start.h2(l)) < start.g(r) + (h1_h2 ? start.h1(r) : start.h2(r));
            });
        }
        for (auto curNode : startNodes) {
            start.stepCount++;
            if (goal.usedNodes.find(*curNode) != goal.usedNodes.end()) {
                std::cout << "Path: " << std::endl;
                findPath(*curNode, start, false);
                std::cout << "FIND = " << *curNode;
                findPath(*curNode, goal, true);
                start.capacity = start.usedNodes.size();
                goal.capacity = goal.usedNodes.size();
                return ;
            } else {
                for(auto curNodeChild: curNode->makeChilds(start.usedNodes)){
                    temp.push_back(curNodeChild);
                }
            }
#ifdef STEP_BY_STEP
            std::cout << "--------------------START TREE--------------------------" << std::endl;
            auto it = std::find(startNodes.begin(), startNodes.end(), curNode)+1;
            if (it == startNodes.end()) {
                std::cout << "There is no nodes for unpacking" << std::endl;
            } else {
                std::cout << "Nodes for unpacking: " << std::endl;
                for (int j = 0; j < curNode->getMat().size(); ++j) {
                    for (auto it_1=it; it_1 < startNodes.end(); ++it_1) {
                        std::cout << ((*it_1)->getMat())[j] << " ";
                    }
                    std::cout << "\n";
                }

                std::cout << " ";
                for (auto it_1=it; it_1 < startNodes.end(); ++it_1) {
                    printf("g = %-3d   ", (*it_1)->getGPrice());
                }
                std::cout << "\n ";
                for (auto it_1=it; it_1 < startNodes.end(); ++it_1) {
                    h1_h2 ? printf("h1 = %-2d   ", (*it_1)->getH1Price()) : printf("h2 = %-2d   ", (*it_1)->getH2Price());
                }
                std::cout << "\n ";
            }
            std::cout << "Current node isn't goal" << std::endl;
            showParentInfo(*curNode, false, false);
#endif
        }
        startNodes = temp;
        temp.clear();

        if (goalNodes.size() == 1) {
            goal.h1(goalNodes.at(0));
            goal.h2(goalNodes.at(0));
        } else {
            std::sort(goalNodes.begin(), goalNodes.end(), [&](Node* l, Node* r){
                return goal.g(l) + (h1_h2 ? goal.h1(l) : goal.h2(l)) < goal.g(r) + (h1_h2 ? goal.h1(r) : goal.h2(r));
            });
        }
        for (auto curNode : goalNodes) {
            goal.stepCount++;
            if (start.usedNodes.find(*curNode) != start.usedNodes.end()) {
                std::cout << "Path: " << std::endl;
                findPath(*curNode, start, false);
                std::cout << "FIND = \n" << *curNode;
                findPath(*curNode, goal, true);
                goal.capacity = goal.usedNodes.size();
                start.capacity = start.usedNodes.size();
                return;
            } else {
                for (auto curNodeChild: curNode->makeChilds(goal.usedNodes)) {
                    temp.push_back(curNodeChild);
                }
            }
#ifdef STEP_BY_STEP
            std::cout << "--------------------GOAL TREE---------------------------" << std::endl;

            auto it = std::find(goalNodes.begin(), goalNodes.end(), curNode)+1;
            if (it == goalNodes.end()) {
                std::cout << "There is no nodes for unpacking" << std::endl;
            } else {
                std::cout << "Nodes for unpacking: " << std::endl;
                for (int j = 0; j < curNode->getMat().size(); ++j) {
                    for (auto it_1=it; it_1 < goalNodes.end(); ++it_1) {
                        std::cout << ((*it_1)->getMat())[j] << " ";
                    }
                    std::cout << "\n";
                }

                std::cout << " ";
                for (auto it_1=it; it_1 < startNodes.end(); ++it_1) {
                    printf("g = %-3d   ", (*it_1)->getGPrice());
                }
                std::cout << "\n ";
                for (auto it_1=it; it_1 < startNodes.end(); ++it_1) {
                    h1_h2 ? printf("h1 = %-2d   ", (*it_1)->getH1Price()) : printf("h2 = %-2d   ", (*it_1)->getH2Price());
                }
                std::cout << "\n ";
            }
            std::cout << "Current node isn't goal" << std::endl;
            showParentInfo(*curNode, false, false);
#endif
        }
        goalNodes = temp;
        temp.clear();
    }
}

void Tree::showParentInfo(Node& parent, bool firstStrategy, bool h1_h2){
    std::cout << "Current node:\n" << parent;
    auto childs = parent.getChilds();
    if (childs.empty()) {
        std::cout << "Node hasn't childs" << std::endl;
    } else {
        std::cout << "New appended nodes:\n";
        for (int j = 0; j < childs[0]->getMat().size(); ++j) {
            for (auto &child: childs) {
                std::cout << (child->getMat())[j] << " ";
            }
            std::cout << "\n";
        }
        if (firstStrategy) {
            std::cout << " ";
            for (auto &child: childs) {
                printf("g = %-3d   ", child->getGPrice());
            }
            std::cout << "\n ";
            for (auto &child: childs) {
                h1_h2 ? printf("h1 = %-2d   ", child->getH1Price()) : printf("h2 = %2d   ", child->getH2Price());
            }
        }
        std::cout << "\n";
    }
    if (parent.duplicatedNodes.empty()) {
        std::cout << "Node hasn't duplicated childs" << std::endl;
    } else {
        std::cout << "Duplicated nodes:\n";
        for (int j = 0; j < parent.duplicatedNodes[0].getMat().size(); ++j) {
            for (auto & duplicate : parent.duplicatedNodes) {
                std::cout << (duplicate.getMat())[j] << " ";
            }
            std::cout << "\n";
        }
    }

    std::cout << std::endl;
    std::cin.get();
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

