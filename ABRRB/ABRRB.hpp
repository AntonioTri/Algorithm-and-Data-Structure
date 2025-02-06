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
        void RBtransplant(Node<T>* u, Node<T>* v);
        void RBDeleteFixup(Node<T>* nodeToAdjust);

    public:
        ABRRB();
        // Costruttore che chiama il costruttore di ABR con un vector vuoto
        ABRRB(std::vector<T> data) : ABR<T, Node<T>>(data){};
        // Qui puoi aggiungere altre inizializzazioni specifiche di ABRRB
        void insertNode(Node<T>* nodeToInsert) override;  // Usa Node<T> come tipo
        void deleteNode(Node<T>* nodeToDelete) override;
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

    if      (follower == nullptr){this->setRoot(nodeToInsert);} 
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


TEMPLATE void ABRRB<T, NodeType>::RBtransplant(Node<T>* startNode, Node<T>* endNode){


    if (startNode->getFather() == nullptr){
        this->setRoot(endNode);
    } else if (startNode == startNode->getFather()->getLeftChild()){
        startNode->getFather()->setLeftChild(endNode);
    } else {
        startNode->getFather()->setRightChild(endNode);
    }

    // Mon vi troviamo la condizione di endNode = Nil e l'operazione viene eseguita a prescindere
    endNode->setFather(startNode->getFather());
    

};

/*

    La delete e' diversa per necessita' di rispettare le proprieta' degli alberi red and black

*/
TEMPLATE void ABRRB<T, NodeType>::deleteNode(Node<T>* nodeToDelete){

    // Il nodo y serve a tenere traccia del nodo che viene cancellato
    Node<T>* y = nodeToDelete;
    // Ne conserviamo il colore
    Color yOriginalColor = y->getColor();

    // Eseguiamo operazioni standard per le transplant con l'accezione di memorizzare
    // Il figlio non nullo del nodo che vogliamo cancellare
    Node<T>* x = nullptr;

    // Primo caso, figlio sinistro nullo, trapiantiamo il figlio destro
    if (nodeToDelete->getLeftChild() == nullptr){
        x = nodeToDelete->getRightChild();
        this->RBtransplant(nodeToDelete, x);
    
    // Secondo caso, figlio destro nullo, trapiantiamo il filgio sinistro
    } else if (nodeToDelete->getRightChild() == nullptr){
        x = nodeToDelete->getLeftChild();
        this->RBtransplant(nodeToDelete, x);
    
    // Terzo caso, il nodo ha entrambi i figli e quindi va trovato il successore
    // Y diventa il successore ed x il suo figlio destro. (In quanto Y e' il successore
    // e' sprovvisto di figlio sinistro, x non puo' essere altro che il filgio destro,
    // vengono coperti anche i casi in cui x sia nullo ugualmente)
    } else {

        // Il colore di y, y ed x adesso cambiano, perche' dobbiamo tenere traccia dellemodifiche 
        // Che stiamo apportando al successore, in quanto lo stiamo trapiantando
        y = this->getMinimum(nodeToDelete->getRightChild());
        x = y->getRightChild();
        yOriginalColor = y->getColor();

        // Trapianto del successore
        if (y->getFather() == nodeToDelete) { x->setFather(y); }
        else {
            this->RBtransplant(y, x);
            y->setRightChild(nodeToDelete->getRightChild());
            y->getRightChild()->setFather(y);
        }

        this->transplant(nodeToDelete, y);
        y->setLeftChild(nodeToDelete->getLeftChild());
        y->getLeftChild()->setFather(y);

        // Y adesso prende il colore del nodo che abbiamo cancellato
        y->setColor(nodeToDelete->getColor());


    }
    
    // Alla fine dobbiamo eseguire una fixup sul nodo x. Y non viola alcuna proprieta'
    // perche' prende il colore del nodo da cancellare nel peggiore dei casi, e quindi rimane la stabilita'
    // definita all'inizio, al contrario il figlio X ora potrebbe star violando qualche proprieta'
    // e ritrovarci con nodi neri mancanti nel percorso oppure due nodi rossi consecutivi

    if (yOriginalColor == BLACK) this->RBDeleteFixup(x);    

};



