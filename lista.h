//lista.h
#ifndef LISTA_H
#define LISTA_H

#include "attivita.h"

//Definizione delcnodo della lista collegata
//Ogni nodo contiene un puntatore ad un'attivita e al nodo successivo
typedef struct nodo{
    Attivita* attivita;
    struct nodo* prossimoNodo;
} Nodo;

//La lista e' un puntatore al primo nodo (testa) della lista
typedef Nodo* Lista;

//Funzioni
//Crea una lista vuota, restituisce una lista vuota
Lista creaLista();

//Effettua inserimento in testa
Lista inserisciInTesta(Lista l, Attivita* att);

//Effettua inserimento in coda
Lista inserisciInCoda(Lista l, Attivita* att);

//Stampa la lista
void stampaLista(const Lista l, Data oggi);

//Restituisce la lunghezza della lista
int lunghezzaLista(Nodo* testa);

//Libera la memoria allocata per la lista
void liberaLista(Lista l);

#endif