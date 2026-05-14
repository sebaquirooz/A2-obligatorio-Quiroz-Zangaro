#include <cassert>
#include <string>
#include <iostream>
#include <limits>
#include "adts/grafos/adj_list_graph.cpp"
#include "adts/tabla/hashA_table.cpp"
#include "funciones/hash/string_hash.cpp"
#include "adts/priority_queue/min_heap.cpp"
#include "adts/iterator/iterator.cpp"
using namespace std;

int main()
{
    int planetas;
    int portales;
    cin >> planetas;
    cin >> portales;
    //grafo
    adj_list_graph g(planetas, false);
    hash_func<string>* h = new string_hash();
    hashA_table<string, int> ids(planetas, h);
    int id = 1;
    for (int i=0; i < portales; i++) {
        //cin >> planeta >> portal
        string A;
        string B;
        int C;
        cin >> A >> B >> C;
        if (!ids.contains(A)) {
            ids.set(A, id);
            id++;
        }
        if (!ids.contains(B)) {
            ids.set(B, id);
            id++;
        }

        int desde = ids.get(A);
        int hasta = ids.get(B);

        g.addWeightedEdge(desde, hasta, C);


    }
    
    return cout << dijkstraCP(g, );
}

int dijkstraCP(adj_list_graph& g, int origen, int destino) {
    int n = g.vertices();
    bool* visitados = new bool[n+1]; 
    int* costo = new int[n+1] ;
    int* anterior = new int[n+1];
    for (int i = 1; i <= n; i++) {
        visitados[i] = false;
        costo[i] = INT_MAX;
        anterior[i] = -1;
    }

    costo[origen] = 0;
    min_heap<int , int> cp(n);
    cp.push(origen, 0);
    while (!cp.isEmpty()) {
        int v = cp.pop();
        if (!visitados[v]) {
            visitados[v] = true;

            if (v == destino) {
                return costo[v];
            }

            if (v == destino) return costo[v];
            ::iterator<edge>* it = g.neighbors(v);
            while (it->hasNext()) {
                edge e = it->next();
                int w = e.to;
                int nuevoCosto = costo[v] + e.weight;
                if (!visitados[w] && costo[w] > nuevoCosto) {
                    costo[w] = nuevoCosto;
                    anterior[w] = v;
                    cp.push(w, nuevoCosto);
                }
            }
        }
    }
    return -1;
}

/*
Usamos Dijkstra sin necesidad de la version para aristas negativas
Pide resolverlo en O((M + N) log N) -> Significa que utilizamos una CP para dijkstra y una lista de adyacencia para el grafo

void dijkstraCP(int origen) {
    bool [] visitados = initVisitados();
    int [] costo = initCostosOrigen();
    int [] anterior = initAnterior();

    ColaPrioridad cp = new ColaPrioridad();
    cp.encolar(origen, 0);

    while(!cp.esVacia()) {
        int v = cp.desencolar();
        visitados[v] = true;
        for(vertice w adyacente en los adyacentes a v) {
            int nuevoCosto = costo[v] + distancia(v,w);
            if(!visitados[w] && costo[w] > nuevoCosto) {
                costo[w] = nuevoCosto;
                anterior[w] = v;
                cp.encolar(w, nuevoCosto);
            }
        }
    }
}
*/
