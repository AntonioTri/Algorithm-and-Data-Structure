#include <iostream>
#include <cmath>

using namespace std;

class alberoPerArray{

    public:

        // int nodeHeight(int *a, int index, int nodeNumber, int value){

        //     if (*a == value)
        //     {
        //         int value1, value2;
        //         value1 = findNodeHeight();
        //         value2 = findNodeHeight()

        //         if(value1 > value2) ? return value1 : return value2;

        //     } else {

        //         int leftChild = 2*index + 1;
        //         int rightChild = 2*index + 2;

        //         if(leftChild > nodeNumber || rightChild > nodeNumber){ return 0 }

        //         int left = nodeHeight(a + leftChild, leftChild, nodeNumber, value);
        //         int right = nodeHeight(a + rightChild, rightChild, nodeNumber, value)


        //     }
            


        // }

        int verificaAppartenenzaERitornaAltezza(const int* array, int indice, int lunghezza, int x, int altezzaCorrente) {
            
            if (indice >= lunghezza || array[indice] == -1) {
                return -1; // Nodo non trovato
            }

            if (array[indice] == x) {
                return altezzaCorrente;
            }

            int indiceSinistro = 2 * indice + 1;
            int indiceDestro = 2 * indice + 2;

            int altezzaSinistra = verificaAppartenenzaERitornaAltezza(array, indiceSinistro, lunghezza, x, altezzaCorrente + 1);
            int altezzaDestra = verificaAppartenenzaERitornaAltezza(array, indiceDestro, lunghezza, x, altezzaCorrente + 1);

            // Se x è presente sia nel sottoalbero sinistro che in quello destro,
            // restituisci l'altezza minima tra i due sottoalberi
            if (altezzaSinistra != -1 && altezzaDestra != -1) {
                return min(altezzaSinistra, altezzaDestra);
            }

            // Altrimenti, restituisci l'altezza massima tra i sottoalberi
            return std::max(altezzaSinistra, altezzaDestra);
        }


};





int main(){

    int array[] = {1, 2, 3, 4, 5, 6, 7, -1, -1, 10, -1, -1, -1, 14};
    int lunghezzaArray = sizeof(array) / sizeof(array[0]);
    alberoPerArray mammt;
    int x = 10;

    int altezza = mammt.verificaAppartenenzaERitornaAltezza(array, 0, lunghezzaArray, x, 0);

    if (altezza != -1) {
        std::cout << "Il valore " << x << " appartiene all'albero e ha altezza " << altezza << std::endl;
    } else {
        std::cout << "Il valore " << x << " non appartiene all'albero." << std::endl;
    }

    return 0;

}