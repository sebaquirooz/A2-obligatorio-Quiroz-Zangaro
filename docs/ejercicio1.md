# Ejercicio 1

## Idea

El ejercicio procesa una secuencia de llaves y puertas. Cada par de caracteres representa:

- una llave encontrada
- una puerta que se intenta abrir

La solucion mantiene una tabla hash con la cantidad disponible de llaves de cada letra. Cuando aparece una llave se incrementa su contador. Cuando aparece una puerta, se transforma a minuscula y se consulta si hay una llave disponible.

Si hay llave disponible, se consume una. Si no hay, se incrementa el contador de puertas que no se pudieron abrir.

## TADs usados

Se usa:

```cpp
hashC_table<char, int>
```

con:

```cpp
char_hash
```

Como el universo de claves son letras, la tabla trabaja sobre un conjunto chico y fijo.

## Flujo

1. Leer la cantidad de puertas.
2. Leer el string de entrada.
3. Recorrer el string de a dos caracteres.
4. Guardar la llave encontrada en la tabla.
5. Convertir la puerta a minuscula.
6. Ver si existe una llave disponible para esa puerta.
7. Si no existe, sumar una puerta no abierta.
8. Imprimir el total.

## Complejidad

Si `P` es la cantidad de puertas, el string tiene `2P` caracteres y el ciclo principal itera `P` veces.

Las operaciones de tabla son `O(1)` promedio y, en este caso, practicamente constantes porque hay pocas letras posibles.

Tiempo:

```text
O(P)
```

Espacio:

```text
O(1)
```

La tabla no crece con la cantidad de puertas, solo con el alfabeto.
