#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <algorithm>
#include "Application.h"

class DSU {
public:
    DSU(int n) : parent(n), rank(n, 1) {
        for (int i = 0; i < n; ++i) {
            parent[i] = i;
        }
    }

    int find(int x) {
        return (parent[x] == x) ? x : (parent[x] = find(parent[x]));
    }

    void unite(int x, int y) {
        int rootX = find(x);
        int rootY = find(y);

        if (rootX != rootY) {
            if (rank[rootX] < rank[rootY]) {
                std::swap(rootX, rootY);
            }
            parent[rootY] = rootX;
            rank[rootX] += rank[rootY];
        }
    }

private:
    std::vector<int> parent;
    std::vector<int> rank;
};

struct Edge {
    std::string u, v;
    int weight;

    bool operator<(const Edge& other) const {
        return weight < other.weight;
    }
};

void Application::exec() {
    std::ifstream file;
    try {
        file.open("C:\\Programming\\C++\\algos\\graph\\graph.txt");
        if (!file.is_open()) {
            throw std::runtime_error("Не удалось открыть файл");
        }
    } catch (const std::exception& e) {
        std::cerr << e.what() << std::endl;
        return;
    }

    std::string line;
    std::getline(file, line);
    std::istringstream edgeStream(line);

    std::string vertex;
    std::vector<std::string> vertices;
    while (edgeStream >> vertex) {
        vertices.push_back(vertex);
    }

    // Считываем матрицу смежности и создаем список рёбер
    std::vector<Edge> edgeList;
    for (size_t i = 0; i < vertices.size(); ++i) {
        for (size_t j = 0; j < vertices.size(); ++j) {
            int weight;
            file >> weight;
            if (i < j && weight > 0) {  // Исключаем дубликаты и нулевые веса
                Edge edge;
                edge.u = vertices[i];
                edge.v = vertices[j];
                edge.weight = weight;
                edgeList.push_back(edge);
            }
        }
    }

    // Сортируем рёбра по весу
    std::sort(edgeList.begin(), edgeList.end());

    // Инициализируем DSU
    DSU dsu(vertices.size());

    // Минимальное остовное дерево
    std::vector<Edge> minimumSpanningTree;

    // Применяем алгоритм Краскала
    for (const Edge& edge : edgeList) {
        if (dsu.find(std::distance(vertices.begin(), std::find(vertices.begin(), vertices.end(), edge.u))) !=
            dsu.find(std::distance(vertices.begin(), std::find(vertices.begin(), vertices.end(), edge.v)))) {
            // Ребро не образует цикл
            minimumSpanningTree.push_back(edge);
            dsu.unite(std::distance(vertices.begin(), std::find(vertices.begin(), vertices.end(), edge.u)),
                      std::distance(vertices.begin(), std::find(vertices.begin(), vertices.end(), edge.v)));
        }
    }

    // Вывод результата
    for (const Edge& edge : minimumSpanningTree) {
        std::cout << edge.u << " " << edge.v << std::endl;
    }

    // Суммарный вес
    int totalWeight = 0;
    for (const Edge& edge : minimumSpanningTree) {
        totalWeight += edge.weight;
    }
    std::cout << totalWeight << std::endl;

    file.close();
}
