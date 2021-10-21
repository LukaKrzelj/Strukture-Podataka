#include<stdio.h>
#include<stdlib.h>

#define MAX_SIZE (128)
#define MAX_LINE (1024)

typedef struct{
    char ime[MAX_SIZE];
    char prezime[MAX_SIZE];
    double bodovi;
}_student;

int BrojRedakaUDatoteci(char *);
_student* DinamickaAlokacijaMemorije(int , char* );
int ispis(char *);
double MaksimalanBrojBodova(char* );
double RelativanBrojBodova(char* , int );

int main()
{
    ispis("datoteka.txt");
    
    return 0;
}

int BrojRedakaUDatoteci(char *imeDatoteke){
    FILE* datoteka = NULL;
    char buffer[MAX_LINE] = {0};
    int br = 0;

    datoteka = fopen(imeDatoteke, "r");
    if(!datoteka){
        printf("Pogreska!");
        return -1;
    }
    while(!feof(datoteka)){
        fgets(buffer, MAX_LINE, datoteka);
        br++;
    }

    fclose(datoteka);

    return br;
}

_student* DinamickaAlokacijaMemorije(int brojStudenata, char* imeDatoteke){
    FILE* datoteka = NULL;
    _student* studenti = NULL;
    int i = 0;

    studenti = (_student*)malloc(brojStudenata * sizeof(_student));
    datoteka = fopen(imeDatoteke, "r");

    if(!datoteka){
        printf("Pogreska!");
        free(studenti);
        return NULL;
    }
    while(!feof(datoteka)){
        fscanf(datoteka, " %s %s %lf",
        studenti[i].ime,
        studenti[i].prezime,
        &studenti[i].bodovi);
        i++;
    }

    fclose(datoteka);

    return studenti;
}

int ispis(char* imeDatoteke){
    int brojStudenata = 0, i = 0;
    _student* studenti = NULL;
    FILE* datoteka = NULL;

    datoteka = fopen(imeDatoteke, "r");
    brojStudenata = BrojRedakaUDatoteci(imeDatoteke);
    studenti = DinamickaAlokacijaMemorije(brojStudenata, imeDatoteke);

    for(i = 0; i < brojStudenata; i++){
        printf(datoteka, "Ime: %s\nPrezime: %s\nApsolutan broj bodova: %lf\nRelativan broj bodova: %lf",
        studenti[i].ime,
        studenti[i].prezime,
        studenti[i].bodovi,
        RelativanBrojBodova(imeDatoteke, i));
        
    }
}

double MaksimalanBrojBodova(char* imeDatoteke){
    _student* studenti = NULL;
    int brojStudenata = 0, i = 0;
    double max = 0;

    brojStudenata = BrojRedakaUDatoteci(imeDatoteke);
    studenti = DinamickaAlokacijaMemorije(brojStudenata, imeDatoteke);
    max = studenti[0].bodovi;

    for(i = 0; i < brojStudenata; i++){
        if(studenti[i].bodovi >= max)
            max = studenti[i].bodovi;
    }

    return max;
}

double RelativanBrojBodova(char* imeDatoteke, int pozicija){
    _student* studenti = NULL;
    int brojStudenata = 0;
    double relativanBrojBodova = 0, max = 0;

    brojStudenata = BrojRedakaUDatoteci(imeDatoteke);
    studenti = DinamickaAlokacijaMemorije(brojStudenata, imeDatoteke);
    max = MaksimalanBrojBodova(imeDatoteke);

    relativanBrojBodova = studenti[pozicija].bodovi / max * 100;
    return relativanBrojBodova;
}