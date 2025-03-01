#include <utility>
#include <random>
#include <typeinfo>
#include <queue>
#include <time.h>
#include "NodeSubTypes.hpp"


using namespace std;

// Enumerazione per definire il tipo di grafo

enum GraphType { ORIENTED, NOT_ORIENTED };

class Graph{
    
    private:

        int globalTime; // Variabile usata dsolo durante la DFS
        GraphType type;
        vector<Node*> vertexes;
        vector<pair<pair<Node*, Node*>, int>> weightedEdges;
        vector<pair<Node*, Node*>> orderedEdges;
        vector<pair<Node*, Node*>> unorderedEdges;
        void buildOrientedGraph(vector<Node*> vertexes);
        void buildNotOrientedGraph(vector<Node*> vertexes);
        void DFSVisit(NodeDFS* root);
        void relax(NodeBFS* x, NodeBFS* y, int weight);
        Node* findSet(Node* x);
        void makeSet(Node* x);
        void unionNode(Node* x, Node* y);
        void link(Node* x, Node* y);


    public:

        Graph(vector<Node*> vertexes, GraphType type);
        void printGraph();
        void printEdges();
        void printWeightedEdges();
        void BFS(NodeBFS* root);
        void DFS(NodeDFS* root);
        void stronglyConnectedComponents();
        void addRandomWeightToEdges();
        Node* kruskalMST(NodeBFS* root);
        Node* primmMST(NodeBFS* root);
        NodeBFS* djikstraMinimumPath(NodeBFS* root);


};

/**
 * Questo costruttore prende in input un tipo di enumerazione oltre che ad un vettore di nodi.
 * Se Il tipo e' oriented, viene costruito un Graph orientato.
 * Se il tipo e' not oriented Viene costruito un Graph non orientato.
 * @param vertexes Il vettore contenente i nodi orfani
 * @param GraphType Il tipo di Graph da generare (ORIENTED, NOT_ORIENTED)
 *  
*/
Graph::Graph(vector<Node*> vertexes, GraphType type){

    switch (type){

        case ORIENTED:
            // Costrisci il Graph orientato con uno stack
            this->buildOrientedGraph(vertexes);
            // Viene settato il tipo del grafo come oriented
            this->type = ORIENTED;
            break;
        
        case NOT_ORIENTED:
            // Costruisci il Graph non orientato
            this->buildNotOrientedGraph(vertexes);
            // Viene settato il tipo del grafo come not oriented
            this->type = NOT_ORIENTED;
            break;
        
        default:
            cout<<"ERRORE: Tipo di Graph non permesso!"<<endl;
            return;

    }

}

/**
 * Questa funzione costruisce un Grafo orientato estraendo casualmente i vertici dal vettore in ingresso
 * e settandone i figli nella lista di adiacenza, il nodo viene successivamente escluso dalla estrazione.
 * I nodi figli scelti sono casuali ed i padri non sono settati in quanto compito delle visite.
 * N.B Il vettore viene passato per valore e non per riferimento, così da non modificare la copia originale
 * 
*/
void Graph::buildOrientedGraph(vector<Node*> vertexes){
    
    // Generatore di numeri casuali
    srand(time(NULL));

    // Questo passaggio garantisce che ogni nodo abbia almeno un vicino
    for (auto& vertex : vertexes) {
        // Se il nodo non ha adiacenti
        if (vertex->getAdjList().size() == 0) { 
            // Viene istanziato un sentinella
            Node* adjVertex;
            // Fin quando il nodo scelto non e' diverso da se stesso,
            // serve per evitare i loop, viene selezionato un nodo dalla lista
            do {
                adjVertex = vertexes[rand()%(vertexes.size()-1)];
            } while (adjVertex == vertex); 

            // Viene aggiunto il nodo scelto alla lista di adiacenza
            vertex->addToAdjList(adjVertex);
            // Viene aggiunto l'arco
            pair<Node*, Node*> edge = make_pair(vertex, adjVertex);
            this->orderedEdges.push_back(edge);
            
        }
    }

    //Nel secondo passaggio avviene la generazione casuale dei vicini
    uniform_int_distribution<int> numDistrib(0, (int)(vertexes.size() / 2));
    
    // Per ogni vertice andiamo ad estrarre un numero casuale di nodi
    // E li inseriamo nella lista di adiacenza
    for(const auto& vertex : vertexes){

        // Generazione del numero di vicini
        int numberOfAdjVertexes = rand()%((int)(vertexes.size()/2));

        for (int i = 0; i < numberOfAdjVertexes; i++){

            // Estrazione casuale del vicino
            Node* adjVertex = vertexes[rand()%(vertexes.size()-1)];
            
            // Se il vicino non e' nella lista di adiacenza viene inserito
            if (!vertex->isNodeAdjacent(adjVertex)){
                // Inserimento nella lista di adiacenza
                vertex->addToAdjList(adjVertex);
                // Viene aggiunto l'arco
                pair<Node*, Node*> edge = make_pair(vertex, adjVertex);
                this->orderedEdges.push_back(edge);

            }

        }

    }

    // Alla fine della creazione delle liste di adiacenza dei nodi, 
    // associamo al vettore locale il vettore apena ridefinito casualmente
    this->vertexes = vertexes;


};

