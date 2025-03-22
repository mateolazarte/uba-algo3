/* TP4
 * LU: 539/22
 * Usuario de vjudge: mateolazarte
 * */

#include <iostream>

using namespace std;

//Algoritmo de D&C
bool stringsEquivalentes(string a, string b){
    int n = a.size();

    //Caso base. Si n == 1, no puedo reducir más el string y pregunto si a == b.
    //Si n es impar, la única solución posible es que a == b.
    if(n == 1 || n % 2 == 1) return a == b;

    //Pregunto por el caso a1b2 y a2b1
    if (stringsEquivalentes(a.substr(0,n/2), b.substr(n/2,n)) &&
        stringsEquivalentes(a.substr(n/2,n), b.substr(0,n/2))) return true;

    //Pregunto por el caso a1b1 y a2b2
    return stringsEquivalentes(a.substr(0,n/2), b.substr(0,n/2)) &&
           stringsEquivalentes(a.substr(n/2,n), b.substr(n/2,n));

    //Si se da cualquiera de los dos casos, retorno true, pues se cumple la equivalencia.
}

int main() {
    //Leo las entradas
    string a;
    string b;
    cin >> a >> b;
    //Ejecuto la función y retorno la respuesta
    bool res = stringsEquivalentes(a,b);
    if(res){
        cout << "YES" << endl;
    } else cout << "NO" << endl;
    return 0;
}
