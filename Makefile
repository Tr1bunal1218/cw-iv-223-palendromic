CC = gcc
CFLAGS = -Wall -Wextra

TARGET = palindrom

all: $(TARGET)

$(TARGET): palindrom.o
	$(CC) $(CFLAGS) -o $(TARGET) palindrom.o

palindrom.o: palindrom.c
	$(CC) $(CFLAGS) -c palindrom.c