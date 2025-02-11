#include <iostream>
#include <vector>

using namespace std;

int main(){

    // Dichiariamo i pesi i valori ed il peso massimo
    vector<int> values = {1,2,3,4,5,6,7,8,9,10};
    vector<int> weight = {3,5,1,12,3,8,9,3,1,6};
    int maxWeight = 20;

    cout<<"I valori sono: ";
    for (const auto& item : values) cout<<item<<" ";

    cout<< endl <<"I pesi sono: ";
    for (const auto& item : weight) cout<<item<<" ";
    cout << endl << endl;

    

}