#include "Tree.h"

//#define STEP_BY_STEP

Tree::Tree() :
    nodeFound(false)
{
    usedNodes.reserve(20000);

    root = nullptr;
    endNode = nullptr;
    stepCount = 0;
    capacity = 0;
}

void Tree::setStartNode(vector &&startState)
{
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

void Tree::dfs(Node* node) {
    if (nodeFound) {
        return;
    }
    stepCount++;
    node->makeChilds(usedNodes);
#ifdef STEP_BY_STEP
    if(!nodeFound) {
        std::cout << "Current node isn't goal" << std::endl;
    }
    showParentInfo(*node);
#endif
    for (auto child : node->getChilds()) {
        if (*child == *endNode) {
            std::cout << "FIND!\n";
            std::cout << *child << "\n";
            nodeFound = true;
            capacity = usedNodes.size();
            break;
        }
        dfs(child);
    }
}

Tree::~Tree() {
    delete root;
    delete endNode;
}

std::vector<Node*> Tree::getVectorChilds(Tree& parentTree, const std::vector<Node*>& parents) {
    std::vector<Node*> childs;
    for (auto parent : parents) {
        parent->makeChilds(parentTree.usedNodes);
        for (auto child : parent->getChilds()) {
            childs.push_back(child);
        }
    }
    return childs;
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

void Tree::bds(Tree &start, Tree &goal) {
    if (*start.root == *goal.root) {
        return;
    }
    std::vector<Node*> startNodes, goalNodes, temp;
    startNodes.push_back(start.root);
    goalNodes.push_back(goal.root);
    while(true) {
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
            }
            std::cout << "Current node isn't goal" << std::endl;
            showParentInfo(*curNode);
#endif
        }
        startNodes = temp;
        temp.clear();

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
            }
            std::cout << "Current node isn't goal" << std::endl;
            showParentInfo(*curNode);
#endif
        }
        goalNodes = temp;
        temp.clear();
    }
}

void Tree::showParentInfo(Node& parent){
    std::cout << "Current node:\n" << parent;
    auto childs = parent.getChilds();
    if (childs.empty()) {
        std::cout << "Node hasn't childs" << std::endl;
    }else {
        std::cout << "New appended nodes:\n";
        for (int j = 0; j < childs[0]->getMat().size(); ++j) {
            for (auto &child: childs) {
                std::cout << (child->getMat())[j] << " ";
            }
            std::cout << "\n";
        }
    }
    if (parent.duplicatedNodes.empty()) {
        std::cout << "Node hasn't duplicated childs" << std::endl;
    }else {
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
