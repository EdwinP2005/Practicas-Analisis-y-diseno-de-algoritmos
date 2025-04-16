#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int **allocateMatrix(int n) {
    int **M = (int **)malloc(n * sizeof(int *));
    for (int i = 0; i < n; i++)
        M[i] = (int *)calloc(n, sizeof(int));
    return M;
}

void freeMatrix(int **M, int n) {
    for (int i = 0; i < n; i++)
        free(M[i]);
    free(M);
}

void fillMatrix(int **M, int n) {
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            M[i][j] = rand() % 10;
}

void printMatrix(int **M, int n) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++)
            printf("%d ", M[i][j]);
        printf("\n");
    }
}

// Tradicional
void traditionalMultiply(int **A, int **B, int **C, int n) {
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            for (int k = 0; k < n; k++)
                C[i][j] += A[i][k] * B[k][j];
}

// Operaciones auxiliares
void add(int **A, int **B, int **C, int n) {
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            C[i][j] = A[i][j] + B[i][j];
}

void subtract(int **A, int **B, int **C, int n) {
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            C[i][j] = A[i][j] - B[i][j];
}

// Divide and Conquer
void dacMultiply(int **A, int **B, int **C, int n) {
    if (n == 1) {
        C[0][0] = A[0][0] * B[0][0];
        return;
    }

    int newSize = n / 2;
    int **A11 = allocateMatrix(newSize), **A12 = allocateMatrix(newSize);
    int **A21 = allocateMatrix(newSize), **A22 = allocateMatrix(newSize);
    int **B11 = allocateMatrix(newSize), **B12 = allocateMatrix(newSize);
    int **B21 = allocateMatrix(newSize), **B22 = allocateMatrix(newSize);
    int **C11 = allocateMatrix(newSize), **C12 = allocateMatrix(newSize);
    int **C21 = allocateMatrix(newSize), **C22 = allocateMatrix(newSize);
    int **T1 = allocateMatrix(newSize), **T2 = allocateMatrix(newSize);

    for (int i = 0; i < newSize; i++)
        for (int j = 0; j < newSize; j++) {
            A11[i][j] = A[i][j];
            A12[i][j] = A[i][j + newSize];
            A21[i][j] = A[i + newSize][j];
            A22[i][j] = A[i + newSize][j + newSize];
            B11[i][j] = B[i][j];
            B12[i][j] = B[i][j + newSize];
            B21[i][j] = B[i + newSize][j];
            B22[i][j] = B[i + newSize][j + newSize];
        }

    dacMultiply(A11, B11, T1, newSize);
    dacMultiply(A12, B21, T2, newSize);
    add(T1, T2, C11, newSize);

    dacMultiply(A11, B12, T1, newSize);
    dacMultiply(A12, B22, T2, newSize);
    add(T1, T2, C12, newSize);

    dacMultiply(A21, B11, T1, newSize);
    dacMultiply(A22, B21, T2, newSize);
    add(T1, T2, C21, newSize);

    dacMultiply(A21, B12, T1, newSize);
    dacMultiply(A22, B22, T2, newSize);
    add(T1, T2, C22, newSize);

    for (int i = 0; i < newSize; i++)
        for (int j = 0; j < newSize; j++) {
            C[i][j] = C11[i][j];
            C[i][j + newSize] = C12[i][j];
            C[i + newSize][j] = C21[i][j];
            C[i + newSize][j + newSize] = C22[i][j];
        }

    freeMatrix(A11, newSize); freeMatrix(A12, newSize);
    freeMatrix(A21, newSize); freeMatrix(A22, newSize);
    freeMatrix(B11, newSize); freeMatrix(B12, newSize);
    freeMatrix(B21, newSize); freeMatrix(B22, newSize);
    freeMatrix(C11, newSize); freeMatrix(C12, newSize);
    freeMatrix(C21, newSize); freeMatrix(C22, newSize);
    freeMatrix(T1, newSize);  freeMatrix(T2, newSize);
}

