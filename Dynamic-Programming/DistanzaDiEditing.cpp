#include <iostream>
#include <vector>

using namespace std;

int findEditingDistance(string sequence1, string sequence2);
void printMatrix(const vector<vector<int>>& matrix);


int main(){

    // Definiamo il problema della Distanza di Editing come il numero minimo di operazioni
    // ( inserimento, cancellazione, sostituzione ) per trasformare una data sequenza A, in un'altra
    // sequenza B

    // Definiamo le sequenze
    string sequence1 = "ANTONIO";
    string sequence2 = "AUTONION";

    int editingDistance = findEditingDistance(sequence1, sequence2);

    cout << endl << "La distanza di editing e': " << editingDistance << endl;
    return 0;


}


int findEditingDistance(string sequence1, string sequence2){
    
    // Definiamo la matrice dei valori
    int rows = sequence1.size();
    int columns = sequence2.size();

    vector<vector<int>> values(rows, vector<int>(columns, 0));

    // La inizializziamo con la prima riga con interi crescenti
    // e con la prima colonna con interi crescenti

    for (int i = 0; i < rows; i++){
        for (int j = 0; j < columns; j++){
            if (i == 0){ values[i][j] = j;}
            else if (j == 0){ values[i][j] = i;}
            else values[i][j] = 0;
        }
    }
    
    // Mostriamo la matrice
    printMatrix(values);
    

    // Adesso ne calcoliamo i vlaori sulla base della sottostruttura ottima
    for (int i = 1; i < rows; i++){
        for (int j = 1; j < columns; j++){

            // Calcolo dei valori
            int epsilon = (sequence1[i] == sequence2[j] ? 0 : 1);
            int value1 = epsilon + values[i - 1][j - 1];
            int value2 = 1 + values[i - 1][j];
            int value3 = 1 + values[i][j - 1];

            // Calcolo del minimo
            int min = INT_MIN;
            min = (value1 < value2 ? value1 : value2);
            min = (min < value3 ? min : value3); 

            // Assegnazione alla matrice
            values[i][j] = min;

        }
        
    }

    // Rimostriamo la matrice con i nuvi valori
    printMatrix(values);
    
    return values[rows-1][columns-1];
};


void printMatrix(const vector<vector<int>>& matrix){
    
    // Visualizziamo la matrice
    for (const auto& row : matrix) {
        for (int value : row) cout << value << " ";
        cout << endl;
    }
    cout << endl;
}
