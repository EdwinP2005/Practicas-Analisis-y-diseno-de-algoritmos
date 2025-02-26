#include<stdio.h>
#include<stdbool.h>

bool palindromo(int x){

    int orig= x;
    int invert=0;

    if(x<0) return false;

    while(x>0){
        invert= invert * 10 + (x%10);
        x/=10;
    }
    return orig == invert;
}

int main(){
    
    int num;

    printf("Ingrese el numero: ");
    scanf("%d", &num);

    if(palindromo(num)){
        printf("Verdadero");
    }else{
        printf("falso");
    }

    return 0;
}