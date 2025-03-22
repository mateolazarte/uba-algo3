#include <iostream>
#include "vector"
#include "cmath"

using namespace std;
//ojo con la necesidad de buscar en vecinos anteriores
long long int minimumWork(vector<long long int> &vecinos){
    long long int work = 0;

    int cantCompradores = 0;
    int cantVendedores = 0;
    for(long long vecino : vecinos){
        if (vecino >= 0) cantCompradores++;
        if (vecino < 0) cantVendedores++;
    }

    vector<pair<long long int, int>> compradores(cantCompradores);
    vector<pair<long long int, int>> vendedores(cantVendedores);

    int iC = 0;
    int iV = 0;
    for(int k = 0 ; k < vecinos.size(); k++){
        if (vecinos[k] >= 0) {
            compradores[iC] = {vecinos[k], k};
            iC ++;
        }
        if (vecinos[k] < 0) {
            vendedores[iV] = {vecinos[k], k};
            iV++;
        }
    }
    iC = 0;
    iV = 0;

    while( iC < cantCompradores && iV < cantVendedores){
        while(compradores[iC].first > 0){
            if(vendedores[iV].first == 0){
                iV++;
                continue;
            }
            if(-vendedores[iV].first <= compradores[iC].first){
                work += abs(vendedores[iV].second - compradores[iC].second) * (-vendedores[iV].first);
                //cout << "Work: " << work << endl;
                compradores[iC].first += vendedores[iV].first;
                vendedores[iV].first -= vendedores[iV].first;
            }
            else {
                long long int diff = -vendedores[iV].first - compradores[iC].first;
                work += abs(vendedores[iV].second - compradores[iC].second) * (-vendedores[iV].first - diff);
                //cout << "Work: " << work << endl;
                compradores[iC].first += vendedores[iV].first + diff;
                vendedores[iV].first -= vendedores[iV].first + diff;
            }
        }
        iC++;
    }
    return work;
}

int main() {
    int n;
    cin >> n;
    vector<long long int> vecinos(n);
    for(int i = 0; i < n; i++){
        cin >> vecinos[i];
    }
    cout << minimumWork(vecinos) << endl;
    return 0;
}
