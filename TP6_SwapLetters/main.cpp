#include <iostream>
#include "list"

using namespace std;

void swappAndAddToList(string &s, int sPos, string &t, int tPos, list<pair<int,int>> &swaps){
    //Swapp
    char copia = t[tPos];
    t[tPos] = s[sPos];
    s[sPos] = copia;

    //Agrego par de posiciones swappeadas a la lista
    pair<int,int> par = {sPos,tPos};
    swaps.push_back(par);
}

/* Para arreglar una discordancia localmente mediante swaps, podemos buscar y encontrarnos tres casos:
 *
 * (Con S y T strings, a y b chars distintos).
 *
 * Caso 1: S[i] = a, T[i] = b, entonces debo buscar una j i<j<n tal que S[j] = a y T[j] = b.
 * Este es el caso más conveniente porque el costo de arreglar con swap es de 1, swappeando solamente T[i] por S[j]
 * y arreglando dos discordancias a la vez.
 *
 * Caso 2: S[i] = a, T[i] = b, entonces debo buscar una j i<j<n tal que S[j] = b y T[j] = a. (Caso cruzado)
 * Este caso es más caro, pues primero hay que swappear T[j] por S[j] para recién poder swappear como en el caso 1.
 * El costo de arreglar este caso es 2.
 *
 * Caso 3: S[i] = a, T[i] = b, y con una j tal que S[j] = a y T[j] = a o S[j] = b y T[j] = b.
 * Este caso no lo voy a utilizar nunca, pues no es eficiente arreglar el problema de la posicion i rompiendo el de j.
 *
 * El algoritmo entonces intentará priorizar siempre el Caso 1, de no encontrar esa situacion, buscará el caso 2. Si no,
 * quiere decir que no hay forma de solucionarlo y se retornara -1.
 * */
int swapLetters(int size, string &s, string &t, list<pair<int,int>> &swaps){
    int cantSwaps = 0;
    for(int i = 0; i < size; i++){
        if(s[i] == t[i]) continue;
        //Caso 1:
        for(int j = i + 1; j < size; j++){
            if(s[i] == s[j] && s[j] != t[j]){
                swappAndAddToList(s, j, t, i, swaps);
                cantSwaps++;
                break;
            }
        }
        if(s[i] == t[i]) continue;
        //Caso 2 (cruzado):
        for(int j = i + 1; j < size; j++){
            if(s[i] == t[j] && s[j] == t[i]){
                swappAndAddToList(s, j, t, j, swaps);
                swappAndAddToList(s, j, t, i, swaps);
                cantSwaps += 2;
                break;
            }
        }
        //Si siguen siendo distintos, no encontré un swap.
        if(s[i] != t[i]) return -1;
    }
    return cantSwaps;
}

int main() {
    //Inicializo estructuras y leo datos de entrada
    int size;
    string s;
    string t;
    list<pair<int,int>> swaps; //En la lista guardaré las posiciones de swap a imprimir
    cin >> size >> s >> t;
    //Ejecuto la función
    int res = swapLetters(size, s, t, swaps);
    //Imprimo solución
    cout << res << endl;
    if(res != -1){
        for(auto& par: swaps){
            cout << par.first + 1 << " " << par.second + 1 << endl;
        }
    }
    return 0;
}
