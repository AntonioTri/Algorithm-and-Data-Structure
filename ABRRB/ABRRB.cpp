#include <iostream>
#include "ABRRB.hpp"

int main(){

    // Dichiarazione dei dati
    std::vector<int> numbers = {1, 2, 3, 4, 5, 6, 7, 87, 8, 9, 96, 3, 2, 5, 325, 46, 57, 247, 25};

    // Dichiarazione dell'albero
    ABRRB<int, Node<int>>* alberoRB = new ABRRB<int, Node<int>>(numbers);

    // Facciamo la visita
    alberoRB->inOrderTraversal(alberoRB->getRoot());
    std::cout<<std::endl;
    
    alberoRB->deleteNode(alberoRB->getRoot());
    
    alberoRB->inOrderTraversal(alberoRB->getRoot());
    std::cout<<std::endl;

    Node<int>* maximum = alberoRB->getMaximum(alberoRB->getRoot());

    //Cancellazione dle massimo
    alberoRB->deleteNode(maximum);


    alberoRB->inOrderTraversal(alberoRB->getRoot());
    std::cout<<std::endl;

    Node<int>* quarantasei = alberoRB->search(46);
    
    //Cancellazione di 46
    alberoRB->deleteNode(quarantasei);


    alberoRB->inOrderTraversal(alberoRB->getRoot());
    std::cout<<std::endl;

}