/**
 * Questa funzione costruisce un Grafo non orientato estraendo casualmente i vertici dal vettore in ingresso,
 * e settandone i figli nella lista di adiacenza, il nodo viene successivamente escluso dalla estrazione.
 * Anche ai nodi figli viene aggiunto nella propria lista di adiacenza il nodo al quale erano stati collegati
 * in qunato grafo non orientato.
 * I nodi figli scelti sono casuali ed i padri non sono settati in quanto compito delle visite.
 * N.B Il vettore viene passato per valore e non per riferimento, così da non modificare la copia originale
 * 
*/

void Graph::buildNotOrientedGraph(vector<Node*> vertexes){
    // Generatore di numeri casuali
    srand(time(NULL));

    // Questo passaggio garantisce che ogni nodo abbia almeno un vicino
    for (auto& vertex : vertexes) {
        // Se il nodo non ha adiacenti
        if (vertex->getAdjList().size() == 0) { 
            // Viene istanziato un sentinella
            Node* adjVertex;
            // Fin quando il nodo scelto non e' diverso da se stesso,
            // serve per evitare i loop, viene selezionato un nodo dalla lista
            do {
                adjVertex = vertexes[rand()%(vertexes.size()-1)];
            } while (adjVertex == vertex); 

            // Viene aggiunto il nodo scelto alla lista di adiacenza
            vertex->addToAdjList(adjVertex);
            // Dato che il grafo qui non e' orientato 
            // definiamo la lista di adiacenza anche del nodo aggiunto
            adjVertex->addToAdjList(vertex);
            // Viene aggiunto l'arco da un lato e dall'altro
            pair<Node*, Node*> edge1 = make_pair(vertex, adjVertex);
            this->unorderedEdges.push_back(edge1);
            pair<Node*, Node*> edge2 = make_pair(adjVertex, vertex);
            this->unorderedEdges.push_back(edge2);
        }
    }
    
    // Per ogni vertice andiamo ad estrarre un numero casuale di nodi
    // E li inseriamo nella lista di adiacenza, ai nodi estratti a loro volta aggiungiamo
    // alla lista di adiacenza il nodo estratto
    for(const auto& vertex : vertexes){

        // Generazione del numero di vicini
        int numberOfAdjVertexes = rand()%((int)(vertexes.size()/2));
        for (int i = 0; i < numberOfAdjVertexes; i++){
            
             // Estrazione casuale del vicino
            Node* adjVertex = vertexes[rand()%(vertexes.size()-1)];
            
            // Se il vicino non e' nella lista di adiacenza viene inserito
            if (!vertex->isNodeAdjacent(adjVertex)){
                // Inserimento nella lista di adiacenza
                vertex->addToAdjList(adjVertex);
                // Inserimento nella lista di adiacenza del nodo associato
                adjVertex->addToAdjList(vertex);
                // Viene aggiunto l'arco da un lato e dall'altro
                pair<Node*, Node*> edge1 = make_pair(vertex, adjVertex);
                this->unorderedEdges.push_back(edge1);
                pair<Node*, Node*> edge2 = make_pair(adjVertex, vertex);
                this->unorderedEdges.push_back(edge2);
                
            }

        }
        
    }

    // Alla fine della creazione delle liste di adiacenza dei nodi, 
    // associamo al vettore locale il vettore apena ridefinito casualmente
    this->vertexes = vertexes;
};



