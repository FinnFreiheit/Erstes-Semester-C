#include <stdio.h>
#include <string.h>
#include <stdlib.h>

//Fritz,Maurer,102347
//0605FRMAU-1717

//Ab,Li,123456
//0202ABLI-1621

//Ki,R,123456
//0102KIR-1621


struct mitarbeiterCode
{

    int anzNachNa; // anz Buchstaben Nachname
    int anzVorNa; //anz Buchstaben Vorname
    char anfangVorNa[3]; // Die Ersten beiden Buchstaben Vorname
    char anfangNachNa[4]; // die Ersten drei Buchstaben Nachname
    int ersteEmplNr; //Die erste Nummer von der EmplNr
    int letzteEmplNr; //Die letzte Nummer EmplNr
    int QuerSummEmplNr; // Quersumme Mitarbeiter Nr
};

struct mitarbeiterInfo //Die Informationen aus der CSV Datei.
{
    char vorname[64];
    int lnVorname; //String Länge Vorname
    char nachname[64];
    int lnNachname; //String Länge Nachname
    long emplNummer;
    long quersummeEmplNummer;
    int ersteNrInfo;
    int letzteNrInfo;
};

int quersumme(int zahl)
{
    if(zahl <= 9) return zahl;
    else return zahl%10 + quersumme(zahl/10);
}

void mitarbeiterCode(char eingabeStringCode[], int groesse, struct mitarbeiterCode *ptrMitarbeiterCode)
{
    //int temp = 0;
    printf("Bitte geben sie den Mitarbeiter Code ein \n");
    scanf("%s", eingabeStringCode);



    //Anzahl Buchstaben Nachname
    ptrMitarbeiterCode->anzNachNa = (((int)eingabeStringCode[0] - 48) * 10);
    ptrMitarbeiterCode->anzNachNa = ptrMitarbeiterCode->anzNachNa + ((int)eingabeStringCode[1] - 48);
    //printf("AnzNachNa %d \n", ptrMitarbeiterCode->anzNachNa);

    //Anzahl Buchstaben Vorname
    ptrMitarbeiterCode->anzVorNa = (((int)eingabeStringCode[2] - 48) * 10);  //Zahl im Char gespeichert also ASKII
    // deswegen - 48
    ptrMitarbeiterCode->anzVorNa = ptrMitarbeiterCode->anzVorNa + ((int)eingabeStringCode[3] - 48);
    //printf("AnzVorNa %d \n", ptrMitarbeiterCode->anzVorNa);

    if (ptrMitarbeiterCode->anzVorNa >= 2)
    {
        ptrMitarbeiterCode->anfangVorNa[0] = eingabeStringCode[4];
        ptrMitarbeiterCode->anfangVorNa[1] = eingabeStringCode[5] + 32;
        ptrMitarbeiterCode->anfangVorNa[2] = '\0';

        if(ptrMitarbeiterCode->anzNachNa >=3)
        {
            ptrMitarbeiterCode->anfangNachNa[0] = eingabeStringCode[6];
            ptrMitarbeiterCode->anfangNachNa[1] = eingabeStringCode[7] + 32;
            ptrMitarbeiterCode->anfangNachNa[2] = eingabeStringCode[8] + 32;
        }else if(ptrMitarbeiterCode->anzNachNa ==2)
        {
            ptrMitarbeiterCode->anfangNachNa[0] = eingabeStringCode[6];
            ptrMitarbeiterCode->anfangNachNa[1] = eingabeStringCode[7] + 32;
            ptrMitarbeiterCode->anfangNachNa[2] = '\0';
        }else if(ptrMitarbeiterCode->anzNachNa ==1)
        {
            ptrMitarbeiterCode->anfangNachNa[0] = eingabeStringCode[6];
            ptrMitarbeiterCode->anfangNachNa[1] = '\0';
            ptrMitarbeiterCode->anfangNachNa[2] = '\0';
        }

        //printf("Vorname Indze %s\n", ptrMitarbeiterCode->anfangVorNa);
        //printf("Nachname Indze %s \n", ptrMitarbeiterCode->anfangNachNa);
    }
    else
    {
        ptrMitarbeiterCode->anfangVorNa[0] = eingabeStringCode[4];
        ptrMitarbeiterCode->anfangVorNa[1] = '\0';
        ptrMitarbeiterCode->anfangVorNa[2] = '\0';

        if(ptrMitarbeiterCode->anzNachNa >=3)
        {
            ptrMitarbeiterCode->anfangNachNa[0] = eingabeStringCode[5];
            ptrMitarbeiterCode->anfangNachNa[1] = eingabeStringCode[6] + 32;
            ptrMitarbeiterCode->anfangNachNa[2] = eingabeStringCode[7] + 32;
        }else if(ptrMitarbeiterCode->anzNachNa ==2)
        {
            ptrMitarbeiterCode->anfangNachNa[0] = eingabeStringCode[5];
            ptrMitarbeiterCode->anfangNachNa[1] = eingabeStringCode[6] + 32;
            ptrMitarbeiterCode->anfangNachNa[2] = '\0';
        }else if(ptrMitarbeiterCode->anzNachNa ==1)
        {
            ptrMitarbeiterCode->anfangNachNa[0] = eingabeStringCode[5];
            ptrMitarbeiterCode->anfangNachNa[1] = '\0';
            ptrMitarbeiterCode->anfangNachNa[2] = '\0';
        }

    }

    //Sucht den '-'
    int count = 0;
    while(eingabeStringCode[count] != '-')
    {
        count++;
    }

    //Erste und Letzte Ziffer der Mitarbeiter Nummer
    ptrMitarbeiterCode->ersteEmplNr = (((int)eingabeStringCode[count + 1] - 48));  //Zahl im Char gespeichert also ASKII deswegen - 48
    //printf("Erste Nr %d \n", ptrMitarbeiterCode->ersteEmplNr);

    ptrMitarbeiterCode->letzteEmplNr = (((int)eingabeStringCode[count + 2] - 48));
    //printf("Letzte Nr %d \n", ptrMitarbeiterCode->letzteEmplNr);

    //Quersumme
    ptrMitarbeiterCode->QuerSummEmplNr = (((int)eingabeStringCode[count + 3] - 48) * 10);  //Zahl im Char gespeichert also ASKII deswegen - 48
    ptrMitarbeiterCode->QuerSummEmplNr = ptrMitarbeiterCode->QuerSummEmplNr + ((int)eingabeStringCode[count + 4] - 48);
    //printf("Quersumme %d \n", ptrMitarbeiterCode->QuerSummEmplNr);

}