TEMPLATE void ABRRB<T, NodeType>::RBDeleteFixup(Node<T>* node){

    Node<T>* nodeToAdjust = node;
    // Fin quando il nodo da riparare e' nero ed e' diverso dalla radice eseguiamo
    // la fixup sul nodo
    while (nodeToAdjust->getColor() == BLACK && nodeToAdjust != this->getRoot()){
        // Se il nodo e' un figlio sinistro vengono eseguite le istruzioni per la sinistra
        if (nodeToAdjust->getFather()->getLeftChild() == nodeToAdjust){
            
            // Il fratello del nodo, dobbiamo osservare lui per eseguire le operazioni
            Node<T>* brother = nodeToAdjust->getFather()->getRightChild();
            Node<T>* father = brother->getFather();
            
            // Ci sono ora tre casi, il fratello e' rosso con figli neri
            // Il fratello e' nero con i figli neri (un nero di troppo)
            // Il fratello e' nero con un figlio rosso
            
            // Caso 1, il fratello diventa nero, il padre rosso ed eseguiamo una left 
            // rotate sul padre, andando poi a settare il fratello come il nuovo figlio destro
            // del padre
            if (brother->getColor() == RED){
                brother->setColor(BLACK);
                father->setColor(RED);
                this->rotateLeft(father);
                brother = nodeToAdjust->getFather()->getRightChild();
            }

            // Ricadiamo ora sicuramente in uno dei casi sottostanti in quanto il fratello e' nero
            
            //Caso 2, il colore del fratello diventa rosso ed il nodo da aggiustare diventa ora il padre
            if (brother->getLeftChild()->getColor() == BLACK && brother->getRightChild()->getColor() == BLACK){
                brother->setColor(RED);
                nodeToAdjust = brother->getFather();
            
            // Caso 3 uno dei figli non e' nero
            } else {

                // Se il figlio rosso e' quello sinistro effettuiamo delle operazioni preliminari
                // relative al bilanciamento
                if (brother->getLeftChild()->getColor() == RED){
                    // Il colore del fratello, diventa rosso, il figlio nero,
                    // effettuiamo una rotazione a destra e settiamo il nuovo fratello del nodo
                    brother->setColor(RED);
                    brother->getLeftChild()->setColor(BLACK);
                    this->rotateRight(brother);
                    brother = nodeToAdjust->getFather()->getRightChild();
                }

                // Sicuramente siamo finiti nel caso limite 4, in cui il fratello e' nero
                // con il filgio destro rosso. Le operazioni che facciamo sono le seguenti:
                
                // Il colore del fratello diventa quello del padre
                // Il colore del padre diventa Nero
                // Il colore del figlio destro del fratello diventa nero
                // Ruotiamo l'albero a sinistra rispeto al padre
                // Settiamo il nodo da aggiustare come la radice dell'albero

                brother->setColor(father->getColor());
                father->setColor(BLACK);
                brother->getRightChild()->setColor(BLACK);
                this->rotateLeft(father);
                nodeToAdjust = this->getRoot();
                
            }
    
        // Caso in cui il nodo da aggiustare sia un figlio destro
        } else {
            
            // Il fratello del nodo, dobbiamo osservare lui per eseguire le operazioni
            Node<T>* brother = nodeToAdjust->getFather()->getLeftChild();
            Node<T>* father = brother->getFather();
            
            // Ci sono ora tre casi, il fratello e' rosso con figli neri
            // Il fratello e' nero con i figli neri (un nero di troppo)
            // Il fratello e' nero con un figlio rosso
            
            // Caso 1, il fratello diventa nero, il padre rosso ed eseguiamo una right 
            // rotate sul padre, andando poi a settare il fratello come il nuovo figlio sinistro
            // del padre
            if (brother->getColor() == RED){
                brother->setColor(BLACK);
                father->setColor(RED);
                this->rotateRight(father);
                brother = nodeToAdjust->getFather()->getLeftChild();
            }

            // Ricadiamo ora sicuramente in uno dei casi sottostanti in quanto il fratello e' nero
            
            //Caso 2, il colore del fratello diventa rosso ed il nodo da aggiustare diventa ora il padre
            if (brother->getLeftChild()->getColor() == BLACK && brother->getRightChild()->getColor() == BLACK){
                brother->setColor(RED);
                nodeToAdjust = brother->getFather();
            
            // Caso 3 uno dei figli non e' nero
            } else {

                // Se il figlio rosso e' quello sinistro effettuiamo delle operazioni preliminari
                // relative al bilanciamento
                if (brother->getRightChild()->getColor() == RED){
                    // Il colore del fratello, diventa rosso, il figlio nero,
                    // effettuiamo una rotazione a destra e settiamo il nuovo fratello del nodo
                    brother->setColor(RED);
                    brother->getRightChild()->setColor(BLACK);
                    this->rotateLeft(brother);
                    brother = nodeToAdjust->getFather()->getLeftChild();
                }

                // Sicuramente siamo finiti nel caso limite 4, in cui il fratello e' nero
                // con il filgio destro rosso. Le operazioni che facciamo sono le seguenti:
                
                // Il colore del fratello diventa quello del padre
                // Il colore del padre diventa Nero
                // Il colore del figlio destro del fratello diventa nero
                // Ruotiamo l'albero a sinistra rispeto al padre
                // Settiamo il nodo da aggiustare come la radice dell'albero

                brother->setColor(father->getColor());
                father->setColor(BLACK);
                brother->getLeftChild()->setColor(BLACK);
                this->rotateRight(father);
                nodeToAdjust = this->getRoot();
                
            }
    
        }
    
    }
    
    // Alla fine di tutto andiamo a settare il colore del nodo da aggiustare a nero, ripristinando tutte
    // Le proprieta' dell'albero

    nodeToAdjust->setColor(BLACK);

};




#endif // ABRRB_H
