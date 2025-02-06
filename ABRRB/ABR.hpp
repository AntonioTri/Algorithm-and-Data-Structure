#ifndef ABR_HPP
#define ABR_HPP

#include "Node.hpp"
#include <vector>

#define TEMPLATE template <typename T>

// La classe ABR implementa tutte le catratteristiche di un albero binario di ricerca
TEMPLATE class ABR{

    private:
        // L'implementazione richiede soltanto la radice come attributo
        Node<T>* root;
        // I metodi per trovare predecessore e successore sono privati
        Node<T>* predecessor(Node<T>* parentNode);
        Node<T>* successor(Node<T>* parentNode);
        Node<T>* treeSearch(Node<T>* root, T key);


    public:
        // Costruttori
        ABR();
        ABR(Node<T>* root);
        ABR(std::vector<T> data);
        Node<T>* getRoot();
        Node<T>* search(T key);
        Node<T>* getMinimum(Node<T>* root);
        Node<T>* getMaximum(Node<T>* root);
        void insertNode(Node<T>* nodeToInsert);
        void deleteNode(Node<T>* nodeToDelete);
        void inOrderTraversal(Node<T>* root);
        void transplant(Node<T>* exRoot, Node<T>* newRoot);

};


template <typename T> ABR<T>::ABR(){
    this->root = nullptr;
};

template <typename T> ABR<T>::ABR(Node<T>* root){
    this->root = root;
};

template <typename T> ABR<T>::ABR(std::vector<T> data){
    // Viene segnata la radice come nullptr per l'inizializzazione
    this->root = nullptr;
    // Per ogni elemento nel vettore viene creato un nuovo nodo ed inserito nell'albero
    for (int i = 0; i < data.size(); i++){
        // Creazione del nodo
        Node<T>* newNode = new Node<T>(data[i]);
        this->insertNode(newNode);
    }

};

TEMPLATE Node<T>* ABR<T>::getRoot(){
    return this->root;
};


TEMPLATE Node<T>* ABR<T>::treeSearch(Node<T>* root, T key){

    // Se il valore del nodo è nullo siamo ad un caso base ed il valore non
    // è  uiqndi stato trovato
    if (root == nullptr) return nullptr;
    // Altrimenti ci troviamo nei casi di controllo

    // Se la chiave e' uguale allora abbiamo trovato il nodo
    if (key == root->getKey()) return root;
    // Se la chiave da cercare e' minore della radice allora andiamo a ricercare a sinistra
    if (key < root->getKey()) return treeSearch(root->getLeftChild(), key);
    // Altrimenti se la chiave e' maggiore o uguale ritorniamo la ricerca a destera
    if (key> root->getKey()) return treeSearch(root->getRightChild(), key);
    // P.S. : L'if qui definito non e' necessario in quanto si ricadrebbe comunque nei casi
    // dopo il fallimento del precedente if

};

TEMPLATE Node<T>* ABR<T>::search(T key){

    // Ritorniamo il valore trovato dalla treeSearch
    return this->treeSearch(this->root, key);

};

TEMPLATE Node<T>* ABR<T>::getMaximum(Node<T>* root) {
    // Controllo se il nodo iniziale è nullo
    if (root == nullptr) return nullptr;

    // Otteniamo un nodo di riferimento per scorrere
    Node<T>* x = root;

    // Scorriamo verso il figlio destro fino a trovare il massimo
    while (x->getRightChild() != nullptr) {
        x = x->getRightChild();
    }

    // Ritorniamo il massimo
    return x;
};

TEMPLATE Node<T>* ABR<T>::getMinimum(Node<T>* root) {
    // Controllo se il nodo iniziale è nullo
    if (root == nullptr) return nullptr;

    // Otteniamo un nodo di riferimento per scorrere
    Node<T>* y = root;

    // Scorriamo verso il figlio sinistro fino a trovare il minimo
    while (y->getLeftChild() != nullptr) {
        y = y->getLeftChild();
    }

    // Ritorniamo il minimo
    return y;
};


TEMPLATE void ABR<T>::insertNode(Node<T>* nodeToInsert){

    // Dichiariamo l'inseguitore
    Node<T>* follower = nullptr;
    // Otteniamo la reference alla radice
    Node<T>* x = this->root;

    // Iniziamo a visitare utilizzando il principio della ricerca, ricordandoci
    // di aggiornare l'inseguitore
    while (x != nullptr){
        // Aggiornamento dell'inseguitore
        follower = x;
        // Controllo per andare nella parte minore
        if (nodeToInsert->getKey() < x->getKey()){ x = x->getLeftChild(); }
        // Controllo per andare nella parte maggiore
        else x = x->getRightChild();
    }

    // Una volta finita la ricerca eseguiamo ulteriori operazioni sul nodo x che ora sara'
    // La posizione finale del nodo da inserire, avendo la variabile follower come reference
    // al padre del nostro nuovo nodo possiamo definirne la posizione finale

    // Sicuramente a prescindere dai casi, il padre del nodo da inserire e' il follower
    nodeToInsert->setFather(follower);

    // Se il follower e' nullo, allora la radice e' nulla e l'albero era vuoto
    // viene pertanto definita la radice uguale al nodo da inserire
    if(follower == nullptr){
        this->root = nodeToInsert;

    // Altrimenti si controlla in quale lato del follower andare a posizionare la chiave
    } else if (nodeToInsert->getKey() < follower->getKey()){
        follower->setLeftChild(nodeToInsert);
    } else {
        follower->setRightChild(nodeToInsert);
    }
    
};


