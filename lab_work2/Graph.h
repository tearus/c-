

#ifndef LAB_WORK2_GRAPH_H
#define LAB_WORK2_GRAPH_H

#include <iostream>
#include <list>
#include <queue>
#include <stack>
#include <algorithm>

class Graph {
protected:
    std::list<int> *adj;

public:
    Graph(int V);

    void addEdge(int v, int w);

    void BFS(int s);

    void DFS(int v, std::vector<bool>& visited,std::vector<int> &result);

    void visualizeWithGraphviz(const std::string &outputFilename);

    void DFSForest();

    int V;

    void Kosaraju();
};


#endif //LAB_WORK2_GRAPH_H
