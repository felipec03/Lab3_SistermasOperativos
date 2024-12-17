#ifndef FUNCIONES_H
#define FUNCIONES_H

// Función para leer el archivo de entrada
int read_input_file(const char *filename, int **array);

// Función para escribir el archivo de salida
int write_output_file(const char *filename, int *array, int n);

// Función para imprimir el arreglo en consola
void print_array(int *array, int n);

// Manejo de hebras
void handle_threads(int *array, int n);

#endif 