void Graph::BFS(NodeBFS* root = nullptr){

    // La visita in ampiezza puo' essere eseguita sia che il grafo sia orientato sia nel caso contrario

    // Viene comunque fatto un controllo per verificare che i nodi siano di tipo BFS 
    if (!dynamic_cast<NodeBFS*>(this->vertexes[0])){
        cout<<"Il tipo di nodo con cui il grafo e' costurito non permette la BFS!\n\n";
        return;
    } 

    // Se non vi sono vertici da iterare la visita si chiude
    if (this->vertexes.empty()){
        cout<<"La visita non puo' essere effettuata in quanto non vi sono vertici presenti nel grafo.\n\n";
        return;
    }

    // Definiamo una sorgente se non e' stata inviata in ingresso
    if (root == nullptr) root = dynamic_cast<NodeBFS*>(this->vertexes[0]);
    
    if (root == nullptr) {
        cout << "Errore: Il nodo radice non è valido.\n";
        return;
    }

    // Iniziamo la visita inizializzando i vertici
    for (Node* &vertex : this->vertexes){
        NodeBFS* u = dynamic_cast<NodeBFS*>(vertex);
        u->setDistance(INT_MAX);
        u->setFather(nullptr);
        u->setColor(WHITE);
    }

    // Settiamo distanza della radice a 0 e colore a grigio
    root->setDistance(0);
    root->setColor(GRAY);

    // Dichiariamo una coda e vi inseriamo la radice
    queue<NodeBFS*> coda;
    coda.push(root);
    

    // Visita della radice
    cout<<"Visita BFS:\n\nNodo "<<root->getKey()<<" con distanza "<< root->getDistance()<<endl;

    // fino a quando la coda non e' vuota
    while (!coda.empty()){
        
        // Estraiamo il primo nodo della coda
        NodeBFS *node = coda.front();
        coda.pop();

        // Per ogni nodo adiacente bianco, il nodo viene visitato
        for (Node* v : node->getAdjList()){
            NodeBFS* adjNode = dynamic_cast<NodeBFS*>(v);
            // Durante la visita dle nodo bianco il colore viene settato a grigio
            // ll padre al nodo che ne ha generato la scoperta e la distanza a quella del padre + 1
            if (adjNode->getColor() == WHITE){

                // Aggiustiamo il nodo
                adjNode->setColor(GRAY);
                adjNode->setFather(node);
                adjNode->setDistance(node->getDistance() + 1);
                
                // Aggiungiamo il nodo alla coda
                coda.push(adjNode);

                // Visitiamo il nodo
                cout<<"Nodo "<<adjNode->getKey()<<" con distanza "<< adjNode->getDistance()<<endl;

            }
        }
        
        // Alla fine della visita dei vicini, il nodo viene impostato a nero
        node->setColor(BLACK);

    }

};


