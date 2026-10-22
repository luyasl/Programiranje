#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// VJEZBA 1:
//   Napisati program koji prvo pročita koliko redaka ima datoteka, tj.koliko ima studenata zapisanih u
//   datoteci.Nakon toga potrebno je dinamički alocirati prostor za niz struktura studenata(ime, prezime,
//   bodovi) i učitati iz datoteke sve zapise.Na ekran ispisati ime, prezime, apsolutni i relativni broj bodova.
//   Napomena: Svaki redak datoteke sadrži ime i prezime studenta, te broj bodova na kolokviju.
//   relatvan_br_bodova = br_bodova / max_br_bodova * 100

#define MAX_BODOVI 100.0

typedef struct {
    char ime[30];
    char prezime[30]; 
    int bodovi;
} Student;

int main() {
    FILE* datoteka = fopen("studenti.txt", "r");
    if (datoteka == NULL) {
        printf("Greska pri otvaranju datoteke.\n");
        return -1;
    }
   
    int brojStudenata = 0;
    char redak[100]; // sluzi za maksimalnu duljinu redka
  
    while (fgets(redak, sizeof(redak), datoteka) != NULL) {
        if (redak[0] != '\n') {  // preskoci prazne retke
            brojStudenata++;
        }
    }

    printf("Broj studenata u datoteci: %d\n\n", brojStudenata);

    Student* studenti = (Student*)malloc(brojStudenata * sizeof(Student));
    if (studenti == NULL) { // provjera ako je alokacija uspjesna
        printf("Greska kod alokacije memorije.\n");
        fclose(datoteka);
        return -1;
    }

    // vracanje na pocetak datoteke i citanje podataka
    rewind(datoteka);
    
    for (int i = 0; i < brojStudenata; i++) {
        fscanf(datoteka, " %s %s %d", studenti[i].ime, studenti[i].prezime, &studenti[i].bodovi);
    }

    fclose(datoteka);
    datoteka = NULL;
    
    printf("%-15s %-15s %-15s %-15s\n", "Ime", "Prezime", "Aps. bodovi", "Rel. bodovi (%)");
    printf("--------------------------------------------------------------\n");

    for (int i = 0; i < brojStudenata; i++) {
        double relativni = (studenti + i)->bodovi / MAX_BODOVI * 100.0;
        printf("%-15s %-15s %-15d %.2f%%\n",
            (studenti + i)->ime,
            (studenti + i)->prezime,
            (studenti + i)->bodovi,
            relativni);
    }
    printf("--------------------------------------------------------------\n");

    free(studenti);
    studenti = NULL; 
    
    return 0;
}
