#include <stdio.h>
#include <stdlib.h>

int comparar(const void *a, const void *b) {
    return (*(int *)a - *(int *)b);
}

long long dividirEquipos(int *skill, int n) {
    qsort(skill, n, sizeof(int), comparar);
    int sumaObjetivo = skill[0] + skill[n - 1];
    long long sumaQuimica = 0;

    for (int i = 0; i < n / 2; i++) {
        if (skill[i] + skill[n - i - 1] != sumaObjetivo) {
            return -1;
        }
        sumaQuimica += (long long)skill[i] * skill[n - i - 1];
    }

    return sumaQuimica;
}

int main() {
    int n;
    printf("Ingresa la cantidad de jugadores (debe ser par): ");
    scanf("%d", &n);

    if (n % 2 != 0 || n < 2 || n > 100000) {
        printf("-1\n");
        return 0;
    }

    int skill[n];
    printf("Ingresa las habilidades de los jugadores: ");
    for (int i = 0; i < n; i++) {
        scanf("%d", &skill[i]);
        if (skill[i] < 1 || skill[i] > 1000) {
            printf("-1\n");
            return 0;
        }
    }

    long long resultado = dividirEquipos(skill, n);
    printf("%lld\n", resultado);
    return 0;
}

