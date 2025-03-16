#include <unordered_map>
#include <algorithm>
#include <iostream>
#include <fstream>
#include <climits>
#include <vector>
#include <queue>

#define TEMPLATE template<typename K>
using namespace std;
enum NodeColor { GRAY, WHITE, BLACK };

/**
 * 
 * Costruire una classe grafo in grado di caricare dati da un file
 * Eseguire una BFS che scriva l'ordine su di un file output.
 * Dotare la classe di un metodo Primm che consenta di generare un mst.
 * Dotare la classe di un metodo is_binary che indichi se un albero è binario.
 * 
*/

TEMPLATE class Node{

    public:
        
        K key;
        Node<K> *father;
        int distance;
        NodeColor color;
        vector<Node<K>*> adjList;

        Node(K key) : key(key), father(nullptr), distance(0){ };

        void addAdjNode(Node<K> *adjNode){
            adjList.push_back(adjNode);
        }

};


TEMPLATE class Edge{

    public:

        Node<K>* source;
        Node<K>* destination;
        int weight;

        Edge(Node<K>* source, Node<K>* destination, int weight) : 
            source(source), 
            destination(destination), 
            weight(weight) {};



};


TEMPLATE class Grafo{

    private:
        vector<Node<K>*> nodes = {};
        vector<Edge<K>*> edges = {};
        
        Node<K>* findNode(K key) {

            for (auto &node : nodes){
                if (node != nullptr){
                    if (node->key == key) return node;
                }
            }
            return nullptr;

        }
    
    public:

        Grafo(string inputFileName){

            // Definizione del file di input
            ifstream input(inputFileName);
            int nodeNumber, edgeNumber;

            // Estrazione delle dimensioni
            input>>nodeNumber>>edgeNumber;

            // Estrazione dei nodi, se un nodo esiste gia' non viene ricreato
            int source, destination, edgeWeight;
            cout<<"Inizio il ciclo di inserimento nodi\n";
            while (input>>source>>destination>>edgeWeight){

                // Definizione del nodo
                Node<K>* newSource = findNode(source);
                Node<K>* newDestination = findNode(destination);
                
                // Se il nodo sorgente non era presente tra quelli registrati viene inserito
                if (newSource == nullptr){
                    newSource = new Node<K>(source);
                    nodes.push_back(newSource);
                }

                // Se il nodo destinazione non era presente tra quelli registrati viene inserito
                if (newDestination == nullptr){
                    newDestination = new Node<K>(destination);
                    nodes.push_back(newDestination);
                }

                // Viene aggiunto il nuovo arco con il peso
                edges.push_back(new Edge<K>(newSource, newDestination, edgeWeight));

                // Viene aggiunto il destinazione alla lista di adiacenza di quello sorgente
                newSource->addAdjNode(newDestination);

            }

            input.close();
            
        }

        // Algoritmo bfs per la visita
        void BFS(Node<K>* root, string outputFileName){

            // Definizione della sorgente nel caos sia nulla
            if (root == nullptr) root = nodes[0];

            // Definizione del file di output
            ofstream output(outputFileName);
            
            // Inizializzazione dei nodi
            for (Node<K>* &node : nodes){
                node->distance = INT_MAX;
                node->father = nullptr;
                node->color = WHITE;
            }
            
            // Definizione della distanza della radice a 0
            // Ed inizializzazione della coda
            root->distance = 0;
            root->color = GRAY;
            queue<Node<K>*> queue;
            queue.push(root);

            // Inserimento delle informazioni della radice
            output<<"Nodo sorgente "<<root->key<<endl;

            // Inizio del ciclo di visita
            while (!queue.empty()){

                // Estrazione del nodo dalla coda
                Node<K>* currentNode = queue.front(); queue.pop();
                
                // Visita dei vicini
                for(Node<K>* adjNode : currentNode->adjList){
                    // Un nodo viene visitato solo se è di colore bianco
                    if (adjNode->color == WHITE){
                        adjNode->color = GRAY;
                        adjNode->distance = currentNode->distance + 1;
                        adjNode->father = currentNode;
                        queue.push(adjNode);

                        // Inserimento delle informazioni nel file
                        output<<"Nodo "<<adjNode->key<<". Distanza da s = "<<adjNode->distance<<". Padre con chiave = "<<adjNode->father->key<<"."<<endl;

                    }
                
                }
                
                // Dichiariamo il nodo come visitato
                currentNode->color = BLACK;

            }
            

            output.close();

        }


};

// Esempio di utilizzo
int main(){

    // Dichiarazione dell'istanza
    Grafo<int>* grafo = new Grafo<int>("GrafoIn.txt");

    cout<<"Inizio ad eseguire la BFS sul file di output.\n";
    
    // Esecuzione della BFS sul file di output
    grafo->BFS(nullptr, "GrafoOut.txt");

    cout<<"Esecuzione avvenuta con successo!\n";

}


