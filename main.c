//main.c
#include <stdio.h>
#include <stdlib.h>
#include "gestione.h"
#include "lista.h"
#include "menu.h"

int main() {
    Data oggi;
    printf("--- GESTIONE STUDIO ---\n");
    do{
    printf("Inserisci data odierna (gg/mm/aaaa):\n");
    printf("Giorno: ");
    scanf("%d", &oggi.giorno);
    printf("Mese: ");
    scanf("%d", &oggi.mese);
    printf("Anno: ");
    scanf("%d", &oggi.anno);
    //Verifica la validita' della data
    if (!dataValida(oggi)) {
                    printf("Data non valida!\n");
                }
            } while (!dataValida(oggi)); 
    Lista lista = NULL;  //Inizializzazione della lista vuota
    
    lista = caricaAttivitaDaFile("attivita.txt"); //Carica la lista delle attivita' dal file, se il file e' vuoto restituisce un avviso
    if (lista == NULL){
        printf("Nessuna attivita' trovata.\n");
    }

    mostraMenu(&lista, oggi);  //Avvia il menu interattivo

    liberaLista(lista); //Libera la memoria allocata

    printf("Programma terminato.\n");
    return 0;
}