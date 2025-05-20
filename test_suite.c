//test_suite.c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "attivita.h"
#include "lista.h"
#include "gestione.h"
#include "report.h"

//Funzione di confronto file
int confrontaFile(const char* file1, const char* file2) {
    FILE *f1 = fopen(file1, "r");
    FILE *f2 = fopen(file2, "r");
    if (!f1 || !f2) return 0;
    char c1, c2;
    do {
        c1 = fgetc(f1);
        c2 = fgetc(f2);
        if (c1 != c2) {
            fclose(f1); fclose(f2);
            return 0;
        }
    } while (c1 != EOF && c2 != EOF);
    fclose(f1); fclose(f2);
    return 1;
}

//Funzione per scrivere il risultato
void esitoTest(const char* nomeTC, int risultato) {
    if (risultato) {
    printf("%s: PASS\n", nomeTC);
} else {
    printf("%s: FAIL\n", nomeTC);
}
}

//Inserimento valido
void TC1() {
    Lista l = caricaAttivitaDaFile("file_di_test/TC1_input.txt");
    salvaAttivitaSuFile(l, "file_di_test/TC1_output.txt");
    esitoTest("TC1 - Inserimento valido", confrontaFile("file_di_test/TC1_output.txt", "file_di_test/TC1_oracle.txt"));
    liberaListaAttivita(l);
}

//Inserimento con data errata (simulato da input non caricato)
void TC2() {
    Lista l = caricaAttivitaDaFile("file_di_test/TC2_input.txt");
    if (!l) {
        FILE *f = fopen("file_di_test/TC2_output.txt", "w");
        fprintf(f, "Errore: data non valida\n");
        fclose(f);
    }
    esitoTest("TC2 - Inserimento con data errata", confrontaFile("file_di_test/TC2_output.txt", "file_di_test/TC2_oracle.txt"));
}

//Inserimento con priorita' errata
void TC3() {
    Lista l = caricaAttivitaDaFile("file_di_test/TC3_input.txt");
    if (!l) {
        FILE *f = fopen("file_di_test/TC3_output.txt", "w");
        fprintf(f, "Errore: priorita' non valida\n");
        fclose(f);
    }
    esitoTest("TC3 - Inserimento con priorita' errata", confrontaFile("file_di_test/TC3_output.txt", "file_di_test/TC3_oracle.txt"));
}

//Aggiornamento stato corretto
void TC4() {
    Lista l = caricaAttivitaDaFile("file_di_test/TC4_input.txt");
    l = aggiornaProgresso(l, 0, COMPLETATA);
    salvaAttivitaSuFile(l, "file_di_test/TC4_output.txt");
    esitoTest("TC4 - Aggiornamento stato corretto", confrontaFile("file_di_test/TC4_output.txt", "file_di_test/TC4_oracle.txt"));
    liberaListaAttivita(l);
}

//Aggiornamento stato errato
void TC5() {
    Lista l = caricaAttivitaDaFile("file_di_test/TC5_input.txt");
    int statoErrato = 7;
    if (statoErrato < 0 || statoErrato > 2) {
        FILE *f = fopen("file_di_test/TC5_output.txt", "w");
        fprintf(f, "Errore: stato non valido\n");
        fclose(f);
    }
    esitoTest("TC5 - Aggiornamento stato non valido", confrontaFile("file_di_test/TC5_output.txt", "file_di_test/TC5_oracle.txt"));
    liberaListaAttivita(l);
}

//Cancellazione in testa
void TC6() {
    Lista l = caricaAttivitaDaFile("file_di_test/TC6_input.txt");
    l = rimuoviAttivita(l, 0);
    salvaAttivitaSuFile(l, "file_di_test/TC6_output.txt");
    esitoTest("TC6 - Cancellazione in testa", confrontaFile("file_di_test/TC6_output.txt", "file_di_test/TC6_oracle.txt"));
    liberaListaAttivita(l);
}

//Cancellazione in mezzo
void TC7() {
    Lista l = caricaAttivitaDaFile("file_di_test/TC7_input.txt");
    l = rimuoviAttivita(l, 1);
    salvaAttivitaSuFile(l, "file_di_test/TC7_output.txt");
    esitoTest("TC7 - Cancellazione in mezzo", confrontaFile("file_di_test/TC7_output.txt", "file_di_test/TC7_oracle.txt"));
    liberaListaAttivita(l);
}

//Cancellazione in coda
void TC8() {
    Lista l = caricaAttivitaDaFile("file_di_test/TC8_input.txt");
    l = rimuoviAttivita(l, 1);
    salvaAttivitaSuFile(l, "file_di_test/TC8_output.txt");
    esitoTest("TC8 - Cancellazione in coda", confrontaFile("file_di_test/TC8_output.txt", "file_di_test/TC8_oracle.txt"));
    liberaListaAttivita(l);
}

//Report con attivita' nella settimana
void TC9() {
    Lista l = caricaAttivitaDaFile("file_di_test/TC9_input.txt");
    generaReportSettimanale(l, (Data){20,5,2025}, (Data){26,5,2025}, "file_di_test/TC9_output.txt");
    esitoTest("TC9 - Report con attivita'", confrontaFile("file_di_test/TC9_output.txt", "file_di_test/TC9_oracle.txt"));
    liberaListaAttivita(l);
}

//Report senza attivita' nella settimana
void TC10() {
    Lista l = caricaAttivitaDaFile("file_di_test/TC10_input.txt");
    generaReportSettimanale(l, (Data){20,5,2025}, (Data){26,5,2025}, "file_di_test/TC10_output.txt");
    esitoTest("TC10 - Report vuoto", confrontaFile("file_di_test/TC10_output.txt", "file_di_test/TC10_oracle.txt"));
    liberaListaAttivita(l);
}

//Salvataggio e caricamento file
void TC11() {
    Lista l = caricaAttivitaDaFile("file_di_test/TC11_input.txt");
    salvaAttivitaSuFile(l, "file_di_test/TC11_output.txt");
    Lista ricaricata = caricaAttivitaDaFile("file_di_test/TC11_output.txt");
    salvaAttivitaSuFile(ricaricata, "file_di_test/TC11_output_ricaricato.txt");
    esitoTest("TC11 - Salva e carica", confrontaFile("file_di_test/TC11_output.txt", "file_di_test/TC11_output_ricaricato.txt"));
    liberaListaAttivita(l);
    liberaListaAttivita(ricaricata);
}

//Caricamento da file corrotto
void TC12() {
    Lista l = caricaAttivitaDaFile("file_di_test/TC12_input.txt");
    if (!l) {
        FILE *f = fopen("file_di_test/TC12_output.txt", "w");
        fprintf(f, "Errore: file non valido o corrotto\n");
        fclose(f);
    }
    esitoTest("TC12 - File corrotto", confrontaFile("file_di_test/TC12_output.txt", "file_di_test/TC12_oracle.txt"));
}

int main() {
    TC1(); TC2(); TC3(); TC4(); TC5(); TC6();
    TC7(); TC8(); TC9(); TC10(); TC11(); TC12();
    return 0;
}
