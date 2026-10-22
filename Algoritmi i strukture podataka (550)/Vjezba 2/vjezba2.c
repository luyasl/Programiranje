
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// VJEZBA 2:

//  Definirati strukturu osoba(ime, prezime, godina rođenja) i napisati program koji :
//      a) dinamički dodaje novi element na početak liste,
//      b) ispisuje listu,
//      c) dinamički dodaje novi element na kraj liste,
//      d) pronalazi element u listi (po prezimenu),
//      e) briše određeni element iz liste.
//  U zadatku se ne smiju koristiti globalne varijable.

typedef struct Osoba* Pozicija;

struct Osoba {
    char ime[50];
    char prezime[50];
    int godinaRodjenja;
    Pozicija Next;
};

int UnosP(Pozicija);
int Ispis(Pozicija);
int UnosK(Pozicija);
Pozicija Trazi(char*, Pozicija);
Pozicija TraziP(char*, Pozicija);
int Brisi(char*, Pozicija);

int main()
{
    struct Osoba Head;
    Head.Next = NULL;

    Pozicija temp;
    char prezime[50];
    int izbor;

    do {
        printf("\n- Lista:\n");
        printf("1. Unos na pocetak\n");
        printf("2. Ispis liste\n");
        printf("3. Unos na kraj\n");
        printf("4. Trazi osobu\n");
        printf("5. Brisi osobu\n");
        printf("0. Izlaz\n");
        printf("Odaberi: ");
        scanf("%d", &izbor);

        if (izbor == 1) {
            UnosP(&Head);
        }
        else if (izbor == 2) {
            Ispis(Head.Next);
        }
        else if (izbor == 3) {
            UnosK(&Head);
        }
        else if (izbor == 4) {
            printf("Unesi prezime: ");
            scanf("%49s", prezime);

            temp = Trazi(prezime, Head.Next);

            if (temp == NULL)
                printf("Osoba nije pronadjena.\n");
            else
                printf("%s %s %d\n",
                    temp->ime, temp->prezime, temp->godinaRodjenja);
        }
        else if (izbor == 5) {
            printf("Unesi prezime: ");
            scanf("%49s", prezime);

            Brisi(prezime, &Head);
        }

    } while (izbor != 0);

    while (Head.Next != NULL) {
        temp = Head.Next;
        Head.Next = temp->Next;
        free(temp);
    }

    return 0;
}

//      a) dinamički dodaje novi element na početak liste,
int UnosP(Pozicija P)
{
    Pozicija q;

    q = (Pozicija)malloc(sizeof(struct Osoba));

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

//      b) ispisuje listu,
int Ispis(Pozicija P)
{
    printf("\nIspis liste:\n");

    while (P != NULL)
    {
        printf("%s %s %d\n",
            P->ime, P->prezime, P->godinaRodjenja);

        P = P->Next;
    }

    return 0;
}

//      c) dinamički dodaje novi element na kraj liste,
int UnosK(Pozicija P)
{
    Pozicija q;

    q = (Pozicija)malloc(sizeof(struct Osoba));

    if (q == NULL)
        return -1;

    printf("\nUnesi ime: ");
    scanf("%49s", q->ime);
    printf("Unesi prezime: ");
    scanf("%49s", q->prezime);
    printf("Unesi godinu rodjenja: ");
    scanf("%d", &q->godinaRodjenja);

    while (P->Next != NULL)
        P = P->Next;

    q->Next = NULL;
    P->Next = q;

    return 0;
}

//      d) pronalazi element u listi (po prezimenu),
Pozicija Trazi(char* prezime, Pozicija P)
{
    while (P != NULL && _stricmp(prezime, P->prezime) != 0)
        P = P->Next;

    return P;
}

// (dio iz e) brisanja) - trazi osobu prije one koja se brise
Pozicija TraziP(char* prezime, Pozicija P)
{
    while (P->Next != NULL &&
        _stricmp(P->Next->prezime, prezime) != 0)
        P = P->Next;

    if (P->Next != NULL)
        return P;

    return NULL;
}

//      e) briše određeni element iz liste.
int Brisi(char* prezime, Pozicija P)
{
    Pozicija prev;

    prev = TraziP(prezime, P);

    if (prev != NULL)
    {
        P = prev->Next;
        prev->Next = P->Next;
        free(P);
    }
    else
        printf("Osoba nije pronadjena.\n");

    return 0;
}