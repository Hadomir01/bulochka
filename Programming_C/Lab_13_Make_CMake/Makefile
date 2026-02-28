.PHONY: all clean 

CC = gcc
SRC_DIR = src/
TARGET = res
LIBRARY = static_lib.a

all: $(TARGET)

$(TARGET): main.o for_main.o
	$(CC) main.o for_main.o -o $(TARGET)

main.o: $(SRC_DIR)main.c
	$(CC) -c $(SRC_DIR)main.c -o main.o -I ./include

for_main.o: $(SRC_DIR)for_main.c 
	$(CC) -c $(SRC_DIR)for_main.c -o for_main.o -I ./include

library: for_main.o
	ar rcs $(LIBRARY) for_main.o

static: library main.o
	$(CC) main.o $(LIBRARY) -o $(TARGET)

clean:
	rm -f *.o *.a $(TARGET)
