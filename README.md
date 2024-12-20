# Laboratorio 3 - Sistemas Operativos
## Explicación del código

> Se nos a pedido desarrollar un programa en C utilizando la librería `phtread.h`. que corresponde a la implementación de hebras en sistemas basados en UNIX. **El objetivo del laboratorio es ordenar un arreglo de $N$ elementos utilizando $N$ hebras**.

****

## Ejecución del laboratorio
Cómo fue estipulado en clases, para poder probar los comandos es necesario el uso de `makefile`, por lo que el comando para la generación de los archivos ejecutables es:
```
make all
```

Para limpiar los archivos residuales post ejecución de los archivos, se utiliza:
```
make clean
```

****

## Estructuración del código

### `funciones.c` y `funciones.h`
> En este apartado se desarrolla la mayor parte del laboratorio, donde se maneja:


- Lectura de archivos
- Escritura a archivos
- Funciones relacionadas a arreglos, imprimir
- Manejo de hebras tomando en consideración implementación de `pthread_mutex` 

> Ahondando en lo anterior, para evitar condición de carrera se utiliza mutex, por ejemplo: Si hay dos elementos en el arreglo, habrán dos hebras que comparten exactamente los mismos datos, *osease figura cómo sección crítica.*

****

### `lab3.c`

> La función que cumple este archivo es prácticamente recopilar todo lo desarrollado en `funciones.c`, haciendo una implementación de flags con `getopt` y manjando el input del usuario por consola. 
