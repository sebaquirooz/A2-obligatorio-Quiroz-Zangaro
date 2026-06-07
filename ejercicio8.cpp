#include <cassert>
#include <string>
#include <iostream>
#include <limits>

using namespace std;

bool esPosible(int* letras, int posiciones) {
    int max = 0;
    for (int i = 0; i < 26; i++){ // O(26) = O(1)
        if (letras[i] > max){
            max = letras[i];
        }
    }
    return max <= (posiciones + 1) / 2;
}

void cartelNeon(int* letras, int cant) {
    string ret = "";
    int anterior = -1;

    for (int i = 0; i < cant; i++){
        bool encontre = false;
        for (int j = 25; j >= 0 && !encontre; j--){
            if (letras[j] == 0) continue;
            else if  (j == anterior) continue;
            else {
                letras[j]--;
                int posiciones = cant - i - 1; 
                if(esPosible(letras, posiciones)){
                    ret += char('a' + j);
                    anterior = j;
                    encontre = true;
                }
                else letras[j]++;
                
            }
        }
        if (!encontre) {
            cout << "Imposible" << endl;
            return;
        }
    }

    cout << ret << endl;
    
}


int main()
{
    string palabra;
    int* letras = new int[26]();
    cin >> palabra;
    int cant = 0;
    int max = 0;
    while (palabra[cant] != '\0')
    {  
        int pos = palabra[cant] - 'a';
        letras[pos]++;
        cant++;
        if (letras[pos] > max){
            max = letras[pos];
        }

    }
    if (!esPosible(letras, cant)) cout << "Imposible" << endl;
    else{
        cartelNeon(letras, cant);
    }
    return 0;
}