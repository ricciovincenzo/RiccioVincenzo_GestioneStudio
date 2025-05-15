//attivita.h
#ifndef ATTIVITA_H
#define ATTIVITA_H

#define DESCRIZIONE_LEN 100
#define CORSO_LEN 50

// Definizioni per le priorità
#define BASSA 0
#define MEDIA 1
#define ALTA 2

// Definizioni per stato
#define IN_CORSO 0
#define COMPLETATA 1
#define IN_RITARDO 2

typedef struct {
    int giorno;
    int mese;
    int anno;
} Data;

typedef struct {
    char descrizione[DESCRIZIONE_LEN];
    char corso[CORSO_LEN];
    Data scadenza; 
    int tempo_stimato;        // in ore
    int priorita;             // 0, 1, 2
    int stato;                // 0, 1, 2
} Attivita;

// Funzioni 
Attivita* creaAttivita(const char* descrizione,
                      const char* corso,
                      Data scadenza,
                      int tempo_stimato,
                      int priorita,
                      int stato);
void stampaAttivita(Attivita* att, Data oggi);
int dataValida(Data d);
void liberaAttivita(Attivita* att);

#endif

