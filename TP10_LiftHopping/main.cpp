//Alumno: Mateo Lazarte
//LU: 539/22
//Cuenta de vjudge: mateolazarte

#include <iostream>
#include <sstream>
#include <limits>
#include "vector"
#include "list"

using namespace std;

struct piso{
    int numeroDePiso;
    int elevador;
};

struct arco{
    int vecino;
    int peso;
};

const int infinity = numeric_limits<int>::max();

void guardarInfo(list<piso> &pisosLista, string &pisosStr, int elevadorActual, vector<vector<int>> &pisosVisitablesPorElevador){
    //Del string leído como input, debo leer cada dato que fue separado por un espacio.
    istringstream iss(pisosStr);
    string dato;
    char delimitador = ' ';
    while(getline(iss, dato, delimitador)){
        pisosLista.emplace_back(piso{
            stoi(dato),
            elevadorActual,
        });
        //Marco que el piso "dato" es visitable por el elevador actual e indico su número de vértice:
        pisosVisitablesPorElevador[stoi(dato)][elevadorActual - 1] = pisosLista.size() - 1;
    }
}

void listaAVector(list<piso> &lista, vector<piso> &vector){
    int i = 0;
    for(piso p : lista){
        vector[i] = p;
        i++;
    }
}

void colocarArcos(vector<list<arco>> &digrafo, vector<piso> &infoPisos, int infoSize, vector<int> tiempos, int n, vector<vector<int>> &pisosVisitablesPorElevador){
    int pisoActual;
    int pisoSiguiente;
    int elevadorActual;
    int elevadorSiguiente;

    for(int i = 1; i < infoSize - 1; i++){
        pisoActual = infoPisos[i].numeroDePiso;
        pisoSiguiente = infoPisos[i+1].numeroDePiso;
        elevadorActual = infoPisos[i].elevador;
        elevadorSiguiente = infoPisos[i+1].elevador;

        //Caso piso 0 se conectan al nodo fantasma (V_0 -> V_i)
        if(pisoActual == 0){
            digrafo[0].emplace_back(arco{
                i, //vecino
                0, //tiempo (peso del arco) vale 0, pues estamos en el piso 0
            });
        }

        //Si hay un piso más para el elevador actual, lo conecto con un arco de ida y vuelta.
        if(elevadorActual == elevadorSiguiente){
            digrafo[i].emplace_back(arco{
                i+1,
                tiempos[elevadorActual - 1] * abs(pisoSiguiente - pisoActual),
            });
            digrafo[i+1].emplace_back(arco{
                    i,
                    tiempos[elevadorActual - 1] * abs(pisoSiguiente - pisoActual),
            });
        }

        //Debo conectar el elevador y piso actual con los demás elevadores que comparten piso:
        for(int j = 0; j < n; j++){
            if(j == elevadorActual - 1) continue; //No quiero conectar al elevador consigo mismo
            if(pisosVisitablesPorElevador[pisoActual][j] == 0) continue; //No quiero conectarlo a otro elevador que no llega al piso
            //Si llegué hasta acá, debo conectar el elevador con otro que llega al mismo piso
            digrafo[i].emplace_back(arco{
                    pisosVisitablesPorElevador[pisoActual][j], //Número del vértice del otro elevador
                    60, //Cambiar de elevador cuesta 60 segundos.
            });
        }
    }
    //El último nodo debo verlo aparte para el caso de "conectar el elevador y su piso con los demas elevadores que comparten piso".
    for(int j = 0; j < n; j++){
        if(j == elevadorSiguiente - 1) continue; //No quiero conectar al elevador consigo mismo
        if(pisosVisitablesPorElevador[pisoSiguiente][j] == 0) continue; //No quiero conectarlo a otro elevador que no llega al piso
        //Si llegué hasta acá, debo conectar el elevador con otro que llega al mismo piso
        digrafo[infoSize - 1].emplace_back(arco{
                pisosVisitablesPorElevador[pisoSiguiente][j], //Número del vértice del otro elevador
                60, //Cambiar de elevador cuesta 60 segundos.
        });
    }
}