TEMPLATE Node<T>* ABR<T>::successor(Node<T>* parent){

    // Per trovare il successore troviamo il minimo del sottoalbero destro
    if (parent->getRightChild() != nullptr) return this->getMinimum(parent->getRightChild());
    
    // Se il nodo non possiede il sottoalbero destro allora il sucessore e' il
    // primo nodo che contiene nel suo sottoalbero sinistro, il nodo scelto

    // Sfruttiamo questa caratteristica scorrendo l'albero verso l'alto in complessita' O(h)
    Node<T>* father = parent->getFather();
    Node<T>* temp = parent;

    // Fin quando non troviamo il nodo che ha come figlio sinistro la catena, non ci fermiamo
    while (father != nullptr && father->getRightChild() == temp){
        // Saliamo la gerarchia
        temp = father;
        father = father->getFather();
    }

    // Alla fine del while, una delle due condizioni sara' non verificata, pertanto usciremo
    // e ritorneremo il successore conservato nella variabile "father"
    return father;
     
};


TEMPLATE Node<T>* ABR<T>::predecessor(Node<T>* parent){

    // Per trovare il predecessore troviamo il massimo del sottoalbero sinistro
    if (parent->getLeftChild() != nullptr) return this->getMaximum(parent->getLeftChild());
    
    // Se il nodo non possiede il sottoalbero destro allora il sucessore e' il
    // primo nodo che contiene nel suo sottoalbero destro, il nodo scelto

    // Sfruttiamo questa caratteristica scorrendo l'albero verso l'alto in complessita' O(h)
    Node<T>* father = parent->getFather();
    Node<T>* temp = parent;

    // Fin quando non troviamo il nodo che ha come figlio destro la catena, non ci fermiamo
    while (father != nullptr && father->getLeftChild() == temp){
        // Saliamo la gerarchia
        temp = father;
        father = father->getFather();
    }

    // Alla fine del while, una delle due condizioni sara' non verificata, pertanto usciremo
    // e ritorneremo il predecessore conservato nella variabile "father"
    return father;

};

// TODO: Da rivedere la transplant che non l'hai capita
TEMPLATE void ABR<T>::transplant(Node<T>* exRoot, Node<T>* newRoot){

    // Se il padre della vecchia radice e' nullo allora e' la stesa radice dell'albero
    // settiamo per tanto la nuova radice come radice dell'albero
    if (exRoot->getFather() == nullptr) { this->root = newRoot; }
    
    // Altrimenti se la nuova radice e' un figlio sinistro settiamo come figlio sinistro
    // del padre della vecchia radice la nuova radice
    else if (exRoot == exRoot->getFather()->getLeftChild()) { exRoot->getFather()->setLeftChild(newRoot); }
    
    // Stesso concetto per la destra
    else { exRoot->getFather()->setRightChild(newRoot); }

    // Alla fine del processo se la vecchia radice e' diverso da un puntatore nullo
    // vengono fatte le nuove associazioni dei padri
    if (newRoot != nullptr) newRoot->setFather(exRoot->getFather());
    
};


TEMPLATE void ABR<T>::deleteNode(Node<T>* nodeToDelete){

    // I primi due casi sono semplici, se uno dei figli e' nullo, allora si trapianta
    // al nodo da cancellare, l'altro suo figlio
    if (nodeToDelete->getLeftChild() == nullptr) { 
        this->transplant(nodeToDelete, nodeToDelete->getRightChild()); 
        delete nodeToDelete;
    }
    else if (nodeToDelete->getRightChild() == nullptr) { 
        this->transplant(nodeToDelete, nodeToDelete->getLeftChild()); 
        delete nodeToDelete;
    }
    /*
        Il terzo caso e' piu' complesso in quanto il nodo ha entrambi i figli:


        - Come primo passo dobbiamo trovare il successore del nodo, che sicuramente per definizione
          Non possiedera' figlio sinistro, in quanto minimo tra i massimi.
        
        - Successivamente eseguiamo una transplant sul successore ed il suo figlio destro
          SE E SOLTANTO SE il padre del successore non e' il nodo da cancellare,
          dandoci la possibilita' di rieseguire i settaggi sui nodi in questione

        - Se il padre del successore invece e' il nodo da cancellare allora e' semplice,
          eseguiamo la transplant e aggiunstiamo i puntatori ai padri

    */
    else { 

        // Successore
        Node<T>* successor = this->successor(nodeToDelete);
        if (successor->getFather() != nodeToDelete){

            this->transplant(successor, successor->getRightChild());
            successor->setRightChild(nodeToDelete->getRightChild());
            // Questa operazione e' gia' implementata nella gestione interna dei nodi
            // Ma viene riapplicata per chiarezza
            successor->getRightChild()->setFather(successor);

        }

        this->transplant(nodeToDelete, successor);  // Sostituiamo z con y
        successor->setLeftChild(nodeToDelete->getLeftChild());
        successor->getLeftChild()->setFather(successor);

        delete nodeToDelete;

    }


};

TEMPLATE void ABR<T>::inOrderTraversal(Node<T>* root) {
    if (root != nullptr) {
        // Visita il sottoalbero sinistro
        this->inOrderTraversal(root->getLeftChild());
        // Visita il nodo corrente
        std::cout << root->getKey() << " ";
        // Visita il sottoalbero destro
        this->inOrderTraversal(root->getRightChild());
    }
}


#endif // ABR_HPP




