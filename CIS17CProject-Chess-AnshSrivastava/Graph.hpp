#ifndef GRAPH_HPP
#define GRAPH_HPP

#include <list>

class Graph
{
private:
  int size;
  std::list<int> *adjacencylist;
public:
  Graph(int s)
  {
    size = s;
    adjacencylist = new std::list<int>[size];
  }
  void addDirectionalEdge(int a, int b)
  {
    adjacencylist[a].push_back(b);
  }
  void addEdge(int a, int b)
  {
    adjacencylist[a].push_back(b);
    adjacencylist[b].push_back(a);
  }

  bool isNeighbor(int node, int elem)
  {
    for (int x : adjacencylist[node])
    {
      if (x==elem)
        return true;
    }
    return false;
  }
};

#endif
