# Makefile for Dining Philosophers

CC = gcc
CFLAGS = -pthread -Wall
TARGET = dining_philosophers

all: $(TARGET)

$(TARGET): dining_philosophers.c
	$(CC) $(CFLAGS) dining_philosophers.c -o $(TARGET)

run: $(TARGET)
	./$(TARGET)

clean:
	rm -f $(TARGET)
