#include <iostream>
#include <math.h>

class ListaArreglo {
private:
    int* cadena;
    int N;

public:
    ListaArreglo(int n) {
        N = n;
        cadena = new int[N];
    }

    ~ListaArreglo() {
        delete[] cadena;
    }

    void setElemento(int index, int valor) {
        cadena[index] = valor;
    }

    // Tu función original exacta
    int* distancia67() {
        int* resultado = new int[N];
        int anterior = -1;

        // y si recorro una vez pa adelante y una vez pa atras?
        for (int i = 0; i < N; i++){ // para adelante
            if (cadena[i] == 7) {
                anterior = i;
                resultado[i] = -1;
            }
            else if (cadena[i] == 6 && anterior != -1) {
                resultado[i] = anterior;
            }
            else {resultado[i] = -1;}
        }
        anterior = 999999999;
        for (int i = N - 1; i > -1; i--) { // para atras
            if (cadena[i] == 7) {
                anterior = i;
            }
            else if (cadena[i] == 6) {
                if (std::abs(i - anterior) < std::abs(i - resultado[i]) || (resultado[i] == -1 && anterior != 999999999)){
                    resultado[i] = anterior;
                }
            }
        }
        return resultado;
    }
};

int main() {
    int N;
    if (!(std::cin >> N)) return 0;

    ListaArreglo lista(N);
    for (int i = 0; i < N; i++) {
        int val;
        std::cin >> val;
        lista.setElemento(i, val);
    }

    int* res = lista.distancia67();

    for (int i = 0; i < N; i++) {
        std::cout << res[i] << (i == N - 1 ? "" : " ");
    }
    std::cout << std::endl;

    delete[] res;
    return 0;
}