#include <iostream>
#include <fstream>
#include <string>

using namespace std;

class Classe{

    public: 

        bool Ceck(string riga, string problema){

            //Se tutte e tre le carddinalita' sono rispettate, il metodo ritorna vero
            //Il problema riga x del file "problema.txt", rispetta la condizione riga x del file "condizione.txt"
            if (Nri_da_1_a_n(problema, riga.length() + 1) && Rispetto_segni(riga, problema) && Rispetto_uguaglianze(riga, problema))
            {
                return true;
            }

            //Altrimenti ritorna false, il problema NON rispetta le condizioni
            return false;


        };

        private:

            bool Rispetto_uguaglianze(string riga, string problema){

                bool flag = false;
                int posizione = 0;

                //Mi prendo il primo numero e ne calcolo il numero di cifre
                int nro1 = stoi(problema);
                int nro2;
                int spiazzamento = CountDigits(nro1);

                for (char ch : riga)
                {

                    //Eseguo uno spiazzamento per andare al numero successivo (numero di cifre del numero precedente + 1 per i segni <>)
                    posizione += spiazzamento;
                    string nro_dopo = problema.substr(posizione);

                    //Mi prendo il numero successivo
                    nro2 = stoi(nro_dopo);
                    spiazzamento = CountDigits(nro2);

                    //Risolvo i casi dinamici
                    switch (ch){

                        case '<':
                            flag = confronti(nro1, nro2, ch);
                            break;

                        case '>':
                            flag = confronti(nro1, nro2, ch);
                            break;

                        default:
                            break;  
                    }

                    //Se una disuguaglianza non e' stata rispettata viene attivata la flag restituita falsa (errato) che fa attivare l'if di ritorno
                    if (!flag)
                    {
                        return false;
                    }

                    //altrimenti si passsa ai successivi due numeri, uno e' gia' memorizzato in nro2 che andiamo a salvare in nro1
                    nro1 = nro2;
                    //il numero 2 viene riaggiornato nel ciclo for puntando al successivo numero. Con la seguente riga di comando e l'if di ritorno di cui
                    //sopra settato a false, si dimostra che i numeri vengono presi in sucessione indifferentemente dal numero di cifre:
                    
                    //cout << nro1 << nro2 << endl;

                }

                //ritorna true se tutte le disuguaglianze sono rispettate
                return true;

            };


            bool Rispetto_segni(string riga, string problema){

                    //dichiaro una stringa vuota
                    string senza_numeri = "";

                    //Scorro carattere per carattere la stringa "problema"
                    for(char carattere : problema){

                        //Se il carattere non e' un numero viene aggiunto alla stringa vuota
                        if(carattere < '0' || carattere >'9'){

                            //Quella ottenuta alla fine sara' una stringa con soltanto i segni maggiore e minore
                            senza_numeri += carattere;

                        }

                    }

                    //Ritorna vero se la riga dal file "condizioni" ha gli stessi segni della corrispettiva riga in "problema" altrimenti ritoran falso
                    return (riga == senza_numeri) ? true : false;

            };


            bool Nri_da_1_a_n(string problema, size_t n){ 

                //Vengono estratti dalla stringa problema soltanto i numeri, uno per uno vengono inseriti in un array
                //Che ci viene restituito dalla funzione numeri_presenti
                int* arr = numeri_presenti(problema, n);
                //Settiamo un array di grandezza n, il numero delle disuguaglianze + 1, booleano a tutti elementi false
                bool numeri_presenti[n] = {false};

                //Scorriamo l'array prima creato, e se il numero all'interno e' un numero che interessa a noi setta la posizione dell'array
                //booleano corrispondente al valore del numero, se il numero e' 2 setta l'indice 1 (seconda posizione) come true, esiste
                for (int i = 0; i<n; i++)
                {
                    if (arr[i] > 0 && arr[i] <= n)
                    {
                        numeri_presenti[arr[i] - 1] = true;
                    }

                }
                
                //Metti caso che un numero non ci sia, la sua corrispettiva posizione non sarebbe stata attivata e quindi troveremo un
                //False settato di default che posto al negativo !false, rendera vero l'if e ci ritorna l'errore
                for (int i = 0; i < n; i++)
                {
                    if (!numeri_presenti[i])
                    {
                        return false;
                    }

                }

                //Se tutto e andato bene ci ritorna true
                return true;

            };

            int* numeri_presenti(string problema, int n){

                //Si crea l'array di n elementi
                int *arr = new int[n];
                int i = 0, j=1;

                //come primo elemento si prende il primo numero della stringa
                arr[0] = stoi(problema);

                //si scorre stra i caratteri, anche quelli gia presi e per ogni carattere si incrementa un contatore di  posizione, lo spiazzamento
                for (char ch : problema)
                {
                    i++;

                    //Se il carattere e' un segno maggiore o minore, si cattura il numero a partire dalla posizione della 
                    //disuguaglianza trovata, posizione registra nella variabile i, e lo si posiziona nell'array
                    if (ch == '<' || ch == '>')
                    {
                        string nuovo_numero = problema.substr(i);
                        arr[j] = stoi(nuovo_numero);
                        j++;
                    }
                    
                }

                //Ritorna l'indirizzo base dell'array
                return arr;

            };


            bool confronti(int nro1, int nro2, char ch){

                switch (ch)
                {
                    case '<': return (nro1 < nro2) ? true : false;
                    case '>': return (nro1 > nro2) ? true : false;
                    
                    default:
                        cout << "Carattere non riconosciuto\n";
                        return false;
                }

            };


            int CountDigits(int num){

                string numero = to_string(num);
                return numero.length() + 1;

            };

};





int main(){

    fstream file_disug;
    fstream file_problemi;
    file_disug.open("C:/Users/anton/Documents/Programmi in VS Code/Algoritmi e strutture dati/condizioni.txt", ios::in | ios::out);
    file_problemi.open("C:/Users/anton/Documents/Programmi in VS Code/Algoritmi e strutture dati/problema.txt", ios::in | ios::out);
    
    fstream file_soluzioni;
    file_soluzioni.open("C:/Users/anton/Documents/Programmi in VS Code/Algoritmi e strutture dati/soluzioni.txt", ios::in | ios::out);

    if (!file_disug || !file_problemi || !file_soluzioni) { cout << "Errore nell'apertura di uno o piu file!\n"; return 0; }
    
    Classe calcolatore;
    string riga, problema;
    
    int i = 1;

    while (getline(file_disug, riga))
    {
        getline(file_problemi, problema);
        
        if (calcolatore.Ceck(riga, problema))
        {
            file_soluzioni << "Riga " << i << " CORRETTA!\n";

        } else {
            
            file_soluzioni << "Riga " << i << " SBAGLIATA!\n";

        }

        i++;

    }

    file_disug.close();
    file_problemi.close();
    file_soluzioni.close();

    return 0;

};