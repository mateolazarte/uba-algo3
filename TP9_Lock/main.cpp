//Alumno: Mateo Lazarte
//LU: 539/22
//Cuenta de vjudge: mateolazarte

#include <iostream>
#include <cmath>
#include "vector"
#include "list"

using namespace std;

//Dados dos numeros del 0 al 9, calcula la minima distancia "circular" entre ambos
int minimumDistanceBetween(int a, int b){
    if(abs(a - b) > 5){
        //Si la distancia absoluta de la resta es mayor a 5, conviene acercarme dando una vuelta
        return 10 - max(a,b) + min(a,b);
    }
    else return abs(a - b);
}

//Dados dos keys, calcula la minima cantidad de rolls necesaria para ir de una a otra.
int minimumRollsBetween(const string &key1, const string &key2){
    int rolls = 0;
    //Itero entre los 4 digitos
    for(int i = 0; i < 4; i++){
        //Restar un '0' al char de un numero, lo "convierte" en int
        rolls += minimumDistanceBetween(key1[i] - '0', key2[i] - '0');
    }
    return rolls;
}

//Caso 0000:
pair<int,int> findClosestNodeToZero(int totalKeys, vector<string> &keys){
    //Entre las keys, busco aquella con menor cantidad de rolls con 0000
    int minIt = 0;
    int minPeso = minimumRollsBetween("0000", keys[0]);
    for(int i = 1; i < totalKeys; i++){
        int pesoActual = minimumRollsBetween("0000", keys[i]);
        if(pesoActual < minPeso){
            minPeso = pesoActual;
            minIt = i;
        }
    }
    //Retorno el nodo cuya arista tiene el menor peso con 0000.
    //Retorno el peso.
    return {minIt, minPeso};
}

int prim(vector<vector<int>> &grafo, int totalKeys, int minIt, int minPeso){
    int res = minPeso;
    list<int> V_T = {minIt};    //lista de vertices pertenecientes al arbol de Prim
    vector<int> visitadas(totalKeys);
    visitadas[minIt] = 1;
    int i = 1;
    while(i <= totalKeys - 1){
        //Busco una arista con un vertice en V_T y otro en V/V_t cuyo peso sea minimo.
        for(int u = 0; u < totalKeys; u++){
            if(visitadas[u] == 1) continue;
            minPeso = grafo[V_T.front()][u];
            minIt = u;
            break;
        }
        for(int v : V_T){
            for(int u = 0; u < totalKeys; u++){
                if(visitadas[u] == 1) continue;
                if(minPeso > grafo[v][u]){
                    minPeso = grafo[v][u];
                    minIt = u;
                }
            }
        }
        //Agrego el vertice a V_T y lo marco como visitado
        V_T.push_back(minIt);
        visitadas[minIt] = 1;
        res += minPeso; //Sumo el peso al res total
        i++;
    }

    return res;
}

int main() {
    int cases;
    int totalKeys;
    cin >> cases;
    for(int i = 0; i < cases; i++){
        cin >> totalKeys;

        //Inicializo memoria
        vector<vector<int>> grafo(totalKeys, (vector<int>(totalKeys)));
        vector<string> keys(totalKeys);

        //Leo las keys de entrada
        for(int j = 0; j < totalKeys; j++){
            cin >> keys[j];
        }

        //Calculo los pesos entre todos los vertices
        for(int j = 0; j < totalKeys; j++){
            for(int k = 0; k < totalKeys; k++){
                if (j == k) continue;
                grafo[j][k] = minimumRollsBetween(keys[j], keys[k]);
            }
        }

        //El problema se resuelve sumando todos los pesos de las aristas del AGM del grafo de keys.
        //Primero resuelvo el caso del 0000:
        pair<int, int> minNode = findClosestNodeToZero(totalKeys, keys);
        //Ahora si, corro prim desde minNode y teniendo en cuenta el peso de la arista inicial.
        int res = prim(grafo, totalKeys, minNode.first, minNode.second);
        cout << res << endl;
    }
    return 0;
}