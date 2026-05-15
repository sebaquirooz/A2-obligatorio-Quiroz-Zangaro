# Ejercicio 4

## Idea

El ejercicio modela planetas y portales como un grafo ponderado no dirigido.

Cada planeta llega como string, por lo que primero se le asigna un id numerico usando una tabla hash. Luego se agrega cada portal como una arista ponderada en una lista de adyacencia.

Para responder la consulta entre origen y destino se usa Dijkstra con cola de prioridad minima.

## TADs usados

Se usan:

```cpp
adj_list_graph
hashCdblHash_table<string, int>
string_hash
min_heap<int, int>
```

El grafo se representa con listas de adyacencia. La tabla hash traduce nombres de planetas a ids. El heap minimo se usa como cola de prioridad para Dijkstra.

## Cambios importantes para rendimiento

La lista enlazada usada por la lista de adyacencia debe insertar al final en `O(1)`.

Para eso se agrego un puntero `tail` en:

```text
adts/lista/linked_list.cpp
```

Sin `tail`, cada `add` recorria toda la lista hasta el final. Eso podia volver muy lenta la construccion del grafo en vertices con muchos vecinos.

Tambien se ajusto `string_hash` para distribuir mejor los nombres:

```cpp
h = h * 31 + c;
```

Esto reduce colisiones frente a un hash que solo suma caracteres.

## Flujo

1. Leer cantidad de planetas y portales.
2. Crear el grafo con `planetas` vertices.
3. Crear la tabla hash de ids.
4. Por cada portal:
   - leer planeta A, planeta B y costo
   - asignar id a A si no existe
   - asignar id a B si no existe
   - obtener ids numericos
   - agregar arista ponderada al grafo
5. Leer origen y destino.
6. Convertir origen y destino a ids.
7. Ejecutar Dijkstra.
8. Imprimir el costo minimo.

## Dijkstra

Se mantienen:

```cpp
bool *visitados;
int *costo;
```

El heap guarda vertices priorizados por costo acumulado. Como no hay decrease-key, si aparece un camino mejor se vuelve a insertar el vertice con menor prioridad. El arreglo `visitados` evita procesar definitivamente un vertice mas de una vez.

## Complejidad

Sea:

```text
N = cantidad de planetas / vertices
M = cantidad de portales / aristas
```

Construccion del grafo:

```text
O(N + M)
```

con hash promedio `O(1)` y listas con `add` en `O(1)`.

Dijkstra:

```text
O((N + M) log M)
```

Tambien suele expresarse como:

```text
O((N + M) log N)
```

para grafos simples.

Espacio:

```text
O(N + M)
```

por el grafo, la tabla hash, los arrays auxiliares y el heap.
