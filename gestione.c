//gestione.c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
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

Nodo* caricaAttivitaDaFile(const char *nomeFile) {
    FILE *f = fopen(nomeFile, "r");
    if (!f) return NULL;

    Nodo *lista = NULL;
    char descrizione[DESCRIZIONE_LEN];
    char corso[CORSO_LEN];
    int giorno, mese, anno;
    int tempo, priorita, stato;

    while (
        fgets(descrizione, sizeof(descrizione), f) &&
        fgets(corso, sizeof(corso), f) &&
        fscanf(f, "%d %d %d\n", &giorno, &mese, &anno) == 3 &&
        fscanf(f, "%d\n", &tempo) == 1 &&
        fscanf(f, "%d\n", &priorita) == 1 &&
        fscanf(f, "%d\n", &stato) == 1
    ) {
        //rimozione "\n"
        descrizione[strcspn(descrizione, "\n")] = '\0';
        corso[strcspn(corso, "\n")] = '\0';

        Data d = {giorno, mese, anno};
        Attivita *a = creaAttivita(descrizione, corso, d, tempo, priorita, stato);
        lista = aggiungiAttivita(lista, a, 0);  //Seleziona l'inserimento in coda (0)
    }

    fclose(f);
    return lista;
}

void salvaAttivitaSuFile(Lista l, const char *nomeFile) {
    FILE *f = fopen(nomeFile, "w");
    if (!f) return;

    for (Nodo *corrente = l; corrente != NULL; corrente = corrente->prossimoNodo) {
        Attivita *a = corrente->attivita;
        fprintf(f, "%s\n", a->descrizione);
        fprintf(f, "%s\n", a->corso);
        fprintf(f, "%d %d %d\n", a->scadenza.giorno, a->scadenza.mese, a->scadenza.anno);
        fprintf(f, "%d\n", a->tempo_stimato);
        fprintf(f, "%d\n", a->priorita);
        fprintf(f, "%d\n", a->stato);
    }

    fclose(f);
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