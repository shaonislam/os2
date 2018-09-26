CC = gcc
CFLAGS = -Wall 
TARGET = master
OBJ = master.o 
TARGET1 = worker
OBJ1 = worker.o
all: $(TARGET) $(TARGET1)

master: $(OBJ)
	$(CC) $(CFLAGS) -o master $(OBJ)
worker: $(OBJ1)
	$(CC) $(CFLAGS) -o worker $(OBJ1)
master.o : master.c
	$(CC) $(CFLAGS) -c master.c
worker.o : worker.c
	$(CC) $(CFLAGS) -c worker.c
clean:
	/bin/rm -f *.o $(TARGET) $(TARGET1)
