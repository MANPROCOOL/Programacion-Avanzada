#include <stdio.h>

void limpiar_cadena(int cantidad, int matriz[cantidad]) {
    for (int i = 0; i < cantidad; i++) {
        matriz[i] = 0;
    }
}

int main () {
    
    int ancho, particiones, temp;
    scanf("%d %d", &ancho, &particiones);
    int resultado[ancho + 1], cadena[particiones + 2];
    limpiar_cadena(ancho + 1, resultado);
    limpiar_cadena(particiones + 2, cadena);
    cadena[0] = 0;
    cadena[particiones + 1] = ancho;
    for (int i = 0; i < particiones; i++) {
        scanf(" %d", &cadena[i + 1]);
    }
    for (int i = 0; i < particiones + 2; i++){
        for (int j = i; j >= 0; j--){
            temp = cadena[i] - cadena[j];
            resultado[temp] = 1;
        }
    }
    resultado[0] = 0;
    for (int i = 0; i <= ancho; i++){
        if (resultado[i] == 1){
            printf("%d ", i);
        }
    }
    return 0;
}