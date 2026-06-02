#include <cassert>
#include <string>
#include <iostream>
#include <limits>

using namespace std;

void merge(int*& tiempos, int*& competidores, int izq, int mid, int der){ //mergesort
    int a = mid - izq + 1;
    int b = der - mid;

    int* auxt1 = new int[a];
    int* auxt2 = new int[b];

    int* auxc1 = new int[a];
    int* auxc2 = new int[b];

    for (int i = 0; i < a ; i++) {
        auxt1[i] = tiempos[izq + i];
        auxc1[i] = competidores[izq + i];
    }
    for (int i = 0; i < a ; i++) {
        auxt2[i] = tiempos[mid + 1 + i];
        auxc2[i] = competidores[mid + 1 + i];
    }

    int i = 0;
    int j = 0;
    int k = izq;

    while (i < a && j < b){
        if (auxt1[i] <= auxt2[j]){
            tiempos[k] = auxt1[i];
            competidores[k] = auxc1[i];
            i++;
        }
        else {
            tiempos[k] = auxt2[j];
            competidores[k] = auxc2[j];
            j++;
        }
        k++;
    }

    while (i < a) {
        tiempos[k] = auxt1[i];
        competidores[k] = auxc1[i];
        i++;
    }

    while (j < b) {
        tiempos[k] = auxt2[j];
        competidores[k] = auxc2[j];
        j++;
    }
}

void mergeSort(int*& tiempos, int*& competidores, int izq, int der){ // divide & conquer
    if (izq >= der) return;

    int mid = izq + (der - izq) / 2;
    mergeSort(tiempos, competidores, izq, mid);
    mergeSort(tiempos, competidores, mid + 1, der);
    merge(tiempos, competidores, izq, mid, der);
}

int main()
{
    int l;
    cin >> l;
    int* tiempos = new int[l];
    int* competidores = new int[l]; //array secundario para en función de que sorteo el tiempo, sorteo el número de competir. orden espacial O(2L) = O(L)

    for (int i = 0; i < l ; i++){
        int tiempoN;
        cin >> tiempoN;
        tiempos[i] = tiempoN;
        competidores[i] = i+1;
    }

    for (int i = 0; i < l ; i++){
        int tiempoCi;
        cin >> tiempoCi;
        tiempos[i]+= tiempoCi;
    }

    for (int i = 0; i < l ; i++){
        int tiempoCa;
        cin >> tiempoCa;
        tiempos[i]+= tiempoCa;
    }
    cout << "-----------" << endl;
    mergeSort(tiempos, competidores, 0, l-1);
    for (int i = 0; i < l ;i++){
        cout << competidores[i] << endl;
    }


    
}