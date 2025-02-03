// File: Node.h
#ifndef NODE_HPP
#define NODE_HPP

// Classe Nodo dell'albero binario, con attributi e metodi
#define TEMPLATEN template <typename T>
enum Color { RED, BLACK };

TEMPLATEN class Node{

    private:

        // Variabili private di chiavi, figli e padri
        T key;
        Color nodeColor;
        Node<T>* father;
        Node<T>* rightChild;
        Node<T>* leftChild;

    public:
        Node();
        Node(T key);

        // Metodi set delle proprieta'
        void setKey(T key);
        void setColor(Color color);
        void setFather(Node<T>* father);
        void setLeftChild(Node<T>* leftChild);
        void setRightChild(Node<T>* rightchild);

        // Metodi get delle proprieta'
        T getKey();
        Color getColor();
        Node<T>* getFather();
        Node<T>* getLeftChild();
        Node<T>* getRightChild();

};


TEMPLATEN Node<T>::Node(){
    this->key = NULL;
    this->nodeColor = RED;
    this->father = nullptr;
    this->leftChild = nullptr;
    this->rightChild = nullptr;
};


TEMPLATEN Node<T>::Node(T key){
    this->key = key;
    this->nodeColor = RED;
    this->father = nullptr;
    this->leftChild = nullptr;
    this->rightChild = nullptr;
};


TEMPLATEN void Node<T>::setKey(T key){
    this->key = key;
};


TEMPLATEN void Node<T>::setColor(Color color){
    this->nodeColor = color;
}


TEMPLATEN void Node<T>::setFather(Node<T>* father){
    this->father = father;
};


TEMPLATEN void Node<T>::setLeftChild(Node<T>* leftChild){
    this->leftChild = leftChild;
    leftChild->setFather(this);
};


TEMPLATEN void Node<T>::setRightChild(Node<T>* rightChild){
    this->rightChild = rightChild;
    rightChild->setFather(this);
};


TEMPLATEN T Node<T>::getKey(){
    return this->key;
};


TEMPLATEN Color Node<T>::getColor(){
    return this->nodeColor;
}


TEMPLATEN Node<T>* Node<T>::getFather(){
    return this->father;
};


TEMPLATEN Node<T>* Node<T>::getLeftChild(){
    return this->leftChild;
}


TEMPLATEN Node<T>* Node<T>::getRightChild(){
    return this->rightChild;
}


#endif // NODE_HPP