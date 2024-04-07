#ifndef WEIGHTEDGRAPH_H
#define WEIGHTEDGRAPH_H
#include <vector>
#include <string>

class WeightedGraph {
    int V; // Количество вершин
    std::vector<std::pair<int, int>>* adj; // Список смежности

public:
    explicit WeightedGraph(int V);
    ~WeightedGraph();

    void addEdge(int v, int w, int weight);
    std::vector<std::tuple<int, int, int>> kruskal();

    void visualizeWithGraphviz(const std::__cxx11::basic_string<char> &outputFilename);
    std::vector<std::tuple<int, int,int>> prim();

    std::vector<int> bellman_ford(int src);

private:
    std::vector<std::tuple<int, int, int>> getEdgesWithWeights();
    int find(std::vector<int>& parent, int i);
    void union_sets(std::vector<int>& parent, int x, int y);
};

#endif // WEIGHTEDGRAPH_H
