#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>

#define IN "beh.txt"
#define OUT "vysledkova_listina.txt"
#define BUFSIZE 150
#define DELIMITERS ";:."

typedef struct DATE
{
    int den;
    int mesic;
    int rok;
} DATE;


typedef struct CAS
{
    int hodiny;
    int minuty;
    int sekundy;
} CAS;

typedef struct ZAVODNIK
{
    int cislo;
    char prijmeni[25];
    char jmeno[20];
    struct DATE narozeni;
    char narodnost[5];
    char klub[35];
    struct CAS cas;
} ZAVODNIK;

int timeToSec(int hours, int minutes, int seconds)
{
    return hours * 3600 + minutes * 60 + seconds;
}

void secToTime(int seconds, char *buf)
{
    sprintf(buf, "%02d:%02d:%02d", seconds / 3600, (seconds - (seconds / 3600) * 3600) / 60, seconds % 60);
}

void swap(ZAVODNIK *x, ZAVODNIK *y)
{
    ZAVODNIK pom = *x;
    *x = *y;
    *y = pom;
}

void bblSort(ZAVODNIK *zav, int pocet)
{
    for (int i = 0; i < pocet; i++)
    {
        for (int j = 0; j < pocet - i - 1; j++)
        {
            if (timeToSec(zav[j].cas.hodiny, zav[j].cas.minuty, zav[j].cas.sekundy) > timeToSec(zav[j + 1].cas.hodiny, zav[j + 1].cas.minuty, zav[j + 1].cas.sekundy))
            {
                swap(&zav[j], &zav[j + 1]);
            }
        }
    }
}

int readfile(ZAVODNIK *zav)
{
    FILE *fr;
    char buffer[BUFSIZE];
    char *data;
    int pocet = 0;
    int sloupec;

    if ((fr = fopen(IN, "r")) == NULL)
    {
        printf("There was an error opening file %s.", IN);
        return EXIT_FAILURE;
    }

    while (fgets(buffer, BUFSIZE, fr) != NULL)
    {
        if (pocet != 0)
        {
            data = strtok(buffer, DELIMITERS);
            sloupec = 0;
            while (data != NULL)
            {
                sloupec++;
                switch (sloupec)
                {
                case 1:
                    zav[pocet - 1].cislo = atoi(data);
                    break;
                case 2:
                    strcpy(zav[pocet - 1].prijmeni, data);
                    break;
                case 3:
                    strcpy(zav[pocet - 1].jmeno, data);
                    break;
                case 4:
                    zav[pocet - 1].narozeni.den = atoi(data);
                    break;
                case 5:
                    zav[pocet - 1].narozeni.mesic = atoi(data);
                    break;
                case 6:
                    zav[pocet - 1].narozeni.rok = atoi(data);
                    break;
                case 7:
                    strcpy(zav[pocet - 1].narodnost, data);
                    break;
                case 8:
                    strcpy(zav[pocet - 1].klub, data);
                    break;
                case 9:
                    zav[pocet - 1].cas.hodiny = atoi(data);
                    break;
                case 10:
                    zav[pocet - 1].cas.minuty = atoi(data);
                    break;
                case 11:
                    zav[pocet - 1].cas.sekundy = atoi(data);
                    break;
                }
                data = strtok(NULL, DELIMITERS);
            }
        }
        pocet++;
    }
    if (fclose(fr) == EOF)
    {
        printf("There was an error closing file %s.", IN);
    }
    return (pocet - 1);
}

