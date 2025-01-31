#include <iostream>
#include "ABR.h"

// Test dell'albero binario di ricerca
int main() {

    // Dichiarazione dei dati
    std::vector<int> data = {1, 2, 3, 4, 5, 6, 7, 87, 8, 9, 96, 3, 2, 5, 325, 46, 57, 247, 25};

    // Dichiarazione dell'albero
    ABR<int> albero(data);

    // Esecuzione dei metodi
    albero.inOrderTraversal(albero.getRoot());

    return 0;
}
