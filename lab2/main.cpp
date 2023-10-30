#include "Tree.h"

int main() {
    Tree tree;
    tree.setStartNode({
        {6, 0, 8},
        {5, 2, 1},
        {4, 3, 7}
    });
    tree.setEndNode({
        {1, 2, 3},
        {8, 0, 4},
        {7, 6, 5}
    });

    // h1 - true
    // h2 - false
    tree.aStar(false, *tree.getStartNode());
    std::cout << "Time complexity: " << tree.getStepCount() << " steps" << std::endl;
    std::cout << "Capacity: " << tree.getCapacity() << " nodes" << std::endl;
    return 0;
}
