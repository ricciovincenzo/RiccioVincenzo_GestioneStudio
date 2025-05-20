//attivita.c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "attivita.h"

//Alloca dinamicamente e inizializza una nuova attivita' con i dati forniti come argomenti
Attivita* creaAttivita(const char* descrizione, const char* corso, Data scadenza, int tempo_stimato, int priorita, int stato) {
    Attivita* nuova = (Attivita*) malloc(sizeof(Attivita));
    if (!nuova) { //Se l'allocazione non va a buon fine
        printf("Errore allocazione memoria per attivita'.\n");
        exit(1);
    }
    
    //Copia la descrizione e il corso nelle stringhe della struct
    strncpy(nuova->descrizione, descrizione, DESCRIZIONE_LEN - 1);
    nuova->descrizione[DESCRIZIONE_LEN - 1] = '\0';

    strncpy(nuova->corso, corso, CORSO_LEN - 1);
    nuova->corso[CORSO_LEN - 1] = '\0';

    //Inizializza e assegna i campi dell'attivita' con i valori passati
    nuova->scadenza = scadenza;
    nuova->tempo_stimato = tempo_stimato;
    nuova->priorita = priorita;
    nuova->stato = stato;

    return nuova;
}


//Stampa a video i dettagli dell'attivita' e la verifica per la validita' della data
void stampaAttivita(Attivita* att, Data oggi) {
    if (!att) {
        printf("Attivita' non valida.\n");
        return;
    }

    //Se l'attivita' non e' completata, verifica se e' in ritardo rispetto alla data odierna e aggiorna lo stato di conseguenza
    if (att->stato != COMPLETATA) {
        if (att->scadenza.anno  < oggi.anno
         || (att->scadenza.anno == oggi.anno && (
              att->scadenza.mese  < oggi.mese
           || (att->scadenza.mese == oggi.mese && att->scadenza.giorno < oggi.giorno)
         )))
        {
            att->stato = 2; // in ritardo
        } 
    }
    
    //Traduce il valore numerico della priorita' in una stringa leggibile
    char* priorita_str;
    switch (att->priorita) {
        case BASSA: priorita_str = "Bassa"; break;
        case MEDIA: priorita_str = "Media"; break;
        case ALTA:  priorita_str = "Alta";  break;
        default:    priorita_str = "Sconosciuta"; break;
    }

    //Traduce il valore numerico dello stato in una stringa leggibile
    char* stato_str;
    switch (att->stato) {
        case IN_CORSO:   stato_str = "In corso";    break;
        case COMPLETATA: stato_str = "Completata";  break;
        case IN_RITARDO: stato_str = "In ritardo";  break;
        default:         stato_str = "Sconosciuto"; break;
    }

    //Stampa tutte le informazioni dell'attivita' in modo formattato
    printf("Descrizione: %s\n",    att->descrizione);
    printf("Corso: %s\n",          att->corso);
    printf("Scadenza: %02d/%02d/%04d\n",
           att->scadenza.giorno,
           att->scadenza.mese,
           att->scadenza.anno);
    printf("Tempo stimato: %d ore\n", att->tempo_stimato);
    printf("Priorita': %s\n", priorita_str);
    printf("Stato: %s\n", stato_str);
}

//Controlla se la data passata e' valida, tenendo conto anche degli anni bisestili
int dataValida(Data d) {
    if (d.giorno < 1 || d.giorno > 31 || d.mese < 1 || d.mese > 12 || d.anno < 1900)
        return 0;

    int giorni_per_mese[] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
    if ((d.anno % 4 == 0 && d.anno % 100 != 0) || (d.anno % 400 == 0))
        giorni_per_mese[1] = 29;

    return d.giorno <= giorni_per_mese[d.mese - 1];
}

//Libera la memoria allocata dinamicamente per una attivita' se e' presente, altrimenti non libera nulla
void liberaAttivita(Attivita* att) {
    if (att != NULL)
        free(att);
}

