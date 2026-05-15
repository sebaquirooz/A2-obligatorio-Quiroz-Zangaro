# Arreglos realizados para el ejercicio 4

## Contexto

El ejercicio 4 ya tenia implementado Dijkstra con cola de prioridad, lista de adyacencia y tabla hash para mapear nombres de planetas a ids numericos. En teoria, esa solucion deberia quedar en:

```text
O((M + N) log N)
```

donde:

- `N` es la cantidad de vertices.
- `M` es la cantidad de aristas.

Sin embargo, en pruebas grandes el programa demoraba mucho mas de lo esperado:

- Caso de 50.000 vertices: 8 a 10 segundos.
- Caso de 100.000 vertices: cerca de 30 segundos.

Eso indicaba que alguna operacion aparentemente simple dentro de un bucle grande estaba costando mas de lo esperado.

## Problema principal: `linked_list::add` era O(n)

El cuello de botella mas importante estaba en la lista enlazada usada por el grafo.

Archivo:

```text
adts/lista/linked_list.cpp
```

Antes, `add` insertaba al final de la lista, pero para llegar al final recorria todos los nodos:

```cpp
node *aux = this->head;

while (aux->next)
{
   aux = aux->next;
}

aux->next = new node{data, nullptr};
```

Eso significa que agregar un elemento a una lista de largo `k` costaba `O(k)`.

En una lista normal esto puede parecer aceptable, pero en una lista de adyacencia es peligroso. Cada vez que el grafo agrega una arista, hace:

```cpp
this->arr[from]->add(e);
```

Si un vertice tiene muchos vecinos, agregar todas sus aristas puede costar:

```text
1 + 2 + 3 + ... + grado(v)
```

Eso es:

```text
O(grado(v)^2)
```

Por eso el programa podia dispararse en casos grandes o densos.

### Arreglo

Se agrego un puntero `tail` a la lista:

```cpp
node *head = nullptr;
node *tail = nullptr;
int length = 0;
```

Ahora `add` no recorre toda la lista. Inserta directamente al final:

```cpp
node *nuevo = new node{data, nullptr};

if (this->head == nullptr)
{
   this->head = nuevo;
   this->tail = nuevo;
}
else
{
   this->tail->next = nuevo;
   this->tail = nuevo;
}

this->length++;
```

Con esto, `add` pasa de:

```text
O(k)
```

a:

```text
O(1)
```

Este es el cambio mas importante para el tiempo del ejercicio 4.

## Ajuste del `tail` al borrar

Al agregar `tail`, tambien habia que mantenerlo correcto cuando se eliminan nodos.

Se actualizaron:

- `remove`
- `removeAt`

Casos contemplados:

- Si se borra el ultimo nodo, `tail` pasa al nodo anterior.
- Si se borra el unico nodo, `tail` queda en `nullptr`.
- Si se borra la cabeza y era tambien la cola, se actualiza correctamente.

Ejemplo:

```cpp
if (this->tail == aux) this->tail = prev;
if (this->length == 0) this->tail = nullptr;
```

Esto mantiene la lista consistente despues de borrar.

## Mismo criterio en la otra lista enlazada

Tambien se ajusto:

```text
adts/grafos/list_iterator/linked_list.cpp
```

Esa lista no parece ser la que usa directamente `adj_list_graph.cpp` actualmente, porque el grafo incluye:

```cpp
#include "../lista/linked_list.cpp"
```

Pero igualmente tenia el mismo problema de orden en `add`, asi que se aplico el mismo arreglo con `tail`.

Ademas, se quito el destructor explicito que tenia:

```cpp
virtual ~linked_list()
```

porque una de las reglas del obligatorio era no tener deleteadores/destructores en los TADs.

## Problema secundario: hash de strings con muchas colisiones

Archivo:

```text
funciones/hash/string_hash.cpp
```

Antes el hash de strings era:

```cpp
int sum = 0;
for (int i = 0; i < data.length(); i++) {
    sum += data[i];
}
return sum;
```

Ese hash es muy debil porque solo suma caracteres.

Por ejemplo, strings con las mismas letras en distinto orden producen el mismo hash. Tambien muchos nombres similares pueden caer en valores muy cercanos.

Como el ejercicio 4 usa una tabla hash para asignar ids a los planetas:

