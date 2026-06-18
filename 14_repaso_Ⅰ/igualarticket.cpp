#include <iostream>
#include <vector>

int main() {
    int cantidad_P;
    std::cin >> cantidad_P;

    while (cantidad_P--) {
        int cantidad_N, cantidad_K;
        std::cin >> cantidad_N >> cantidad_K;

        std::vector<int> N(cantidad_N);
        std::vector<int> K(cantidad_K);

        for (int i = 0; i < cantidad_N; i++) { // lee N
            std::cin >> N[i];
        }

        for (int i = 0; i < cantidad_K; i++) { // leo K
            std::cin >> K[i];
        }

        for (int i = 0; i < cantidad_N; i++) { //cuento
            int veces_encontrado = 0;
            
            // Recorremos K buscando coincidencias con el N[i] actual
            for (int j = 0; j < cantidad_K; j++) {
                if (K[j] == N[i]) {
                    veces_encontrado++;
                }
            }

            // Imprimir la cantidad de ocurrencias
            std::cout << veces_encontrado << " ";
            
        }
        // Salto de línea 
        std::cout << std::endl;
    }
    return 0;
}   