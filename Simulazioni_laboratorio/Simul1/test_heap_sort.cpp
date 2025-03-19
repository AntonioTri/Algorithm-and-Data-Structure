#include "heap_sort.hpp"
#include <fstream>

int main(){

    ifstream file("input.txt");
    vector<int> numeri;

    if (!file) return 0;
    
    int numero_attuale;

    while (file >> numero_attuale){
        numeri.push_back(numero_attuale);
    }

    file.close();

    // Stampiamo l'array per verificare
    std::cout << "Numeri letti dal file:" << std::endl;
    for (int n : numeri) {
        std::cout << n << " ";
    }
    std::cout << std::endl;
    


    MaxHeap<int> arraySorter;

    arraySorter.heapSort(numeri);

    // Stampiamo l'array per verificare
    std::cout << "Numeri ordinati secondo heap:" << std::endl;
    for (int n : numeri) {
        std::cout << n << " ";
    }
    std::cout << std::endl;


};