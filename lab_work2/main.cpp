#include "Graph.h"
#include "WeightedGraph.h"
#include <iostream>
#include <numeric>
#include <chrono>

int main() {
    Graph BFS_DFS_graph(10);
    BFS_DFS_graph.addEdge(0, 1);
    BFS_DFS_graph.addEdge(1, 0);
    BFS_DFS_graph.addEdge(0, 2);
    BFS_DFS_graph.addEdge(0, 3);
    BFS_DFS_graph.addEdge(1, 4);
    BFS_DFS_graph.addEdge(2, 5);
    BFS_DFS_graph.addEdge(3, 6);
    BFS_DFS_graph.addEdge(5, 4);
    BFS_DFS_graph.addEdge(5, 6);
    BFS_DFS_graph.addEdge(6, 7);
    BFS_DFS_graph.addEdge(7, 8);
    BFS_DFS_graph.addEdge(4, 9);


    Graph Kosaraju_graph(9);
    Kosaraju_graph.addEdge(0, 1);
    Kosaraju_graph.addEdge(1, 2);
    Kosaraju_graph.addEdge(2, 3);
    Kosaraju_graph.addEdge(3, 0);
    Kosaraju_graph.addEdge(4, 3);
    Kosaraju_graph.addEdge(3, 4);
    Kosaraju_graph.addEdge(3, 5);
    Kosaraju_graph.addEdge(4, 5);
    Kosaraju_graph.addEdge(5, 6);
    Kosaraju_graph.addEdge(6, 7);
    Kosaraju_graph.addEdge(7, 8);
    Kosaraju_graph.addEdge(8, 7);

    Kosaraju_graph.visualizeWithGraphviz("Kosaraju_graph.png");
    std::cout << "BFS: ";
    BFS_DFS_graph.BFS(0);
    std::cout << std::endl;

    std::vector<bool> visited(BFS_DFS_graph.V, false);
    std::vector<bool> visited2(BFS_DFS_graph.V, false);

    for (int i = 0; i < BFS_DFS_graph.V; i++) {
        visited[i] = false;
    }

    std::cout << "DFS: ";
    std::vector<int> dfs;
    BFS_DFS_graph.DFS(0, visited, dfs);
    for (auto result: dfs) {
        std::cout << result << " ";
    }
    std::cout << std::endl;
    std::string Tree;
    std::cout << "DFS  Forest:" <<std::endl;
    BFS_DFS_graph.DFSForest(0, visited2, Tree);
    BFS_DFS_graph.visualizeWithGraphviz("kruskal_prime_graph.png");
    std::cout << "Kosaraju algorithm:" <<std::endl;
    Kosaraju_graph.Kosaraju();
    WeightedGraph kruskal_prime_graph(9);
    kruskal_prime_graph.addEdge(0, 1, 10);
    kruskal_prime_graph.addEdge(0, 2, 6);
    kruskal_prime_graph.addEdge(0, 3, 5);
    kruskal_prime_graph.addEdge(1, 3, 15);
    kruskal_prime_graph.addEdge(2, 3, 4);
    kruskal_prime_graph.addEdge(1, 4, 7);
    kruskal_prime_graph.addEdge(2, 4, 8);
    kruskal_prime_graph.addEdge(3, 4, 9);
    kruskal_prime_graph.addEdge(4, 5, 11);
    kruskal_prime_graph.addEdge(4, 6, 12);
    kruskal_prime_graph.addEdge(4, 7, 13);
    kruskal_prime_graph.addEdge(5, 6, 14);
    kruskal_prime_graph.addEdge(6, 7, 15);
    kruskal_prime_graph.addEdge(7, 8, 16);
//kruskal_prime_graph.addEdge(0, 1, 10);
//    kruskal_prime_graph.addEdge(0, 2, 6);
//    kruskal_prime_graph.addEdge(0, 3, 5);
//    kruskal_prime_graph.addEdge(1, 3, 15);
//    kruskal_prime_graph.addEdge(2, 3, 4);
    std::cout << "minimal spanning tree \n";
    auto start = std::chrono::high_resolution_clock::now();
    std::vector<std::tuple<int, int, int>> mst_kruskal = kruskal_prime_graph.kruskal();
    auto end = std::chrono::high_resolution_clock::now();
    for (const auto &edge: mst_kruskal) {
        std::cout << "(" << std::get<0>(edge) << ", " << std::get<1>(edge) << ") with weight " << std::get<2>(edge)
                  << std::endl;
    }
    std::chrono::duration<double, std::milli> kruskal_time = end - start;
    start = std::chrono::high_resolution_clock::now();
    auto mst_prim = kruskal_prime_graph.prim();
    end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double, std::milli> prim_time = end - start;
    kruskal_prime_graph.visualizeWithGraphviz("kruskal_prime_graph.png");

    int sum_kruskal = std::accumulate(mst_kruskal.begin(), mst_kruskal.end(), 0,
                                      [](int sum, const std::tuple<int, int, int> &edge) {
                                          return sum + std::get<2>(edge);
                                      });
    int sum_prim = std::accumulate(mst_kruskal.begin(), mst_kruskal.end(), 0,
                                   [](int sum, const std::tuple<int, int, int> &edge) {
                                       return sum + std::get<2>(edge);
                                   });
    std::cout << "(Kruskal) Sum of weights in the spanning tree: " << sum_kruskal << "\nTime: "
              << kruskal_time << " milliseconds" << std::endl;
    std::cout << "(Prim) Sum of weights in the spanning tree : " << sum_prim << "\nTime: " << prim_time
              << " milliseconds" << std::endl;
    std::cout << "Bellman-Ford algorithm \n";
    try {
        WeightedGraph bellman_ford_graph(10);

        bellman_ford_graph.addEdge(0, 1, 2);
        bellman_ford_graph.addEdge(0, 2, 6);
        bellman_ford_graph.addEdge(1, 2, 3);
        bellman_ford_graph.addEdge(1, 3, 8);
        bellman_ford_graph.addEdge(1, 4, 5);
        bellman_ford_graph.addEdge(2, 3, 4);
        bellman_ford_graph.addEdge(2, 4, 2);
        bellman_ford_graph.addEdge(3, 4, 0);
        bellman_ford_graph.addEdge(4, 5, 1);
        bellman_ford_graph.addEdge(4, 6, 3);
        bellman_ford_graph.addEdge(5, 6, 2);
        bellman_ford_graph.addEdge(5, 7, 4);
        bellman_ford_graph.addEdge(6, 7, 1);
        bellman_ford_graph.addEdge(6, 8, 2);
        bellman_ford_graph.addEdge(7, 8, 3);
        bellman_ford_graph.addEdge(7, 9, 1);
        bellman_ford_graph.addEdge(8, 9, 2);
        std::vector<int> dist = bellman_ford_graph.bellman_ford(0);
        bellman_ford_graph.visualizeWithGraphviz("bellman_ford_graph.png");
        std::cout << "Shortest distances from vertex 0 to other vertices:\n";
        for (int i = 0; i < dist.size(); i++) {
            std::cout << "To the top " << i << ": " << dist[i] << std::endl;
        }
    } catch (const std::runtime_error &e) {
        std::cerr << "Error " << e.what() << std::endl;
    }

    return 0;
}
