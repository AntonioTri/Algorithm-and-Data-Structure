#include <map>
#include <iostream>
#include <string>

using namespace std;

int main() {

    map<string,int> amap;

    amap["Primo"] = 1;
    amap["Secondo"] = 2;

    cout << "Size : " << amap.size() << endl;

    amap["Terzo"] = 3;
    amap["Quarto"] = 4;

    amap.insert(pair<string,int>(string("Quinto"),5));
    amap.insert(make_pair("Sesto",6));

    cout << "Size : " << amap.size() << endl;

    map<string,int>::iterator it;
    for ( it=amap.begin(); it!=amap.end(); it++)
    cout << "map : " << it->first << " " << it->second << endl;

    cout << amap.find("Terzo")->second << endl; //se Terzo non esiste?
    cout << amap.at("Quinto") << endl;
    
    amap.clear(); //rimuove gli elementi dalla mappa
    return 0;
}