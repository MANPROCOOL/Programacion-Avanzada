# include <stdio.h>

void llenar_matriz(int f, int c, int matriz[f][c]) {
    for (int i = 0; i < f; i++) {
        for (int j = 0; j < c; j++) {
            scanf("%d", &matriz[i][j]);
        }
    }
}


int main () {
    int f_og, c_og, f_ker, c_ker;
    scanf ("%d %d %d %d", &f_og, &c_og, &f_ker, &c_ker);
    int matriz_og[f_og][c_og], matriz_ker[f_ker][c_ker];
    llenar_matriz(f_og, c_og, matriz_og);
    llenar_matriz(f_ker, c_ker, matriz_ker);
    for (int i = 0; i < f_og - f_ker + 1; i++) { //Recorro una matriz imaginaria de las dimensiones de la matriz final
        for (int j = 0; j < c_og - c_ker + 1; j++) {
            int suma = 0;
            for (int k = 0; k < f_ker; k++) { //Recorro el kernel
                for (int l = 0; l < c_ker; l++) { // El kernel se posa como una ventana en cada region de la matriz original
                    suma += matriz_og[i+k][j+l] * matriz_ker[f_ker-1-k][c_ker-1-l]; //Leo el kernel invertido
                }   //Aca arriba tomo el elemento de la matriz og en la fila i mas k (fila kernel)
            }       // lo mismo para la columna, y multiplico
            printf("%d ", suma);
        }
        printf("\n");
    }
}