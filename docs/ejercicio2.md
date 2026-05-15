# Ejercicio 2

## Idea

El ejercicio calcula el ganador de un juego por rondas. Cada ronda tiene un jugador y una variacion de puntaje.

La regla importante es que gana el jugador que:

1. termina con el puntaje final maximo
2. alcanza ese puntaje primero durante la reconstruccion ronda a ronda

Por eso la solucion hace dos pasadas conceptuales:

- primero calcula los puntajes finales
- despues reconstruye los puntajes parciales para encontrar quien alcanza primero el maximo final

## TADs usados

Se usa:

```cpp
hashCdblHash_table<string, Jugador>
```

con:

```cpp
string_hash
```

El struct `Jugador` guarda:

```cpp
int ptsFinal;
int ptsParcial;
```

Tambien se guardan arrays auxiliares para poder reconstruir las rondas en el mismo orden en que fueron leidas.

## Flujo

1. Leer la cantidad de rondas.
2. Para cada ronda:
   - leer nombre y puntaje
   - guardar nombre y cambio en arrays
   - acumular el puntaje final del jugador en la tabla
   - guardar el nombre si es un jugador nuevo
3. Recorrer los jugadores distintos para obtener el puntaje final maximo.
4. Recorrer nuevamente las rondas en orden:
   - actualizar puntaje parcial del jugador
   - si su puntaje final es el maximo y su parcial ya alcanzo ese maximo, imprimirlo y terminar

## Complejidad

Sea:

```text
R = cantidad de rondas
J = cantidad de jugadores distintos
```

con `J <= R`.

Las pasadas son:

```text
O(R) + O(J) + O(R)
```

Entonces, con hash promedio `O(1)`:

```text
O(R)
```

Espacio:

```text
O(R)
```

por los arrays de rondas, cambios, jugadores y la tabla hash.

En peor caso patologico de la tabla hash, las operaciones pueden degradar, pero el orden esperado de la solucion es lineal.
