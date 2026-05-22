# Ejercicio 5

## Idea

La solución verifica si un grafo no dirigido es bipartito. Un grafo es bipartito si puede colorearse con solo dos colores de forma que ninguna arista conecte dos vértices del mismo color.

La estrategia es recorrer el grafo por componentes conexas usando un BFS implícito con una cola. Cada vez que se inicia una componente nueva, se pinta el primer vértice con color `0` y sus vecinos con el color opuesto `1 - color[v]`.

Si durante el recorrido se encuentra una arista entre dos vértices que ya tienen el mismo color, el grafo no es bipartito y se imprime `NO`. Si se termina de revisar todos los vértices sin conflicto, se imprime `SI`.

## TADs usados

Se utilizan los siguientes tipos de datos y estructuras:

- `adj_list_graph`: grafo representado con listas de adyacencia.
- `cola<int>`: cola FIFO para el recorrido en anchura.
- `Iterator<edge>`: iterador para recorrer los vecinos de un vértice.

Además se usa un arreglo dinámico `int *color` para almacenar el color de cada vértice.

## Flujo

1. Leer la cantidad de `vertices` y `aristas`.
2. Crear el grafo `g` con `vertices` vértices y sin orientación.
3. Leer cada arista y agregarla al grafo con `g.addEdge(from, to)`.
4. Crear un arreglo `color` de tamaño `vertices + 1` y asignar `-1` a todos los vértices para indicar que están sin colorear.
5. Recorrer todos los vértices de `1` a `vertices`.
   - Si un vértice aún no tiene color (`color[i] == -1`), significa que empieza una nueva componente conexa.
   - Pintar ese vértice con `0`.
   - Encolar el vértice en `c` y recorrer la componente con un bucle BFS.
6. Mientras la cola no esté vacía:
   - Sacar un vértice `v` de la cola.
   - Obtener sus vecinos mediante `g.neighbors(v)`.
   - Para cada vecino `w`:
     - Si `w` no está coloreado, asignarle `1 - color[v]` y encolarlo.
     - Si `w` ya está coloreado y `color[w] == color[v]`, entonces hay un conflicto y el grafo no es bipartito.
7. Si se detecta un conflicto, imprimir `NO`, liberar memoria y terminar.
8. Si se procesan todas las componentes sin conflictos, imprimir `SI` y liberar memoria.

## Qué usamos y por qué

- `adj_list_graph` para representar el grafo de forma eficiente en memoria y poder iterar sobre los vecinos de cada vértice.
- `cola<int>` para implementar BFS, que es adecuado para propagar colores en capas y detectar rápidamente contradicciones de bipartición.
- `Iterator<edge>` para leer de forma ordenada cada arista incidente en el vértice.
- Un arreglo `color` con valores `-1`, `0` y `1` para marcar el estado de cada vértice:
  - `-1`: no visitado / sin color.
  - `0` ó `1`: color asignado.

## Orden de ejecución

1. Lectura de entrada y construcción del grafo.
2. Inicialización del arreglo de colores.
3. Iteración por cada vértice para cubrir todas las componentes conexas.
4. Recorrido BFS desde cada nuevo vértice no coloreado.
5. Verificación de la condición de bipartición en cada arista.
6. Salida final según el resultado.

## Complejidad

Sea `V` la cantidad de vértices y `E` la cantidad de aristas.

- Construcción del grafo: `O(E)`.
- Inicialización del arreglo de colores: `O(V)`.
- Recorrido BFS en todo el grafo: `O(V + E)`.

En total:

```text
O(V + E)
```

Espacio adicional:

```text
O(V)
```

por el arreglo de colores y la cola de recorrido.

## Observaciones

- El algoritmo maneja grafos no dirigidos, por lo que `g.addEdge(from, to)` debe registrar la arista en ambas direcciones.
- El BFS se aplica a cada componente conexa independientemente, de modo que el algoritmo es correcto aun cuando el grafo no sea conexo.
- La elección de los colores `0` y `1` es arbitraria; lo importante es alternar colores entre vecinos.
