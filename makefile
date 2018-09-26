CC = gcc
CFLAGS = -Wall 
TARGET = master
OBJ = master.o 

stats: $(OBJ)
	$(CC) $(CFLAGS) -o master $(OBJ)
master.o : master.c
	$(CC) $(CFLAGS) -c master.c
clean:
	/bin/rm -f *.o $(TARGET)
