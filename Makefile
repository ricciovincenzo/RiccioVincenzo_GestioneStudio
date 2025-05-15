# Nome eseguibile
EXEC = gestione_studio

# File sorgenti
SRC = main.c attivita.c gestione.c lista.c report.c menu.c

# File header
HEADERS = attivita.h gestione.h lista.h report.h menu.h

# Compilatore e flags
CC = gcc
CFLAGS = -Wall -Wextra -std=c99

# Obiettivi
all: $(EXEC)

$(EXEC): $(SRC) $(HEADERS)
	$(CC) $(CFLAGS) -o $(EXEC) $(SRC)

clean:
	rm -f $(EXEC)

.PHONY: all clean

