#include "Graph.hpp"

int main(){

    // dichiarazione del vettore di nodi di tipo BFS
    vector<NodeBFS*> vertexesBFS;

    // Un for genera 10 nodi, con valori da 1 a 10
    for (int i = 0; i < 10; i++){
        NodeBFS *newNode = new NodeBFS(i);
        vertexesBFS.push_back(newNode);
    }
    
    // Creiamo un vettore di Node* per la compatibilità con il costruttore di Graph
    vector<Node*> vertexes1(vertexesBFS.begin(), vertexesBFS.end());

    // Dichiarazione del grafo
    Graph grafo1(vertexes1, ORIENTED);

    // Print del grafo
    grafo1.printGraph();
    // Generiamo i pesi degli archi
    grafo1.addRandomWeightToEdges();
    // Printiamo gli archi con i pesi
    grafo1.printWeightedEdges();

    // Visita DFS non permessa
    grafo1.DFS();

    // Visita BFS permessa
    grafo1.BFS(vertexesBFS[0]);



    // dichiarazione del vettore di nodi di tipo DFS
    vector<NodeDFS*> vertexesDFS;

    // Un for genera 10 nodi, con valori da 1 a 10
    for (int i = 0; i < 10; i++){
        NodeDFS *newNode = new NodeDFS(i);
        vertexesDFS.push_back(newNode);
    }
    
    // Creiamo un vettore di Node* per la compatibilità con il costruttore di Graph
    vector<Node*> vertexes2(vertexesDFS.begin(), vertexesDFS.end());

    // Dichiarazione del grafo
    Graph grafo2(vertexes2, NOT_ORIENTED);

    // Print del grafo
    grafo2.printGraph();
    grafo2.printEdges();

    // Visita DFS permessa
    grafo2.DFS(vertexesDFS[0]);

    // Visita BFS non permessa
    grafo2.BFS();


}