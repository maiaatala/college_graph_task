CC = gcc
CFLAGS = -Wall -Wextra -std=c99

SOURCE = main.c
OBJECT = main.o

INPUT_FILE = ./entry_files/arq_grafo.txt
30_FILE = ./entry_files/grafo_15_30.txt
100_FILE = ./entry_files/grafo_15_100.txt
REGULAR_FILE = ./entry_files/grafo_regular.txt
NCICLICO_FILE = ./entry_files/grafo_nciclico.txt
GRAFO_CONEXO = ./entry_files/grafo_conexo.txt
GRAFO_CONEXO2 = ./entry_files/grafo_conexo_multiplo.txt
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

CONEXO: $(OBJECT)
	$(CC) $(CFLAGS) $(OBJECT) -o programa
	./programa $(GRAFO_CONEXO) $(OUTPUT_FILE)

CONEXO2: $(OBJECT)
	$(CC) $(CFLAGS) $(OBJECT) -o programa
	./programa $(GRAFO_CONEXO2) $(OUTPUT_FILE)
	
clean:
	rm -f programa $(OBJECT) $(OUTPUT_FILE)
