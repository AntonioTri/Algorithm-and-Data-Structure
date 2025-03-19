#include <unordered_map>
#include <unordered_set>
#include <algorithm>
#include <iostream>
#include <fstream>
#include <climits>
#include <vector>
#include <queue>
#include <functional>

// Funzione di hash per pair<Node*, Node*>
template <typename K>
struct pair_hash {
    template <typename A, typename B>
    std::size_t operator ()(const std::pair<A, B>& p) const {
        auto h1 = std::hash<A>{}(p.first);
        auto h2 = std::hash<B>{}(p.second);
        // Combinazione delle due hash
        return h1 ^ (h2 << 1); // XOR dei due hash, spostando il secondo per evitare collisioni
    }
};


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
        // Questa variabile serve all'algoritmo di primm per generare l'MST
        int primmKey;

        Node(K key) : key(key), father(nullptr), distance(0), primmKey(INT_MAX){ };

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
        // Mappa che associa all'arco il suo peso in relazione (coppia/peso)
        unordered_map<pair<Node<K>*, Node<K>*>, K, pair_hash<K>> edgesWeights;

        // Overload per la definizione di una minQUEUE per i nodi
        struct MinimumPriorityNode{
            bool operator()(Node<K>* a, Node<K>* b){
                return a->key > b->key;
            }
        };
        
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
                // Viene aggiunto alla mappa come normale coppia
                edgesWeights[make_pair(newSource, newDestination)] = edgeWeight;

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

        // Metodo di Primm per trovare un minimum spanning tree partendo
        // da una sorgente definita
        Node<K>* primmMST(Node<K>* root){

            root = this->nodes[0];

            cout << "Inizializzazione dei nodi..." << endl;

            // Inizializzazione dei nodi
            for (Node<K>* &node : nodes){
                // Per ogni nodo viene settata la chiave ed il padre
                node->primmKey = INT_MAX;
                node->father = nullptr;
                
                // Debugging: Mostra i nodi inizializzati
                cout << "Nodo inizializzato: " << node->key << " con primmKey = " << node->primmKey << endl;
            }

            // Viene definita la coda di priorita' minima
            priority_queue<Node<K>*, vector<Node<K>*>, MinimumPriorityNode> minQueue;
            // Un unordered_set per tracciare i nodi visitati
            unordered_set<Node<K>*> nodeSet;
            
            // Aggiungiamo i nodi nella coda di priorità
            for (Node<K>* node : nodes) {
                minQueue.push(node);
                // Debugging: Mostra i nodi aggiunti alla coda
                cout << "Nodo " << node->key << " aggiunto alla coda con primmKey = " << node->primmKey << endl;
            }

            // Inizializziamo la sorgente
            root->primmKey = 0;
            cout << "Sorgente " << root->key << " inizializzata con primmKey = " << root->primmKey << endl;

            // Inizia il ciclo di costruzione dell'albero
            while (!minQueue.empty()){
                // Estraiamo il nodo con minima priorita'
                Node<K>* currentNode = minQueue.top(); minQueue.pop();

                cout << "\nEstrazione nodo con chiave " << currentNode->key << " da minQueue (primmKey = " << currentNode->primmKey << ")" << endl;
                
                // Inseriamo il nodo nel set di nodi visitati
                nodeSet.insert(currentNode);
                
                // Debugging: Mostra lo stato della coda e del set di nodi visitati
                cout << "Set di nodi visitati: ";
                for (Node<K>* node : nodeSet) {
                    cout << node->key << " ";
                }
                cout << endl;

                // Vengono visitati i vicini
                for(Node<K>* &adjNode : currentNode->adjList){
                    // Ogni vicino conserva come chiave il peso dell'arco in entrata
                    int weight = edgesWeights[make_pair(currentNode, adjNode)];
                    
                    cout << "Esplorando arco verso " << adjNode->key << " con peso = " << weight << endl;

                    // Se il peso è minore della chiave del vicino e il nodo non è ancora stato visitato
                    if (weight < adjNode->primmKey && nodeSet.find(adjNode) == nodeSet.end()){
                        cout << "Aggiornamento nodo " << adjNode->key << " con nuova primmKey = " << weight << " e padre = " << currentNode->key << endl;
                        
                        // Aggiorniamo la chiave e il padre del nodo
                        adjNode->primmKey = weight;
                        adjNode->father = currentNode;

                        // Rimuoviamo il nodo dal set
                        nodeSet.erase(adjNode);
                    }
                }
            }

            cout << "Algoritmo di Prim completato." << endl;

            return root;
        }



        // Metodo che controlla se dalla radice inviata si generi un albero binario
        bool isBinary(Node<K>* root){

            // Caso base, il nodo inviato e' un nullptr
            if (root == nullptr) return true;
            
            // Altro caso base, il nodo ha piu' di due figli ed e' 
            // sicuramente diverso da nullptr
            if(root->adjList.size() > 2) return false;

            // Se non fossimo in un caso base allora andiamo a richiamare ricorsivamente
            // la funzione sul figlio destro e sinistro

            // Variabili per conservare i valori delle ricorsioni
            bool isBinarySX, isBinaryDX;

            // Controllo figlio sinistro se esiste
            if (root->adjList.size() > 0) isBinarySX = isBinary(root->adjList[0]);

            // Controllo figlio destro se esiste
            if (root->adjList.size() > 1) isBinaryDX = isBinary(root->adjList[1]);

            // Viene ritornato l'and tra i due booleani
            return isBinarySX && isBinaryDX;


        }


};

// Esempio di utilizzo
int main(){

    // Dichiarazione dell'istanza
    Grafo<int>* grafo = new Grafo<int>("GrafoIn.txt");

    cout<<"Inizio ad eseguire la BFS sul file di output.\n";
    
    // Esecuzione della BFS sul file di output
    grafo->BFS(nullptr, "GrafoOut.txt");

    // Esecuzione di primm
    Node<int>* root = grafo->primmMST(nullptr);

    if (grafo->isBinary(root)){
        cout<<"\nL'albero di primm e' binario\n";
    } else{
        cout<<"\nL'albero di primm NON e' binario\n";
    }
    


    cout<<"Esecuzione avvenuta con successo!\n";

}


