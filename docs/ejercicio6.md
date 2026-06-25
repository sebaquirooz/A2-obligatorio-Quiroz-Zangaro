# Ejercicio 6

El ejercicio recibe `n` puntos en el plano y una distancia `d`, y debe determinar si existe al menos un par de puntos cuya distancia sea menor o igual a `d`.

La solucion evita calcular raices cuadradas comparando distancias al cuadrado contra `d * d`. Primero ordena los puntos por coordenada `x` y luego aplica una estrategia recursiva para buscar el par critico en cada mitad o cerca de la division central.

## Metodo usado

**Divide & Conquer:** se divide el arreglo de puntos en dos mitades de forma recursiva. Primero se busca si existe un par valido dentro de la mitad izquierda o dentro de la mitad derecha. Si no se encuentra, se revisan los puntos cercanos a la linea divisoria, ya que un posible par critico tambien puede estar formado por un punto de cada mitad.

Durante la recursion, los puntos se mantienen ordenados por coordenada `y` despues de resolver cada subproblema. Esto permite construir y revisar la franja central de forma eficiente.

## Flujo

1. Leer `n` y `d`.
2. Leer los `n` puntos.
3. Ordenar los puntos por coordenada `x` usando MergeSort.
4. Llamar a `resolver(puntos, aux, franja, 0, n-1, d*d)`.
5. En cada llamada recursiva:
   - Si hay 0 o 1 puntos, no puede existir un par.
   - Si hay hasta 3 puntos, comparar todos los pares directamente y ordenar ese tramo por `y`.
   - Si hay mas de 3 puntos, dividir el arreglo en dos mitades.
   - Resolver recursivamente la mitad izquierda y la mitad derecha.
   - Fusionar ambas mitades ordenadas por `y`.
   - Construir una franja con los puntos cuya distancia horizontal al punto medio es menor o igual a `d`.
   - Revisar los pares posibles dentro de la franja, cortando cuando la diferencia en `y` ya supera `d`.
6. Imprimir `true` si se encuentra un par valido, o `false` en caso contrario.

## Complejidad

Sea `n` la cantidad de puntos.

- Ordenamiento inicial por `x`: O(n log n).
- Division recursiva: en cada llamada se resuelven dos subproblemas de tamano n/2.
- Trabajo por nivel de recursion: O(n), porque se fusionan los puntos por `y`, se arma la franja central y se revisan sus candidatos.
- Revision de la franja: O(n) por nivel, ya que los puntos estan ordenados por `y` y solo se comparan candidatos cercanos antes de cortar por diferencia vertical.

Como el algoritmo divide el problema en mitades y en cada nivel procesa todos los puntos una vez, la parte recursiva cuesta O(n log n). Sumado al ordenamiento inicial, el tiempo total sigue siendo:

**O(n log n)**

Espacio: **O(n)** por los arreglos auxiliares `aux` y `franja`, mas el espacio de la recursion.