int mitarbeiterInfoDatei(FILE *ptr, struct mitarbeiterInfo *infoMitarbeiter)
{
    if(ptr == NULL)
    {
        printf("Nichts gefunden ");
        return 0;
    }

    char stringCsvDatei[70];
    char komma[] =",";
    char* abschnitt;
    char strEmplNr[7];
    char ersteNrTemp;
    char letzteNrTemp;

    fscanf(ptr, "%s", stringCsvDatei);

    //Vorname
    abschnitt = strtok(stringCsvDatei, komma);
    strcpy(infoMitarbeiter->vorname,abschnitt);
    //printf("Abschnitt : %s \n",infoMitarbeiter->vorname);
    infoMitarbeiter->lnVorname = strlen(infoMitarbeiter->vorname);
    //printf("Vorname länge %d \n",infoMitarbeiter->lnVorname);

    //Nachname
    abschnitt = strtok(NULL,komma);

    if(abschnitt != NULL)
    {
        strcpy(infoMitarbeiter->nachname, abschnitt);
        //printf("Abschnitt : %s \n",infoMitarbeiter->nachname);
        infoMitarbeiter->lnNachname = strlen(infoMitarbeiter->nachname);
        //printf("Nachname länge %d \n",infoMitarbeiter->lnNachname);

        //Mitarbeiter Nummer
        abschnitt = strtok(NULL, komma);
        strcpy(strEmplNr, abschnitt);

        ersteNrTemp = strEmplNr[0];
        infoMitarbeiter->ersteNrInfo = (((int) ersteNrTemp - 48));
        //printf("Erste Nummer int = %d \n",infoMitarbeiter->ersteNrInfo);

        letzteNrTemp = strEmplNr[5];
        infoMitarbeiter->letzteNrInfo = (((int) letzteNrTemp - 48));
        //printf("Letzte Nummer int = %d \n",infoMitarbeiter->letzteNrInfo);



        infoMitarbeiter->emplNummer = strtol(strEmplNr, NULL, 10);
        //printf("Employ Nummer: %ld \n",infoMitarbeiter->emplNummer);
        infoMitarbeiter->quersummeEmplNummer = quersumme(infoMitarbeiter->emplNummer);
        //printf("mod 42 : %ld \n",infoMitarbeiter->quersummeEmplNummer);
        return 0;
    }
    else
    {
        printf("Person Nicht gefunden \n");
        return 1;
    }
}

