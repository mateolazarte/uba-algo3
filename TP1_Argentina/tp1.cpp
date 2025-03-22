#include <iostream>
#include "vector"

using namespace std;

struct Jugador {
    string nombre;
    int ataque;
    int defensa;
};

vector<Jugador> Jugadores(10);
vector<Jugador> mejorCombo(10);
int mejorAtk = 0;
int mejorDef = 0;

void maradona(vector<Jugador> &combo, vector<int> &candidatos, int sumAtk, int sumDef, int iteraciones){
    //Al llegar a las 10 iteraciones ya tengo mis 10 jugadores ordenados
    if(iteraciones == 10){
        //Me quedo con el combo de jugadores de mayor ataque
        if(sumAtk > mejorAtk){
            mejorAtk = sumAtk;
            mejorDef = sumDef;
            mejorCombo = combo;
            return;
        }
        //Si mi mejor combo tiene igual ataque que mi combo actual, me quedo con el de mayor defensa
        if(sumAtk == mejorAtk && sumDef > mejorDef){
            mejorDef = sumDef;
            mejorCombo = combo;
            return;
        }
        //Si hay empate en ataque y defensa, priorizo por orden lexicográfico a los atacantes "que vienen antes".
        if(sumAtk == mejorAtk && sumDef == mejorDef){
            //Comparo uno a uno cada atacante y me quedo con los de menor orden lexicográfico
            for(int i = 0; i < 5; i++){
                if(combo[i].nombre > mejorCombo[i].nombre) return;
            }
            mejorCombo = combo;
            return;
        }
        return;
    }

    //Organizo atacantes cuando iteraciones es menor a 5.
    for(int i = 0; i < 10 && iteraciones < 5; i++){
        //Pregunto si el candidato está disponible
        if(candidatos[i] == 1) continue;
        //Si no es el primer candidato, veo si se cumple el orden lexicográfico con el anterior
        if(iteraciones > 0 && combo[iteraciones-1].nombre > Jugadores[i].nombre) continue;
        //Marco al candidato como ocupado
        candidatos[i] = 1;
        //Asigno el candidato correspondiente en mi combo de jugadores
        combo[iteraciones] = Jugadores[i];
        //Llamo a la función recursivamente, sumando el nuevo valor de ataque
        maradona(
            combo,
            candidatos,
            sumAtk + combo[iteraciones].ataque,
            sumDef,
            iteraciones + 1
        );
        //Al volver de la recursión, desocupo al jugador.
        candidatos[i] = 0;
    }

    //Al salir del bucle de atacantes debo tener 5 iteraciones,
    //de lo contrario no tuve atacantes para completar y debo retornar.
    //Además, los atacantes deben sumar un ataque mayor a la maxima actual, si no retorno.
    if(iteraciones < 5 || sumAtk < mejorAtk) return;

    //Organizo defensores cuando iteraciones es mayor o igual a 5.
    for(int i = 0; i < 10; i++){
        //Mismo procedimiento que con atacantes pero sumando la defensa en cada llamado recursivo en vez del ataque.
        if(candidatos[i] == 1) continue;
        if(iteraciones > 5 && combo[iteraciones-1].nombre > Jugadores[i].nombre) continue;
        candidatos[i] = 1;
        combo[iteraciones] = Jugadores[i];
        maradona(
            combo,
            candidatos,
            sumAtk,
            sumDef + combo[iteraciones].defensa,
            iteraciones + 1
        );
        candidatos[i] = 0;
    }
}

int main() {
    int casos;
    cin >> casos;

    //Bucle para procesar todos los casos de entrada
    for(int i = 1; i <= casos; i++){
        for(int j = 0; j < 10; j++){
            cin >> Jugadores[j].nombre  >> Jugadores[j].ataque >> Jugadores[j].defensa;
        }

        //Reseteo valores
        vector<Jugador> combo(10);
        vector<int> candidatos(10);
        mejorAtk = 0;
        mejorDef = 0;

        //Llamo a la función principal
        maradona(combo, candidatos, 0, 0, 0);

        //Imprimo resultados
        printf("Case %d:\n", i);
        printf("(%s, %s, %s, %s, %s)\n",
               mejorCombo[0].nombre.c_str(),
               mejorCombo[1].nombre.c_str(),
               mejorCombo[2].nombre.c_str(),
               mejorCombo[3].nombre.c_str(),
               mejorCombo[4].nombre.c_str());
        printf("(%s, %s, %s, %s, %s)\n",
               mejorCombo[5].nombre.c_str(),
               mejorCombo[6].nombre.c_str(),
               mejorCombo[7].nombre.c_str(),
               mejorCombo[8].nombre.c_str(),
               mejorCombo[9].nombre.c_str());
    }

    return 0;
}