/*

    Classe nodo di grafo
    Devono avere le liste di adiacenza, io farei un vettore semplice
    di coppie <Nodo, Nodo> per il grafo, invece farei semplicemente
    un vettore per la lista di adiacenza di un singolo nodo

    Una enumerazione definsce un colore, successivamente getter e setter 
    per le proprietà


*/
#include <iostream>
#include <vector>
#include <list>
#include <algorithm>

using namespace std;

// enumerazione per i colori
enum Color { WHITE, GRAY, BLACK };

class Node {

    protected:
        int key;
        std::list<Node*> adjList;
        Color color;
        Node *father;

    public:
        Node();
        Node(int key);
        virtual ~Node() {}; // Distruttore virtuale per abilitare RTTI

        // Valore usato per la link per gli MST
        int rank = 0;

        // Getter
        int getKey();
        std::list<Node*> getAdjList();
        Color getColor();
        Node* getFather();

        // Setter
        void setKey(int newKey);
        void setAdjList(std::list<Node*>& newAdjList);
        void addToAdjList(Node *nodeToAdd);
        void setColor(Color newColor);
        void setFather(Node* newFather);
        void printAdjList();
        bool isNodeAdjacent(Node *nodeToCheck);


};

Node::Node(){
    this->key = INT_MIN;
    this->adjList = {};
    this->color = WHITE;
    this->father = nullptr;
}

Node::Node(int key){
    this->key = key;
    this->adjList = {};
    this->color = WHITE;
    this->father = nullptr;
}


// Implementazione dei getter
int Node::getKey(){
    return this->key;
}

std::list<Node*> Node::getAdjList(){
    return this->adjList;
}

Color Node::getColor(){
    return this->color;
}

Node* Node::getFather(){
    return this->father;
}

// Implementazione dei setter
void Node::setKey(int newKey){
    this->key = newKey;
}

void Node::setAdjList(std::list<Node*>& newAdjList){
    this->adjList = newAdjList;
}

void Node::addToAdjList(Node *nodeToAdd){
    this->adjList.push_back(nodeToAdd);
}

void Node::setColor(Color newColor){
    this->color = newColor;
}

void Node::setFather(Node* newFather){
    this->father = newFather;
}

bool Node::isNodeAdjacent(Node *nodeToCheck){

    // Se il nodo da verificare è lo stesso nodo corrente, evitiamo auto-loop
    if (nodeToCheck == this) return true; 

    // Controllo se l'elemento è presente nella lista
    for (auto &vertex : this->adjList){
        if (vertex->getKey() == nodeToCheck->getKey())
            return true;
    }

    // ritorniamo false i=nei restanti casi
    return false;
}


void Node::printAdjList(){

    cout<<"ADJ list of "<< this->key<<": ";
    for (auto &node : this->adjList){
        cout<<node->getKey()<<" -> ";
    }
    cout<<"NULL"<<endl;
}
