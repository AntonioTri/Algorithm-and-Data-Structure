#include <list>
#include <cstdlib> // per rand()
#include <iostream>

using namespace std;

int main() {

    list <int> container;
    int val;

    for (int i=0; i<10; i++) {
        val = (int)((float)rand()/RAND_MAX*10);
        container.push_back(val);
    }

    list <int>::iterator it1;
    for ( it1=container.begin(); it1!= container.end(); it1++)
    cout << "elemento della lista: " << *it1 << endl;
    
    return 0;
}