# Ejercicio 3

## Idea

El ejercicio ordena pacientes por prioridad de atencion.

La prioridad se define con:

1. mayor urgencia primero
2. si empatan en urgencia, menor hora primero
3. si tambien empatan en hora, menor numero de ingreso primero

Para eso se usa un heap maximo donde la prioridad esta representada por el struct `PrioridadUrgencia`.

## TADs usados

Se usa:

```cpp
max_heap<Paciente, PrioridadUrgencia>
```

El operador `>` de `PrioridadUrgencia` define cual paciente tiene mayor prioridad.

El struct `Paciente` guarda:

```cpp
int nro;
int hora;
int urgencia;
int nroIngreso;
```

## Flujo

1. Leer la cantidad de pacientes.
2. Para cada paciente:
   - leer numero, hora y urgencia
   - crear el paciente
   - crear su prioridad
   - insertarlo en el heap
3. Mientras el heap no este vacio:
   - sacar el maximo
   - imprimir el numero del paciente

## Complejidad

Sea:

```text
N = cantidad de pacientes
```

Insertar cada paciente cuesta:

```text
O(log N)
```

Se hacen `N` inserciones:

```text
O(N log N)
```

Luego se hacen `N` extracciones, tambien de costo `O(log N)`:

```text
O(N log N)
```

Tiempo total:

```text
O(N log N)
```

Espacio:

```text
O(N)
```

por el heap.
