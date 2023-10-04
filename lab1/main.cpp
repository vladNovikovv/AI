#include "Tree.h"

//#define FIRST

int main() {
    Tree treeDfs, treeStart, treeGoal;

    // first strategy - dfs
#ifdef FIRST
    treeDfs.setStartNode({
        {6, 0, 8},
        {5, 2, 1},
        {4, 3, 7}
    });////jhjhj
    treeDfs.setEndNode({
        {1, 2, 3},
        {8, 0, 4},
        {7, 6, 5}
    });
    treeDfs.dfs(treeDfs.getStartNode());

    std::cout << "Time complexity: " << treeDfs.getStepCount() << " steps" << std::endl;
    std::cout << "Capacity: " << treeDfs.getCapacity() << " nodes" << std::endl;
#else
    // second strategy - bidirectional search
    treeStart.setStartNode({
        {6, 0, 8},
        {5, 2, 1},
        {4, 3, 7}
    });
    treeGoal.setStartNode({
        {1, 2, 3},
        {8, 0, 4},
        {7, 6, 5}
    });
    Tree::bds(treeStart, treeGoal);

    std::cout << "Time complexity: " << treeStart.getStepCount() + treeGoal.getStepCount()<< " steps" << std::endl;
    std::cout << "Capacity: " << treeStart.getCapacity()+treeStart.getCapacity()<< " nodes" << std::endl;
#endif
    return 0;
}
