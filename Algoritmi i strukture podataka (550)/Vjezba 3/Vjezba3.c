#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// VJEZBA 3:
//  1. Unos iza traženog elementa - gotovo
//  2. Unos ispred traženog elementa - gotovo
//  3. Sortiranje po prezimenu
//  4. Upis liste u datoteku
//  5. Unos iz datoteke u listu


typedef struct Osoba* Pozicija;

struct Osoba {
    char ime[50];
    char prezime[50];
    int godinaRodjenja;
    Pozicija Next;
};

int Ispis(Pozicija P);
int Unos(Pozicija P, char* ime, char* prezime, int godina);
int UnosIza(char* prezime, Pozicija);
int UnosIspred(char* prezime, Pozicija);
int SortPrezime(Pozicija);
int UpisiUDatoteku(Pozicija);
int ProcitajIzDatoteke(Pozicija);

int main()
{
    struct Osoba Head;
    Head.Next = NULL;

    Pozicija temp;
    char prezime[50];
    int izbor;

    Unos(&Head, "Pero", "Peric", 2000);
    Unos(&Head, "Antun", "Antic", 1998);
    Unos(&Head, "Luka", "Lukic", 2002);

    do {
        printf("\n- Lista:\n");
        printf("1. Ispis liste\n");
        printf("2. Unos iza trazenog elementa\n");
        printf("3. Unos ispred trazenog elementa\n");
        printf("4. Sortiranje po prezimenu\n");
        printf("5. Upis liste u datoteku\n");
        printf("6. Unos iz datoteke u listu\n");
        printf("0. Izlaz\n");
        printf("Odaberi: ");
        scanf("%d", &izbor);

        if (izbor == 1) {
            Ispis(&Head);
        }
        else if (izbor == 2) {
            printf("Unesi prezime osobe iza koje zelis unos: ");
            scanf("%49s", prezime);

            UnosIza(prezime, &Head);
        }
        else if (izbor == 3) {
            printf("Unesi prezime osobe ispred koje zelis unos: ");
            scanf("%49s", prezime);

            UnosIspred(prezime, &Head);
        }
        else if (izbor == 4) {
            SortPrezime(&Head);
        }
        else if (izbor == 5) {
            UpisiUDatoteku(&Head);
        } 
        else if (izbor == 6) {
            ProcitajIzDatoteke(&Head);
        }

    } while (izbor != 0);

    while (Head.Next != NULL) {
        temp = Head.Next;
        Head.Next = temp->Next;
        free(temp);
    }

    return 0;
}

int Unos(Pozicija P, char* ime, char* prezime, int godina){
    Pozicija q = malloc(sizeof(struct Osoba));

    if (q == NULL)
        return -1;

    strcpy(q->ime, ime);
    strcpy(q->prezime, prezime);
    q->godinaRodjenja = godina;
    q->Next = NULL;

    while (P->Next != NULL)
        P = P->Next;

    P->Next = q;

    return 0;

}

int UnosIza(char* prezime, Pozicija P)
{
    while (P->Next != NULL && _stricmp(prezime, P->Next->prezime) != 0){
        P = P->Next;
    }

    if (P->Next == NULL){
        printf("Osoba nije pronadjena.\n");
        return -1;
    }

    Pozicija q = malloc(sizeof(struct Osoba));

    if (q == NULL)
        return -1;

    printf("\nUnesi ime: ");
    scanf("%49s", q->ime);

    printf("Unesi prezime: ");
    scanf("%49s", q->prezime);

    printf("Unesi godinu rodjenja: ");
    scanf("%d", &q->godinaRodjenja);

    q->Next = P->Next->Next;
    P->Next->Next = q;

    return 0;
}

int UnosIspred(char* prezime, Pozicija P)
{
    while (P->Next != NULL && _stricmp(prezime, P->Next->prezime) != 0){
        P = P->Next;
    }

    if (P->Next == NULL){
        printf("Osoba nije pronadjena.\n");
        return -1;
    }

    Pozicija q = malloc(sizeof(struct Osoba));

    if (q == NULL)
        return -1;

    printf("\nUnesi ime: ");
    scanf("%49s", q->ime);

    printf("Unesi prezime: ");
    scanf("%49s", q->prezime);

    printf("Unesi godinu rodjenja: ");
    scanf("%d", &q->godinaRodjenja);

    q->Next = P->Next;
    P->Next = q;

    return 0;
}

int SortPrezime(Pozicija P) {
        Pozicija j, prev_j, temp, end;

        end = NULL;
        while (P->Next != end) {
            prev_j = P;
            j = P->Next;

            while (j->Next != end) {
                if (strcmp(j->prezime, j->Next->prezime) > 0) {
                    temp = j->Next;
                    prev_j->Next = temp;
                    j->Next = temp->Next;
                    temp->Next = j;
                    j = temp;
                }

                prev_j = j;
                j = j->Next;
            }
            end = j;
        }
    return 0;
}

int UpisiUDatoteku(Pozicija P)
{
    FILE* fp = fopen("osobe.txt", "w");

    if (fp == NULL) {
        printf("Greska pri otvaranju datoteke!\n");
        return -1;
    }

    Pozicija temp = P->Next;

    while (temp != NULL) {
        fprintf(fp, "%s %s %d\n", temp->ime, temp->prezime, temp->godinaRodjenja);
        temp = temp->Next;
    }

    fclose(fp);
    return 0;
}

int ProcitajIzDatoteke(Pozicija P)
{
    FILE* fp = fopen("datoteka.txt", "r");

    if (fp == NULL) {
        printf("Greska pri otvaranju datoteke!\n");
        return -1;
    }

    char ime[50];
    char prezime[50];
    int godina;

    while (fscanf(fp, "%49s %49s %d", ime, prezime, &godina) == 3){
        Pozicija q = malloc(sizeof(struct Osoba));

        if (q == NULL) {
            fclose(fp);
            return -1;
        }

        strcpy(q->ime, ime);
        strcpy(q->prezime, prezime);
        q->godinaRodjenja = godina;

        q->Next = NULL;

        while (P->Next != NULL)
            P = P->Next;

        P->Next = q;
    }

    fclose(fp);
    return 0;
}

int Ispis(Pozicija P)
{
    printf("\nIspis liste:\n");

    P = P->Next;

    while (P != NULL)
    {
        printf("%s %s %d\n",
            P->ime, P->prezime, P->godinaRodjenja);

        P = P->Next;
    }

    return 0;
}