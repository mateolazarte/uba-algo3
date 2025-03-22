/* TP3
 * LU: 539/22
 * Usuario en vjudge: mateolazarte
 */

#include <iostream>
#include "vector"

using namespace std;

int cantArboles;
int caida;

//Algoritmo bottom up
int maximizarBellotas(vector<vector<int>> &memoria, vector<vector<int>> &arboles, int altura){
    //Maximos es un vector que guardará el maximo para cada altura.
    vector<int> maximos(altura + 1, -1);

    //Inicializo los primeros valores en la memoria, comenzando por la altura maxima.
    for(int i = 0; i < cantArboles; i++){
        memoria[altura][i] = arboles[altura][i];
        if (memoria[altura][i] > maximos[altura]){
            maximos[altura] = memoria[altura][i];
        }
    }

    //Recorro el resto de alturas y completo la memoria, viendo dos casos por cada árbol.
    for(int i = altura - 1; i >= 0 ; i--){
        for(int j = 0; j < cantArboles; j++){
            //Caso venir del mismo árbol, utilizo la memoria del mismo árbol en la altura anterior y
            //sumo la cantidad de bellotas actual
            int max = memoria[i + 1][j] + arboles[i][j];

            //Caso venir de otro árbol
            //Utilizo el máximo de la altura actual más la caida. Sumo la cantidad de bellotas actual.
            if(i + caida <= altura){
                int suma = maximos[i + caida] + arboles[i][j];
                if (suma > max) max = suma;
            }

            //Guardo el máximo en la memoria para la altura y árbol actuales.
            //Si ademas es el máximo total en la altura actual, lo guardo en máximos.
            memoria[i][j] = max;
            if (max > maximos[i]) maximos[i] = max;
        }
    }

    //máximos en 0 tiene la suma maxima de bellotas que se pueden obtener.
    return maximos[0];
}

int main() {
    int casos;
    cin >> casos;

    for(int i = 1 ; i <= casos; i++){
        //Leo las entradas e inicializo estructuras
        int altura;
        cin >> cantArboles >> altura >> caida;

        vector<vector<int>> arboles(altura + 1, vector<int>(cantArboles, 0));
        vector<vector<int>> memoria(altura + 1, vector<int>(cantArboles, -1));

        int cantNueces;
        for(int k = 0; k < cantArboles; k++){
            cin >> cantNueces;
            for(int j = 0; j < cantNueces; j++){
                int alturaNuez;
                cin >> alturaNuez;
                arboles[alturaNuez][k] ++;
            }
        }

        //Ejecuto la función e imprimo el resultado.
        int res= maximizarBellotas(memoria, arboles, altura);
        cout << res << endl;
    }

    return 0;
}