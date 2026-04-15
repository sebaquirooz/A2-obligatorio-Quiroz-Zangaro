#include <cassert>
#include <string>
#include <iostream>
#include <limits>
#include "adts/priority_queue/max_heap.cpp"
#include "adts/priority_queue/priority_queue.cpp"
using namespace std;

struct Paciente {
    int nro;
    int hora;
    int urgencia;
    int nroIngreso;

    Paciante(int nroP, int horaP, int urgenciaP, int nroIngresoP) {
        nro = nroP;
        hora = horaP;
        urgencia = urgenciaP;
        nroIngreso = nroIngresoP;
    }
};



int main()
{
    int pacientes;
    cin >> pacientes;
    for (int i = 0; i < pacientes; i++){
        int nro;
        int hora;
        int urgencia;
        int nroIngreso = i+1;
        cin >> nro >> hora >> urgencia;
        int hora = stoi(horaStr);

        Paciente p = new Paciante(nro, hora, urgencia, nroIngreso);

        heap.push(p);
    
    }

    while(!heap.isEmpty()) {
        Paciante p = heap.top();
        
    }




    // TODO
    return 0;
}   

/*
1. Struct paciente: urgencia (heap), hora de ingreso, orden de ingreso al sistema.
2. Estructuras: max_heap, tamaño n. por urgencia. guardamos nodos
                lista por orden de ingreso, tamaño n. guardamos nodos
3. Ingresamos todos los datos en el heap y en la lista
4. Hacemos output
- Elemento top -> Recursion para ver urgencia de los hijos
- Si horario menor a top, recursión para ver urgencia de sus hijos, seguimos así.
- Cuando dejemos de
*/