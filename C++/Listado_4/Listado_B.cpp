#include <stdio.h>
#include <stdlib.h>

void limpiar(int a, char arreglo[]){
    for (int i = 0; i < a; i++){
        arreglo[i] = 0;
    }
}

long long obtener_super_digit(long long numero) {
    if (numero < 10) {
        return numero;
    }
    
    long long suma = 0;
    while (numero > 0) {
        suma += numero % 10;
        numero /= 10;
    }
    
    return obtener_super_digit(suma);
}

int main() {
    int cuantos;
    char *original = (char *)malloc(100005 * sizeof(char)); 
    limpiar(100005, original);
    
    scanf("%s %d", original, &cuantos);
    
    long long suma_inicial = 0;
    for (int j = 0; original[j] != '\0'; j++){
        suma_inicial += original[j] - '0'; 
    }
    
    long long total_inicial = suma_inicial * cuantos;
    
    long long resultado_final = obtener_super_digit(total_inicial);
    printf("%lld\n", resultado_final);
    free(original);
    
    return 0;
}