void writeToTerm(ZAVODNIK *zav, int pocet)
{
    int cesi = 0;
    int nejstarsi = 3000;
    char nejstarsijmeno[25];
    char nejstarsijmeno2[25];

    time_t seconds = time(NULL);
    struct tm *current_time = localtime(&seconds);

    for (int i = 0; i < pocet; ++i)
    {
        if (nejstarsi > zav[i].narozeni.rok + 1, NULL, 10)
        {
            nejstarsi = zav[i].narozeni.rok + 1, NULL, 10;
            strcpy(nejstarsijmeno, zav[i].prijmeni);
            strcpy(nejstarsijmeno2, zav[i].jmeno);
        }

        if (!strcmp(zav[i].narodnost, "CZE"))
        {
            cesi++;
        }
    }

    printf("==================================================================================================================\n");
    printf("======================================= S T A R T O V N Í  L I S T I N A =========================================\n");
    printf("==================================================================================================================\n");
    printf("  STARTOVNI CISLO|      PRIJMENI|      JMENO|   NAROZENI|  NARODNOST|                              KLUB|      CAS|\n");
    printf("-----------------------------------------------------------------------------------------------------------------+\n");

    for (int j = 0; j < pocet; j++)
    {
        printf("%17d|%14s|%11s| %02d.%02d.%04d| %10s| %33s| %02d:%02d:%02d|\n",
               zav[j].cislo,
               zav[j].prijmeni,
               zav[j].jmeno,
               zav[j].narozeni.den,
               zav[j].narozeni.mesic,
               zav[j].narozeni.rok,
               zav[j].narodnost,
               zav[j].klub,
               zav[j].cas.hodiny,
               zav[j].cas.minuty,
               zav[j].cas.sekundy
        );
    }
    printf("==================================================================================================================\n");
    printf("\nNa startu je %d zavodniku.\n", pocet);
    printf("Cechu je %d\n", cesi);
    printf("Nejstarsim zavodnikem je %s %s narozen v roce %d. je mu %d let.\n", nejstarsijmeno, nejstarsijmeno2, nejstarsi, (current_time->tm_year + 1900) - nejstarsi);
    printf("Zavodnici dle narodnosti:\n");
    printf("Byl vytvoren soubor %s\n", OUT);
}

void writeToFile(ZAVODNIK *zav, int pocet)
{
    char celkem[10];
    char ztrata[10];
    int prvset = 0;
    FILE *fw;
    if ((fw = fopen(OUT, "w")) == NULL)
    {
        printf("FILE %s couldn't be opened.\n", OUT);
    }

    fprintf(fw, "==================================================================================================================================\n");
    fprintf(fw, "============================================== V Y S L E D K O V A  L I S T I N A ================================================\n");
    fprintf(fw, "==================================================================================================================================\n");
    fprintf(fw, "PORADI|STARTOVNI CISLO|      PRIJMENI|      JMENO|   NAROZENI|   NARODNOST|                              KLUB|      CAS|   ZTRATA|\n");
    fprintf(fw, "---------------------------------------------------------------------------------------------------------------------------------+\n");
    prvset = timeToSec(zav[0].cas.hodiny, zav[0].cas.minuty, zav[0].cas.sekundy);

    for (int i = 0; i < pocet; ++i)
    {
        secToTime(timeToSec(zav[i].cas.hodiny, zav[i].cas.minuty, zav[i].cas.sekundy) - prvset, ztrata);
        fprintf(fw, "%6d|%15d|%14s|%11s| %02d.%02d.%04d| %11s| %33s| %02d:%02d:%02d|%s%s|\n",
                i + 1,
                zav[i].cislo,
                zav[i].prijmeni,
                zav[i].jmeno,
                zav[i].narozeni.den,
                zav[i].narozeni.mesic,
                zav[i].narozeni.rok,
                zav[i].narodnost,
                zav[i].klub,
                zav[i].cas.hodiny,
                zav[i].cas.minuty,
                zav[i].cas.sekundy,
                i == 0 ? " " : "+",
                i == 0 ? "        " : ztrata
            );
    }

    fprintf(fw,"==================================================================================================================================\n");

    if (fclose(fw) == EOF)
    {
        printf("FILE %s couldn't be closed.\n", OUT);
    }
}

int main()
{
    ZAVODNIK zav[BUFSIZE];

    int pocet = 0;

    pocet = readfile(zav);
    writeToTerm(zav, pocet);
    bblSort(zav, pocet);
    writeToFile(zav, pocet);

    return EXIT_SUCCESS;
}