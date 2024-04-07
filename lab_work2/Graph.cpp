
#include <fstream>
#include <sstream>
#include "Graph.h"

Graph::Graph(int V) {
    this->V = V;
    adj = new std::list<int>[V];
}

void Graph::addEdge(int v, int w) {
    adj[v].push_back(w);
}

void Graph::BFS(int s) {
    std::vector<bool> visited(V, false);
    std::queue<int> q;
    visited[s] = true;
    q.push(s);

    while (!q.empty()) {
        s = q.front();
        std::cout << s << " ";
        q.pop();

        for (auto i = adj[s].begin(); i != adj[s].end(); ++i) {
            if (!visited[*i]) {
                q.push(*i);
                visited[*i] = true;
            }
        }
    }
}

void Graph::DFSForest() {
    std::vector<bool> visited(V, false);
    for (int i = 0; i < V; ++i) {
        if (!visited[i]) {
            std::vector<int> result;
            DFS(i, visited, result);
            std::cout << "Tree: ";
            for (int u : result) {
                std::cout << u << " ";
            }
            std::cout << std::endl;
        }
    }
}


void Graph::DFS(int v, std::vector<bool> &visited, std::vector<int> &result) {
    visited[v] = true;
    result.push_back(v);
    for (auto i = adj[v].begin(); i != adj[v].end(); ++i) {
        if (!visited[*i]) {
            DFS(*i, visited, result);
        }
    }
}

void Graph::Kosaraju() {
    std::vector<bool> visited(V, false);
    std::vector<int> stack;
    std::vector<int> result;

    // Первый обход в глубину для определения порядка вершин
    for (int i = 0; i < V; ++i) {
        if (!visited[i]) {
            DFS(i, visited, stack);
        }
    }

    // Транспонирование графа
    Graph transposedGraph(V);
    for (int v = 0; v < V; ++v) {
        for (auto w : adj[v]) {
            transposedGraph.addEdge(w, v);
        }
    }

    // Второй обход в глубину для обнаружения сильно связных компонентов
    visited.assign(V, false);
    while (!stack.empty()) {
        int v = stack.back();
        stack.pop_back();
        if (!visited[v]) {
            DFS(v, visited, result);
            std::cout << "strongly coupled component: ";
            for (int u : result) {
                std::cout << u << " ";
            }
            std::cout << std::endl;
            result.clear();
        }
    }
}


void Graph::visualizeWithGraphviz(const std::string &outputFilename) {
    std::string dotFilename = "temp_graph.dot";
    std::ofstream file(dotFilename);

    file << "digraph G {\n";

    // Добавляем вершины
    for (int i = 0; i < V; ++i) {
        file << "    \"" << i << "\" [label=\"" << i << "\"];\n";
    }

    // Добавляем ребра
    for (int v = 0; v < V; ++v) {
        for (auto w: adj[v]) {
            file << "    \"" << v << "\" -> \"" << w << "\";\n";
        }
    }

    file << "}\n";
    file.close();
    std::string command = "dot -Tpng " + dotFilename + " -o " + outputFilename;
    system(command.c_str());


}