#include <cassert>
#include <string>
#include <iostream>
#include <limits>

using namespace std;

struct Punto {
    long x;
    long y;
};

bool menorPorX(Punto a, Punto b) {
    if (a.x != b.x) return a.x < b.x;
    return a.y < b.y;
}

bool menorPorY(Punto a, Punto b) {
    if (a.y != b.y) return a.y < b.y;
    return a.x < b.x;
}

long distanciaCuadrada(Punto a, Punto b) {
    long dx = a.x - b.x;
    long dy = a.y - b.y;

    return dx * dx + dy * dy;
}

void mergePorX(Punto* puntos, Punto* aux, int ini, int medio, int fin) {
    int i = ini;
    int j = medio + 1;
    int k = ini;

    while (i <= medio && j <= fin) {
        if (menorPorX(puntos[i], puntos[j])) {
            aux[k] = puntos[i];
            i++;
        } else {
            aux[k] = puntos[j];
            j++;
        }
        k++;
    }

    while (i <= medio) {
        aux[k] = puntos[i];
        i++;
        k++;
    }

    while (j <= fin) {
        aux[k] = puntos[j];
        j++;
        k++;
    }

    for (int t = ini; t <= fin; t++) {
        puntos[t] = aux[t];
    }
}

void mergeSortPorX(Punto* puntos, Punto* aux, int ini, int fin) {
    if (ini >= fin) return;

    int medio = (ini + fin) / 2;

    mergeSortPorX(puntos, aux, ini, medio);
    mergeSortPorX(puntos, aux, medio + 1, fin);

    mergePorX(puntos, aux, ini, medio, fin);
}

void mergePorY(Punto* puntos, Punto* aux, int ini, int medio, int fin) {
    int i = ini;
    int j = medio + 1;
    int k = ini;

    while (i <= medio && j <= fin) {
        if (menorPorY(puntos[i], puntos[j])) {
            aux[k] = puntos[i];
            i++;
        } else {
            aux[k] = puntos[j];
            j++;
        }
        k++;
    }

    while (i <= medio) {
        aux[k] = puntos[i];
        i++;
        k++;
    }

    while (j <= fin) {
        aux[k] = puntos[j];
        j++;
        k++;
    }

    for (int t = ini; t <= fin; t++) {
        puntos[t] = aux[t];
    }
}

void ordenarPorYBase(Punto* puntos, int ini, int fin) {
    for (int i = ini + 1; i <= fin; i++) {
        Punto actual = puntos[i];
        int j = i - 1;

        while (j >= ini && menorPorY(actual, puntos[j])) {
            puntos[j + 1] = puntos[j];
            j--;
        }

        puntos[j + 1] = actual;
    }
}

bool resolver(Punto* puntos, Punto* aux, Punto* franja, int ini, int fin, long d2) {
    int cantidad = fin - ini + 1;

    if (cantidad <= 1) {
        return false;
    }

    if (cantidad <= 3) {
        for (int i = ini; i <= fin; i++) {
            for (int j = i + 1; j <= fin; j++) {
                if (distanciaCuadrada(puntos[i], puntos[j]) <= d2) {
                    return true;
                }
            }
        }

        ordenarPorYBase(puntos, ini, fin);
        return false;
    }

    int medio = (ini + fin) / 2;
    long xMedio = puntos[medio].x;

    if (resolver(puntos, aux, franja, ini, medio, d2)) {
        return true;
    }

    if (resolver(puntos, aux, franja, medio + 1, fin, d2)) {
        return true;
    }

    mergePorY(puntos, aux, ini, medio, fin);

    int cantFranja = 0;

    for (int i = ini; i <= fin; i++) {
        long dx = puntos[i].x - xMedio;

        if (dx * dx <= d2) {
            franja[cantFranja] = puntos[i];
            cantFranja++;
        }
    }

    for (int i = 0; i < cantFranja; i++) {
        for (int j = i + 1; j < cantFranja; j++) {
            long dy = franja[j].y - franja[i].y;

            if (dy * dy > d2) {
                break;
            }

            if (distanciaCuadrada(franja[i], franja[j]) <= d2) {
                return true;
            }
        }
    }

    return false;
}

bool existeParCritico(Punto* puntos, int n, long d) {
    if (n < 2) return false;

    Punto* aux = new Punto[n];
    Punto* franja = new Punto[n];

    mergeSortPorX(puntos, aux, 0, n - 1);

    long d2 = d * d;

    bool resultado = resolver(puntos, aux, franja, 0, n - 1, d2);

    return resultado;
}

int main() {
    int n;
    long d;

    cin >> n >> d;

    Punto* puntos = new Punto[n];

    for (int i = 0; i < n; i++) {
        cin >> puntos[i].x >> puntos[i].y;
    }

    bool resultado = existeParCritico(puntos, n, d);

    if (resultado) {
        cout << "true" << endl;
    } else {
        cout << "false" << endl;
    }

    return 0;
}