void Graph::DFS(NodeDFS* root = nullptr){
    // La visita in ampiezza puo' essere eseguita solo nel caso in cui il graso sia //TODO: inserire il tipo di nodo

    // Viene comunque fatto un controllo per verificare che i nodi siano di tipo DFS 
    if (!dynamic_cast<NodeDFS*>(this->vertexes[0])){
        cout<<"Il tipo di nodo con cui il grafo e' costurito non permette la DFS!\n\n";
        return;
    } 

    // Se non vi sono vertici da iterare la visita si chiude
    if (this->vertexes.empty()){
        cout<<"La visita non puo' essere effettuata in quanto non vi sono vertici presenti nel grafo.\n\n";
        return;
    }

    // Definiamo una sorgente se non e' stata inviata in ingresso
    if (root == nullptr) root = dynamic_cast<NodeDFS*>(this->vertexes[0]);
    
    if (root == nullptr) {
        cout << "Errore: Il nodo radice non è valido.\n";
        return;
    }

    // Iniziamo la visita DFS inizializzando i vertici
    for (Node* &vertex : this->vertexes){
        NodeDFS* u = dynamic_cast<NodeDFS*>(vertex);
        u->setColor(WHITE);
        u->setFather(nullptr);
        u->setFinalTime(INT_MAX);
        u->setStartingTime(INT_MIN);
    }

    this->globalTime = 0;

    // Per ogni vertice, se il colore e' bianco iniziamo una nuova visita DFS
    // Potrebbe generarsi una foresta
    for (Node* &x : this->vertexes){
        if (x->getColor() == WHITE){
            cout<<"Nuovo albero DF:"<<endl<<endl;
            NodeDFS* u = dynamic_cast<NodeDFS*>(x);
            this->DFSVisit(u);
        }
        cout<<endl;
    }


};

/**
 * La DFV visit è una funziona ricorsiva che visita istantaneamente i figli di un nodo
 * visitando così prima i nodi foglia o quelli che non hanno archi uscenti a nuovi nodi bianchi,
 * risalendo poi la chiamata allo stack di memoria e visitando i nodi precedenti se questi non
 * hanno nuovi archi in avanti bianchi
 * 
*/
void Graph::DFSVisit(NodeDFS* root){
    
    // Settiamo il colore della attuale radice come grigio
    root->setColor(GRAY);
    // Aumentiamo il tempo globale
    this->globalTime += 1;
    // Settiamo il tempo di inizio visita
    root->setStartingTime(this->globalTime);

    // Per ogni vicino bianco effettuamo una chiamata ricorsiva
    // ed assegnando il padre
    for (auto &x : root->getAdjList()){
        if (x->getColor() == WHITE){
            NodeDFS* v = dynamic_cast<NodeDFS*>(x);
            v->setFather(root);
            this->DFSVisit(v);
        }
    }

    // Quando tutti i vicini del nodo sono stati visitati
    // vengono settati il colore a nero ed il tempo di fine.
    // Viene effettuata la visita della attuale radice
    this->globalTime += 1;
    root->setFinalTime(this->globalTime);
    root->setColor(BLACK);

    cout<<"Nodo "<< root->getKey()<<" con tempo di inizio "<<root->getStartingTime()<<" e tempo di fine "<<root->getFinalTime()<<endl;

}

void Graph::addRandomWeightToEdges(){

    // Tipo orientato
    if (this->type == ORIENTED){
        // Scorriamo gli elementi del vettore di archi di tipo orientato
        for (auto &arch : this->orderedEdges){
            this->weightedEdges.push_back(make_pair(arch, rand()%10));
        }
    
    // Tipo non orientato
    } else {
        // Scorriamo gli elementi del vettore di archi di tipo non orientato
        for (auto &arch : this->unorderedEdges){
            this->weightedEdges.push_back(make_pair(arch, rand()%10));
        }

    }

    // Alla fine il vettore viene ordinato
    sort(weightedEdges.begin(), weightedEdges.end(), 
         [](const pair<pair<Node*, Node*>, int>& a, 
            const pair<pair<Node*, Node*>, int>& b) {
            return a.second < b.second; 
            });

};

void Graph::stronglyConnectedComponents(){

};

Node* Graph::kruskalMST(NodeBFS* root = nullptr){
    // Crea i set
    for (auto &x : this->weightedEdges){
        this->makeSet(x.first.first);
        this->makeSet(x.first.second);
    }
    
    // Gli archi sono ordinati per peso dall'inizio

    // Estrai un arco
    for (auto &arch : this->weightedEdges){
        // Estrai i due nodi
        Node* node1 = arch.first.first;
        Node* node2 = arch.first.second;

        // Controlla che abbiano rappresentanti differenti
        if (findSet(node1) != findSet(node2)){
            // Se li hanno unisci i due nodi per rango
            link(findSet(node1), findSet(node2));
        }
    }
    
    // Viene ritornato il rappresentante dell'MST
    return findSet(this->weightedEdges.at(0).first.first);

};

