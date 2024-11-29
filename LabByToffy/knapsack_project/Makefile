CC = gcc
CFLAGS = -Iinclude -Wall
SRC = src/main.c src/algorithms/*.c src/utils/*.c
OBJ = $(SRC:.c=.o)
TARGET = knapsack

all: $(TARGET)

$(TARGET): $(OBJ)
    $(CC) $(CFLAGS) -o $@ $^

clean:
    rm -f $(OBJ) $(TARGET)