CC = gcc
CFLAGS = -Wall -pthread
TARGET = producer_consumer

all: $(TARGET)

$(TARGET): producer_consumer.c
	$(CC) $(CFLAGS) producer_consumer.c -o $(TARGET)

clean:
	rm -f $(TARGET)
