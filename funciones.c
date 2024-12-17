#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include "funciones.h"

// Mutex para sincronización
// Solamente funcionaría en sistemas basados en UNIX
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

// Variables globales para compartir entre hebras
int *shared_array;
int size;


// Entradas: void *arg, un puntero a void
// Salidas: void *, un puntero a void
// Descripción:Función que las hebras ejecutarán
void *thread_function(void *arg) {
    int index = *(int *)arg;
    int myval = shared_array[index];

    // Lógica de hebras
    while (1) {

        // Se deja entrar a una hebra a la vez
        pthread_mutex_lock(&mutex);

        // Se obtiene el índice anterior, formula para arreglo circular
        int prev_index = (index - 1 + size) % size;

        // Sección crítica!!!
        // Se obtiene el máximo entre el valor actual y el anterior
        if (shared_array[prev_index] > myval) {
            // Memoria compartida
            myval = shared_array[prev_index];
            shared_array[index] = myval;
        }

        // Se cede el paso a la siguiente hebra
        pthread_mutex_unlock(&mutex);

        // Condición de término: si todos los elementos son iguales se termina
        int finished = 1;
        for (int i = 0; i < size; i++) {
            if (shared_array[i] != myval) {
                finished = 0;
                break;
            }
        }
        if (finished) break;
    }

    // Se termina la hebra
    pthread_exit(NULL);
}

// Entradas: int *array, un puntero a entero, int n, un entero
// Salidas: void
// Descripción: Manejar las hebras
void handle_threads(int *array, int n) {
    // Crear hebras
    pthread_t threads[n];
    int indices[n];
    shared_array = array;
    size = n;

    // Se crean n hebras para n elementos del arreglo
    for (int i = 0; i < n; i++) {
        indices[i] = i;
        pthread_create(&threads[i], NULL, thread_function, &indices[i]);
    }

    // Esperar a que todas las hebras terminen
    for (int i = 0; i < n; i++) {
        pthread_join(threads[i], NULL);
    }
}
// Entradas: const char *filename, nombre de archivo, int **array, donde se guardará el arreglo
// Salidas: int, tamaño del arreglo
// Descripción: Leer archivo de entrada
int read_input_file(const char *filename, int **array) {
    // Se abre el archivo
    FILE *file = fopen(filename, "r");

    // En caso de que falle
    if (!file) {
        return -1;
    }

    // Se lee el tamaño del arreglo
    int n, i = 0;
    fscanf(file, "%d", &n);
    *array = malloc(n * sizeof(int));

    // Se lee el arreglo en un solo paso
    // Aprovechando el retorno de fscanf
    while (fscanf(file, "%d", &(*array)[i++]) == 1);
    fclose(file);

    return n;
}

// Entrada: const char *filename, nombre de archivo, int *array, arreglo a escribir, int n, tamaño del arreglo
// Salida: int, 0 si se escribió correctamente, -1 si no
// Descripción: Escribir archivo de salida
int write_output_file(const char *filename, int *array, int n) {
    // Se abre el archivo
    FILE *file = fopen(filename, "w");
    if (!file) {
        return -1;
    }

    // Se escribe el tamaño del arreglo 
    for (int i = 0; i < n; i++) {
        fprintf(file, "%d\n", array[i]);
    }
    fclose(file);

    return 0;
}

// Entrada: int *array, arreglo a imprimir, int n, tamaño del arreglo
// Salida: void, hace un print en consola
// Descipción: Imprimir el arreglo
void print_array(int *array, int n) {
    for (int i = 0; i < n; i++) {
        printf("%d ", array[i]);
    }
    printf("\n");
}
