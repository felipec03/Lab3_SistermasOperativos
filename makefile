CC = gcc
CFLAGS = -Wall -pthread
TARGET = lab3

all: $(TARGET)

$(TARGET): lab3.o funciones.o
	$(CC) $(CFLAGS) -o $(TARGET) lab3.o funciones.o

lab3.o: lab3.c funciones.h
	$(CC) $(CFLAGS) -c lab3.c

funciones.o: funciones.c funciones.h
	$(CC) $(CFLAGS) -c funciones.c

clean:
	rm -f *.o $(TARGET)
