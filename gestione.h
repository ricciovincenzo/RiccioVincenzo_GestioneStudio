//gestione.h
#ifndef GESTIONE_H
#define GESTIONE_H

#include "lista.h"
#include "attivita.h"

//Aggiunge un'attività alla lista (inTesta = 1 → in testa, 0 → in coda)
Lista aggiungiAttivita(Lista l, Attivita* att, int inTesta);

//Modifica l'attività alla posizione specificata
Lista modificaAttivita(Lista l, int posizione, Attivita* nuovaAtt);

//Rimuove l'attività alla posizione specificata
Lista rimuoviAttivita(Lista l, int posizione);

//Aggiorna lo stato (progresso) dell'attività alla posizione specificata
Lista aggiornaProgresso(Lista l, int posizione, int nuovoStato);

//Carica la lista delle attività dal file
Lista caricaAttivitaDaFile(const char *nomeFile);

//Salva la lista delle attivita sul file
void salvaAttivitaSuFile(Lista l, const char *nomeFile);

//Libera la memoria allocata
void liberaListaAttivita(Lista l);

#endif
