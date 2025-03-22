//Alumno: Mateo Lazarte
//LU: 539/22
//Cuenta de vjudge: mateolazarte

#include <iostream>
#include "vector"

using namespace std;

void reordenarMatriz(vector<int> &orden, vector<vector<int>> &matriz){
    vector<vector<int>> matrizCopia = matriz;
    //Reordeno columnas:
    int j = 0;
    for(int i = orden.size() - 1; i >= 0; i--){
        int idx = orden[i];
        for(int k = 0; k < matriz.size(); k++){
            matriz[k][j] = matrizCopia[k][idx];
        }
        j++;
    }
    //Reordeno filas:
    matrizCopia = matriz;
    j = 0;
    for(int i = orden.size() - 1; i >= 0; i--){
        int idx = orden[i];
        for(int k = 0; k < matriz.size(); k++){
            matriz[j][k] = matrizCopia[idx][k];
        }
        j++;
    }
}

//Suma todos los elementos de una submatriz desde la posición 0 hasta la k.
long long sumarSubMatrizK(vector<vector<int>> &matriz, int k){
    long long sum = 0;
    for(int i = 0; i <= k; i++){
        for(int j = 0; j <= k; j++){
            sum += matriz[i][j];
        }
    }
    return sum;
}

//Basado en el algoritmo de Dantzig que se dio en la clase práctica:
long long sumaDeMatricesDeDantzig(vector<vector<int>> &matriz){
    long long res = 0;
    int minJ;
    for(int k = 0; k < matriz.size() - 1; k++) {
        //Sumo al resultado todos los elementos de la matriz k-ésima.
        res += sumarSubMatrizK(matriz, k);

        //Calculo los caminos minimos de la siguiente matriz:
        for(int i = 0; i <= k; i++){
            minJ = matriz[i][0] + matriz[0][k+1];
            for(int j = 1 ; j <= k; j++){
                minJ = min(minJ, matriz[i][j] + matriz[j][k+1]);
            }
            matriz[i][k+1] = minJ;

            minJ = matriz[k+1][0] + matriz[0][i];
            for(int j = 1 ; j <= k; j++){
                minJ = min(minJ, matriz[k+1][j] + matriz[j][i]);
            }
            matriz[k+1][i] = minJ;
        }
        for(int i = 0; i <= k; i++){
            for(int j = 0; j <= k; j++){
                matriz[i][j] = min(matriz[i][j], matriz[i][k+1] + matriz[k+1][j]);
            }
        }
    }
    //Finalmente, sumo al resultado todos los elementos de la matriz final de Dantzig.
    res += sumarSubMatrizK(matriz, matriz.size() - 1);
    return res;
}

int main() {
    int casos;
    cin >> casos;
    for(int i = 0; i < casos; i++){
        int cantTorres;
        cin >> cantTorres;

        //Leo los datos de entrada y armo mi matriz de adyacencias.
        vector<vector<int>> matriz(cantTorres, vector<int>(cantTorres));
        for(int j = 0; j < cantTorres; j++){
            for(int k = 0; k < cantTorres; k++){
                cin >> matriz[j][k];
            }
        }

        //Guardo el orden en que deben destruirse las torres
        vector<int> orden(cantTorres);
        for(int j = 0; j < cantTorres; j++){
            cin >> orden[j];
        }

        //La idea es reordenar la matriz para que en las primeras posiciones estén las últimas torres a ser destruidas.
        //Esto me va a permitir aprovechar el invariante de dantzig y sumar todos los elementos de cada una de sus matrices,
        //que representarán la destrucción de cada una de las torres.
        reordenarMatriz(orden, matriz);
        long long res = sumaDeMatricesDeDantzig(matriz);

        //El resultado es entonces la energía que se necesita para destruir todas las torres.
        cout << res << endl;
    }
    return 0;
}