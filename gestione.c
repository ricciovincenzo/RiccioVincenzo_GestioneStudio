//gestione.c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "gestione.h"
#include "lista.h"
#include "attivita.h"

//Crea un nuovo nodo con l'attivita' e lo inserisce nella lista
//inTesta == 1 in testa, in Testa == 0 in coda
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

//Modifica l'attivita' alla posizione specificata nella lista
//Libera la vecchia attivita' e assegna la nuovaAtt passata
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

//Rimuove e libera l'attivita' alla posizione indicata nella lista
//Gestisce i casi di rimozione in testa e posizione generica
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

//Aggiorna lo stato dell'attivita' alla posizione indicata nella lista
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

//Carica le attivita' da un file di testo formattato e costruisce la lista
//Ogni attivita' e' composta da una descrizione, corso, data, tempo stimato, priorita' e stato
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

//Salva la lista delle attivita' in un file di testo con formato leggibile
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

//Libera tutta la memoria occupata dalla lista e dalle attivita' associate
void liberaListaAttivita(Lista l) {
    Nodo* corrente = l;
    while (corrente != NULL) {
        Nodo* daLiberare = corrente;
        corrente = corrente->prossimoNodo;
        liberaAttivita(daLiberare->attivita);
        free(daLiberare);
    }
}