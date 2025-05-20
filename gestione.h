//gestione.h
#ifndef GESTIONE_H
#define GESTIONE_H

#include "lista.h"
#include "attivita.h"

//Funzioni
//Aggiunge un'attivita' in coda alla lista
Lista aggiungiAttivita(Lista l, Attivita* att);

//Modifica l'attivita' alla posizione indicata con la nuovaAtt
Lista modificaAttivita(Lista l, int posizione, Attivita* nuovaAtt);

//Rimuove l'attivita' alla posizione indicata
Lista rimuoviAttivita(Lista l, int posizione);

//Aggiorna lo stato (progresso) dell'attivita' alla posizione indicata con nuovo Stato
Lista aggiornaProgresso(Lista l, int posizione, int nuovoStato);

//Carica la lista delle attivita' dal file e restituisce la lista creata
Lista caricaAttivitaDaFile(const char *nomeFile);

//Salva la lista delle attivita su file di testo
void salvaAttivitaSuFile(Lista l, const char *nomeFile);

//Libera la memoria allocata dalla lista delle attivita'
void liberaListaAttivita(Lista l);

#endif
