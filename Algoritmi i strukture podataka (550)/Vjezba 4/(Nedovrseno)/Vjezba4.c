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

int mnozenjePolinoma(listPoli);
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
            else if (odabir == 2)
            {
                // mnozenje
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



int zbrajanjePolinoma(listPoli P1, listPoli P2, listPoli Rez) // TREBA NADORADIT
{
    listPoli temp1 = P1->Next;
    listPoli temp2;
    listPoli novi;

    int suma;
    int pronadjen;

    // Prolazimo kroz prvi polinom
    while (temp1 != NULL)
    {
        suma = temp1->Koef;
        pronadjen = 0;

        temp2 = P2->Next;

        // Trazimo isti eksponent u drugom polinomu
        while (temp2 != NULL)
        {
            if (temp1->Pot == temp2->Pot)
            {
                suma += temp2->Koef;
                pronadjen = 1;
                break;
            }

            temp2 = temp2->Next;
        }

        // Dodajemo rezultat u novu listu
        if (suma != 0)
        {
            novi = malloc(sizeof(struct Polinom));

            if (novi == NULL)
                return -1;

            novi->Koef = suma;
            novi->Pot = temp1->Pot;
            novi->Next = Rez->Next;
            Rez->Next = novi;
        }

        temp1 = temp1->Next;
    }

    // Prolazimo kroz drugi polinom
    // Dodajemo eksponente koji ne postoje u prvom
    temp2 = P2->Next;

    while (temp2 != NULL)
    {
        temp1 = P1->Next;
        pronadjen = 0;

        while (temp1 != NULL)
        {
            if (temp1->Pot == temp2->Pot)
            {
                pronadjen = 1;
                break;
            }

            temp1 = temp1->Next;
        }

        if (!pronadjen && temp2->Koef != 0)
        {
            novi = malloc(sizeof(struct Polinom));

            if (novi == NULL)
                return -1;

            novi->Koef = temp2->Koef;
            novi->Pot = temp2->Pot;
            novi->Next = Rez->Next;
            Rez->Next = novi;
        }

        temp2 = temp2->Next;
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

    printf("\nIspis liste:\n");

    while (temp != NULL) {
        printf("%d %d\n", temp->Koef, temp->Pot);
        temp = temp->Next;
    }

    printf("\nIspis polinoma:\n");

    temp = P->Next;

    if (temp == NULL) {
        printf("0\n");
        return 0;
    }

    int prvi = 1;

    while (temp != NULL) {
        if (temp->Koef == 0) {
            temp = temp->Next;
            continue;
        }

        if (temp->Koef > 0 && !prvi)
            printf(" + ");

        else if (temp->Koef < 0)
            printf(" - ");

        printf("%d", abs(temp->Koef));

        if (temp->Pot > 0){
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