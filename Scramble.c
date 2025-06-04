#include <stdio.h>
#include <string.h>
#include <stdbool.h>

bool tienenMismosCaracteres(char s1[], char s2[], int len) {
    int conteo[26] = {0};

    for (int i = 0; i < len; i++) {
        conteo[s1[i] - 'a']++;
        conteo[s2[i] - 'a']--;
    }

    for (int i = 0; i < 26; i++) {
        if (conteo[i] != 0)
            return false;
    }
    return true;
}

bool esScramble(char s1[], char s2[], int len) {
    if (strncmp(s1, s2, len) == 0)
        return true;

    if (!tienenMismosCaracteres(s1, s2, len))
        return false;

    for (int i = 1; i < len; i++) {
        
        if (esScramble(s1, s2, i) && esScramble(s1 + i, s2 + i, len - i))
            return true;

        if (esScramble(s1, s2 + len - i, i) && esScramble(s1 + i, s2, len - i))
            return true;
    }

    return false;
}

int main() {
    char s1[31], s2[31];

    printf("Ingresa la primera cadena: ");
    scanf("%s", s1);

    printf("Ingresa la segunda cadena: ");
    scanf("%s", s2);

    int len1 = strlen(s1);
    int len2 = strlen(s2);

    if (len1 != len2) {
        printf("Resultado: false\n");
        return 0;
    }

    if (esScramble(s1, s2, len1))
        printf("Resultado: true\n");
    else
        printf("Resultado: false\n");

    return 0;
}