```cpp
hashCdblHash_table<string, int> ids(planetas, h);
```

muchas colisiones hacen que `contains`, `set` y `get` tarden mas.

### Arreglo

Se cambio por FNV-1a:

```cpp
unsigned int hash = 2166136261u;
for (int i = 0; i < data.length(); i++) {
    hash ^= (unsigned char)data[i];
    hash *= 16777619u;
}
return (int)(hash & 0x7fffffff);
```

Este hash distribuye mucho mejor las claves y reduce colisiones.

## Mejora en la tabla hash con doble hashing

Archivo:

```text
adts/tabla/hashCdblHash_table.cpp
```

La tabla usa doble hashing:

```cpp
int h1 = abs(hash) % this->bucketCount;
int h2 = 1 + (abs(hash) % (this->bucketCount - 1));
return (h1 + collisions * h2) % this->bucketCount;
```

Para que doble hashing funcione bien, conviene que el tamano de la tabla sea primo. Si no, la secuencia de posiciones puede no recorrer bien toda la tabla y puede generar mas colisiones de las necesarias.

### Arreglo

Se agregaron funciones para buscar el siguiente primo:

```cpp
bool isPrime(int n)
int nextPrime(int n)
```

Y se cambio el tamano inicial:

```cpp
this->bucketCount = nextPrime(expectedSize * 2 + 1);
```

Tambien se ajusto `rehash`:

```cpp
this->bucketCount = nextPrime(newSize);
```

Con esto la tabla queda mejor preparada para el doble hashing.

## Entrada mas rapida en `ejercicio4.cpp`

Archivo:

```text
ejercicio4.cpp
```

Se agrego al inicio de `main`:

```cpp
ios::sync_with_stdio(false);
cin.tie(nullptr);
```

Esto acelera `cin` y `cout`, especialmente en casos con muchas lineas de entrada.

No cambia el orden teorico del algoritmo, pero en pruebas grandes puede bajar varios segundos.

## Quitar destructores explicitos en TADs

Segun las reglas indicadas:

> Los TADs no pueden tener deleteadores, estilo `virtual ~linked_list()`.

Se quitaron destructores explicitos que aparecian en:

```text
adts/grafos/list_iterator/linked_list.cpp
adts/priority_queue/min_heap.cpp
adts/tabla/hashCdblHash_table.cpp
```

Esto se hizo para respetar la consigna.

Importante: esto implica que algunas estructuras ya no liberan memoria internamente al destruirse. Pero en este obligatorio, la prioridad era cumplir la regla indicada y corregir los problemas de orden.

## Evitar constructores vacios

Otra regla indicada fue:

> No puedes usar constructores vacios.

Se reemplazaron constructores como:

```cpp
linked_list() {}
pair() {}
```

por constructores que inicializan explicitamente sus campos.

Ejemplo:

```cpp
linked_list()
{
   this->head = nullptr;
   this->tail = nullptr;
   this->length = 0;
}
```

Y en los heaps:

```cpp
pair() {
   this->elem = E();
   this->prio = P();
}
```

## Resultado esperado

Despues de estos cambios, la construccion del grafo deja de tener el problema cuadratico causado por insertar al final de una lista enlazada sin `tail`.

El flujo principal queda mas cercano a lo esperado:

```text
Construccion del grafo: O(M)
Dijkstra con heap: O((M + N) log M)
Hash de nombres: promedio cercano a O(1) por operacion
```

En la practica, los casos de 50.000 y 100.000 vertices deberian bajar mucho, especialmente si el caso tiene vertices con grado alto.

## Comando de compilacion

La compilacion esperada sigue siendo:

```bash
g++ -std=c++11 -o ejercicio4 ejercicio4.cpp
```

No se cambio la forma de compilar ni se agregaron dependencias externas.

## Nota sobre verificacion

No pude compilar desde la terminal usada para hacer los cambios porque `g++` no estaba disponible en el `PATH`, y WSL estaba instalado pero sin distribuciones configuradas.

La revision estatica confirmo que ya no aparecen:

- destructores virtuales del estilo `virtual ~...`
- constructores completamente vacios del estilo `Clase() {}`

Tampoco se hizo ningun commit ni push a GitHub.
