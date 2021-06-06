#ifndef TreeList_HPP 
#define TreeList_HPP

#include <vector>
#include "Tree.hpp"

template <class T>
class TreeList
{
private:
  Tree<T> lstTree;
public:
  void push_back(T dat)   { lstTree.root = lstTree.insert(lstTree.root, dat); }
  T &operator[](int indx) 
  {
    std::vector<bool*> indexes = lstTree.getIndexes(lstTree.root); 
    return *(indexes[indx]); 
  }
};

#endif
