#ifndef ABRRB_H
#define ABRRB_H

#include "../ABR/ABR.hpp"
#include "Node.hpp"


TEMPLATE class ABRRB : public ABR<T, Node<T>> {

    private:
        // Una grande differenza sta nell'implementazione della fixup
        // E delle funzioni di rotazione
        void rotateLeft(Node<T>* nodeToRotate);
        void rotateRight(Node<T>* nodeToRotate);
        void insertFixup(Node<T>* nodeToInsert);

    public:
        ABRRB();
        // Costruttore che chiama il costruttore di ABR con un vector vuoto
        ABRRB(std::vector<T> data) : ABR<T, Node<T>>(data){};
        // Qui puoi aggiungere altre inizializzazioni specifiche di ABRRB
        void insertNode(Node<T>* nodeToInsert) override;  // Usa Node<T> come tipo

};


template<class T, class NodeType> ABRRB<T, NodeType>::ABRRB() {
    this->root = nullptr;
};

TEMPLATE void ABRRB<T, NodeType>::insertNode(Node<T>* nodeToInsert) {
    
    Node<T>* follower = nullptr;
    Node<T>* x = this->getRoot();

    while (x != nullptr){
    
        if (nodeToInsert->getKey() >= x->getKey()){ 
            follower = x;
            x = x->getRightChild();
        }
        else if (nodeToInsert->getKey() < x->getKey()) { 
            follower = x;
            x = x->getLeftChild();
        }

    }

    nodeToInsert->setFather(follower);

    if      (follower == nullptr){} 
    else if (nodeToInsert->getKey() < follower->getKey()){ follower->setLeftChild(nodeToInsert);}
    else if (nodeToInsert->getKey() >= follower->getKey()) { follower->setRightChild(nodeToInsert);}
    
    // Piccola differenza, coloriamo il nodo di rosso ed eseguiamo la fixup
    nodeToInsert->setColor(RED);
    this->insertFixup(nodeToInsert);    
    

};


TEMPLATE void ABRRB<T, NodeType>::insertFixup(Node<T>* nodeToInsert){

    // Reference al nodo
    Node<T>* x = nodeToInsert;

    // Fin quando il colore del nodo padre e' rosso la procedura viene riapplicata]
    while (x->getFather()->getColor() == RED){

        // Estraiamo il padre
        Node<T>* father = x->getFather();
        // Estraiamo il nonno
        Node<T>* grandpa = father->getFather();

        // Viene controllato se il padre e' un figlio sinistro
        if (father == grandpa->getLeftChild()){

            // Dopo il controllo viene estratto lo zio che si trova a destra del nonno
            Node<T>* uncle = grandpa->getRightChild();

            // Se il colore dello zio e' ROSSO vengono applicati degli aggiustamenti
            if (uncle->getColor() == RED){
                // Zio, padre e nonno cambiano colore
                uncle->setColor(BLACK);
                father->setColor(BLACK);
                grandpa->setColor(RED);
                // ripetiamo il ciclo con x uguale a suo nonno, in quanto ora lui
                // e' diventato rosso e potrebbe violare a sua volta il principio
                x = grandpa;
            
            // Altrimenti eseguiamo fixup specifici per l'altro caso,
            // quello in cui lo zio sia nero
            } else {

                // Se x e' il figlio destro, lo settiamo come il padre e lo ruotiamo
                if (x == father->getRightChild()){
                    x = father;
                    this->rotateLeft(x);
                }

                // Queste seguenti operazioni vengono eseguite a prescindere
                // Il colore del padre diventa nero
                x->getFather()->setColor(BLACK);
                // Il nono rosso
                x->getFather()->getFather()->setColor(RED);
                // Tutto viene ruotato alla base del nonno
                this->rotateLeft(x->getFather()->getFather());

            }

        // L'altro caso grosso e' quello in cui il padre e' un figlio destro
        // Tutto rimane uguale a prima, solo che vengono invertite destra e sinistra
        } else {

            // Dopo il controllo viene estratto lo zio che si trova a sinistra del nonno
            Node<T>* uncle = grandpa->getLeftChild();

            // Viene controllato il colore dello zio
            if (uncle->getColor() == RED){
                // Zio, padre e nonno cambiano colore
                uncle->setColor(BLACK);
                father->setColor(BLACK);
                grandpa->setColor(RED);
                // ripetiamo il ciclo con x uguale a suo nonno, in quanto ora lui
                // e' diventato rosso e potrebbe violare a sua volta il principio
                x = grandpa;
            
            // Altrimenti eseguiamo fixup specifici per l'altro caso,
            // quello in cui lo zio sia nero
            } else {

                // Se x e' il figlio destro, lo settiamo come il padre e lo ruotiamo
                if (x == father->getLeftChild()){
                    x = father;
                    this->rotateRight(x);
                }

                // Queste seguenti operazioni vengono eseguite a prescindere
                // Il colore del padre diventa nero
                x->getFather()->setColor(BLACK);
                // Il nono rosso
                x->getFather()->getFather()->setColor(RED);
                // Tutto viene ruotato alla base del nonno
                this->rotateRight(x->getFather()->getFather());

            }
        }
    }
};


