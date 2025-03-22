#include <iostream>
#include <vector>

using namespace std;

struct Edificio {
    int altura;
    int ancho;
};

int cantEdificios;

//Algoritmo bottom up
pair<int,int> edificio_mas_ancho(vector<Edificio> &edificios){
    //Inicializo una estructura de memoria para cada caso, el creciente y el decreciente.
    vector<int> memoriaInc(cantEdificios, -1);
    vector<int> memoriaDec(cantEdificios, -1);

    //El valor inicial de ambas corresponde al ancho del primer edificio.
    memoriaInc[0] = edificios[0].ancho;
    memoriaDec[0] = edificios[0].ancho;

    //Variables para ir guardando el mayor en cada caso
    int elMayorInc = memoriaInc[0];
    int elMayorDec = memoriaDec[0];

    //Recorro el resto de edificios buscando el mayor para cada caso.
    for(int i = 1; i < cantEdificios; i++){
        int maxAnteriorInc = 0;
        int maxAnteriorDec = 0;
        //Para el edificio actual, veo todos los anteriores para ver si cumplen y calculo el ancho acumulado
        //más grande hasta i.
        for(int j = i - 1; j >= 0; j--){
            //Caso creciente.
            //Si la altura actual es mayor a la altura de j, es creciente.
            //Si el máximo ancho en la memoria para j es mayor al número de anchos más grande encontrado hasta ahora,
            //entonces lo guardo.
            if (edificios[j].altura < edificios[i].altura && memoriaInc[j] > maxAnteriorInc){
                maxAnteriorInc = memoriaInc[j];
            }
            //Caso decreciente. Análogo al anterior.
            if (edificios[j].altura > edificios[i].altura && memoriaDec[j] > maxAnteriorDec){
                maxAnteriorDec = memoriaDec[j];
            }
        }
        //Habiendo encontrado el ancho acumulativo más grande para i, lo guardo en la memoria para cada caso
        //sumando el ancho actual.
        memoriaInc[i] = maxAnteriorInc + edificios[i].ancho;
        memoriaDec[i] = maxAnteriorDec + edificios[i].ancho;
        //Si el ancho para i es el más grande de todos, actualizo la variable correspondiente.
        if(memoriaInc[i] > elMayorInc) elMayorInc = memoriaInc[i];
        if(memoriaDec[i] > elMayorDec) elMayorDec = memoriaDec[i];
    }

    //Retorno el mayor de cada caso
    return {elMayorInc, elMayorDec};
}

int main(){
    int casos;
    cin >> casos;
    for(int n = 1; n <= casos; n++){
        //Recibo los valores de entrada e inicializo estructuras
        cin >> cantEdificios;
        vector<Edificio> edificios(cantEdificios);

        for(int i = 0; i < cantEdificios; i++){
            cin >> edificios[i].altura;
        }

        for(int i = 0; i < cantEdificios; i++){
            cin >> edificios[i].ancho;
        }

        //Ejecuto la función
        pair<int, int> res = edificio_mas_ancho(edificios);

        //Retorno el resultado según el orden requerido
        if (res.first >= res.second){
            printf("Case %d. Increasing (%d). Decreasing (%d).\n", n, res.first, res.second);
        } else {
            printf("Case %d. Decreasing (%d). Increasing (%d).\n", n, res.second, res.first);
        }
    }
}