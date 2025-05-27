#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_CHARS 256

// Nodo para árbol de Huffman
typedef struct Nodo {
    char caracter;
    int frecuencia;
    struct Nodo *izq, *der;
} Nodo;

// Nodo de la cola de prioridad
typedef struct {
    Nodo* datos[MAX_CHARS];
    int tam;
} ColaPrioridad;

// Codigos de Huffman
char* codigos[MAX_CHARS];

// Funciones de cola de prioridad
void insertar(ColaPrioridad* cola, Nodo* nodo) {
    int i = cola->tam++;
    while (i > 0 && nodo->frecuencia < cola->datos[(i - 1) / 2]->frecuencia) {
        cola->datos[i] = cola->datos[(i - 1) / 2];
        i = (i - 1) / 2;
    }
    cola->datos[i] = nodo;
}

Nodo* extraer_min(ColaPrioridad* cola) {
    Nodo* min = cola->datos[0];
    Nodo* ultimo = cola->datos[--cola->tam];
    int i = 0, hijo;
    while (i * 2 + 1 < cola->tam) {
        hijo = i * 2 + 1;
        if (hijo + 1 < cola->tam && cola->datos[hijo + 1]->frecuencia < cola->datos[hijo]->frecuencia)
            hijo++;
        if (ultimo->frecuencia <= cola->datos[hijo]->frecuencia) break;
        cola->datos[i] = cola->datos[hijo];
        i = hijo;
    }
    cola->datos[i] = ultimo;
    return min;
}

// Crear nuevo nodo
Nodo* crear_nodo(char c, int f) {
    Nodo* nodo = (Nodo*)malloc(sizeof(Nodo));
    nodo->caracter = c;
    nodo->frecuencia = f;
    nodo->izq = nodo->der = NULL;
    return nodo;
}

// Generar códigos recursivamente
void generar_codigos(Nodo* raiz, char* buffer, int profundidad) {
    if (raiz->izq == NULL && raiz->der == NULL) {
        buffer[profundidad] = '\0';
        codigos[(unsigned char)raiz->caracter] = strdup(buffer);
        return;
    }
    if (raiz->izq) {
        buffer[profundidad] = '0';
        generar_codigos(raiz->izq, buffer, profundidad + 1);
    }
    if (raiz->der) {
        buffer[profundidad] = '1';
        generar_codigos(raiz->der, buffer, profundidad + 1);
    }
}

// Construir árbol de Huffman
Nodo* construir_arbol(int frecuencias[]) {
    ColaPrioridad cola = { .tam = 0 };
    for (int i = 0; i < MAX_CHARS; ++i)
        if (frecuencias[i])
            insertar(&cola, crear_nodo(i, frecuencias[i]));

    while (cola.tam > 1) {
        Nodo* izq = extraer_min(&cola);
        Nodo* der = extraer_min(&cola);
        Nodo* nuevo = crear_nodo('\0', izq->frecuencia + der->frecuencia);
        nuevo->izq = izq;
        nuevo->der = der;
        insertar(&cola, nuevo);
    }
    return extraer_min(&cola);
}

// Codificar archivo
int codificar_archivo(const char* texto, const char* salida) {
    FILE* fout = fopen(salida, "w");
    int bits_totales = 0;
    for (int i = 0; texto[i]; ++i) {
        char* codigo = codigos[(unsigned char)texto[i]];
        fputs(codigo, fout);
        bits_totales += strlen(codigo);
    }
    fclose(fout);
    return bits_totales;
}

// Decodificar archivo
void decodificar_archivo(Nodo* raiz, const char* archivo_codificado) {
    FILE* fin = fopen(archivo_codificado, "r");
    char bit;
    Nodo* actual = raiz;
    printf("\nTexto decodificado:\n");
    while ((bit = fgetc(fin)) != EOF) {
        actual = (bit == '0') ? actual->izq : actual->der;
        if (actual->izq == NULL && actual->der == NULL) {
            putchar(actual->caracter);
            actual = raiz;
        }
    }
    fclose(fin);
    printf("\n");
}

int main() {
    FILE* f = fopen("entrada.txt", "r");
    if (!f) {
        perror("No se pudo abrir entrada.txt");
        return 1;
    }

    // Leer texto y contar frecuencias
    int frecuencias[MAX_CHARS] = {0};
    char texto[10000];
    int len = fread(texto, 1, sizeof(texto) - 1, f);
    texto[len] = '\0';
    fclose(f);

    for (int i = 0; texto[i]; ++i)
        frecuencias[(unsigned char)texto[i]]++;

    // Construir árbol de Huffman
    Nodo* raiz = construir_arbol(frecuencias);

    // Generar códigos
    char buffer[100];
    generar_codigos(raiz, buffer, 0);

    // Codificar archivo
    int bits_codificado = codificar_archivo(texto, "codificado.txt");
    int bits_original = strlen(texto) * 8;

    printf("Tamano original: %d bits\n", bits_original);
    printf("Tamano codificado: %d bits\n", bits_codificado);
    printf("Tasa de compresion: %.2f%%\n", 100.0 * bits_codificado / bits_original);

    // Decodificar archivo
    decodificar_archivo(raiz, "codificado.txt");

    // Liberar memoria
    for (int i = 0; i < MAX_CHARS; ++i)
        free(codigos[i]);
    return 0;
}