//Decide si el arco (v -> u) se encuentra en el digrafo. Asume v perteneciente a V(digrafo).
//De existir, guarda en peso el peso del arco.
bool esArco(vector<list<arco>> &digrafo, int v, int u, int &peso){
    for(arco e : digrafo[v]){
        if(e.vecino == u) {
            peso = e.peso;
            return true;
        }
    }
    return false;
}

void dijkstra(vector<list<arco>> &digrafo, int nodoInicial, vector<int> &caminosMinimos){
    caminosMinimos[nodoInicial] = 0;
    list<int> S = {nodoInicial}; //S es el arbol de caminos minimos de Dijkstra
    vector<int> visitados(digrafo.size());
    visitados[nodoInicial] = 1;
    int peso;
    for(int i = 0; i < digrafo.size(); i++){
        //Veo los arcos de mi nodo inicial:
        if(nodoInicial == i) continue;
        if(esArco(digrafo, nodoInicial, i, peso)){
            caminosMinimos[i] = peso;
        } else {
            caminosMinimos[i] = infinity;
        }
    }
    while (S.size() != digrafo.size()){
        //Busco un vertice w del digrafo no perteneciente a S tal que caminosMinimos[w] es minimo.
        int w = infinity;
        int pesoMin = infinity;
        for(int i = 0; i < digrafo.size(); i++){
            if(visitados[i] == 1) continue;
            if (caminosMinimos[i] <= pesoMin){
                pesoMin = caminosMinimos[i];
                w = i;
            }
        }
        //Lo agrego a S y lo marco como visitado
        S.emplace_back(w);
        visitados[w] = 1;
        //Actualizo caminosMinimos con todos los vertices vecinos de w que no estén en S.
        for(int i = 0; i < digrafo.size(); i++){
            if(visitados[i] == 1) continue;
            if(not esArco(digrafo, w, i, peso)) continue;
            if(caminosMinimos[w] == infinity) continue;
            if(caminosMinimos[i] > caminosMinimos[w] + peso){
                caminosMinimos[i] = caminosMinimos[w] + peso;
            }
        }
    }
}

int main() {
    int n; //cantidad de elevadores
    int k; //piso objetivo

    while(cin >> n >> k){
        vector<int> tiempos(n); //Tiempos de cada elevador para moverse a un piso adyacente
        //Leo los tiempos para cada elevador:
        for(int i = 0; i < n; i++){
            cin >> tiempos[i];
        }

        //Leo los pisos visitados por cada elevador y guardo la informacion de cada piso en infoPisos. Cada piso será un vértice.
        //Para optimizar la complejidad temporal, comenzaré guardando la info en una lista y despues lo pasaré a un vector.
        string pisosStr;
        list<piso> infoPisosLista = {{0, 0}}; //La inicializo con un nodo fantasma
        vector<vector<int>> pisosVisitablesPorElevador(100, vector<int>(n));
        cin.ignore(); //salto de linea para usar getline
        for(int i = 0; i < n; i++){
            getline(cin, pisosStr);
            guardarInfo(infoPisosLista, pisosStr, i+1, pisosVisitablesPorElevador);
        }

        //Paso lista a vector
        vector<piso> infoPisos(infoPisosLista.size());
        listaAVector(infoPisosLista, infoPisos);

        //Armo mi grafo
        vector<list<arco>> digrafo(infoPisos.size());
        colocarArcos(digrafo, infoPisos, infoPisos.size(), tiempos, n, pisosVisitablesPorElevador);

        //El problema se resuelve calculando los caminos minimos desde el nodo fantasma 0.
        //Como no hay pesos negativos, corro dijkstra.
        vector<int> caminosMinimos(infoPisos.size());
        dijkstra(digrafo, 0, caminosMinimos);

        //El piso k puede ser visitado por varios elevadores a la vez, por lo que busco el minimo camino entre los que van a cada uno de ellos con el piso k:
        int res = infinity;
        for(int j = 0; j < infoPisos.size(); j++){
            if(infoPisos[j].numeroDePiso != k) continue;
            res = min(res, caminosMinimos[j]);
        }

        //Imprimo en pantalla la respuesta
        if(res == infinity){
            cout << "IMPOSSIBLE" << endl;
        } else{
            cout << res << endl;
        }
    }
    return 0;
}