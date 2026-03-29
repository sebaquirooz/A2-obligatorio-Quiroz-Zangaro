#include <cassert>
#include <string>
#include <iostream>
#include <limits>
#include "adts/tabla/hashC_table.cpp"
#include "funciones/hash/char_hash.cpp"
using namespace std;

int main()
{
    int puertas;
    string entrada;
    int output = 0;

    cin >> puertas;
    cin >> entrada;

    char_hash* h = new char_hash();
    hashC_table<char, int> tabla(26, h);
    
    for (int i = 0; i < entrada.size(); i = i + 2){
        char llave = entrada[i];
        if (tabla.contains(llave)){
            tabla.set(llave, tabla.get(llave) + 1);
        }
        else {
            tabla.set(llave, 1);
        }

        char puerta = entrada[i+1] + 32; //lo llevo en ascii a minúscula
        if (tabla.contains(puerta) && tabla.get(puerta) > 0){ //puede contener a la puerta pero tenerla con 0 llaves porque ya la uso. no puedo usar get de una porque si no existe el assert me rompe todo.
            tabla.set(puerta, tabla.get(puerta) - 1);
        }
        else{
            output++;
        }
    }

    cout << output;
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