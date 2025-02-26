#include<stdio.h>

int divide(int dividendo, int divisor) {

    int negativo = (dividendo < 0) ^ (divisor < 0);
    
    int a = (dividendo < 0) ? -dividendo : dividendo;
    int b = (divisor < 0) ? -divisor : divisor;

    int cociente = 0;

    while (a >= b) {
        a -= b;
        cociente++;
    }

    return negativo ? -cociente : cociente;
}

int main(){

    int a=0, b=0;
    int resultado=0;

    printf("Ingresa el dividendo: ");
    scanf("%d", &a);
    printf("Ingresa el divisor: ");
    scanf("%d", &b);

    resultado= divide (a,b);

    printf("Resultado: %d\n", resultado);
    return 0;
}