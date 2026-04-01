#include <stdio.h>
int main(){
    int cod1, cod2;
    scanf("%d%d", &cod1, &cod2);
    if (cod1%2==0 || cod2%2!=0){
        printf("Sí roba.\n");
    }
    else{
        printf("No roba.\n");
    }
    return 0;
}