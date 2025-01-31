// File: Node.h
#ifndef NODE_H
#define NODE_H

// Classe Nodo dell'albero binario, con attributi e metodi
template <typename T>
class Node{

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

template <typename T>
Node<T>::Node(){
    this->father = nullptr;
    this->leftChild = nullptr;
    this->rightChild = nullptr;
    this->key = NULL;
};

template <typename T>
Node<T>::Node(T key){
    this->key = key;
    this->father = nullptr;
    this->leftChild = nullptr;
    this->rightChild = nullptr;
};

template <typename T>
void Node<T>::setKey(T key){
    this->key = key;
};

template <typename T>
void Node<T>::setFather(Node<T>* father){
    this->father = father;
};

template <typename T>
void Node<T>::setLeftChild(Node<T>* leftChild){
    this->leftChild = leftChild;
    leftChild->setFather(this);
};

template <typename T>
void Node<T>::setRightChild(Node<T>* rightChild){
    this->rightChild = rightChild;
    rightChild->setFather(this);
};

template <typename T>
T Node<T>::getKey(){
    return this->key;
};

template <typename T>
Node<T>* Node<T>::getFather(){
    return this->father;
};

template <typename T>
Node<T>* Node<T>::getLeftChild(){
    return this->leftChild;
}

template <typename T>
Node<T>* Node<T>::getRightChild(){
    return this->rightChild;
}


#endif // NODE_H