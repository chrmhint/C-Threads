CC = gcc

DEBUG = -g

TARGET = bank

CFLAGS = -c -Wall $(DEBUG)

all: $(TARGET)

$(TARGET): bank.o
	$(CC) bank.o -o $(TARGET) -lpthread

bank.o: bank.c
	$(CC) $(CFLAGS) bank.c

clean:
	rm *.o *~ $(TARGET)
