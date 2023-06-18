CC = gcc
CFLAGS = -Wall -Wextra -std=c99

SOURCE = main.c
OBJECT = main.o

INPUT_FILE = arq_grafo.txt
OUTPUT_FILE = output.txt

final: $(OBJECT)
	$(CC) $(CFLAGS) $(OBJECT) -o programa
	./programa $(INPUT_FILE) $(OUTPUT_FILE)

$(OBJECT): $(SOURCE)
	$(CC) $(CFLAGS) -c $(SOURCE) -o $(OBJECT)

clean:
	rm -f programa $(OBJECT) $(OUTPUT_FILE)
