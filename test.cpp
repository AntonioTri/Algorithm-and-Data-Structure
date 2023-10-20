#include <iostream>
#include <array>

using namespace std;

int main() {
    array<int, 10> arr = {0, 1, 2, 3, 4, 5, 6, 7, 8}; // Array di 10 elementi

    // Crea un array di booleani per tenere traccia dei numeri da 0 a 9
    bool numeriPresenti[10] = {false};

    // Scansiona l'array e imposta a true l'elemento corrispondente nell'array dei booleani
    for (int num : arr) {
        if (num >= 0 && num < 10) {
            numeriPresenti[num] = true;
        }
    }

    // Controlla se tutti i numeri da 0 a 9 sono presenti
    bool contieneTuttiINumeri = true;
    for (int i = 0; i < 10; i++) {
        if (!numeriPresenti[i]) {
            contieneTuttiINumeri = false;
            break; // Se manca un numero, esci dal ciclo
        }
    }

    if (contieneTuttiINumeri) {
        cout << "L'array contiene tutti i numeri da 0 a 9." << endl;
    } else {
        cout << "L'array non contiene tutti i numeri da 0 a 9." << endl;
    }

    return 0;
}
