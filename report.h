//report.h
#ifndef REPORT_H
#define REPORT_H

#include "lista.h"

//Genera un report delle attivita' in una specifica settimana
//La settimana viene specificata tramite due stringhe: data_inizio e data_fine nel formato gg/mm/aaaa
//Il report viene scritto su file e stampato a schermo

//Verifica se la data e' compresa tra due date
int dataInIntervallo(Data data, Data inizio, Data fine);

//Stampa le statistiche delle attivita' in un file
void statisticheStatoAttivita(Lista lista, FILE* fp);

//Genera un report delle attivita' in una settimana specificata
void generaReportSettimanale(Lista lista, Data inizio, Data fine, const char* nome_file);
    
#endif