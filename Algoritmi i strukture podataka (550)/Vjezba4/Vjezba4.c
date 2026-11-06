#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// VJEZBA 4:
//	Napisati program za zbrajanje i množenje polinoma. 
//  Koeficijenti i eksponenti se čitaju iz datoteke.
//	( Napomena: Eksponenti u datoteci nisu nužno sortirani. )

typedef struct Polinom* listPoli;

struct Polinom {
    int Koef;
    int Pot;
    listPoli Next;
};

int mnozenjePolinoma(listPoli P1, listPoli P2, listPoli Rez);
int zbrajanjePolinoma(listPoli P1, listPoli P2, listPoli Rez);
int ProcitajIzDatoteke(listPoli, char*);
int Ispis(listPoli);
void ObrisiListu(listPoli);


int main()
{
    struct Polinom Head1, Head2, HeadZ;

    Head1.Next = NULL;
    Head2.Next = NULL;
    HeadZ.Next = NULL;

    int odabir = 0;

    do {
        printf("\nOdaberite operaciju:\n");
        printf("0) Exit\n");
        printf("1) Zbrajanje polinoma\n");
        printf("2) Mnozenje polinoma\n");
        printf("Odabir: ");

        scanf("%d", &odabir);

        if (odabir == 1 || odabir == 2)
        {
            ProcitajIzDatoteke(&Head1, "P1.txt");
            ProcitajIzDatoteke(&Head2, "P2.txt");

            printf("\nPrvi polinom:");
            Ispis(&Head1);

            printf("\nDrugi polinom:");
            Ispis(&Head2);

            if (odabir == 1)
            {
                zbrajanjePolinoma(&Head1, &Head2, &HeadZ);

                printf("\nZbroj polinoma:");
                Ispis(&HeadZ);
            }
            else if (odabir == 2) {
                mnozenjePolinoma(&Head1, &Head2, &HeadZ);

                printf("\nProdukt polinoma:");
                Ispis(&HeadZ);
            }

            ObrisiListu(&Head1);
            ObrisiListu(&Head2);
            ObrisiListu(&HeadZ);
        }
        else if (odabir != 0)
        {
            printf("Neispravan odabir!\n");
        }

    } while (odabir != 0);

    return 0;
}

int zbrajanjePolinoma(listPoli P1, listPoli P2, listPoli Rez) {
    listPoli temp = P1->Next;
    while (temp != NULL) {
        listPoli novi = malloc(sizeof(struct Polinom));
        if (novi == NULL) return -1;
        novi->Koef = temp->Koef;
        novi->Pot = temp->Pot;
        novi->Next = Rez->Next;
        Rez->Next = novi;
        temp = temp->Next;
    }

    temp = P2->Next;
    while (temp != NULL) {
        listPoli trazim = Rez->Next;
        while (trazim != NULL && trazim->Pot != temp->Pot)
            trazim = trazim->Next;

        if (trazim != NULL) {
            trazim->Koef += temp->Koef;  
        }
        else {
            listPoli novi = malloc(sizeof(struct Polinom));
            if (novi == NULL) return -1;
            novi->Koef = temp->Koef;
            novi->Pot = temp->Pot;
            novi->Next = Rez->Next;
            Rez->Next = novi;
        }
        temp = temp->Next;
    }

    return 0;
}

int mnozenjePolinoma(listPoli P1, listPoli P2, listPoli Rez) {
    listPoli temp1 = P1->Next;

    while (temp1 != NULL) {
        listPoli temp2 = P2->Next;

        while (temp2 != NULL) {
            int noviKoef = temp1->Koef * temp2->Koef;
            int novaPot = temp1->Pot + temp2->Pot;

            listPoli trazim = Rez->Next;
            listPoli pronadjen = NULL;

            while (trazim != NULL) {
                if (trazim->Pot == novaPot) {
                    pronadjen = trazim;
                    break;
                }
                trazim = trazim->Next;
            }

            if (pronadjen != NULL) {
                pronadjen->Koef += noviKoef;
            }
            else {
                listPoli novi = malloc(sizeof(struct Polinom));
                if (novi == NULL) return -1;

                novi->Koef = noviKoef;
                novi->Pot = novaPot;
                novi->Next = Rez->Next;
                Rez->Next = novi;
            }

            temp2 = temp2->Next;
        }

        temp1 = temp1->Next;
    }

    return 0;
}

int ProcitajIzDatoteke(listPoli P, char* dat)
{
    FILE* fp = fopen(dat, "r");

    if (fp == NULL) {
        printf("Greska pri otvaranju datoteke!\n");
        return -1;
    }

    int koeficijent;
    int potencija;

    while (fscanf(fp, "%d %d", &koeficijent, &potencija) == 2) {
        listPoli q = malloc(sizeof(struct Polinom));

        if (q == NULL) {
            fclose(fp);
            return -1;
        }

        q->Koef = koeficijent;
        q->Pot = potencija;

        q->Next = NULL;

        while (P->Next != NULL)
            P = P->Next;

        P->Next = q;
    }

    fclose(fp);
    return 0;
}

int Ispis(listPoli P)
{
    listPoli temp = P->Next;
    int prvi = 1;

    printf("\nPolinom: ");

    while (temp != NULL)
    {
        if (temp->Koef == 0)
        {
            temp = temp->Next;
            continue;
        }

        if (!prvi)
        {
            if (temp->Koef > 0)
                printf(" + ");
            else
                printf(" - ");
        }
        else if (temp->Koef < 0)
        {
            printf("-");
        }

        if (abs(temp->Koef) != 1 || temp->Pot == 0)
            printf("%d", abs(temp->Koef));

        if (temp->Pot > 0)
        {
            printf("x");

            if (temp->Pot > 1)
                printf("^%d", temp->Pot);
        }

        prvi = 0;
        temp = temp->Next;
    }

    if (prvi)
        printf("0");

    printf("\n");

    return 0;
}

void ObrisiListu(listPoli P)
{
    listPoli temp;

    while (P->Next != NULL)
    {
        temp = P->Next;
        P->Next = temp->Next;
        free(temp);
    }

}