int vergleichCodeMitDatei(struct mitarbeiterInfo * infoMitarbeiter, struct mitarbeiterCode *codeMitarbeiter)
{
    int zaehler = 0;
    int BOOL = 1;

    if(codeMitarbeiter->anzVorNa == infoMitarbeiter->lnVorname)
    {
        //printf("vor anz Passt\n");
        zaehler++;
    } else return 1;

    if (codeMitarbeiter->anzNachNa == infoMitarbeiter->lnNachname)
    {
        //printf("Nach anz Passt\n");
        zaehler++;
    } else return 1;

    if(codeMitarbeiter->anzVorNa >= 2)
    {
        if (strncmp(codeMitarbeiter->anfangVorNa, infoMitarbeiter->vorname, 2) == 0)
        {
            //printf("StringComp Vorname Passt\n");
            zaehler++;
        }
        else return 1;
    }else
    {
        if (strncmp(codeMitarbeiter->anfangVorNa, infoMitarbeiter->vorname, 1) == 0)
        {
            //printf("StringComp Vorname Passt\n");
            zaehler++;
        }
        else return 1;
    }

    if(strncmp(codeMitarbeiter->anfangNachNa, infoMitarbeiter->nachname, 3) == 0)
    {
        zaehler++;
        //printf("StringComp Nachname Passt\n");
    }else return 1;

    if(codeMitarbeiter->ersteEmplNr == infoMitarbeiter->ersteNrInfo)
    {
        zaehler++;
        // printf("Erste Nummer Passt\n");
    }else return 1;

    if(codeMitarbeiter->letzteEmplNr == infoMitarbeiter->letzteNrInfo)
    {
        zaehler++;
        //printf("Letzte Nummer Passt\n");
    }else return 1;

    if (codeMitarbeiter->QuerSummEmplNr == infoMitarbeiter->quersummeEmplNummer)
    {
        zaehler++;
        //printf("Quersumme Passt\n");
    }else return 1;


    if(zaehler == 7) BOOL = 0;
    return BOOL;
}

int main()
{
    int BOOL = 0;
    struct mitarbeiterCode code;
    struct mitarbeiterCode *ptrCode;

    struct mitarbeiterInfo info;
    struct mitarbeiterInfo *ptrInfo;

    char feld[15] = {0} ;
    FILE* fileptr;

    //fileptr = fopen("Mitarbeiterliste.txt","w"); //Textdatei erstellen.
    fileptr = fopen("Mitarbeiterliste.txt","r");


    if(fileptr == NULL)
    {
        printf("Datei kann nicht geöffnet werden");
        return 0;
    }
    else
    {
        ptrCode = &code;
        ptrInfo = &info;

        printf("Wollen sie nach einem Mitarbeiter Suchen ? [j] oder [n] \n");
        char jodern;
        jodern = (char) getchar();
        //printf("die Eingabe war %c \n ", jodern);

        while (jodern == 'j')
        {
            mitarbeiterCode(feld, 14, ptrCode);
            mitarbeiterInfoDatei(fileptr, ptrInfo);


            while (vergleichCodeMitDatei(ptrInfo, ptrCode))
            {
                BOOL = mitarbeiterInfoDatei(fileptr, ptrInfo);
                if (BOOL == 1) break;

            }
            if (BOOL != 1)
                printf("Mitarbeiter: %s, %s \n", ptrInfo->vorname, ptrInfo->nachname);


            fflush(stdin);
            printf("Wollen sie nach einem weiteren Mitarbeiter Suchen ? [j] oder [n] \n");
            jodern = (char) getchar();
        }
    }
    return 0;
}




