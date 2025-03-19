#include <iostream>
#include <vector>
#include <fstream>
#include <unordered_map>


/**
 * 
 * Dato in input un file con una visita preorder di un albero binario
 * creare l'albero binario con coppie chiave valore e mostrare la sua visita preorder
 * 
 * Successivamente, vedendo l'albero come fosse una codifica di huffman, codificare una stringa in input
 * Dotare la classe anche di un metodo per fare il contrario
 * 
 */


#define TEMPLATE template<typename K, typename V>
using namespace std;


// Classe nodo dell'albero binario
TEMPLATE class Node{

    public:
        Node<K,V>* leftChild;
        Node<K,V>* rightChild;
        Node<K,V>* father;
        K key;
        V value;

        Node(K key, V value) : key(key), value(value) {
            leftChild = rightChild = father = nullptr;
        }

};



TEMPLATE class HuffmanABR{

    private:

        // La radice del nodo
        Node<K,V>* root;
        // La mappa contenente le coppie chiave (carattere) valore (codifica di huffman)
        unordered_map<V, string> codificheHuffman;

        // Il metodo insert nserisce u nodo nell'albero binario
        void insertNode(K key, V value){

            // Viene creato il nodo e definite le variabili di inseguitore
            // ed di scorrimento
            Node<K,V>* newNode = new Node<K,V>(key, value);
            Node<K,V>* follower = nullptr;
            Node<K,V>* x = root;

            // Un while esegue la ricerca
            while (x != nullptr){
                // Fin quando x e' diverso da puntatore nullo scendiamo nell'albero
                
                // Assegnamo a follower il valore di x
                follower = x;

                // E ad x il valore del suo figlio sinitro o destro sulla base 
                // del criterio di ordinamento dell'albero

                // Se il valore della chiave del nuovo nodo e' maggiore o uguale
                // x diventa il suo figlio destro
                if (newNode->key >= x->key){ x = x->rightChild; }
                // Altrimenti diventa il figlio sinistro
                else { x = x->leftChild; }

            }

            // Alla fine del while andiamo a controllare se x sia 
            // uguale ad un puntatore nullo, in tal caso x diventa radice
            // Se la radice e' vuota allora definiamo il nodo come radice ed usciamo
            if (follower == nullptr){
                root = newNode;
            
            // altrimenti andiamo a definire il nuovo nodo come
            // figlio destro o sinistro dell'inseguitore che ora punta
            // al padre designato del nuovo nodo
            } else if (newNode->key >= follower->key){
                follower->rightChild = newNode;
            } else {
                follower->leftChild = newNode;
            }
            
            // Assegna il padre
            newNode->father = follower;

        };

        // Visita preorder
        void preorderVisit(Node<K,V>* nodeToVisit, ofstream& output){
            
            // Caso base
            if (nodeToVisit == nullptr) return;
            // Visita del nodo inviato
            output<<"Nodo con chiave "<<nodeToVisit->key<<" - Valore = "<<nodeToVisit->value<<"\n";
            // Visita del figlio sinistro
            preorderVisit(nodeToVisit->leftChild, output);
            // Visita del figliod destro
            preorderVisit(nodeToVisit->rightChild, output);

        };

        // La visita preorder modificata per generare la mappa di codifica
        void huffmanPreorderVisit(Node<K,V>* nodeToVisit, ofstream& output, string currentCode){
            
            // Caso base
            if (nodeToVisit == nullptr) return;

            // soltanto se il nodo e' una foglia allora generiamo la sua codifica
            if (nodeToVisit->leftChild == nullptr && nodeToVisit->rightChild == nullptr){
                // Inseriamo nella mappa la sua codifica
                codificheHuffman[nodeToVisit->value] = currentCode;
                cout<<"Codifica con chiave/valore = ("<<nodeToVisit->value<<", "<<codificheHuffman[nodeToVisit->value]<<")\n";
                // La inseriamo nel file di output
                output<<"Nodo con chiave "<<nodeToVisit->key<<" e valore "<<nodeToVisit->value<<". La sua codifica vale: "<<currentCode<<"\n";
            }
            
            // In entrambi i casi viene concatenata alla stringa il bit di codifica
            // Visita del figlio sinistro anche nel caso null ptr
            huffmanPreorderVisit(nodeToVisit->leftChild, output, currentCode + "0");
            // Visita del figlio destro anche nel caso null ptr
            huffmanPreorderVisit(nodeToVisit->rightChild, output, currentCode + "1");

        };



    public:

        HuffmanABR(string inputFileName) : root(nullptr) {

            // Definizione del file di input
            ifstream input(inputFileName);
            // Definizione delle variabili di input
            K key; V value;

            // Con un while andiamo ad inserire i valori nell'albero
            while (input>>key>>value){
                insertNode(key, value);
            }

            // Chiudiamo l'input
            input.close();

        };

        // Metodo che mostra la visita preorder su di un file indicato
        void printPreorder(string outputFileName){
            // Definizione del file di output
            ofstream output(outputFileName);
            output<<"Visita preorder:\n\n";
            // Richiamo alla funzione di visita
            preorderVisit(root, output);
            // Chiusura del file
            output.close();
        };

        // Questo metodo seguendo il principio della visita preorder genera
        // la mappa della codifica secondo il principio di huffman
        void generateHuffmanCode(string outputFileName){
            // Definizione del file di output
            ofstream output(outputFileName);
            output<<"Codifica dell'albero:\n\n";
            // Richiamo alla funzione di visita
            huffmanPreorderVisit(root, output, "");
            // Chiusura del file
            output.close();
        };

        // Metodo che codifica una stringa in input secondo huffman
        string getEncryptedString(string stringToEncrypt){

            // Variabile di appoggio
            string encryptedString = "";
            // Per ogni carattere viene aggiunta la codifica generata precedentemente
            for (int i = 0; i < stringToEncrypt.size(); i++){
                encryptedString += codificheHuffman[stringToEncrypt[i]];
            }

            return encryptedString;

        };

        string decriptString(string strigToDecript){

            // Variabile di appoggio
            string decriptedStrig = "";
            // Nodo viaggiatore
            Node<K,V>* translator = root;

            // Per ogni carattere della string eseguiamo la sua decodifica

            /**
             * Il ragionamento prevede che un bit appartenga ad una sequenza.
             * Se l'attuale nodo contiene dei figli allora non e' un carattere
             * da decodificare. I nodi vengono attraversati se non si trattano di 
             * nodi foglia, per ogni bit scendiamo nell'albero se la precedente 
             * condizione si rivela vera.
             * 
             * Quando arriviamo ad una foglia, resettiamo il traduttore alla radice
             * e concateniamo il carattere del nodo raggiunto alla stringa decodificata
             */
            for (char bit : strigToDecript){

                // Se il bit e' uno 0 scendiamo a destra
                if (bit == '0'){
                    translator = translator->leftChild;
                } else if (bit == '1'){
                    translator = translator->rightChild;
                }
                
                // Se siamo arrivati ad un nodo foglia allora aggiungiamo la
                // decrittazione alla stringa decrittata e ritorniamo alla radice
                if (translator->leftChild == nullptr && translator->rightChild == nullptr){
                    decriptedStrig += translator->value;
                    translator = root;
                }

            }

            // Alla fine ritorniamo la stringa decriptata
            return decriptedStrig;
        }


};


// Test di esecuzione
int main(){

    // Istanza dell'albero
    HuffmanABR<int, char>* Habr = new HuffmanABR<int, char>("ABRin.txt");
    // Esecuzione della visita preorder
    Habr->printPreorder("preorder_visit.txt");
    // Generazione del codice di huffman
    Habr->generateHuffmanCode("huffman_encryption.txt");
    // Codifica di una stringa designata senza spazi
    string encryptedString = Habr->getEncryptedString("CIAO!");

    // Print del valore codificato
    cout<<endl<<"Codifica della stringa = "<<encryptedString<<endl;
    // Decofidica della stringa
    string decriptedString = Habr->decriptString(encryptedString);
    // Print del valore decodificato
    cout<<endl<<"Decodifica della stringa = "<<decriptedString<<endl;


    return 0;
}