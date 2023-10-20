#include <iostream>
using namespace std;

class Contenitore{

    public:

        void versa(int lt){

            qt += lt;

        };

        void togli(int lt){

            if (lt > qt) { return; }

            qt -= lt;

        };

        int getQt(){

            return qt;

        };

    protected:

        int qt = 0;

};



class Anfora: public Contenitore{

    public:

        Anfora(int x, char y){ 

            if (x <= 0) { return; }

            capacita = x; 
            nome = y;

        };

        int getCapacita(){ return capacita; };

        void riempi(){ 

            cout << "Riempio " << this->nome << "\n";

            qt = capacita;
            
        };

        void svuota(){ 
            
            cout << "Svuoto " << this->nome << "\n";
            
            qt = 0; 
        
        };

        void spostaContenuto(Anfora &altra_anfora){

            if (altra_anfora.getQt() + this->getQt() > altra_anfora.capacita)
            {
                
                int restanti = this->getQt() - (altra_anfora.capacita - altra_anfora.getQt());
                int spostati = this->getQt() - restanti;

                cout << "Sposto " << spostati << " litri da " << this->nome <<" verso " << altra_anfora.nome << "\n";
                this->qt = restanti;

                altra_anfora.qt += spostati;

            
            }else{

                cout << "Sposto i "<< this->getQt() <<" litri da " << this->nome <<" verso " << altra_anfora.nome << "\n";
                altra_anfora.qt += this->qt;
                this->svuota();

            }
            

        };

        void isVuota(){

            if (this->qt == 0) {

                cout << "L'anfora "<< this->nome <<" e' VUOTA\n";

            }

        };

        void isPiena(){

            if (this->qt == capacita) {

                cout << "L'anfora "<< this->nome <<" e' PIENA\n";

            }

        };


    private:

        int capacita = 0;
        char nome;

        

};


class Indovinello{

    public:

        Indovinello() : A(5, 'A'), B(3, 'B'){};


        void risolvi(){

            A.isVuota(); B.isVuota();
            B.riempi(); A.isVuota(); B.isPiena();


            B.spostaContenuto(A); 
            cout << "A = "<< A.getQt() << " "; cout << "B = "<< B.getQt() << "\n";

            B.riempi(); B.isPiena();
            cout << "A = "<< A.getQt() << " "; cout << "B = "<< B.getQt() << "\n";

            B.spostaContenuto(A); 
            cout << "A = "<< A.getQt() << " "; cout << "B = "<< B.getQt() << "\n";

            A.svuota();
            cout << "A = "<< A.getQt() << " "; cout << "B = "<< B.getQt() << "\n";

            B.spostaContenuto(A);
            cout << "A = "<< A.getQt() << " "; cout << "B = "<< B.getQt() << "\n";

            B.riempi(); B.isPiena();
            cout << "A = "<< A.getQt() << " "; cout << "B = "<< B.getQt() << "\n";

            B.spostaContenuto(A);
            cout << "A = "<< A.getQt() << " "; cout << "B = "<< B.getQt() << "\n";

    };


    private:

    Anfora A;
    Anfora B;


};





int main (){

    Indovinello risolutore;

    risolutore.risolvi();


    return 0;

}