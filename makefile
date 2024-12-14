FLAGS: -Wall

all: lab3.o

lab3.o: lab3.c funciones.h
    gcc -c $(FLAGS) lab3.c $(FLAGS)

funciones.o: funciones.c funciones.h
    gcc -c $(FLAGS) funciones.c -o funciones.o