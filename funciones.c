#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include "funciones.h"

// Mutex para sincronización
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

// Variables globales para compartir entre hebras
int *shared_array;
int size;

// Función que las hebras ejecutarán
void *thread_function(void *arg) {
    int index = *(int *)arg;
    int myval = shared_array[index];

    while (1) {
        pthread_mutex_lock(&mutex);
        int prev_index = (index - 1 + size) % size;

        if (shared_array[prev_index] > myval) {
            myval = shared_array[prev_index];
            shared_array[index] = myval;
        }
        pthread_mutex_unlock(&mutex);

        // Condición de término: si todos los elementos son iguales
        int finished = 1;
        for (int i = 0; i < size; i++) {
            if (shared_array[i] != myval) {
                finished = 0;
                break;
            }
        }
        if (finished) break;
    }

    pthread_exit(NULL);
}

// Manejar las hebras
void handle_threads(int *array, int n) {
    pthread_t threads[n];
    int indices[n];
    shared_array = array;
    size = n;

    for (int i = 0; i < n; i++) {
        indices[i] = i;
        pthread_create(&threads[i], NULL, thread_function, &indices[i]);
    }

    for (int i = 0; i < n; i++) {
        pthread_join(threads[i], NULL);
    }
}

// Leer archivo de entrada
int read_input_file(const char *filename, int **array) {
    FILE *file = fopen(filename, "r");
    if (!file) return -1;

    int n, i = 0;
    fscanf(file, "%d", &n); // Leer el tamaño del arreglo
    *array = malloc(n * sizeof(int));

    while (fscanf(file, "%d", &(*array)[i++]) == 1);
    fclose(file);

    return n;
}

// Escribir archivo de salida
int write_output_file(const char *filename, int *array, int n) {
    FILE *file = fopen(filename, "w");
    if (!file) return -1;

    for (int i = 0; i < n; i++) {
        fprintf(file, "%d\n", array[i]);
    }
    fclose(file);

    return 0;
}

// Imprimir el arreglo
void print_array(int *array, int n) {
    for (int i = 0; i < n; i++) {
        printf("%d ", array[i]);
    }
    printf("\n");
}
