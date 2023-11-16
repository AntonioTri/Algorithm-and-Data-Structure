#include <vector>
#include <iostream>

using namespace std;

int main(){

    vector<int> v;
    const int n = 10;

    for (int i = 1; i <= n; ++i) {
        v.push_back(i);
    }

    for (int i = n - 1; i >= 0; --i) {
        cout << v[i] << " ";
    }

    cout << v.size();
    return(0);

} 