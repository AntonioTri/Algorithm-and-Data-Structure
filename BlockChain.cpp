#include <iostream>
#include <string>

#define Template template <typename T>
using namespace std;

//class NodoLista
Template class LinkedList{

    private:

        T *head;
        T *tail;

    public:

        LinkedList(){
            head = nullptr;
            tail = nullptr;
        };

        void setNext(T *next){

            if (head == nullptr){ 
                head = tail = next;
            } else {
                tail->next = next;
                tail = next;
            }

        };

        T* getHead(){return head;};

        void mostraLista(){

            T *current;
            current = getHead();
            
            while (current != nullptr) {
                
                cout << current->getNome() << endl;
                current = current->next;

            }

        };

};

class Transaction{

    friend class LinkedList<Transaction>;

    private:

        string from;
        string to;
        int qt;
        string nome;
        Transaction *next = nullptr;

    public:

        Transaction(string from, string to, int qt, string nome){

            this->from = from;
            this->to = to;
            this->qt = qt;
            this->nome = nome;

        };

        string getFrom(){ return from;};
        string getTo(){return to;};
        int getQT(){return qt;};
        void setNextTransaction(Transaction &next){ this->next = &next; };
        string getNome(){return nome;};

};


class Blocco {

    friend class LinkedList<Blocco>;
        
    private:

        Blocco *next = nullptr;
        LinkedList<Transaction> *listaDiTransazioni;
        string nome = "";

    public:

        Blocco(){};
        Blocco(string nome){this->nome = nome;};
        string getNome(){return nome;};
        void setListOfTransaction(LinkedList<Transaction> *transazioni){ listaDiTransazioni = transazioni; };
        void mostraTransazioni(){ listaDiTransazioni->mostraLista(); };
};







int main(){

    Blocco *blocco1 = new Blocco("Paperino");
    Blocco *blocco2 = new Blocco("Pluto");

    Transaction *primaTransazione = new Transaction("T1", "T2", 100, "Prima");
    Transaction *secondaTransazione = new Transaction("T4", "T32", 14250, "Seconda");
    Transaction *terzaTransazione = new Transaction("T2", "T992", 432002, "Terza");

    LinkedList<Transaction> *listaDiTransazioni = new LinkedList<Transaction>();

    listaDiTransazioni->setNext(primaTransazione);
    listaDiTransazioni->setNext(secondaTransazione);
    listaDiTransazioni->setNext(terzaTransazione);

    blocco1->setListOfTransaction(listaDiTransazioni);
    blocco2->setListOfTransaction(listaDiTransazioni);

    LinkedList<Blocco> *listaDiBlocchi = new LinkedList<Blocco>();

    listaDiBlocchi->setNext(blocco1);
    listaDiBlocchi->setNext(blocco2);

    listaDiBlocchi->mostraLista();

    blocco1->mostraTransazioni();
    blocco2->mostraTransazioni();

    return 0;
}