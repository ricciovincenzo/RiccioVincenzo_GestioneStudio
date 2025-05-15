//lista.h
#ifndef LISTA_H
#define LISTA_H

#include "attivita.h"

//definizione della lista
typedef struct nodo{
    Attivita* attivita;
    struct nodo* prossimoNodo;
} Nodo;

typedef Nodo* Lista;

//Prototipi delle funzioni
//crea una lista vuota, restituisce una lista vuota
Lista creaLista();
//Effettua inserimento in testa
Lista inserisciInTesta(Lista l, Attivita* att);
//Effettua inserimento in coda
Lista inserisciInCoda(Lista l, Attivita* att);
//stampa la lista
void stampaLista(const Lista l, Data oggi);
//libera la memoria allocata per la lista
void liberaLista(Lista l);

#endif