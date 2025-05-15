//lista.c
#include <stdio.h>
#include <stdlib.h>
#include "lista.h"
#include "attivita.h"

//Funzione per creare una lista vuota
Lista creaLista() {
    return NULL; //La lista vuota è rappresentata da NULL
}
//Funzione per inserire un'attività in testa alla lista
Lista inserisciInTesta(Lista l, Attivita* att){
    Nodo* nuovoNodo = (Nodo*)malloc(sizeof(Nodo));
    if (nuovoNodo == NULL) {
        printf("Errore di allocazione della memoria\n");
        return l; //Restituisce la lista originale in caso di errore
    }
    nuovoNodo->attivita = att; //Aggiunge la nuova attività al nodo
    nuovoNodo->prossimoNodo = l; //Collega il nuovo nodo alla lista esistente
    return nuovoNodo; //Restituisce il nuovo nodo come testa
        }

// Funzione per inserire un'attività in coda alla lista
Lista inserisciInCoda(Lista l, Attivita* att) {
        Nodo* nuovoNodo = (Nodo*)malloc(sizeof(Nodo));
        if (nuovoNodo == NULL) {
            printf("Errore di allocazione della memoria\n");
            return l; //Restituisce la lista originale in caso di errore
        }
        nuovoNodo->attivita = att; //aggiunge la nuova attività al nodo
        nuovoNodo->prossimoNodo = NULL; //Il nuovo nodo sarà l'ultimo, quindi il prossimo nodo è NULL
        if (l == NULL) {
            return nuovoNodo; //Se la lista è vuota, il nuovo nodo sarà la testa
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
    Nodo* corrente = l;
    while (corrente != NULL) {
        stampaAttivita(corrente->attivita, oggi); //Stampa l'attività del nodo corrente
        corrente = corrente->prossimoNodo; //Passa al nodo successivo
    }
}
// Funzione per liberare la memoria allocata per la lista
void liberaLista(Lista l){
    Nodo* corrente = l;
    while (corrente != NULL){
        Nodo* daLiberare = corrente; //Salva il nodo corrente
        corrente = corrente->prossimoNodo; //Passa al nodo successivo
        liberaAttivita(daLiberare->attivita); //Libera l'attività del nodo
        free(daLiberare); //Libera il nodo stesso
    }
}

