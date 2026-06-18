#include <iostream>
#include <vector>
#include "utils/sort.hpp"

int main() {
    std::vector<int> K;
    int cantidad_N, cantidad_P, cantidad_K, temp;
    std::cin >> cantidad_P;
    while(cantidad_P--){
        int indice_encontrado = -1;
        std::cin >> cantidad_N >> cantidad_K;

        int N[cantidad_N] = {0};

        for (int i = 0; i < cantidad_N; i++) {
            std::cin >> N[i];
        }
        sort(N, cantidad_N);
        for (int i = 0; i < cantidad_K; i++) {
            std::cin >> temp;
            K.push_back(temp);
            // checkeo
            if (i >= cantidad_N && indice_encontrado == -1){
                sort(K);
            }
        }

        std::cout << indice_encontrado << std::endl;
    }
    return 0;
}
