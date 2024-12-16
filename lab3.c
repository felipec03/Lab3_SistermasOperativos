#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include "funciones.h"
#include <bits/getopt_core.h>

int main(int argc, char *argv[]) {
    char *input_file = NULL;
    char *output_file = NULL;
    int flag_display = 0;

    int opt;
    while ((opt = getopt(argc, argv, "i:o:D")) != -1) {
        switch (opt) {
            case 'i':
                input_file = optarg;
                break;
            case 'o':
                output_file = optarg;
                break;
            case 'D':
                flag_display = 1;
                break;
            default:
                fprintf(stderr, "Uso: %s -i <input_file> -o <output_file> [-D]\n", argv[0]);
                exit(EXIT_FAILURE);
        }
    }

    if (!input_file || !output_file) {
        fprintf(stderr, "Error: Los argumentos -i y -o son obligatorios.\n");
        exit(EXIT_FAILURE);
    }

    // Leer el archivo de entrada y crear el arreglo
    int *array = NULL;
    int size = read_input_file(input_file, &array);
    if (size == -1) {
        fprintf(stderr, "Error al leer el archivo de entrada.\n");
        exit(EXIT_FAILURE);
    }

    // Crear y manejar las hebras
    handle_threads(array, size);

    // Mostrar el arreglo final si se activó el flag -D
    if (flag_display) {
        print_array(array, size);
    }

    // Escribir el arreglo resultante en el archivo de salida
    if (write_output_file(output_file, array, size) == -1) {
        fprintf(stderr, "Error al escribir el archivo de salida.\n");
        exit(EXIT_FAILURE);
    }

    free(array);
    return 0;
}
