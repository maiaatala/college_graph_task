CC = gcc
CFLAGS = -Wall -Wextra -std=c99

SOURCE = main.c
OBJECT = main.o

INPUT_FILE = arq_grafo.txt
30_FILE = grafo_15_30.txt
100_FILE = grafo_15_100.txt
OUTPUT_FILE = output.txt

final: $(OBJECT)
	$(CC) $(CFLAGS) $(OBJECT) -o programa
	./programa $(INPUT_FILE) $(OUTPUT_FILE)

$(OBJECT): $(SOURCE)
	$(CC) $(CFLAGS) -c $(SOURCE) -o $(OBJECT)

30: $(OBJECT)
	$(CC) $(CFLAGS) $(OBJECT) -o programa
	./programa $(30_FILE) $(OUTPUT_FILE)

$(OBJECT): $(SOURCE)
	$(CC) $(CFLAGS) -c $(SOURCE) -o $(OBJECT)

100: $(OBJECT)
	$(CC) $(CFLAGS) $(OBJECT) -o programa
	./programa $(100_FILE) $(OUTPUT_FILE)
	
$(OBJECT): $(SOURCE)
	$(CC) $(CFLAGS) -c $(SOURCE) -o $(OBJECT)


clean:
	rm -f programa $(OBJECT) $(OUTPUT_FILE)
