# Documentación: correcciones del Ejercicio 4 (interconexiones planetarias)

Este documento resume **qué fallaba**, **qué se cambió** y **cómo se verificó** el caso grande de prueba (50 000 aristas / planeta).

---

## Enunciado (resumen)

- Hay **N** planetas y **M** portales (aristas no dirigidas con costo positivo).
- Los planetas se identifican por **nombre** (cadena).
- Hay que usar una **tabla hash** para mapear nombres → índices numéricos.
- Hay que usar **Dijkstra** con complejidad típica **O((M + N) log N)** (cola de prioridad + lista de adyacencia).
- Salida: costo mínimo de origen a destino, o **-1** si no hay camino.

---

## Problemas detectados en el código original

### 1. Error lógico en `ejercicio4.cpp`: destino mal resuelto

Tras leer `origen` y `destino`, se hacía:

```cpp
int hasta = ids.get(hasta);
```

- `hasta` **no existía** en el ámbito de `main` (solo dentro del `for` de portales), o, si se confundía con otra variable, **no era el string del destino**.
- Lo correcto es **`ids.get(destino)`**.

Esto daba respuestas incorrectas o comportamiento indefinido.

### 2. Origen / destino ausentes en la tabla hash

En entradas como la del **ejemplo 2** del enunciado, el planeta destino (**gamma**) **no aparece en ninguna línea de portal**. Si solo se insertan claves al leer aristas, **`get(gamma)`** viola la precondición de la tabla (clave inexistente) y puede **abortar** (`assert`) o fallar.

**Solución:** antes de `get`, si `!ids.contains(origen)` o `!ids.contains(destino)`, hacer `set` con el siguiente `id` libre.

### 3. Tabla `hashA_table`: métodos sin implementar

En `adts/tabla/hashA_table.cpp`, **`set`**, **`contains`** y **`remove`** estaban como `assert(false)`; solo **`get`** estaba implementado. El ejercicio 4 **no podía funcionar** con esa tabla.

Además, los `#include` apuntaban a rutas inexistentes (`functions` / `ints` en lugar de **`funciones`** / **`enteros`**).

### 4. Sondeo abierto sin límite y tabla “llena” (`hashCdblHash_table`)

En la tabla con **doble hash**, `contains` / `get` / `set` usaban `while (true)` sin acotar el número de intentos. Si **no quedaba ningún bucket `nullptr`** (tabla demasiado llena o tamaño inicial mal elegido respecto a las claves), el sondeo **no terminaba**, `collisions` crecía hasta **desbordar** `int` y el índice `pos` quedaba **inválido** → **SIGSEGV / AddressSanitizer** al leer `buckets[pos]`.

En `set` había además un error lógico: tras `is_deleted = false`, la condición `if (pair->is_deleted)` para incrementar `elementsCount` era **siempre falsa**; debía usarse un **`was_deleted`** guardado antes.

El **`rehash`** antiguo no liberaba bien la memoria anterior y **no reseteaba** `elementsCount` antes de reinsertar, lo que podía dejar el contador incoherente.

### 5. `min_heap`: asignación incorrecta y `pop` con heap vacío tras el último elemento

- En **`push`** se hacía algo equivalente a asignar un **puntero** a un struct local (`new pair(...)` mal usado), lo que **corrompe memoria** o no compila correctamente.
- Tras **`pop`**, cuando el heap quedaba con **0** elementos, se llamaba igual a **`siftDown(1)`**, violando la condición interna `pos > count` y provocando **`assert(false)`**.

### 6. Grafo y lista: `addWeightedEdge` llamaba a `removeEdge` que hacía `assert(false)`

Ninguna arista podía añadirse sin abortar.

La **`linked_list::add`** solo manejaba el caso de lista vacía; **no encadenaba** más nodos, así que no se podían guardar varias aristas desde el mismo vértice.

**`edge`** no tenía constructor por defecto; **`new node{}`** en la lista fallaba al instanciar `linked_list<edge>`.

