#include <cassert>
#include <string>
#include <iostream>
#include <limits>
#include "adts/queue/cola.cpp"
#include "adts/grafos/adj_list_graph.cpp"
#include "adts/iterator/iterator.cpp"

using namespace std;

int main()
{
    int vertices;
    int aristas;
    cin >> vertices >> aristas;
    adj_list_graph g(vertices, false);
    cola <int> c;
    for (int i = 0; i < aristas; i++)
    {
        int from;
        int to;
        cin >> from >> to;
        g.addEdge(from, to);
        
    }
    int* color = new int[vertices + 1];
    for (int i = 1; i <= vertices; i++)
    {
        color[i] = -1;
    }
    for (int i = 1; i <= vertices; i++)
    {
        if (color[i] == -1) //acá se entra sii empezamos una componente conexa. o sea, recorrimos todo el grafo desde v[1] y nos quedaron cosas sin colorear 
        {
            color[i] = 0; //por eso pongo color 0, da igual, ninguno de la componente conexa tiene color
            c.push(i);
            while (!c.isEmpty())
            {
                int v = c.pop();
                Iterator<edge> *it = g.neighbors(v);
                while (it->hasNext())  
                {
                    edge e = it->next();
                    int w = e.to;
                    if (color[w] == -1)
                    {
                        color[w] = 1 - color[v];
                        c.push(w);
                    }
                    else if (color[w] == color[v])
                    {
                        cout << "NO" << endl;
                        delete[] color;
                        return 0;
                    }
                }
            }
        }
    }
    cout << "SI" << endl;
    delete[] color; 
    return 0;
}

/* 
Un grafo es bipartito sii se su número cromatico = 2
Agarro vertice v, lo pinto de color 0. hago bfs desde v y pinto a sus vecinos w de color 1 - color[v].
Ejemplo
vertices | vecinos | color
1 | 2, 3 | 0
2 | 1, 4 | 1-color[1] = 1
3 | 1 | 1 - color[1] = 1
4 | 2 | 1 - color[2] = 0

En este caso es biparito, pero si agregamos arista entre 2, 3 y/o 4, ya nos quedarian del mismo color.
*/