#include <iostream>
#include <vector>
#include <unordered_map>

// Funzione per creare un grafo orientato da un array di coppie
class Graph {
private:
    std::unordered_map<int, std::vector<int>> adjList; // Lista di adiacenza

public:
    // Metodo per aggiungere un arco al grafo
    void addEdge(int from, int to) {
        adjList[from].push_back(to);
    }

    // Metodo per stampare il grafo
    void printGraph() {
        for (const auto& pair : adjList) {
            std::cout << pair.first << " -> ";
            for (int neighbor : pair.second) {
                std::cout << neighbor << " ";
            }
            std::cout << std::endl;
        }
    }
};

int main() {
    // Array di input con gli archi del grafo
    std::vector<std::pair<int, int>> edges = {
        {0, 1}, {1, 2}, {2, 0}, {2, 3}, {3, 4}
    };

    // Creazione del grafo
    Graph graph;

    // Aggiunta degli archi al grafo
    for (const auto& edge : edges) {
        graph.addEdge(edge.first, edge.second);
    }

    // Stampa del grafo
    std::cout << "Il grafo orientato:\n";
    
    graph.printGraph();

    return 0;
}
