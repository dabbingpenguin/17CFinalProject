#include <iostream>
#include "Tree.hpp"
#include "TreeList.hpp"

int main()
{

    Tree<int> avl;
    cout << "Adding elements 1, 2, 3, ..., 41, 42 to the tree\n";
    for (int i=1; i<=42; ++i)
        avl.root = avl.insert(avl.root, i);
    std::cout << "Balancing tree...\n";
//  tree.levelorder(tree.root);
//  for (int i=0; i<10; ++i)
//    std::coutNode<bool> *tree << tree.getIndx(tree.root, i) << std::endl;
  std::cout << "End\n";
}
