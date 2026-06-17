#include <cassert>
#include <string>
#include <iostream>
#include <limits>

using namespace std;

struct Estado {
    int valor, peso, cant;
};

Estado mejor(Estado a, Estado b) {
    if (a.valor != b.valor) return a.valor > b.valor ? a : b;
    if (a.peso  != b.peso)  return a.peso  < b.peso  ? a : b;
    return a.cant < b.cant ? a : b;
}

Estado mochila(int maxP, int maxV, int maxC, int S, int M, int cantElem, int* pesos, int* volumen, int* costos, int* valores, int* esSup) {
    Estado****** tab = new Estado*****[cantElem + 1];
    for (int i=0; i<=cantElem; i++) {
        tab[i] = new Estado****[maxP+1];
    
        for (int p=0; p<=maxP; p++) {
            tab[i][p] = new Estado***[maxV + 1];

            for (int v=0; v<=maxV; v++) {
                tab[i][p][v] = new Estado**[maxC + 1];

                for (int c=0; c<=maxC; c++) {
                    tab[i][p][v][c] = new Estado*[S +1];

                    for (int s=0; s<=S; s++) {
                        tab[i][p][v][c][s] = new Estado [M + 1]();
                    }
                }
            }
        }
    }
    
    for (int i=1; i <= cantElem; i++) {
        for (int p=0; p <= maxP; p++) {
            for (int v=0;v<=maxV;v++ ) {
                for (int c=0; c<=maxC; c++) {
                    for (int s=0; s<=S; s++) {
                        for (int m=0; m<=M; m++) {

                            Estado no = tab[i-1][p][v][c][s][m];
                            Estado usar;
                            usar.valor = -1;
                            usar.peso  = 0;
                            usar.cant  = 0;; // valor -1 = inválido, nunca gana

                            int pesoI  = pesos[i-1];
                            int volI   = volumen[i-1];
                            int costoI = costos[i-1];
                            int valI   = valores[i-1];
                            int supI   = esSup[i-1];       // supervivencia que consume
                            int comI   = 1 - esSup[i-1];   // comida que consume

                            if (p >= pesoI && v >= volI && c >= costoI && s >= supI && m >= comI) {
                                Estado anterior = tab[i-1][p-pesoI][v-volI][c-costoI][s-supI][m-comI];
                                usar.valor = anterior.valor + valI;
                                usar.peso  = anterior.peso  + pesoI;
                                usar.cant  = anterior.cant  + 1;
                            }
                            tab[i][p][v][c][s][m] = mejor(no, usar);
                        
                        }
                    }
                
                }
            }
        }
    }
    Estado res = tab[cantElem][maxP][maxV][maxC][S][M];
    return res;
}
int main()
{
    int cant, maxP, maxV, maxC, S, M;
    cin >> cant;

    int pesos[cant];
    int volumenes[cant];
    int costos[cant];
    int valores[cant];
    int esSup[cant]; // 1 si supervivencia, 0 si comida

    cin >> maxP >> maxV >> maxC >> S >> M; // faltaba leer esto

    for (int i = 0; i < cant; i++) {
        string cat;
        cin >> pesos[i] >> volumenes[i] >> costos[i] >> valores[i] >> cat;
        esSup[i] = (cat == "supervivencia") ? 1 : 0;
    }

    Estado res = mochila(maxP, maxV, maxC, S, M, cant, pesos, volumenes, costos, valores, esSup);

    cout << res.valor << " " << res.peso << " " << res.cant << endl;

    return 0;
}