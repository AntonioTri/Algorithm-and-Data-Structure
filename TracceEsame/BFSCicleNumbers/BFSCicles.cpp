#include <algorithm>
#include <iostream>
#include <fstream>
#include <climits>
#include <vector>

using namespace std;
#define TEMPLATE template<typename T>

/**
 * Creare una classe Grafo che legga i nodi da un file ed esegua la bfs su di un file di output
 * Dotare il metodo BFS di un modo per contare i cicli
 * Dotare la classe di un modo per classsificare gli archi
 * 
*/

enum NodeColor { WHITE, BLACK, GRAY };


TEMPLATE class Node{

    public:

        Node<T>* father;
        int startingTime;
        int finalTime;
        T key;
        NodeColor color;
        vector<Node<T>*> adjList;

        Node(T key) : 
            father(nullptr), 
            startingTime(0),    
            finalTime(0),   
            color(WHITE), 
            key(key){};

        void addAdjNode(Node<T>* adjNode){ adjList.push_back(adjNode); };

};


enum EdgeType { AVANTI, INDIETRO, TRASVERSALE };

TEMPLATE class Edge{

    public:

        Node<T>* source;
        Node<T>* destination;
        EdgeType type;

        Edge(Node<T>* source, Node<T>* destination, EdgeType type) : 
            source(source), 
            destination(destination),
            type(type) {  };

};


TEMPLATE class Grafo{

    private:

        vector<Node<T>*> nodes = {};
        vector<Edge<T>*> edges = {};
        int time;
        // La variabile seguente conserva il numero di cicli
        int cicleNumber;

        Node<T>* findNode(T key){
            for (Node<T>* &node : nodes){
                if (node != nullptr && node->key == key){
                    return node;
                }
            }
            // Caso peggiore ritorna nullptr
            return nullptr;
        }

    public:

        Grafo(string inputFileName) : time(0), cicleNumber(0) {

            // Definizione del file di input
            ifstream input(inputFileName);
            
            // Variabili per conservare nodo partenza, destinazione e peso arco
            int sorgente, destinazione;
            
            // Ciclo while per estrarre i nodi
            while (input>>sorgente>>destinazione){
                
                // Ricerca dei nodi con chiave uguale a quella in ingresso
                // Se i nodi esistono viene ritornata la reference
                // Altrimenti nullptr e viene gestita la creazione di unn nuovo nodo
                Node<T>* nuovaSorgente = findNode(sorgente);
                Node<T>* nuovaDestinazione = findNode(destinazione);

                // Si controlla se i nodi siano stati trovati
                // In caso contrario vengono istanziati
                if (nuovaSorgente == nullptr){
                    nuovaSorgente = new Node<T>(sorgente);
                    nodes.push_back(nuovaSorgente);
                }

                if (nuovaDestinazione == nullptr){
                    nuovaDestinazione = new Node<T>(destinazione);
                    nodes.push_back(nuovaDestinazione);
                }

                // Viene aggiutno il nodo destinazione alla lista di adiacenza
                // della sorgente
                nuovaSorgente->addAdjNode(nuovaDestinazione);

            }
            
        }

        /**
         * Questa dfs scrive nel file di output l'ordine di visita dei nodi
         * i loro tempi di fine e di inizio. 
         * Scrive nel file anche la classificazione degli archi
         * ed infine il numero di cicli presenti nel grafo
         * 
        */
        void DFS(string outputFileName){
            
            // Definizione del file di output
            ofstream output(outputFileName);

            // Inizializzazione dei nodi (anche se sono già inizializzati dal loro costruttore)
            for (Node<T>* &node : nodes){
                node->father = nullptr;
                node->startingTime = INT_MAX;
                node->finalTime  = INT_MAX;
                node->color = WHITE;
            }

            // Scorriamo i nodi e quando ne troviamo uno bianco
            // eseguiamo una visita di quell'albero
            for (Node<T>* &node : nodes){
                if (node->color == WHITE){
                    output<<"Nuovo albero DFS trovato:\n";
                    DFSVisit(node, output);
                    output<<endl;
                }   
            }

            // Alla fine delle visite degli alberi viene segnato nel file di output
            // la classificazione degli archi
            output<<"\nClassificazione degli archi:\n\n";
            for (Edge<T>* &edge : edges){
                switch (edge->type){
                case AVANTI:
                    output<<"Arco da "<<edge->source->key<<" a "<<edge->destination->key<<" è un arco in AVANTI\n";
                    break;
                
                case INDIETRO:
                    output<<"Arco da "<<edge->source->key<<" a "<<edge->destination->key<<" è un arco all'INDIETRO\n";
                    break;
                
                case TRASVERSALE:
                    output<<"Arco da "<<edge->source->key<<" a "<<edge->destination->key<<" è un arco TRASVERSALE\n";
                    break;

                }
                
            }

            // Alla fine viene anche scritto il numero di cicli presenti nel grafo
            output<<"\nIl numero di cicli presenti nel grafo è uguale a: "<<cicleNumber;
            time = 0;
            cicleNumber = 0;
            output.close();
            

        }


        // La DFS visit serve a visitare un albero da una sorgente inviata
        // Classifica anche gli archi in base al loro tipo e conta i cicli presenti
        void DFSVisit(Node<T>* root, ofstream& output){
            
            // Dichiariamo il tempo di inizio del nodo
            time++;
            root->startingTime = time;
            root->color = GRAY;

            // Per ogni nodo adiacente viene controllato se sia un arco in avanti
            // indietro o trasversale
            for (Node<T>* &adjNode : root->adjList){
                
                // Primo caso, arco in avanti, colore del nodo destinazione bianco
                if(adjNode->color == WHITE){
                    // Settiamo il padre
                    adjNode->father = root;
                    // Viene definito l'arco come arco in avanti
                    edges.push_back(new Edge<T>(root, adjNode, AVANTI));
                    // Eseguiamo la DFS visit sul nodo
                    DFSVisit(adjNode, output);
                
                // Caso due, colore del nodo destinazione grigio, arco all'indietro
                // Viene anche incrementato il contatore per definire il numero di cicli
                } else if (adjNode->color == GRAY){
                    edges.push_back(new Edge<T>(root, adjNode, INDIETRO));
                    cicleNumber++;
                
                // Terzo caso, nodo adiacente nero, arco in avanti o trasversale
                // Userò trasversale per comodita'
                } else if (adjNode->color == BLACK){
                    edges.push_back(new Edge<T>(root, adjNode, TRASVERSALE));
                }
            }

            // Alla fine delle visite interne definiamo i tempi di fine e scriviamo
            // la visita nell'output
            time++;
            root->finalTime = time;
            root->color = BLACK;
            output<<"Nodo con chiave "<<root->key<<". Tempi di inizio/fine = ("<<root->startingTime<<", "<<root->finalTime<<").\n";
        }


};


// Test di esecuzione
int main(){


    // Creazione dell'istanza
    Grafo<int>* grafo = new Grafo<int>("GrafoIn.txt");
    // Esecuzione BFS che scrive nel file la sequenza di visita
    // classificazione degli archi e numero di cili
    grafo->DFS("GrafoOutput.txt");

    return 0;

};