TEMPLATE void ABRRB<T, NodeType>::rotateLeft(Node<T>* nodeToRotate){

    Node<T>* rightChild = nodeToRotate->getRightChild();
    // iniziamo settando il figlio destro del nodo da ruotare
    nodeToRotate->setRightChild(rightChild->getLeftChild());

    // Se il figlio sinistro del figlio destro del nodo da ruotare non era nullo
    // allora dobbiamo settarvi il nuovo padre
    if (rightChild->getLeftChild() != nullptr){
        rightChild->getLeftChild()->setFather(nodeToRotate);
    }
    
    // Settiamo il padre del nodo da ruotare
    rightChild->setFather(nodeToRotate->getFather());

    // Se il nodo da ruotare era la radice dell'albero allora 
    // inizializziamo la stessa come il figlio destro del nodo da ruotare
    if (nodeToRotate->getFather() == nullptr){
        this->setRoot(rightChild);
    
    // Altrimenti se il nodo da ruotare era un figlio sinistro settiamo
    // I puntatori del padre al nuovo figlio sinistro
    } else if (nodeToRotate == nodeToRotate->getFather()->getLeftChild()){
        nodeToRotate->getFather()->setLeftChild(rightChild);

    //Lo stesso viene applicato al lato destro
    } else {
        nodeToRotate->getFather()->setRightChild(rightChild);
    }

    // Alla fine settiamo il nuovo padre 
    // Ed il nuovo figlio
    rightChild->setLeftChild(nodeToRotate);
    nodeToRotate->setFather(rightChild);
    
    
};




TEMPLATE void ABRRB<T, NodeType>::rotateRight(Node<T>* nodeToRotate){

    Node<T>* leftChild = nodeToRotate->getLeftChild();
    // Iniziamo settando il figlio sinistro del nodo da ruotare
    nodeToRotate->setLeftChild(leftChild->getRightChild());

    // Se il figlio destro del figlio sinistro del nodo da ruotare non era nullo
    // allora dobbiamo settarvi il nuovo padre
    if (leftChild->getLeftChild() != nullptr){
        leftChild->getLeftChild()->setFather(nodeToRotate);
    }
    
    // Settiamo il padre del nodo da ruotare
    leftChild->setFather(nodeToRotate->getFather());

    // Se il nodo da ruotare era la radice dell'albero allora 
    // inizializziamo la stessa come il figlio destro del nodo da ruotare
    if (nodeToRotate->getFather() == nullptr){
        this->setRoot(leftChild);
    
    // Altrimenti se il nodo da ruotare era un figlio sinistro settiamo
    // I puntatori del padre al nuovo figlio sinistro
    } else if (nodeToRotate == nodeToRotate->getFather()->getLeftChild()){
        nodeToRotate->getFather()->setLeftChild(leftChild);

    //Lo stesso viene applicato al lato destro
    } else {
        nodeToRotate->getFather()->setRightChild(leftChild);
    }

    // Alla fine settiamo il nuovo padre 
    // Ed il nuovo figlio
    leftChild->setRightChild(nodeToRotate);
    nodeToRotate->setFather(leftChild);
    
    
};


#endif // ABRRB_H
