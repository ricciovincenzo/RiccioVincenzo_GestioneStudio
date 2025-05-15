//main.c
#include <stdio.h>
#include <stdlib.h>
#include "lista.h"
#include "menu.h"

int main() {
    Data oggi;
    printf("Inserisci data odierna (gg mm aaaa):\n");
    printf("Giorno: ");
    scanf("%d", &oggi.giorno);
    printf("Mese: ");
    scanf("%d", &oggi.mese);
    printf("Anno: ");
    scanf("%d", &oggi.anno);
    Lista lista = NULL;  // Inizializzazione della lista vuota

    printf("Benvenuto nel sistema di gestione delle attività di studio!\n");

    mostraMenu(lista, oggi);  // Avvia il menu interattivo

    liberaLista(lista); // Libera la memoria allocata

    printf("Programma terminato.\n");
    return 0;
}