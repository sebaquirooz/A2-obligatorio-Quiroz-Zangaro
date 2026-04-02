#include <cassert>
#include <string>
#include <iostream>
#include <limits>
#include "adts/tabla/hashCdblHash_table.cpp"
#include "adts/lista/linked_list.cpp"
#include "funciones/hash/string_hash.cpp"

using namespace std;

#include <cassert>
#include <string>
#include <iostream>
#include <limits>
#include "adts/tabla/hashCdblHash_table.cpp"
#include "funciones/hash/string_hash.cpp"

using namespace std;

struct Jugador {
    int puntajeFinal;
    int puntajeParcial;

    Jugador() {
        puntajeFinal = 0;
        puntajeParcial = 0;
    }
};



int main() {
    int rondas;
    cin >> rondas;

    string* jugadorRonda = new string[rondas];
    int* cambios = new int[rondas];

    // Para poder recorrer luego los jugadores únicos
    string* jugadores = new string[rondas];
    int cantJugadores = 0;

    string_hash* h = new string_hash();
    hashCdblHash_table<string, Jugador> tabla(rondas, h);

    // Primera pasada: guardar rondas y acumular puntajes finales
    for (int i = 0; i < rondas; i++) {
        string nombre;
        int pts;
        cin >> nombre >> pts;

        jugadorRonda[i] = nombre;
        cambios[i] = pts;

        if (!tabla.contains(nombre)) {
            Jugador j;
            j.puntajeFinal = pts;
            tabla.set(nombre, j);

            jugadores[cantJugadores] = nombre;
            cantJugadores++;
        } else {
            Jugador j = tabla.get(nombre);
            j.puntajeFinal += pts;
            tabla.set(nombre, j);
        }
    }

    // Hallar máximo final
    int maxFinal = numeric_limits<int>::min();

    for (int i = 0; i < cantJugadores; i++) {
        Jugador j = tabla.get(jugadores[i]);
        if (j.puntajeFinal > maxFinal) {
            maxFinal = j.puntajeFinal;
        }
    }

    // Segunda pasada: reconstruir puntajes parciales
    for (int i = 0; i < rondas; i++) {
        string nombre = jugadorRonda[i];
        int delta = cambios[i];

        Jugador j = tabla.get(nombre);
        j.puntajeParcial += delta;
        tabla.set(nombre, j);

        if (j.puntajeFinal == maxFinal && j.puntajeParcial >= maxFinal) {
            cout << nombre << endl;
            break;
        }
    }

    delete[] jugadorRonda;
    delete[] cambios;
    delete[] jugadores;
    delete h;

    return 0;
}

/* 
Idea:
Hash cerrado, cantidad de buckets -> Cantidad de entradas.siguientePrimo()
Definmos un ptsMaximo = minNumber y nombreMaximo = ""

Si tenemos 3 entradas, a lo maximo vamos a tener 3 personas. Si vamos al siguiente primo, vamos a tener en
el peor caso 7-3 = 4 buckets libres. Respetamos el factor de carga [0.5, 0.7], vamos a tener fC = 3/5 = 0,6.
Es verdad que capaz usamos memoria al pedo, pero no es taaaan grave.

Insertar en el hash.
i = 0
fHashDoble = string_hash(nombre[0]) + i * buckets 
pos = fHashDoble(nombre[0]) % buckets 

int valor = stringHash.hash(nombre.c_str());

int h1 = valor % buckets;
int h2 = 1 + (valor % (buckets - 1));

int pos = (h1 + i * h2) % buckets;

while i < M:
    pos = (h1(clave) + i * h2(clave)) mod M

    si tabla[pos] está vacía:
        insertar (nombre, puntaje)
        if puntaje > ptsMax
            ptsMax = puntaje
            nombreMaximo = clave;
        terminar
        terminar

    si tabla[pos].nombre == clave:
        actualizar puntaje
        if puntaje > ptsMax
            ptsMax = puntaje
            nombreMaximo = clave;
        terminar

    si no:
        i++

1       bob	        +90	        bob: 90
2	    ana	        +100	    ana: 100
3	    ana	        -10	        ana: 90
4	    ana	        -40	        ana: 50
5       pepe        +90        pepe: 90

1       bob	        +90	        bob: 90
2	    ana	        +100	    ana: 100
3	    ana	        -10	        ana: 90
4	    ana	        -40	        ana: 50
5       pepe        +90         pepe: 90
6       ana         +40         ana: 90
	

*/

