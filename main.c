//main.c
#include <stdio.h>
#include <stdlib.h>
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
    //Verifica la validità della data
    if (!dataValida(oggi)) {
                    printf("Data non valida!\n");
                }
            } while (!dataValida(oggi)); 
    Lista lista = NULL;  //Inizializzazione della lista vuota

    mostraMenu(lista, oggi);  //Avvia il menu interattivo

    liberaLista(lista); //Libera la memoria allocata

    printf("Programma terminato.\n");
    return 0;
}