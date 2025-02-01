// File: Node.h
#ifndef NODE_H
#define NODE_H

// Classe Nodo dell'albero binario, con attributi e metodi
#define TEMPLATE template <typename T>

TEMPLATE class Node{

    private:

        // Variabili private di chiavi, figli e padri
        T key;
        Node<T>* father;
        Node<T>* rightChild;
        Node<T>* leftChild;

    public:
        Node();
        Node(T key);

        // Metodi set delle proprieta'
        void setKey(T key);
        void setFather(Node<T>* father);
        void setLeftChild(Node<T>* leftChild);
        void setRightChild(Node<T>* rightchild);

        // Metodi get delle proprieta'
        T getKey();
        Node<T>* getFather();
        Node<T>* getLeftChild();
        Node<T>* getRightChild();

};


TEMPLATE Node<T>::Node(){
    this->father = nullptr;
    this->leftChild = nullptr;
    this->rightChild = nullptr;
    this->key = NULL;
};


TEMPLATE Node<T>::Node(T key){
    this->key = key;
    this->father = nullptr;
    this->leftChild = nullptr;
    this->rightChild = nullptr;
};


TEMPLATE void Node<T>::setKey(T key){
    this->key = key;
};


TEMPLATE void Node<T>::setFather(Node<T>* father){
    this->father = father;
};


TEMPLATE void Node<T>::setLeftChild(Node<T>* leftChild){
    this->leftChild = leftChild;
    leftChild->setFather(this);
};


TEMPLATE void Node<T>::setRightChild(Node<T>* rightChild){
    this->rightChild = rightChild;
    rightChild->setFather(this);
};


TEMPLATE T Node<T>::getKey(){
    return this->key;
};


TEMPLATE Node<T>* Node<T>::getFather(){
    return this->father;
};


TEMPLATE Node<T>* Node<T>::getLeftChild(){
    return this->leftChild;
}


TEMPLATE Node<T>* Node<T>::getRightChild(){
    return this->rightChild;
}


#endif // NODE_H