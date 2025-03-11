#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *map[] = {"abc", "def", "ghi", "jkl", "mno", "pqrs", "tuv", "wxyz"};

void gen(char *d, int i, char *p, char **r, int *c) {
    if (!d[i]) { r[(*c)++] = strdup(p); return; }
    for (int j = 0; map[d[i] - '2'][j]; j++) {
        p[i] = map[d[i] - '2'][j];
        gen(d, i + 1, p, r, c);
    }
}

char **combs(char *d, int *n) {
    if (!*d) return *n = 0, NULL;
    int max = 1; for (int i = 0; d[i]; i++) max *= strlen(map[d[i] - '2']);
    char **r = malloc(max * sizeof(char *)), p[strlen(d) + 1];
    p[strlen(d)] = '\0'; *n = 0; gen(d, 0, p, r, n); return r;
}

int main() {
    char d[10];
    printf("Ingrese los dígitos (2-9): ");
    scanf("%9s", d);
    
    int n, i;
    char **r = combs(d, &n);
    printf("[");
    for (i = 0; i < n; i++) printf("\"%s\"%s", r[i], i == n - 1 ? "" : ", "), free(r[i]);
    printf("]\n");
    free(r);
    return 0;
}