Node* Graph::primmMST(NodeBFS* root = nullptr){
    return new Node();
};

NodeBFS* Graph::djikstraMinimumPath(NodeBFS* root) {
    
    // Inizializza le distanze per tutti i nodi
    for (auto node : vertexes) {
        NodeBFS* bfsNode = static_cast<NodeBFS*>(node);
        bfsNode->setDistance(INT_MAX);
        bfsNode->setFather(nullptr);
    }
    
    // Distanza del nodo sorgente impostata a 0
    root->setDistance(0);
    
    // Priority queue per selezionare il nodo con distanza minore
    using NodeDist = pair<int, NodeBFS*>;
    priority_queue<NodeDist, vector<NodeDist>, greater<NodeDist>> pq;
    
    pq.push({0, root});
    
    while (!pq.empty()) {
        NodeBFS* u = pq.top().second;
        pq.pop();
        
        // Esplora tutti i vicini di u
        for (const auto& edge : weightedEdges) {
            if (edge.first.first == u) { // Consideriamo solo gli archi usciti da u
                NodeBFS* v = static_cast<NodeBFS*>(edge.first.second);
                int weight = edge.second;
                
                // Se troviamo un percorso più breve per v, aggiorniamo la distanza
                this->relax(u, v, weight);
                pq.push({v->getDistance(), v});
                
            }
        }
    }

    return root;
    
};

void Graph::relax(NodeBFS* u, NodeBFS* v, int weight){
    
    // Se la distanza di v e' maggiore della distanza del padre piu'
    // il peso dell'arco, allora abbiamo trovato un nuovo cammino minimo
    if (v->getDistance() > u->getDistance() + weight){
        // Lo andiamo a settare
        v->setDistance(u->getDistance() + weight);
        v->setFather(u);
    }
    
};

void Graph::makeSet(Node* x){
    x->setFather(x);
};

Node* Graph::findSet(Node* x){

    while (x->getFather() != x) x = x->getFather();
    return x;

};

void Graph::link(Node*x, Node* y){

    if (x->rank > y->rank){
        y->setFather(x);
    
    } else {
        x->setFather(y);
        if (x->rank == y->rank) y->rank += 1;
    
    }
    
};

void Graph::unionNode(Node*x, Node* y){
    this->link(this->findSet(x), this->findSet(y));
};


void Graph::printGraph(){

    cout<<endl<<"Liste di adiacenza del grafo G."<<endl<<endl;
    for (auto &vertex : this->vertexes){
        vertex->printAdjList();
    }
    cout<<endl;

}


void Graph::printEdges(){

    // Check per controllare se il grafo abbia dei vertici
    if (this->vertexes.size() ==0){
        cout<<"Il grafo non ha vertici e archi.\n\n";
        return;
    }
    
    // Print per il caso oriented
    if (this->type == ORIENTED){
        for (auto &edge : this->orderedEdges){ 
            cout<<"( "<<edge.first->getKey()<<", "<<edge.second->getKey()<<" )\n"; 
        }
        cout<<endl;

    // Print per il caso non oriented
    } else {
        for (auto &edge : this->unorderedEdges){ 
            cout<<"( "<<edge.first->getKey()<<", "<<edge.second->getKey()<<" )\n"; 
        }
        cout<<endl;
    }

};


void Graph::printWeightedEdges(){

    // Check per controllare se il grafo abbia dei vertici
    if (this->vertexes.size() ==0){
        cout<<"Il grafo non ha vertici e archi.\n\n";
        return;
    }
    
    // Print per il caso oriented
    if (this->type == ORIENTED){
        for (auto &edge : this->weightedEdges){ 
            cout<<"( "<<edge.first.first->getKey()<<", "<<edge.first.second->getKey()<<" ) "<<"w = "<<edge.second<<"\n"; 
        } 
        cout<<endl;

    // Print per il caso non oriented
    } else {
        for (auto &edge : this->weightedEdges){ 
            cout<<"( "<<edge.first.first->getKey()<<", "<<edge.first.second->getKey()<<" ) "<<"w = "<<edge.second<<"\n"; 
        }
        cout<<endl;
    }

};