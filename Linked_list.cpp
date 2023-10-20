#include <iostream>
#include <string>
using namespace std;


class Impiegato{

    protected:

        string nome = "";
        float salario = 0;
        Impiegato *nextImpiegato = nullptr;

    public:

        Impiegato(){};
        Impiegato(string n, float f): nome(n){ 

            if (f < 5000){ salario = f; } else {cout << "Il salario inserito e' troppo alto per un impiegato comune\n"; return;}; 

        };

        string getNome(){ return nome;};
        float getSalario(){ return salario;};

        void impiegatoSuccessivo(Impiegato &prossimo){ nextImpiegato = &prossimo; };
        Impiegato* getProssimo(){return nextImpiegato;};


};


class Manager : public Impiegato{

    public:

        Manager(string n, float f): Impiegato(n,f){
            
            if (f < 5000){ salario = f + 1000; } else {cout << "Il salario inserito e' troppo alto per un Manager\n"; return;};

        }

};

// impiegato + float

float operator+(Impiegato x, float n){

    return x.getSalario() + n;

};

//Variabile globale di inizio e fine lista




class LinkedList{

    Impiegato *inizioLista = nullptr;
    Impiegato *fineLista = nullptr;

    public:

    void mostraLista(){

        Impiegato *persona = inizioLista;
        
        while (persona != nullptr){

            cout << "Nome impiegato = " << persona->getNome() << " --> Salario = " << persona->getSalario();
            persona = persona->getProssimo();
            cout << endl;

        };

        cout << endl;

    };

    void aggiungiImpiegato(string nome, float stipendio, bool flag) {
        
        Impiegato* nuovoImpiegato = nullptr;
        Impiegato* nodoDiAppoggio = nullptr;

        if (flag) {
            nuovoImpiegato = new Manager(nome, stipendio);
        } else {
            nuovoImpiegato = new Impiegato(nome, stipendio);
        }

        if (inizioLista == nullptr) {

            inizioLista = nuovoImpiegato;
            fineLista = nuovoImpiegato;

        } else {
    
            nodoDiAppoggio = fineLista;
            fineLista = nuovoImpiegato;
            nodoDiAppoggio->impiegatoSuccessivo(*fineLista);

        }

    };


    void rimuoviImpiegato(string nome, float stipendio) {

        Impiegato* precedente = nullptr;
        Impiegato* attuale = inizioLista;

        while (attuale != nullptr) {

            if (attuale->getNome() == nome && attuale->getSalario() == stipendio) {

                Impiegato* prossimo = attuale->getProssimo();
                
                if (precedente) {

                    precedente->impiegatoSuccessivo(*prossimo);

                } else {

                    inizioLista = prossimo;
                }
                
                delete attuale;
                break;

            } else {

                precedente = attuale;
                attuale = attuale->getProssimo();

            }
            
        }

    };


    void pagaMensileTotale(){

        float totale = 0;
        Impiegato *attuale = inizioLista;

        while (attuale != nullptr){

            totale = *attuale + totale;
            attuale = attuale->getProssimo();

        }
        
        cout << "Il totale degli stipendi mensili e': " << totale << "\n\n";

    };

};



int main(){

    cout << "*** Benvenuto nel programma di assunzione e licenziamento dipendenti! ***\n\n";

    string risposta;
    LinkedList listaDipendenti;

    string nome; 
    float stipendio;
    int risposta_int;
    

    do {

        cout << "Scegli un' operazione:\n1) Assumi un semplice impiegato\n2) Assumi un Manager.\n3) Licezia qualcuno! E' divertente!\n4) Mostra la paga totale mensile.\n5) Mostra la lista degli impiegati. \n6) Esci dal programma.\n\n";
        cin >> risposta;

        risposta_int = stoi(risposta);

        switch (risposta_int)
        {
            case 1:


                cout << "Come si chiama il tuo Impiegato? Inserisci il suo nome: ";
                cin >> nome; fflush(stdin);
                cout << "Quanto guadagna al mese? Inserisci la paga: ";
                cin >> stipendio; cout << endl; fflush(stdin);

                listaDipendenti.aggiungiImpiegato(nome, stipendio, false);

                break;

            case 2:

                cout << "Come si chiama il tuo Manager? Inserisci il suo nome: ";
                cin >> nome; fflush(stdin);
                cout << "Quanto guadagna al mese? Inserisci la paga (a questa verra' aggiunto un bonus di 1000 soldi): ";
                cin >> stipendio; cout << endl; fflush(stdin);

                listaDipendenti.aggiungiImpiegato(nome, stipendio, true);

                break;

            case 3:

                cout << "Inserisic il nome della persona che vorresti licenziare: ";
                cin >> nome; fflush(stdin);
                cout << "Inserisci quanto guadagna al mese, onde evitare di licenziare qualcuno con lo stesso nome: ";
                cin >> stipendio; cout << endl; fflush(stdin);

                listaDipendenti.rimuoviImpiegato(nome, stipendio);

                break;

            case 4:

                listaDipendenti.pagaMensileTotale();

                break;

            case 5:

                listaDipendenti.mostraLista();

                break;

            case 6: break;

            default:

                cout << "Hai inserito un valore non valido! Riprova.\n\n"; fflush(stdin);

                break;
        }

        fflush(stdin);
        
    } while (risposta_int != 6);
    
    cout << "Grazie e alla prossima :)!\n\n";

    return 0;

}