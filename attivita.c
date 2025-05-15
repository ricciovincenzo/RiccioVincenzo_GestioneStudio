//attivita.c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "attivita.h"

Attivita* creaAttivita(const char* descrizione, const char* corso, Data scadenza, int tempo_stimato, int priorita, int stato) {
    Attivita* nuova = (Attivita*) malloc(sizeof(Attivita));
    if (!nuova) {
        printf("Errore allocazione memoria per attività.\n");
        exit(1);
    }

    strncpy(nuova->descrizione, descrizione, DESCRIZIONE_LEN - 1);
    nuova->descrizione[DESCRIZIONE_LEN - 1] = '\0';

    strncpy(nuova->corso, corso, CORSO_LEN - 1);
    nuova->corso[CORSO_LEN - 1] = '\0';

    nuova->scadenza = scadenza;

    nuova->tempo_stimato = tempo_stimato;
    nuova->priorita = priorita;
    nuova->stato = stato;

    return nuova;
}



void stampaAttivita(Attivita* att, Data oggi) {
    if (!att) {
        printf("Attività non valida.\n");
        return;
    }

    // confronta anno/mese/giorno
    if (att->stato != COMPLETATA) {
        if (att->scadenza.anno  < oggi.anno
         || (att->scadenza.anno == oggi.anno && (
              att->scadenza.mese  < oggi.mese
           || (att->scadenza.mese == oggi.mese && att->scadenza.giorno < oggi.giorno)
         )))
        {
            att->stato = IN_RITARDO;
        } else {
            att->stato = IN_CORSO;
        }
    }

    // stampa semplice
    printf("Descrizione: %s\n",    att->descrizione);
    printf("Corso: %s\n",          att->corso);
    printf("Scadenza: %02d/%02d/%04d\n",
           att->scadenza.giorno,
           att->scadenza.mese,
           att->scadenza.anno);
    printf("Tempo stimato: %d ore\n", att->tempo_stimato);
    printf("Priorità (0=bassa,1=media,2=alta): %d\n", att->priorita);
    printf("Stato   (0=in corso,1=completata,2=in ritardo): %d\n\n", att->stato);
}

int dataValida(Data d) {
    if (d.giorno < 1 || d.giorno > 31 || d.mese < 1 || d.mese > 12 || d.anno < 1900)
        return 0;

    int giorni_per_mese[] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
    if ((d.anno % 4 == 0 && d.anno % 100 != 0) || (d.anno % 400 == 0))
        giorni_per_mese[1] = 29;

    return d.giorno <= giorni_per_mese[d.mese - 1];
}

void liberaAttivita(Attivita* att) {
    if (att != NULL)
        free(att);
}

