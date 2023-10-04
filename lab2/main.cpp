#include "Tree.h"

//#define FIRST

int main() {
    Tree treeDfsH1, treeDfsH2, treeStartH1, treeStartH2, treeGoalH1, treeGoalH2;

    // first strategy - dfs
#ifdef FIRST
    std::cout << "DFS H1: Started\n";
    treeDfsH1.setStartNode({
        {6, 0, 8},
        {5, 2, 1},
        {4, 3, 7}
    });
    treeDfsH1.setEndNode({
        {1, 2, 3},
        {8, 0, 4},
        {7, 6, 5}
    });
    treeDfsH1.dfs(treeDfsH1.getStartNode(), true);

    std::cout << "DFS H1: Time complexity: " << treeDfsH1.getStepCount() << " steps" << std::endl;
    std::cout << "DFS H1: Capacity: " << treeDfsH1.getCapacity() << " nodes" << std::endl;

    std::cout << "\nDFS H2: Started\n";
    treeDfsH2.setStartNode({
                                   {6, 0, 8},
                                   {5, 2, 1},
                                   {4, 3, 7}
                           });
    treeDfsH2.setEndNode({
                                 {1, 2, 3},
                                 {8, 0, 4},
                                 {7, 6, 5}
                         });
    treeDfsH2.dfs(treeDfsH2.getStartNode(), false);

    std::cout << "DFS H2: Time complexity: " << treeDfsH2.getStepCount() << " steps" << std::endl;
    std::cout << "DFS H2: Capacity: " << treeDfsH2.getCapacity() << " nodes" << std::endl;
#else
    // second strategy - bidirectional search
    std::cout << "BDS H1: Started\n";
    treeStartH1.setStartNode({
        {6, 0, 8},
        {5, 2, 1},
        {4, 3, 7}
    });
    treeStartH1.setEndNode({
         {1, 2, 3},
         {8, 0, 4},
         {7, 6, 5}
    });
    treeGoalH1.setStartNode({
        {1, 2, 3},
        {8, 0, 4},
        {7, 6, 5}
    });
    treeGoalH1.setEndNode({
        {6, 0, 8},
        {5, 2, 1},
        {4, 3, 7}
    });
    Tree::bds(treeStartH1, treeGoalH1, true);

    std::cout << "BDS H1: Time complexity: " << treeStartH1.getStepCount() + treeGoalH1.getStepCount()<< " steps" << std::endl;
    std::cout << "BDS H1: Capacity: " << treeStartH1.getCapacity()+treeStartH1.getCapacity()<< " nodes" << std::endl;

    std::cout << "\nBDS H2: Started\n";
    treeStartH2.setStartNode({
           {6, 0, 8},
           {5, 2, 1},
           {4, 3, 7}
    });
    treeStartH2.setEndNode({
           {1, 2, 3},
           {8, 0, 4},
           {7, 6, 5}
    });
    treeGoalH2.setStartNode({
            {1, 2, 3},
            {8, 0, 4},
            {7, 6, 5}
    });
    treeGoalH2.setEndNode({
              {6, 0, 8},
              {5, 2, 1},
              {4, 3, 7}
    });
    Tree::bds(treeStartH2, treeGoalH2, false);

    std::cout << "BDS H2: Time complexity: " << treeStartH2.getStepCount() + treeGoalH2.getStepCount()<< " steps" << std::endl;
    std::cout << "BDS H2: Capacity: " << treeStartH2.getCapacity()+treeStartH2.getCapacity()<< " nodes" << std::endl;
#endif
    return 0;
}
