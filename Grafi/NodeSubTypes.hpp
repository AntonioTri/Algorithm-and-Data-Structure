#include "GraphNode.hpp"

/**
 * Classe Nodo BFS che contiene come attributi propri la distanza
*/
class NodeBFS : public Node {

    private:
        int distance;

    public:
        NodeBFS() : Node(){};
        NodeBFS(int key) : Node(key){};

        // Getter
        int getDistance();

        // Setter
        void setDistance(int newDistance);
};


// Implementazione dei getter
int NodeBFS::getDistance(){
    return this->distance;
}

// Implementazione dei setter
void NodeBFS::setDistance(int newDistance) {
    this->distance = newDistance;
}


/**
 * Classe nodo DFS, che contiene starting time e final time come attributi propri
*/
class NodeDFS : public Node {

    private:
        int startingTime;
        int finalTime;

    public:
        NodeDFS() : Node(){
            this->startingTime = INT_MIN;
            this->finalTime = INT_MAX;
        };
        NodeDFS(int key) : Node(key){
            this->startingTime = INT_MIN;
            this->finalTime = INT_MAX;
        };

        // Getter
        int getStartingTime();
        int getFinalTime();

        // Setter
        void setStartingTime(int newStartingTime);
        void setFinalTime(int newFinalTime);
};


// Implementazione dei getter
int NodeDFS::getStartingTime(){
    return this->startingTime;
}

int NodeDFS::getFinalTime(){
    return this->finalTime;
}

// Implementazione dei setter
void NodeDFS::setStartingTime(int newStartingTime) {
    this->startingTime = newStartingTime;
}

void NodeDFS::setFinalTime(int newFinalTime) {
    this->finalTime = newFinalTime;
}





