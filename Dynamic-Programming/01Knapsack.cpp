#include <iostream>
#include <vector>

using namespace std;

vector<vector<int>> zeroOneKnapsack(vector<int> values, vector<int> weight, int maxWeight);
void printMatrix(const vector<vector<int>> &valueMatrix);
vector<int> findObjectToTake(const vector<vector<int>> &matrixValue, vector<int> weight);


int main(){

    // Dichiariamo i pesi i valori ed il peso massimo
    vector<int> values = {1,2,3,4,5,6,7,8,9,10};
    vector<int> weight = {3,5,1,12,3,8,9,3,1,6};
    int maxWeight = 20;

    cout<<"I valori sono: ";
    for (const auto& item : values) cout<<item<<" ";

    cout<< endl <<"I pesi sono: ";
    for (const auto& item : weight) cout<<item<<" ";
    cout << endl << endl;

    // Inviamo  valori alla funzione che calcola lo zaino ed il massimo valore ottenibile
    vector<vector<int>> matrixValue = zeroOneKnapsack(values, weight, maxWeight);

    cout << endl << "Il valore massimo ottenibile e' : " << matrixValue[values.size()-1][maxWeight-1] << endl;

    vector<int> objectToTake = findObjectToTake(matrixValue, weight);

    cout<<"Gli oggetti da prendere sono gli 1, gli 0 sono quelli da non prendere. ( ";
    
    for (const auto& item : objectToTake) cout<<item<<" "; 
    
    cout<<")"<<endl;

    // Prova del nove, scorriamo l'array ei valori, e sommiamo il valore attuale al totale
    // Se l'oggetto e' uguale ad uno, altrimenti proseguiamo
    int sumTot = 0;
    for (int i = 0; i < values.size() ; i++){
        cout<<objectToTake[i]<<" : "<<values[i]<<endl;
        if (objectToTake[i] == 1) sumTot += values[i];
    }

    cout<<"Somma calcolata iterativamente sommando i valori degli oggetti presi: "<<sumTot<<endl;

}


vector<vector<int>> zeroOneKnapsack(vector<int> values, vector<int> weight, int maxWeight){

    // Otteniamo le misure per la matrice
    int rows = values.size();
    int columns = maxWeight;

    // dichiariamo la matrice
    vector<vector<int>> valueMatrix(rows, vector<int>(columns, 0));

    // La inizializziamo
    for (int i = 0; i < rows; i++){
        for (int j = 0; j < columns; j++) {
            valueMatrix[i][j] = 0;
        } 
    }

    // Utilizando ora l'approccio dinamico popoliamo la matrice
    for (int i = 1; i < rows; i++){ 
        for (int j = 1; j < maxWeight; j++){
            // Calcoliamo i tre valori e selezioniamo il massimo

            // Se  il peso dell'oggetto e' maggiore non possiamo prendere l'oggetto
            // e restiamo col valore dell'oggetto precedente gia' risolto
            if (weight[i] > j){
                valueMatrix[i][j] = valueMatrix[i - 1][j];
            
            // Altrimenti dobbiamo trovare il massimo tra, il valore calcolato prendendo l'oggetto 
            // precedente ed il valore calcolato prendendo l'attuale oggetto, tenendone ovviamente
            // in considerazione il suo peso
            } else if (valueMatrix[i - 1][j] < valueMatrix[i - 1][j - weight[i]] + values[i]){
                valueMatrix[i][j] = valueMatrix[i - 1][j - weight[i]] + values[i];
            } else {
                valueMatrix[i][j] = valueMatrix[i - 1][j];
            }
        }
    }

    // Mostriamo la matrice dei valori
    printMatrix(valueMatrix);
    // Ritorniamo il massimo valore possibile
    return valueMatrix;

};


vector<int> findObjectToTake(const vector<vector<int>> &matrixValue, vector<int> weight){

    // righe e colonne
    int row = (int)matrixValue.size()-1;
    int column = (int)matrixValue[0].size()-1;  

    // Array di 0 ed 1 che rappresenta gli oggetti da prendere
    vector<int> objectToTake(row+1, 0);

    // Eseguiamo un while per partire dalla fine della matrice
    while (row > 0 && column > 0){
        
        // Se il valore dell'attuale cella e' diverso dalla cella sovrastante
        // l'oggetto e' stato preso, scaliamo le colonne e le righe per riferirci
        // all'oggeto preso recedentemente con il peso aggiornato
        // ( alle colonne sottraiamo il peso dell'attuale oggetto, ed alle righe
        // sottraiamo uno per arrivare all'oggetto precedente )
        if (matrixValue[row][column] != matrixValue[row-1][column]){
            objectToTake[row] = 1;
            column -= weight[row];
            row--;

        // Se invece l'oggetto non e' stato preso, quindi il valore della cella e'
        // uguale alla cella sovrastante, scaliamo la riga e segnaliamo che l'oggetto non
        // e' stato preso. Le colonne rimangono invariate
        } else {
            objectToTake[row] = 0;
            row--;
        }
    }
    
    // ritorniamo la lista degli oggetti da prendere
    return objectToTake;

};


void printMatrix(const vector<vector<int>> &valueMatrix){

    for(const auto &row : valueMatrix){
        for(auto value : row){
            cout<< value << "\t";
        }
        cout<<endl;
    }
};