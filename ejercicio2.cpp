#include <cassert>
#include <string>
#include <iostream>
#include <limits>
#include "adts/tabla/hashCdblHash_table.cpp"
#include "funciones/hash/string_hash.cpp"

using namespace std;

int main()
{
    int rondas;
    string nombreMaximo;
    string nombreMaximoHistorico;
    int ptsMaximo = 0;
    int ptsMaximoHistorico = 0;
    int output = 0;

    cin >> rondas;

    string_hash* h = new string_hash();
    hashCdblHash_table<string, int> table(rondas, h);

    for (int i = 0; i < rondas; i++){
        string nombre;
        string numero;
        cin >> nombre >> numero;
        int pts = std::stoi(numero);; //función de la libreria string, string to integer.

        table.set()

    }
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

