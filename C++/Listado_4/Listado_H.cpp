#include <stdio.h>
#include <string.h>
#include <string>

using namespace std;

void limpiar(char matrix[][10]){ //Solo el primer [] va vacio
    for (int i = 0; i < 10; i++){
        for (int j = 0; j < 10; j++){
            matrix[i][j] = '0';
        }
    }
}

int main() {

    string palabras;
    char matriz[10][10], todas[10][10];
    for (int i = 0; i < 10; i++){
        scanf("%s", &matriz[i]);
    }
    scanf("%s", &palabras);

    return 0;

}