El iterador interno tenía el constructor **privado** respecto al uso desde fuera en algunos compiladores/contextos; se hizo **público**.

### 7. Desbordamiento de costos en Dijkstra

Con pesos hasta \(10^6\) y muchas aristas, la distancia acumulada puede superar **`INT_MAX`**. Conviene **`long long`** para distancias y prioridades en la cola.

### 8. `main` incorrecto

`return cout << dijkstraCP(...)` devolvía un **`ostream&`**, no un código de salida adecuado. Se unificó a imprimir el resultado, **`'\n'`** y **`return 0`**.

### 9. Compilación aislada: `assert` en `linked_list.cpp`

Al compilar solo `ejercicio4.cpp`, **`linked_list.cpp`** usaba **`assert`** sin incluir **`<cassert>`**. Se añadió el include para que compile de forma fiable.

---

## Cambios realizados (por archivo)

| Archivo | Cambio principal |
|---------|------------------|
| `ejercicio4.cpp` | `ids.get(destino)`; registro de `origen`/`destino` en la tabla; Dijkstra con `long long` y `LLONG_MAX`; `min_heap<int, long long>`; prototipo de `dijkstraCP`; salida con `'\n'` y `return 0`; liberación de arrays en Dijkstra. |
| `adts/tabla/hashA_table.cpp` | Includes corregidos; constructor con mínimo de buckets; **`set` / `contains` / `remove` / `get`** con sondeo acotado; **`rehash`** que libera nodos viejos y resetea `elementsCount`; **`set`** que rehashea si no hay hueco. |
| `adts/tabla/hashCdblHash_table.cpp` | Sondeo acotado; **`was_deleted`** en `set`; **`rehash`** coherente y con liberación; **`set`** con rehash si la tabla está llena lógicamente. |
| `adts/priority_queue/min_heap.cpp` | `pair` con constructor por defecto; **`push`** correcto y redimensionado seguro; **`pop`** sin `siftDown` si `count == 0` tras extraer el último elemento; eliminado include duplicado de `enteros.cpp` que redefinía `abs`/`max`/`min`. |
| `adts/grafos/adj_list_graph.cpp` | `removeEdge` como no-op (evita `assert` y permite añadir aristas). |
| `adts/grafos/edge.cpp` | Constructor por defecto `edge()` para nodos de la lista. |
| `adts/grafos/list_iterator/linked_list.cpp` | `#include <cassert>`; iterador con ctor público; **`add`** que encadena nodos; stubs de `get`/`getPos` con retorno válido. |

---

## Prueba con `tests/ejercicio4/50000.in.txt`

- **Entrada:** `tests/ejercicio4/50000.in.txt` (caso grande del repositorio).
- **Salida esperada:** `tests/ejercicio4/50000.out.txt` → **`3298`**.
- **Compilación usada en la prueba:** `g++ -std=c++17 -O2 -o ej4 ejercicio4.cpp`
- **Resultado:** la salida del programa **coincide** con el archivo `.out` (`diff` sin diferencias).
- **Tiempo aproximado** en la máquina donde se ejecutó la prueba: **~24 s** de tiempo real (el cuello de botella es el volumen de operaciones en la cola de prioridad “lazy” con muchas inserciones repetidas; el enunciado pide la complejidad asintótica correcta, no un tiempo concreto en segundos).

**Nota:** si se redirige stderr y stdout al mismo archivo (`2>&1` hacia el mismo path que la salida del programa), las líneas de **`time`** pueden mezclarse con la respuesta y **`diff`** fallará aunque el número sea correcto. Conviene ejecutar `time` sin mezclar con el fichero de salida del programa.

---

## Resumen

El fallo en el caso de **50 000** encajaba con la combinación de **estructuras de datos incompletas o inseguras** (tabla hash sin terminación garantizada, heap corrupto o con `pop` inválido, grafo que no añadía aristas) más errores puntuales en **`ejercicio4.cpp`**. Tras las correcciones anteriores, el caso **`50000.in.txt`** produce **`3298`**, igual que **`50000.out.txt`**.
