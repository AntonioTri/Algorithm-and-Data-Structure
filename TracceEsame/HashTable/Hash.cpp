#include <vector>
#include <fstream>
#include <iostream>


using namespace std;
#define TEMPLATE template<typename K, typename V>

/**
 * Definire una classe hash table capace di inserire dati da un file
 * Eliminare una chiave
 * Inserire una chiave
 * Un metodo print che inserisca l'attuale stato della hash table in un file indicato
 * 
*/

TEMPLATE class HashTable{

    private:

        // Struct interna per la definizione delle coppie chiave valore
        struct Entry{
            K key;
            V value;
            bool isDeleted = false;

            Entry(K key, V value) : key(key), value(value) {};
        };


        vector<Entry*> table;
        int currentSize;
        int totalCapacity;

    public:

        HashTable(string inputFile) : currentSize(0), totalCapacity(999){

            // Ridefiniamo il size della table sulla base della capacità totale
            table.resize(totalCapacity, nullptr);

            // Definiamo lo strem di input
            ifstream input(inputFile);

            // Valori (int, char)
            int currentKey; char currentChar;

            // Estrazione dei valori col while
            while (input>>currentKey>>currentChar){
                insertPair(currentKey, currentChar);
            }

            // Chiusura del file di input
            input.close();
            

        }

        // Col metodo insert pair andiamo a definire una nuova coppia 
        // e la inseriamo nella posizione del vettore
        void insertPair(K key, V value){

            // Indice di scorrimento
            int i = 0;
            
            while (i < totalCapacity){
                
                // Calcolo dell'indice lineare 
                int index = linearHash(key, i);
                // Se la posizione del vettore è nulla allora inseriamo l'elemento
                // Viene anche controllato che non vi sia uina cancellazione logica
                if (table[index] == nullptr || table[index]->isDeleted){
                    // Inseriamo
                    table[index] = new Entry(key, value);
                    // Incrementiamo la grandezza delle celle occupate
                    currentSize++;
                    // Ritorniamo
                    return;
                }
                
                // Incrementiamo i se non era un indice disponibile
                i++; // Ripetendo il ciclo in una nuova posizione

            }
            
            // Nel caso peggiore se l'inserimento non era possibile viene segnalato
            cout<<"\nInserimento non concesso, limite di oggetti contenuti raggiunto (999).\n";
        
        }


        // Metodo che esegue la delete logica
        void logicalDelete(K key){

            // Indice di scorrimento
            int i = 0;

            // Ciclo while che itera sulle posizioni
            while (i < totalCapacity){
                
                // Definizione dell'indice
                int index = linearHash(key, i);

                // Se l'indice e' presente, non cancellato e la chiave e' uguale a quella cercata
                // Il valore viene eliminato
                if (!table[index]->isDeleted && table[index]->key == key){
                    // Cancellazione logica
                    table[index]->isDeleted = true;
                    // Resize dell'attuale dimensione della tavola
                    currentSize--;
                    return;
                }

                // Incremento di i
                i++;
                
            };

        };


        // La funzione della tavola che ritorna il valore associato alla chiave se esiste
        V findValue(K key){

            // Definizione dell'indice
            int i = 0;

            // Ciclo while
            while (i < totalCapacity){
                
                // Calcolo dell'indice
                int index = linearHash(key, i);

                // Se l'attuale indice viene trovato allora viene ritornato
                // Vi è anche il controllo sulla cancellazione
                if (!table[index]->isDeleted && table[index]->key == key){
                    return table[index]->value;
                }

                // Incremento dell'indice
                i++;

            }

            cout<<"Errore! Valore con chiave "<< key <<" non trovato.";
            return -1;
            
        }

        // Funzione di hash lineare (Linear Probing)
        int linearHash(K key, int index){
            return (key + index) % totalCapacity;
        }


        void print(string outputFileName){

            // Definizione dell'output stream
            ofstream output(outputFileName);

            // Inseriamo del contenuto
            output<<"Contenuto della Hash Table:\n\n";

            // Il ciclo for scorre le celle e stampa solo quelle con valori presenti
            for (int i = 0; i < totalCapacity; i++){
                if (table[i] != nullptr && !table[i]->isDeleted){
                    output<<"Posizione nella tabella = "<<i<<". Coppia chiave valore ("<<table[i]->key<<", "<<table[i]->value <<")\n";
                }
            }
            
            // Chiusura del file stream
            output.close();
        }        


};


int main(){

    // Istanza
    HashTable<int, char>* hashTable = new HashTable<int, char>("HashIn.txt");
    // Print degli inserimeti
    hashTable->print("HashAllContent.txt");
    // Eliminazione di alcune chiavi
    hashTable->logicalDelete(9);
    hashTable->logicalDelete(1);
    hashTable->logicalDelete(0);
    // Print delle cancellazioni
    hashTable->print("HashAfterDelete.txt");
    // Ricerca di un elemento
    char carattere = hashTable->findValue(2); // Dovrebbe essere una G
    cout<<"Elemento con chiave 2 = "<<carattere<<".\n";

    // L'inserimento viene testato alla creazione del file
    
    
    return 0;
}