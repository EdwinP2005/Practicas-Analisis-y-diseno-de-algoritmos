#include <stdio.h>

#define MAX_ITEMS 4
#define MAX_WEIGHT 4

// Estructura para representar cada objeto
typedef struct {
    char nombre[10];
    int peso;
    int valor;
} Objeto;

int max(int a, int b) {
    return (a > b) ? a : b;
}

int main() {
    Objeto objetos[MAX_ITEMS] = {
        {"Guitarra", 1, 1500},
        {"Estereo",  4, 3000},
        {"Laptop",   3, 2000},
        {"iPhone",   1, 2000}
    };

    int dp[MAX_ITEMS + 1][MAX_WEIGHT + 1];

    // Inicializar la tabla
    for (int i = 0; i <= MAX_ITEMS; i++) {
        for (int w = 0; w <= MAX_WEIGHT; w++) {
            if (i == 0 || w == 0) {
                dp[i][w] = 0;
            } else if (objetos[i - 1].peso <= w) {
                dp[i][w] = max(
                    objetos[i - 1].valor + dp[i - 1][w - objetos[i - 1].peso],
                    dp[i - 1][w]
                );
            } else {
                dp[i][w] = dp[i - 1][w];
            }
        }
    }

    // Mostrar la tabla
    printf("Tabla de valores máximos:\n");
    for (int i = 0; i <= MAX_ITEMS; i++) {
        for (int w = 0; w <= MAX_WEIGHT; w++) {
            printf("%5d ", dp[i][w]);
        }
        printf("\n");
    }

    // Resultado final
    printf("\nValor máximo que se puede llevar: $%d\n", dp[MAX_ITEMS][MAX_WEIGHT]);

    // Recuperar objetos seleccionados
    int w = MAX_WEIGHT;
    printf("Objetos seleccionados:\n");
    for (int i = MAX_ITEMS; i > 0 && w > 0; i--) {
        if (dp[i][w] != dp[i - 1][w]) {
            printf("- %s ($%d, %dlb)\n", objetos[i - 1].nombre, objetos[i - 1].valor, objetos[i - 1].peso);
            w -= objetos[i - 1].peso;
        }
    }

    return 0;
}
