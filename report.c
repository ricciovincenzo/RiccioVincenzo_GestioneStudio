//report.c
#include <stdio.h>
#include "attivita.h"
#include "attivita.h"
#include "lista.h"
#include "report.h"

//Converte una stringa in intero
static int stringToInt(const char* str, int start, int length){
    int val = 0;
    for (int i=0; i<length; i++){
        val = val*10 + (str[start+i] - '0');
    }
    return val;
}

//Confronta se data_str è compresa tra inizio_str e fine_str
int dataInIntervallo(Data data, Data inizio, Data fine) {
    if (data.anno < inizio.anno || 
   (data.anno == inizio.anno && data.mese < inizio.mese) || 
   (data.anno == inizio.anno && data.mese == inizio.mese && data.giorno < inizio.giorno)) {
    return 0;
}

if (data.anno > fine.anno || 
   (data.anno == fine.anno && data.mese > fine.mese) || 
   (data.anno == fine.anno && data.mese == fine.mese && data.giorno > fine.giorno)) {
    return 0;
}
return 1;
}

//Stampa le statistiche delle attività in un file
void statisticheStatoAttivita(Lista lista, FILE* fp) {
    int in_corso = 0, completate = 0, in_ritardo = 0;

    Nodo* corrente = lista;
    while (corrente != NULL) {
        switch (corrente->attivita->stato) {
            case IN_CORSO:
                in_corso++;
                break;
            case COMPLETATA:
                completate++;
                break;
            case IN_RITARDO:
                in_ritardo++;
                break;
        }
        corrente = corrente->prossimoNodo;
    }
    fprintf(fp, "Statistiche settimanali:\n");
    fprintf(fp, "Attività in corso: %d\n", in_corso);
    fprintf(fp, "Attività completate: %d\n", completate);
    fprintf(fp, "Attività in ritardo: %d\n", in_ritardo);
}
//Genera un file di report delle attività in una settimana specificata
void generaReportSettimanale(Lista lista, Data data_inizio, Data data_fine, const char* nome_file) {

    FILE* fp = fopen(nome_file, "w");
    if (!fp) {
        printf("Errore nell'apertura del file di report.\n");
        return;
    }

    fprintf(fp, "Report settimanale delle attività:\n");
    fprintf(fp, "Periodo: %d/%d/%d - %d/%d/%d\n", data_inizio.giorno, data_inizio.mese, data_inizio.anno, data_fine.giorno, data_fine.mese, data_fine.anno);
    fprintf(fp, "-------------------------\n");
    Nodo* corrente = lista;
    int trovate = 0;

    while (corrente != NULL) {
        if (dataInIntervallo(corrente->attivita->scadenza, data_inizio, data_fine)) {
            fprintf(fp, "Descrizione: %s\n", corrente->attivita->descrizione);
            fprintf(fp, "Corso: %s\n", corrente->attivita->corso);
            fprintf(fp, "Scadenza: %02d/%02d/%04d\n", 
                corrente->attivita->scadenza.giorno,
                corrente->attivita->scadenza.mese,
                corrente->attivita->scadenza.anno);
            fprintf(fp, "Tempo stimato: %d ore\n", corrente->attivita->tempo_stimato);

            char* priorita_str;
            switch (corrente->attivita->priorita) {
                case BASSA: priorita_str = "Bassa"; break;
                case MEDIA: priorita_str = "Media"; break;
                case ALTA:  priorita_str = "Alta";  break;
                default:    priorita_str = "Sconosciuta"; break;
            }

            char* stato_str;
            switch (corrente->attivita->stato) {
                case IN_CORSO:   stato_str = "In corso";    break;
                case COMPLETATA: stato_str = "Completata";  break;
                case IN_RITARDO: stato_str = "In ritardo";  break;
                default:         stato_str = "Sconosciuto"; break;
            }
            fprintf(fp, "Priorità: %s\n", priorita_str);
            fprintf(fp, "Stato: %s\n", stato_str);
            fprintf(fp, "-------------------------\n");
            trovate=1;
        }
        corrente = corrente->prossimoNodo;
    }
    if (trovate==0) {
        fprintf(fp, "Nessuna attività trovata nel periodo specificato.\n");
    }

    statisticheStatoAttivita(lista, fp);
    fclose(fp);
    printf("Report settimanale generato con successo: %s\n", nome_file);
}
