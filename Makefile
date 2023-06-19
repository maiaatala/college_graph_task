CC = gcc
CFLAGS = -Wall -Wextra -std=c99

SOURCE = main.c
OBJECT = main.o

INPUT_FILE = arq_grafo.txt
30_FILE = grafo_15_30.txt
100_FILE = grafo_15_100.txt
REGULAR_FILE = grafo_regular.txt
NCICLICO_FILE = grafo_nciclico.txt
OUTPUT_FILE = output.txt

final: $(OBJECT)
	$(CC) $(CFLAGS) $(OBJECT) -o programa
	./programa $(INPUT_FILE) $(OUTPUT_FILE)

$(OBJECT): $(SOURCE)
	$(CC) $(CFLAGS) -c $(SOURCE) -o $(OBJECT)

30: $(OBJECT)
	$(CC) $(CFLAGS) $(OBJECT) -o programa
	./programa $(30_FILE) $(OUTPUT_FILE)

100: $(OBJECT)
	$(CC) $(CFLAGS) $(OBJECT) -o programa
	./programa $(100_FILE) $(OUTPUT_FILE)
	
REG: $(OBJECT)
	$(CC) $(CFLAGS) $(OBJECT) -o programa
	./programa $(REGULAR_FILE) $(OUTPUT_FILE)

NCI: $(OBJECT)
	$(CC) $(CFLAGS) $(OBJECT) -o programa
	./programa $(NCICLICO_FILE) $(OUTPUT_FILE)
	
clean:
	rm -f programa $(OBJECT) $(OUTPUT_FILE)