// Strassen
void strassenMultiply(int **A, int **B, int **C, int n) {
    if (n == 1) {
        C[0][0] = A[0][0] * B[0][0];
        return;
    }

    int newSize = n / 2;
    int **A11 = allocateMatrix(newSize), **A12 = allocateMatrix(newSize);
    int **A21 = allocateMatrix(newSize), **A22 = allocateMatrix(newSize);
    int **B11 = allocateMatrix(newSize), **B12 = allocateMatrix(newSize);
    int **B21 = allocateMatrix(newSize), **B22 = allocateMatrix(newSize);
    int **M1 = allocateMatrix(newSize), **M2 = allocateMatrix(newSize);
    int **M3 = allocateMatrix(newSize), **M4 = allocateMatrix(newSize);
    int **M5 = allocateMatrix(newSize), **M6 = allocateMatrix(newSize);
    int **M7 = allocateMatrix(newSize);
    int **T1 = allocateMatrix(newSize), **T2 = allocateMatrix(newSize);

    for (int i = 0; i < newSize; i++)
        for (int j = 0; j < newSize; j++) {
            A11[i][j] = A[i][j];
            A12[i][j] = A[i][j + newSize];
            A21[i][j] = A[i + newSize][j];
            A22[i][j] = A[i + newSize][j + newSize];
            B11[i][j] = B[i][j];
            B12[i][j] = B[i][j + newSize];
            B21[i][j] = B[i + newSize][j];
            B22[i][j] = B[i + newSize][j + newSize];
        }

    add(A11, A22, T1, newSize);
    add(B11, B22, T2, newSize);
    strassenMultiply(T1, T2, M1, newSize);

    add(A21, A22, T1, newSize);
    strassenMultiply(T1, B11, M2, newSize);

    subtract(B12, B22, T1, newSize);
    strassenMultiply(A11, T1, M3, newSize);

    subtract(B21, B11, T1, newSize);
    strassenMultiply(A22, T1, M4, newSize);

    add(A11, A12, T1, newSize);
    strassenMultiply(T1, B22, M5, newSize);

    subtract(A21, A11, T1, newSize);
    add(B11, B12, T2, newSize);
    strassenMultiply(T1, T2, M6, newSize);

    subtract(A12, A22, T1, newSize);
    add(B21, B22, T2, newSize);
    strassenMultiply(T1, T2, M7, newSize);

    int **C11 = allocateMatrix(newSize), **C12 = allocateMatrix(newSize);
    int **C21 = allocateMatrix(newSize), **C22 = allocateMatrix(newSize);

    add(M1, M4, T1, newSize);
    subtract(T1, M5, T2, newSize);
    add(T2, M7, C11, newSize);

    add(M3, M5, C12, newSize);
    add(M2, M4, C21, newSize);

    add(M1, M3, T1, newSize);
    subtract(T1, M2, T2, newSize);
    add(T2, M6, C22, newSize);

    for (int i = 0; i < newSize; i++)
        for (int j = 0; j < newSize; j++) {
            C[i][j] = C11[i][j];
            C[i][j + newSize] = C12[i][j];
            C[i + newSize][j] = C21[i][j];
            C[i + newSize][j + newSize] = C22[i][j];
        }

    freeMatrix(A11, newSize); freeMatrix(A12, newSize);
    freeMatrix(A21, newSize); freeMatrix(A22, newSize);
    freeMatrix(B11, newSize); freeMatrix(B12, newSize);
    freeMatrix(B21, newSize); freeMatrix(B22, newSize);
    freeMatrix(M1, newSize); freeMatrix(M2, newSize);
    freeMatrix(M3, newSize); freeMatrix(M4, newSize);
    freeMatrix(M5, newSize); freeMatrix(M6, newSize);
    freeMatrix(M7, newSize); freeMatrix(T1, newSize);
    freeMatrix(T2, newSize);
    freeMatrix(C11, newSize); freeMatrix(C12, newSize);
    freeMatrix(C21, newSize); freeMatrix(C22, newSize);
}

// MAIN
int main() {
    int n = 128;  // Cambia a 64, 128, 256, 512, 1024 para probar

    srand(time(NULL));
    int **A = allocateMatrix(n);
    int **B = allocateMatrix(n);
    int **C = allocateMatrix(n);

    fillMatrix(A, n);
    fillMatrix(B, n);

    clock_t start, end;

    start = clock();
    traditionalMultiply(A, B, C, n);
    end = clock();
    printf("Tradicional:        %.4f segundos\n", (double)(end - start) / CLOCKS_PER_SEC);

    start = clock();
    dacMultiply(A, B, C, n);
    end = clock();
    printf("Divide and Conquer: %.4f segundos\n", (double)(end - start) / CLOCKS_PER_SEC);

    start = clock();
    strassenMultiply(A, B, C, n);
    end = clock();
    printf("Strassen:           %.4f segundos\n", (double)(end - start) / CLOCKS_PER_SEC);

    freeMatrix(A, n);
    freeMatrix(B, n);
    freeMatrix(C, n);

    return 0;
}
