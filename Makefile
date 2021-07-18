 #Copyright 2021 Shadai Rafael Lopez Garcia
CC=g++
CFLAGS=-Werror -I ./
TARGET = tictactoe
OBJ = main.o
LIBS = -lsfml-graphics -lsfml-window -lsfml-system

all:$(TARGET)

$(TARGET): $(OBJ)
	$(CC) -o $@ $^ $(LIBS)

%.o: %.cpp
	$(CC) -c -o $@ $< $(CFLAGS)

.PHONY: clean
clean:
	rm *.o
	rm $(TARGET)

