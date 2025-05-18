//lista.c
#include <stdio.h>
#include <stdlib.h>
#include "lista.h"
#include "attivita.h"

//Funzione per creare una lista vuota
Lista creaLista() {
    return NULL; //La lista vuota e' rappresentata da NULL
}
//Funzione per inserire un'attivita' in testa alla lista
Lista inserisciInTesta(Lista l, Attivita* att){
    Nodo* nuovoNodo = (Nodo*)malloc(sizeof(Nodo));
    if (nuovoNodo == NULL) {
        printf("Errore di allocazione della memoria\n");
        return l; //Restituisce la lista originale in caso di errore
    }
    nuovoNodo->attivita = att; //Aggiunge la nuova attivita' al nodo
    nuovoNodo->prossimoNodo = l; //Collega il nuovo nodo alla lista esistente
    return nuovoNodo; //Restituisce il nuovo nodo come testa
        }

// Funzione per inserire un'attivita' in coda alla lista
Lista inserisciInCoda(Lista l, Attivita* att) {
        Nodo* nuovoNodo = (Nodo*)malloc(sizeof(Nodo));
        if (nuovoNodo == NULL) {
            printf("Errore di allocazione della memoria\n");
            return l; //Restituisce la lista originale in caso di errore
        }
        nuovoNodo->attivita = att; //aggiunge la nuova attivita' al nodo
        nuovoNodo->prossimoNodo = NULL; //Il nuovo nodo sara' l'ultimo, quindi il prossimo nodo e' NULL
        if (l == NULL) {
            return nuovoNodo; //Se la lista e' vuota, il nuovo nodo sara' la testa
        }
        
            Nodo* corrente = l;
            while (corrente->prossimoNodo != NULL) {
                corrente = corrente->prossimoNodo; //Scorre la lista fino all'ultimo nodo
            }
        corrente->prossimoNodo = nuovoNodo; //Collega il nuovo nodo alla fine della lista
        return l; //Restituisce la lista aggiornata
}

// Funzione per stampare la lista
void stampaLista(const Lista l, Data oggi) {
    int indice = 1;
    Nodo* corrente = l;
    while (corrente != NULL) {
        printf("-------------------\n");
        printf("Attivita' %d:\n", indice++); //Stampa il numero dell'attivita'
        printf("\n");
        stampaAttivita(corrente->attivita, oggi); //Stampa l'attivita' del nodo corrente
        corrente = corrente->prossimoNodo; //Passa al nodo successivo
    }
}
//Restituisce la lunghezza della lista
int lunghezzaLista(Nodo* testa) {
    int contatore = 0;
    while (testa != NULL) {
        contatore++;
        testa = testa->prossimoNodo; //Passa al nodo successivo
    }
    return contatore; //Restituisce la lunghezza della lista
}

// Funzione per liberare la memoria allocata per la lista
void liberaLista(Lista l){
    Nodo* corrente = l;
    while (corrente != NULL){
        Nodo* daLiberare = corrente; //Salva il nodo corrente
        corrente = corrente->prossimoNodo; //Passa al nodo successivo
        liberaAttivita(daLiberare->attivita); //Libera l'attivita' del nodo
        free(daLiberare); //Libera il nodo stesso
    }
}

