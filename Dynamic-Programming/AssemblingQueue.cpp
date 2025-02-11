#include <iostream>
#include <vector>
#include <utility>
#include <random>

using namespace std;

pair<vector<int>, int> findFastestWay(pair<int,int> startValues, 
                                      vector<vector<int>> factoriesTime, 
                                      vector<vector<int>> factoriesTranfertTime, 
                                      pair<int,int> exitValues, 
                                      int factoryNumber);

int main(){

    // Generatore di numeri casuali
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<int> distrib(1, 10); 

    // Numero di catene
    int chains = 2;
    int factoryNumber = 10;
    
    // Tempi di inizio
    pair<int, int> startValues = make_pair(3, 2);
    
    // Tempi interni delle fabbriche
    vector<vector<int>> factoriesTime(chains, vector<int>(factoryNumber));
    
    // Tempi di trasferimento tra una catena e l'altra
    vector<vector<int>> factoriesTranfertTime(chains, vector<int>(factoryNumber - 1));

    // Tempi di uscita
    pair<int, int> exitValues = make_pair(4, 5);

    // Inizializzazione delle matrici delle catene
    for (int i = 0; i < chains; i++){
        cout<<"Tempi interni alla fabbrica "<<i<<": ";
        for (int j = 0; j < factoryNumber; j++){
            factoriesTime[i][j] = distrib(gen);
            cout<<factoriesTime[i][j]<<" ";
        }
        cout<<endl;
    }

    // Inizializzazione delle matrici dei tempi di trasferimento
    for (int i = 0; i < chains; i++){
        cout<<"Tempi di trasferimento della fabbrica "<<i<<": ";
        for (int j = 0; j < factoryNumber - 1; j++){
            factoriesTranfertTime[i][j] = distrib(gen);
            cout<<factoriesTranfertTime[i][j]<<" ";
        }
        cout<<endl;
    }
    
    // Richiamo della funzione per il calcolo del percorso minimo
    pair<vector<int>, int> result = findFastestWay(startValues, factoriesTime, factoriesTranfertTime, exitValues, factoryNumber);

    // Accesso ai valori restituiti
    vector<int> path = result.first;
    int minTime = result.second;

    // Stampa dei risultati
    cout << "Percorso migliore: ";
    for (int station : path) {
        cout << station << " ";
    }
    cout << "\nTempo minimo: " << minTime << endl;

    return 0;
}


pair<vector<int>, int> findFastestWay(pair<int,int> startValues, 
                                      vector<vector<int>> factoriesTime, 
                                      vector<vector<int>> factoriesTranfertTime, 
                                      pair<int,int> exitValues, 
                                      int factoryNumber){
    
    // Inizializzazione delle strutture per la programmaione dinamica
    vector<int> f1(factoryNumber, 0);
    vector<int> f2(factoryNumber, 0);
    vector<int> lf(factoryNumber, 0);
    
    // inizializzazione dei valori di inizio
    f1[0] = startValues.first + factoriesTime[0][0];
    f2[0] = startValues.second + factoriesTime[1][0];
    
    // Iniziamo a scorrere gli array effettuando i confronti tra i tempi di costruzione
    for (int j = 1; j < factoryNumber; j++){

        // Confronti per trovare il minimo nei confronti della prima catena
        if (f1[j-1] + factoriesTime[0][j] <= f2[j-1] + factoriesTranfertTime[0][j-1] + factoriesTime[0][j]){
            f1[j] = f1[j-1] + factoriesTime[0][j];
            lf[j] = 1;
        } else {
            f1[j] = f2[j-1] + factoriesTranfertTime[0][j-1] + factoriesTime[0][j];
            lf[j] = 2;
        }

        // confronti per trovare il minimo nei confronti della seconda catena
        if (f2[j-1] + factoriesTime[1][j] <= f1[j-1] + factoriesTranfertTime[1][j-1] + factoriesTime[1][j]){
            f2[j] = f2[j-1] + factoriesTime[1][j];
            lf[j] = 2;
        } else {
            f2[j] = f1[j-1] + factoriesTranfertTime[1][j-1] + factoriesTime[1][j];  
            lf[j] = 1;
        }
    }

    // Costruzione dei valori finali
    int fastestTime = 0;
    int lastLine = 0;
    if (f1[factoryNumber - 1] + exitValues.first <= f2[factoryNumber - 1] + exitValues.second){
        fastestTime = f1[factoryNumber - 1] + exitValues.first;
        lastLine = 1;
    } else {
        fastestTime = f2[factoryNumber - 1] + exitValues.second;
        lastLine = 2;
    }

    // Formattazione
    vector<int> optimalPath(factoryNumber);
    optimalPath[factoryNumber - 1] = lastLine;
    for (int j = factoryNumber - 2; j >= 0; j--) {
        optimalPath[j] = lf[j + 1];
    }

    // ritorno dei valori formattati
    return make_pair(optimalPath, fastestTime);
}
