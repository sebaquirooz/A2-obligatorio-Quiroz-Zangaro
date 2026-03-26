#include <cassert>
#include <string>
#include <iostream>
#include <limits>

using namespace std;

int main()
{
    // TODO
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

*/