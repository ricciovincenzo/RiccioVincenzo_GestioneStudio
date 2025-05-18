//attivita.h
#ifndef ATTIVITA_H
#define ATTIVITA_H
//Lunghezze massime per i campi descrizione e corso
#define DESCRIZIONE_LEN 100
#define CORSO_LEN 50
//Valori possibili per il campo priorita'
#define BASSA 0
#define MEDIA 1
#define ALTA 2
//Valori possibili per il campo stato
#define IN_CORSO 0
#define COMPLETATA 1
#define IN_RITARDO 2
//Struct per rappresentare la data
typedef struct {
    int giorno;
    int mese;
    int anno;
} Data;
//Struct che rappresenta l'attivita' di studio
typedef struct {
    char descrizione[DESCRIZIONE_LEN];
    char corso[CORSO_LEN];
    Data scadenza; 
    int tempo_stimato;        // in ore
    int priorita;             // 0, 1, 2
    int stato;                // 0, 1, 2
} Attivita;

//Funzioni 
//Crea e restituisce un puntatore a una nuova attivita' con i dati forniti come argomenti
Attivita* creaAttivita(const char* descrizione, const char* corso, Data scadenza, int tempo_stimato, int priorita, int stato);

//Stampa i dettagli dell'attivita'
void stampaAttivita(Attivita* att, Data oggi);

//Verifica se la data e' valida (esempio: 41/05 non e' valida)
int dataValida(Data d);

//Libera la memoria allocata per l'attivita
void liberaAttivita(Attivita* att);

#endif

