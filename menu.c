//menu.c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "menu.h"
#include "attivita.h"
#include "gestione.h"
#include "report.h"
#include "lista.h"

int lunghezza;
void mostraMenu(Lista *lista, Data oggi) {
    int scelta;
    do {
        printf("\n--- Menu ---\n");
        printf("1. Aggiungi Attivita'\n");
        printf("2. Modifica Attivita'\n");
        printf("3. Elimina Attivita'\n");
        printf("4. Mostra Attivita'\n");
        printf("5. Aggiorna Progresso\n");
        printf("6. Genera Report Settimanale\n");
        printf("0. Salva ed esci\n");
        printf("Scelta: ");
        scanf("%d", &scelta);
        getchar();

        int posizione;

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
                Data scad;
                printf("Inserisci la data di scadenza (gg/mm/aaaa):\n");
                do {
                printf("Giorno scadenza: ");
                scanf("%d", &scad.giorno);
                printf("Mese scadenza:  ");
                scanf("%d", &scad.mese);
                printf("Anno scadenza:  ");
                scanf("%d", &scad.anno);
                //Verifica il formato corretto della data
                if (!dataValida(scad)) {
                    printf("Data non valida!\n");
                }
            } while (!dataValida(scad)); 

                //leggi resto dei campi
                printf("Tempo stimato (ore): ");
                scanf("%d", &tempo);

                do{
                    printf("Priorita' (0=bassa,1=media,2=alta): ");
                    scanf("%d", &prio);
                    if (prio < 0 || prio > 2){
                        printf("Errore: priorita' non valida.\n");
                    }
                } while (prio < 0 || prio > 2);

                do{
                printf("Stato (0=in corso,1=completata,2=in ritardo): ");
                scanf("%d", &stat);
                if (stat < 0 || stat > 2){
                    printf("Errore: stato non valido.\n");
                }
                } while (stat < 0 || stat > 2);

                //crea e inserisci
                Attivita* nuova = creaAttivita(desc, corso, scad, tempo, prio, stat);
                *lista = aggiungiAttivita(*lista, nuova, 0);

                //svuota eventuale newline rimasto prima del prossimo fgets
                int _c;
                while ((_c = getchar()) != '\n' && _c != EOF);

                break;
}

            case 2: 
                printf("Posizione dell'attivita' da modificare: ");
                scanf("%d", &posizione); //L'utente inserisce la posizione da 1 a n, noi la convertiamo in 0 a n-1
                getchar(); //pulisce il buffer
                posizione--;
                //Controlla se la posizione è valida
                lunghezza = lunghezzaLista(*lista);
                if (posizione < 0 || posizione >= lunghezza) {
                    printf("Posizione non valida! Le attivita sono %d.\n", lunghezza);
                    break;
                }

                char desc2[DESCRIZIONE_LEN], corso2[CORSO_LEN];
                int tempo2, prio2, stat2;
                //leggi descrizione
                printf("Descrizione: ");
                fgets(desc2, DESCRIZIONE_LEN, stdin);
                desc2[strcspn(desc2, "\n")] = '\0';

                //leggi corso
                printf("Corso: ");
                fgets(corso2, CORSO_LEN, stdin);
                corso2[strcspn(corso2, "\n")] = '\0';
                //legge data di scadenza come tre interi
                Data scad2;
                printf("Inserisci la data di scadenza (gg/mm/aaaa):\n");
                do {
                printf("Giorno scadenza: ");
                scanf("%d", &scad2.giorno);
                printf("Mese scadenza: ");
                scanf("%d", &scad2.mese);
                printf("Anno scadenza: ");
                scanf("%d", &scad2.anno);
                //Verifica il formato corretto della data
                if (!dataValida(scad2)) {
                    printf("Data non valida!\n");
                }
                } while (!dataValida(scad2)); 
                printf("Tempo stimato (ore): ");   scanf("%d", &tempo2);

                do{
                printf("Priorita' (0=bassa,1=media,2=alta): ");
                    scanf("%d", &prio2);
                    if (prio2 < 0 || prio2 > 2){
                        printf("Errore: priorita' non valida.\n");
                    }
                } while (prio2 < 0 || prio2 > 2);

                do{
                    printf("Stato (0=in corso,1=completata,2=in ritardo): ");
                    scanf("%d", &stat2);
                    if (stat2 < 0 || stat2 > 2){
                        printf("Errore: stato non valido.\n");
                    }
                } while (stat2 < 0 || stat2 > 2);

                Attivita* nuova = creaAttivita(desc2, corso2, scad2, tempo2, prio2, stat2);
                *lista = modificaAttivita(*lista, posizione, nuova);
                break;
    
            case 3:
                printf("Posizione dell'attivita' da eliminare: ");
                scanf("%d", &posizione); //L'utente inserisce la posizione da 1 a n, noi la convertiamo in 0 a n-1
                posizione--;
                //Controlla se la posizione è valida
                lunghezza = lunghezzaLista(*lista);
                if (posizione < 0 || posizione >= lunghezza) {
                    printf("Posizione non valida! Le attivita sono %d.\n", lunghezza);
                    break;
                }
                *lista = rimuoviAttivita(*lista, posizione);
                break;

            case 4:
            lunghezza = lunghezzaLista(*lista);
                if (lunghezza > 0)
                    stampaLista(*lista, oggi);
                else
                    printf("Non hai inserito nessuna attivita'.\n");
                break;

            case 5:
                printf("Posizione dell'attivita' da aggiornare: ");
                scanf("%d", &posizione); //L'utente inserisce la posizione da 1 a n, noi la convertiamo in 0 a n-1
                posizione--;
                //Controlla se la posizione è valida
                lunghezza = lunghezzaLista(*lista);
                if (posizione < 0 || posizione >= lunghezza) {
                    printf("Posizione non valida! Le attivita sono %d.\n", lunghezza);
                    break;
                }

                int nuovoStato;
                do{
                    printf("Nuovo stato (0=in corso,1=completata,2=in ritardo): ");
                    scanf("%d", &nuovoStato);
                    if (nuovoStato < 0 || nuovoStato > 2){
                        printf("Errore: stato non valido.\n");
                    }
                } while (nuovoStato < 0 || nuovoStato > 2);
                *lista = aggiornaProgresso(*lista, posizione, nuovoStato);
                break;

            case 6:
                Data inizio, fine;
                do{
                printf("Data inizio (gg/mm/aaaa):\n");
                printf("Giorno: ");
                scanf("%d", &inizio.giorno);
                printf("Mese: ");
                scanf("%d", &inizio.mese);
                printf("Anno: ");
                scanf("%d", &inizio.anno);
                //Verifica il formato corretto della data
                if (!dataValida(inizio)) {
                    printf("Data non valida!\n");
                }
                } while (!dataValida(inizio));
                do{
                printf("Data fine (gg/mm/aaaa):\n");
                printf("Giorno: ");
                scanf("%d", &fine.giorno);
                printf("Mese: ");
                scanf("%d", &fine.giorno);
                printf("Anno: ");
                scanf("%d", &fine.anno);
                if (!dataValida(fine)) {
                    printf("Data non valida!\n");
                }
                } while (!dataValida(fine)); //Verifica la validità della data
                generaReportSettimanale(*lista, inizio, fine, "report.txt");
                break;

            case 0:
                salvaAttivitaSuFile(*lista, "attivita.txt"); //Salva la lista delle attività sul file appena l'utente termina il programma
                printf("Le attivita' sono state salvate su file.\n");
                printf("Uscita...\n");
                break;

            default:
                printf("Scelta non valida\n");
        }
    } while (scelta != 0);
}
