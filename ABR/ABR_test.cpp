#include <iostream>
#include <vector>
#include "ABR.h"

// Test dell'albero binario di ricerca
int main() {

    // Dichiarazione dei dati
    std::vector<int> numbers = {1, 2, 3, 4, 5, 6, 7, 87, 8, 9, 96, 3, 2, 5, 325, 46, 57, 247, 25};

    // Dichiarazione dell'albero
    ABR<int> albero(numbers);

    // Esecuzione dei metodi
    // albero.inOrderTraversal(albero.getRoot());
    
    Node<int>* maximum = albero.getMaximum(albero.getRoot());
    
    std::cout << "Valore massimo: " << maximum->getKey() << std::endl;
    std::cout << "Rimozione del massimo ...\n";
    
    albero.deleteNode(maximum);
    
    // Viene mostrato l'albero senza il massimo
    albero.inOrderTraversal(albero.getRoot());

    return 0;
}
