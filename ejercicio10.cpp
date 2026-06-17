#include <cassert>
#include <string>
#include <iostream>
#include <limits>

using namespace std;

int operacion(int op, int a, int b) {
    switch (op) {
        case 0: return a + b;
        case 1: return a - b;
        case 2: return a * b;
        case 3: return a / b;
    }

    return 0;
}

bool validarResta(int a, int b)
{
    return a > b;
}

bool validarDivision(int a, int b)
{
    return (b > 0 && (a % b == 0));
}


int* nuevaBaraja(int* valores, int n, int i, int j, int nuevo)
{
    int* ret = new int[n - 1];
    int pos = 0;

    for (int k = 0; k < n; k++) {
        if (k != i && k != j) {
            ret[pos] = valores[k];
            pos++;
        }
    }

    ret[pos] = nuevo;

    return ret;
}

bool countdown(int* valores, int n, int obj) 
{
    if (n == 1) {
        return valores[0] == obj;
    }

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (i != j) {
                for (int op = 0; op < 4; op++) {
                    int a = valores[i];
                    int b = valores[j];

                    if ((op == 1 && !validarResta(a, b)) || 
                        (op == 3 && !validarDivision(a, b))) {
                        continue;
                    }

                    int nuevo = operacion(op, a, b);

                    int* nuevosValores = nuevaBaraja(valores, n, i, j, nuevo);

                    if (countdown(nuevosValores, n - 1, obj)) {
                        delete[] nuevosValores;
                        return true;
                    }

                    delete[] nuevosValores;
                }
            }
        }
    }

    return false;
}

int main()
{
    int n;
    cin >> n;

    int* valores = new int[n];

    for (int i = 0; i < n; i++) {
        cin >> valores[i];
    }

    int obj;
    cin >> obj;

    cout << countdown(valores, n, obj);

    delete[] valores;

    return 0;
}