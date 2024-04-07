#include "WeightedGraph.h"
#include <algorithm>
#include <string>
#include <fstream>
#include <tuple>
#include <queue>
#include <limits>
#include <unordered_set>


WeightedGraph::WeightedGraph(int V) : V(V) {
    adj = new std::vector<std::pair<int, int>>[V];
}

WeightedGraph::~WeightedGraph() {
    delete[] adj;
}

void WeightedGraph::addEdge(int v, int w, int weight) {
    adj[v].push_back({w, weight});
    adj[w].push_back({v, weight}); // Для ненаправленного графа
}

std::vector<std::tuple<int, int, int>> WeightedGraph::getEdgesWithWeights() {
    std::vector<std::tuple<int, int, int>> edges;
    for (int v = 0; v < V; ++v) {
        for (auto &edge: adj[v]) {
            if (v < edge.first) { // Избегаем дублирования ребер
                edges.push_back({v, edge.first, edge.second});
            }
        }
    }
    return edges;
}

std::vector<std::tuple<int, int, int>> WeightedGraph::kruskal() {
    std::vector<std::tuple<int, int, int>> edges = getEdgesWithWeights();
    std::sort(edges.begin(), edges.end(), [](const std::tuple<int, int, int> &a, const std::tuple<int, int, int> &b) {
        return std::get<2>(a) < std::get<2>(b);
    });

    std::vector<std::tuple<int, int, int>> mst;
    std::vector<int> parent(V);
    for (int i = 0; i < V; ++i) {
        parent[i] = i;
    }

    for (auto &edge: edges) {
        int u = std::get<0>(edge);
        int v = std::get<1>(edge);
        int parent_u = find(parent, u);
        int parent_v = find(parent, v);
        if (parent_u != parent_v) {
            mst.push_back(edge);
            union_sets(parent, parent_u, parent_v);
        }
    }

    return mst;
}

int WeightedGraph::find(std::vector<int> &parent, int i) {
    if (parent[i] == i) {
        return i;
    }
    return parent[i] = find(parent, parent[i]);
}

void WeightedGraph::union_sets(std::vector<int> &parent, int x, int y) {
    int xroot = find(parent, x);
    int yroot = find(parent, y);
    parent[yroot] = xroot;
}

struct pair_hash {
    template<class T1, class T2>
    std::size_t operator()(const std::pair<T1, T2> &p) const {
        auto h1 = std::hash<T1>{}(p.first);
        auto h2 = std::hash<T2>{}(p.second);
        return h1 ^ h2;
    }
};

void WeightedGraph::visualizeWithGraphviz(const std::string &outputFilename) {
    std::string dotFilename = "temp_graph.dot";
    std::ofstream file(dotFilename);

    file << "graph G {\n";
    file << "    overlap=false;\n"; // Избегаем перекрытия вершин

    // Добавляем вершины
    for (int i = 0; i < V; ++i) {
        file << "    \"" << i << "\" [label=\"" << i << "\"];\n";
    }

    // Используем set для отслеживания уже добавленных ребер
    std::unordered_set<std::pair<int, int>, pair_hash> addedEdges;

    // Добавляем ребра с весами, избегая повторного связывания
    for (int v = 0; v < V; ++v) {
        for (auto w: adj[v]) {
            std::pair<int, int> edge = std::minmax(v, w.first);
            if (addedEdges.find(edge) == addedEdges.end()) {
                file << "    \"" << v << "\" -- \"" << w.first << "\" [label=\"" << w.second << "\"];\n";
                addedEdges.insert(edge);
            }
        }
    }

    file << "}\n";
    file.close();
    std::string command = "dot -Tpng " + dotFilename + " -o " + outputFilename;
    system(command.c_str());
}


std::vector<std::tuple<int, int, int>> WeightedGraph::prim() {
    std::vector<bool> visited(V, false);
    std::vector<int> key(V, std::numeric_limits<int>::max());
    key[0] = 0; // Устанавливаем начальную вершину

    std::priority_queue<std::pair<int, int>, std::vector<std::pair<int, int>>, std::greater<std::pair<int, int>>> pq;
    pq.emplace(0, 0); // Вставляем начальную вершину с ключом 0

    std::vector<std::tuple<int, int, int>> mst;

    while (!pq.empty()) {
        int u = pq.top().second;
        pq.pop();

        if (!visited[u]) {
            visited[u] = true;

            for (auto &edge: adj[u]) {
                int v = edge.first;
                int weight = edge.second;

                if (!visited[v] && weight < key[v]) {
                    key[v] = weight;
                    pq.emplace(weight, v);
                    bool alreadyAdded = false;
                    for (const auto &mstEdge: mst) {
                        if ((std::get<0>(mstEdge) == u && std::get<1>(mstEdge) == v) ||
                            (std::get<0>(mstEdge) == v && std::get<1>(mstEdge) == u)) {
                            alreadyAdded = true;
                            break;
                        }
                    }
                    if (!alreadyAdded) {
                        mst.push_back({u, v, weight});
                    }
                }
            }
        }
    }

    return mst;
}

std::vector<int> WeightedGraph::bellman_ford(int src) {
    std::vector<int> dist(V, INT_MAX);
    dist[src] = 0;

    for (int i = 1; i <= V - 1; i++) {
        for (int u = 0; u < V; u++) {
            for (auto &edge: adj[u]) {
                int v = edge.first;
                int weight = edge.second;
                if (dist[u] != INT_MAX && dist[u] + weight < dist[v])
                    dist[v] = dist[u] + weight;
            }
        }
    }

    for (int u = 0; u < V; u++) {
        for (auto &edge: adj[u]) {
            int v = edge.first;
            int weight = edge.second;
            if (dist[u] != INT_MAX && dist[u] + weight < dist[v])
                throw std::runtime_error("Graph contains negative weight cycle");
        }
    }

    return dist;
}




