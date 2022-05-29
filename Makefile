CC = gcc
CFLAGS = -Wall --std=c99
OBJECTS = my_string.o lab7.o generic_vector.o tree.o

lab7: my_string.o lab7.o generic_vector.o tree.o
	$(CC) $(CFLAGS) -o lab7 $(OBJECTS)
lab7.o: lab7.c
my_string.o: my_string.c my_string.h
tree.o: tree.c
generic_vector.o: generic_vector.c generic_vector.h
clean:
	rm lab7 $(OBJECTS)
