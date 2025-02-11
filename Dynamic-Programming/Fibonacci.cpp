#include <iostream>
#include <unordered_map>

using namespace std;


// Funzione di Fibonacci con memoization
int fibonacci(int number, unordered_map<int, int>& preprocessedNumbers) {
    // Caso base
    if (number == 0) return 0;
    if (number == 1) return 1;

    // Se il numero è già stato calcolato, lo ritorniamo
    if (preprocessedNumbers.find(number) != preprocessedNumbers.end()) {
        return preprocessedNumbers[number];
    }

    // Calcoliamo il valore e lo memorizziamo nella mappa
    preprocessedNumbers[number] = fibonacci(number - 1, preprocessedNumbers) + fibonacci(number - 2, preprocessedNumbers);
    
    return preprocessedNumbers[number];
}


int main(){

    // Numero di fibonacci da voler trovare
    int fibNumber = 20;

    // Mappa per la memorizzazione dei dati
    unordered_map<int, int> preprocessedNumbers;

    // Troviamo il numero di fibonacci
    int fibonacciNumber = fibonacci(fibNumber, preprocessedNumbers);

    // Lo stampiamo
    cout<<"Il "<<fibNumber<<"-esimo numero di fibonacci e' uguale a: "<<fibonacciNumber<<endl;


}