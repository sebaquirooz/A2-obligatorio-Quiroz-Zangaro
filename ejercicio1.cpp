#include <cassert>
#include <string>
#include <iostream>
#include <limits>

using namespace std;

int main()
{
    return 0;
}

/*
hash cerrado, sabemos que vamos a tener bucketrs de A-Z, o sea, 27 buckets (creo)
Definimos cont de puertas que no podemos abrir.

Para crear el hash, hay que instanciar el las hash_func de chars.

char_hash* h = new char_hash();
hashC_table<char, int> tabla(expectedSize, h);


fHash = letra - a
ej. a - a = 0 | z - a = 27, etc.
En el hash -> clave = letra; valor = cantidad, todas setteadas en 0, y cada vez que encontramos uno, la sumamos.
Cuando tenemos que abrir la puerta, consultamos la posición.
pos = fHash(letra.toLowerCase() (creo que lowerCase sería - a, o algo así))
 si valor > 0, -- al valor y pasamos al siguiente
 else, cont++

 return contador

*/