#include <mutex>

mutex mux;

void Funz1 ( ) {mux.lock(); cout << "Primo thread "; mux.unlock();}
void Funz2 ( ) {mux.lock(); cout << "Secondo thread "; mux.unlock();}

int main(){ 
    
    thread Th1 { Funz1 };
    thread Th2 { Funz2 };

    Th1.join();
    Th2.join();

    return 0;

}