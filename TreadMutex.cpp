#include <iostream>
#include <mutex>
#include <thread>

using namespace std;

mutex mux;

int main(){ 
    
    thread Th1 { Funz1() };
    thread Th2 { Funz2() };

    Th1.join();
    Th2.join();

    return 0;

}

void Funz1 ( ) {mux.lock(); cout << "Primo thread "; mux.unlock();}
void Funz2 ( ) {mux.lock(); cout << "Secondo thread "; mux.unlock();}