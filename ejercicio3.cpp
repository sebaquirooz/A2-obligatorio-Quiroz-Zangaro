#include <cassert>
#include <string>
#include <iostream>
#include <limits>
#include "adts/priority_queue/urgency_heap.cpp"
#include "adts/priority_queue/priority_queue.cpp"
using namespace std;


struct PrioridadUrgencia {
    int urgencia;
    int hora;
    int nroIngreso;

    bool operator> (const PrioridadUrgencia& other) const {
        if (this->urgencia != other.urgencia) return this->urgencia > other.urgencia;
        if (this->hora != other.hora) return this->hora < other.hora;
        return this->nroIngreso < other.nroIngreso;
    }

    bool operator==(const PrioridadUrgencia& other) const {
        return this->urgencia == other.urgencia &&
               this->hora == other.hora &&
               this->nroIngreso == other.nroIngreso;
    }
};

struct Paciente {
    int nro;
    int hora;
    int urgencia;
    int nroIngreso;

    Paciente() {
        nro = 0;
        hora = 0;
        urgencia = 0;
        nroIngreso = 0;
    }

    Paciente(int nroP, int horaP, int urgenciaP, int nroIngresoP) {
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
    urgency_heap<Paciente, PrioridadUrgencia> heap(pacientes);
    for (int i = 0; i < pacientes; i++){
        int nro;
        string horaStr;
        int urgencia;
        int nroIngreso = i+1;
        cin >> nro >> horaStr >> urgencia;
        int hora = stoi(horaStr);

        Paciente p(nro, hora, urgencia, nroIngreso);

        PrioridadUrgencia prio;
        prio.urgencia = urgencia;
        prio.hora = hora;
        prio.nroIngreso = nroIngreso;
        heap.push(p, prio);
    
    }

    while(!heap.isEmpty()) {
        Paciente p = heap.pop();
        cout << p.nro << endl;
    }

    return 0;
}   

/*
1. Struct paciente: urgencia (heap), hora de ingreso, orden de ingreso al sistema.
2. Estructuras: max_heap, tamaño n. por urgencia. guardamos nodos
                lista por orden de ingreso, tamaño n. guardamos nodos
3. Ingresamos todos los datos en el heap y en la lista
4. Lista auxiliar -> Vamos a ir guardando los nodos por nivel de top
5. Hacemos output
- Elemento top -> Vamos a ir guardando lso elementos de misma urgencia, cuando encontremos uno diferente, ordenamos esos
- If lista vacia -> guardamos top
- If lista no vacia -> vemos si top tiene misma urgencia
    Misma urgencia -> Insertamos en la lista auxiliar, ordenando en base a la hora de ingreso. Si hora de ingreso es misma ==, por orden en sistema.
    Distinta urgencia -> Ordenamos nueva lista y la limpiamos para trabajar con la nueva urgencia
        Vamos tirandolos como output
- Si horario menor a top, recursión para ver urgencia de sus hijos, seguimos así.
- Cuando dejemos de
*/