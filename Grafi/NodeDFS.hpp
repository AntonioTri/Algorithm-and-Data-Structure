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

enum Color { WHITE, GRAY, BLACK };

class NodeDFS{

    private:
        int key;
        std::vector<NodeDFS*> adjList;
        Color color;
        NodeDFS *father;
        int startingTime;
        int finalTime;

    public:
        NodeDFS();
        NodeDFS(int key);

        // Getter
        int getKey() const;
        std::vector<NodeDFS*> getAdjList() const;
        Color getColor() const;
        NodeDFS* getFather() const;
        int getStartingTime() const;
        int getFinalTime() const;

        // Setter
        void setKey(int newKey);
        void setAdjList(const std::vector<NodeDFS*>& newAdjList);
        void addToAdjList(NodeDFS *nodeToAdd);
        void setColor(Color newColor);
        void setFather(NodeDFS* newFather);
        void setStartingTime(int newStartingTime);
        void setFinalTime(int newFinalTime);
};

NodeDFS::NodeDFS(){
    this->key = NULL;
    this->adjList = {};
    this->color = WHITE;
    this->father = nullptr;
    this->startingTime = 0;
    this->finalTime = 0;
}


NodeDFS::NodeDFS(int key){
    this->key = key;
    this->adjList = {};
    this->color = WHITE;
    this->father = nullptr;
    this->startingTime = 0;
    this->finalTime = 0;
}


// Implementazione dei getter
int NodeDFS::getKey() const {
    return this->key;
}

std::vector<NodeDFS*> NodeDFS::getAdjList() const {
    return this->adjList;
}

Color NodeDFS::getColor() const {
    return this->color;
}

NodeDFS* NodeDFS::getFather() const {
    return this->father;
}

int NodeDFS::getStartingTime() const {
    return this->startingTime;
}

int NodeDFS::getFinalTime() const {
    return this->finalTime;
}

// Implementazione dei setter
void NodeDFS::setKey(int newKey) {
    this->key = newKey;
}

void NodeDFS::setAdjList(const std::vector<NodeDFS*>& newAdjList) {
    this->adjList = newAdjList;
}

void NodeDFS::addToAdjList(NodeDFS *nodeToAdd) {
    this->adjList.push_back(nodeToAdd);
}

void NodeDFS::setColor(Color newColor) {
    this->color = newColor;
}

void NodeDFS::setFather(NodeDFS* newFather) {
    this->father = newFather;
}

void NodeDFS::setStartingTime(int newStartingTime) {
    this->startingTime = newStartingTime;
}

void NodeDFS::setFinalTime(int newFinalTime) {
    this->finalTime = newFinalTime;
}




