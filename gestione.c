//gestione.c
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "gestione.h"
#include "lista.h"
#include "attivita.h"

Lista aggiungiAttivita(Lista l, Attivita* att, int inTesta) {
    Nodo* nuovoNodo = (Nodo*) malloc(sizeof(Nodo));
    if (nuovoNodo == NULL) return l;

    nuovoNodo->attivita = att;
    nuovoNodo->prossimoNodo = NULL;

    if (inTesta || l == NULL) {
        nuovoNodo->prossimoNodo = l;
        return nuovoNodo;
    }

    Nodo* corrente = l;
    while (corrente->prossimoNodo != NULL) {
        corrente = corrente->prossimoNodo;
    }
    corrente->prossimoNodo = nuovoNodo;
    return l;
}

Lista modificaAttivita(Lista l, int posizione, Attivita* nuovaAtt) {
    Nodo* corrente = l;
    int i = 0;

    while (corrente != NULL && i < posizione) {
        corrente = corrente->prossimoNodo;
        i++;
    }

    if (corrente != NULL) {
        liberaAttivita(corrente->attivita);
        corrente->attivita = nuovaAtt;
    }

    return l;
}

Lista rimuoviAttivita(Lista l, int posizione) {
    if (l == NULL) return NULL;

    if (posizione == 0) {
        Nodo* daRimuovere = l;
        l = l->prossimoNodo;
        liberaAttivita(daRimuovere->attivita);
        free(daRimuovere);
        return l;
    }

    Nodo* corrente = l;
    int i = 0;
    while (corrente->prossimoNodo != NULL && i < posizione - 1) {
        corrente = corrente->prossimoNodo;
        i++;
    }

    if (corrente->prossimoNodo != NULL) {
        Nodo* daRimuovere = corrente->prossimoNodo;
        corrente->prossimoNodo = daRimuovere->prossimoNodo;
        liberaAttivita(daRimuovere->attivita);
        free(daRimuovere);
    }

    return l;
}

Lista aggiornaProgresso(Lista l, int posizione, int nuovoStato) {
    Nodo* corrente = l;
    int i = 0;
    while (corrente != NULL && i < posizione) {
        corrente = corrente->prossimoNodo;
        i++;
    }
    if (corrente != NULL) {
        corrente->attivita->stato = nuovoStato;
    }
    return l;
}

void liberaListaAttivita(Lista l) {
    Nodo* corrente = l;
    while (corrente != NULL) {
        Nodo* daLiberare = corrente;
        corrente = corrente->prossimoNodo;
        liberaAttivita(daLiberare->attivita);
        free(daLiberare);
    }
}