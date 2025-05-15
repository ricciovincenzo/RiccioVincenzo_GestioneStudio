//menu.c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "menu.h"
#include "attivita.h"
#include "gestione.h"
#include "report.h"
#include "lista.h"

void mostraMenu(Lista lista, Data oggi) {
    int scelta;
    do {
        printf("\n--- Menu ---\n");
        printf("1. Aggiungi Attività\n");
        printf("2. Modifica Attività\n");
        printf("3. Elimina Attività\n");
        printf("4. Mostra Attività\n");
        printf("5. Aggiorna Progresso\n");
        printf("6. Genera Report Settimanale\n");
        printf("0. Esci\n");
        printf("Scelta: ");
        scanf("%d", &scelta);
        getchar();

        int posizione;
        Attivita* nuova;
        char inizio[11], fine[11];

        switch (scelta) {
            case 1: {
                char desc[DESCRIZIONE_LEN], corso[CORSO_LEN];
                int tempo, prio, stat;
                //leggi descrizione
                printf("Descrizione: ");
                fgets(desc, DESCRIZIONE_LEN, stdin);
                desc[strcspn(desc, "\n")] = '\0';

                //leggi corso
                printf("Corso: ");
                fgets(corso, CORSO_LEN, stdin);
                corso[strcspn(corso, "\n")] = '\0';

                //leggi data di scadenza come tre interi
                int g, m, a;
                printf("Giorno scadenza: ");
                scanf("%d", &g);
                printf("Mese scadenza:  ");
                scanf("%d", &m);
                printf("Anno scadenza:  ");
                scanf("%d", &a);
                //Verifica il formato corretto della data
                Data scad = { g, m, a };
                if (!dataValida(scad)) {
                    printf("Data non valida!\n");
                     break;
                }

                //leggi resto dei campi
                printf("Tempo stimato (ore): ");
                scanf("%d", &tempo);
                printf("Priorità (0=bassa,1=media,2=alta): ");
                scanf("%d", &prio);
                printf("Stato (0=in corso,1=completata,2=in ritardo): ");
                scanf("%d", &stat);

                //crea e inserisci
                nuova = creaAttivita(desc, corso, scad, tempo, prio, stat);
                lista = aggiungiAttivita(lista, nuova, 0);

                //svuota eventuale newline rimasto prima del prossimo fgets
                int _c;
                while ((_c = getchar()) != '\n' && _c != EOF);

                break;
}

            case 2: 
                printf("Posizione dell'attività da modificare: ");
                scanf("%d", &posizione);
                char desc2[DESCRIZIONE_LEN], corso2[CORSO_LEN];
                int tempo2, prio2, stat2;
                printf("Descrizione: ");    scanf(" %99[^\n]", desc2);
                printf("Corso: ");         scanf(" %49[^\n]", corso2);
                int g2, m2, a2;
                printf("Giorno scadenza: ");
                scanf("%d", &g2);
                printf("Mese scadenza: ");
                scanf("%d", &m2);
                printf("Anno scadenza: ");
                scanf("%d", &a2);
                Data scad2 = { g2, m2, a2 };
                //Verifica il formato corretto della data
                if (!dataValida(scad2)) {
                    printf("Data non valida!\n");
                     break;
                }
                printf("Tempo stimato (ore): ");   scanf("%d", &tempo2);
                printf("Priorità (0=bassa,1=media,2=alta): "); scanf("%d", &prio2);
                printf("Stato (0=in corso,1=completata,2=in ritardo): "); scanf("%d", &stat2);

                nuova = creaAttivita(desc2, corso2, scad2, tempo2, prio2, stat2);
                lista = modificaAttivita(lista, posizione, nuova);
                break;
    
            case 3:
                printf("Posizione dell'attività da eliminare: ");
                scanf("%d", &posizione);
                lista = rimuoviAttivita(lista, posizione);
                break;

            case 4:
                stampaLista(lista, oggi);
                break;

            case 5:
                printf("Posizione dell'attività da aggiornare: ");
                scanf("%d", &posizione);

                int nuovoStato;
                printf("Nuovo stato (0=in corso, 1=completata, 2=in ritardo): ");
                scanf("%d", &nuovoStato);
                lista = aggiornaProgresso(lista, posizione, nuovoStato);
                break;

            case 6:
                int g_inizio, m_inizio, a_inizio;
                int g_fine, m_fine, a_fine;
                printf("Data inizio (gg mm aaaa): ");
                scanf("%d %d %d", &g_inizio, &m_inizio, &a_inizio);
                printf("Data fine (gg mm aaaa): ");
                scanf("%d %d %d", &g_fine, &m_fine, &a_fine);
                generaReportSettimanale(lista, g_inizio, m_inizio, a_inizio, g_fine, m_fine, a_fine, "report.txt");
                break;

            case 0:
                printf("Uscita...\n");
                break;

            default:
                printf("Scelta non valida\n");
        }
    } while (scelta != 0);
}
