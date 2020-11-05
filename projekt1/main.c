#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>


bool v(FILE **zaznamyText){
    *zaznamyText = fopen("pacienti.txt", "r");
    if (*zaznamyText == NULL) {
        printf("Neotvoreny subor");
        return false;
    }

    else{
        char *lineBuffer = (char *)malloc(sizeof(char) * 20);
        while (fgets(lineBuffer,20,*zaznamyText)!=NULL){
            printf("meno priezvisko: %s",lineBuffer);
            printf("rodne cislo: %s",fgets(lineBuffer,20,*zaznamyText));
            printf("diagnoza: %s",fgets(lineBuffer,20,*zaznamyText));
            printf("vysetrenie: %s",fgets(lineBuffer,20,*zaznamyText));
            printf("vysledok: %s",fgets(lineBuffer,20,*zaznamyText));
            printf("datum: %s",fgets(lineBuffer,20,*zaznamyText));
            if(fgets(lineBuffer,20,*zaznamyText)!=NULL){
                printf("%s",lineBuffer);
            }
        }
    }
    return true;
}

void o(char ***diagnozy,FILE **zaznamyText){
    if (*zaznamyText==NULL){
        *zaznamyText = fopen("pacienti.txt", "r");
    }
    else{
        rewind(*zaznamyText);
    }
    char *line=(char*) calloc(20, sizeof(char));
    long long int datumNacitNeskor,datumNacitSkor;
    long long int datum;
    char *strol;
    *diagnozy = calloc(1,sizeof(char*));
    int sizeOfDiagnozy = 1;
    (*diagnozy)[0] = calloc(3,sizeof(char));

    printf("nacitajte datum\n");
    scanf("%lld",&datumNacitNeskor);

    do {
        for (int i = 0; i < 2; ++i) {
            fgets(line, 20, *zaznamyText);
        }
        fgets(line, 20, *zaznamyText);
        strcpy((*diagnozy)[sizeOfDiagnozy-1],line);
        *diagnozy = realloc(*diagnozy,sizeof(char*)*(sizeOfDiagnozy+1));
        (*diagnozy)[sizeOfDiagnozy] = calloc(3,sizeof(char));
        sizeOfDiagnozy++;
        for (int i = 0; i < 3; ++i) {
            fgets(line, 20, *zaznamyText);
        }
        line[(int )strlen(line)-1]="\0";
        datum=strtoll(line,&strol,10);
    }
    while ((datum < datumNacitNeskor) && (fgets(line, 20, *zaznamyText) != NULL));

    int pocetNajvecsi =1;
    int pocet=1;
    int indexNaj=0;
    for (int i = 0; i < sizeOfDiagnozy-1; ++i) {
        for (int j = 0; j < sizeOfDiagnozy-1; ++j) {
            if (strcmp((*diagnozy)[i],(*diagnozy)[j])==0){
                pocet++;
            }
        }
        if (pocetNajvecsi<pocet){
            pocetNajvecsi=pocet;
            indexNaj=i;
        }
        pocet=1;
    }
    printf("Najcastejšie vysetrovana diagnoza do %lld je %s.",datumNacitNeskor,(*diagnozy)[indexNaj]);
}

void n(char ***mena, long long int **rodneCislo, char ***diagnoza, char ***vysetrenie, float **vysledok, long int **datum, FILE **zaznamyText){
    if (*zaznamyText == NULL) {
        printf("Prikaz v nebol vykonany");
        return;
    }
    else{
        rewind(*zaznamyText);
    }
    if (*mena!=0x45){
        free(*mena);
        free(*rodneCislo);
        free(*diagnoza);
        free(*vysetrenie);
        free(*vysledok);
        free(*datum);
    }
    *mena = calloc(1,sizeof(char*));
    (*mena)[0]=calloc(50,sizeof(char));
    *rodneCislo= calloc(1,sizeof(long long int));
    *diagnoza= calloc(1,sizeof(char*));
    (*diagnoza)[0]=calloc(3,sizeof(char));
    *vysetrenie= calloc(1,sizeof(char*));
    (*vysetrenie)[0]=calloc(50,sizeof(char));
    *vysledok= calloc(1,sizeof(float));
    *datum= calloc(1,sizeof(long int));

    int pocetZaznamov=0;
        char *line = calloc(50,sizeof(char));
        char *strol;
        char *strof;
        do {
            pocetZaznamov++;
            if (pocetZaznamov!=1){
                *mena = realloc(*mena,sizeof(char*)*(pocetZaznamov));
                (*mena)[pocetZaznamov-1] = calloc(50,sizeof(char));
                *rodneCislo = realloc(*rodneCislo,sizeof(long long int)*(pocetZaznamov));
                *diagnoza = realloc(*diagnoza,sizeof(char*)*(pocetZaznamov));
                (*diagnoza)[pocetZaznamov-1] = calloc(3,sizeof(char));
                *vysetrenie = realloc(*vysetrenie,sizeof(char*)*(pocetZaznamov));
                (*vysetrenie)[pocetZaznamov-1] = calloc(50,sizeof(char));
                *vysledok = realloc(*vysledok,sizeof(float)*(pocetZaznamov));
                *datum = realloc(*datum,sizeof(long int)*(pocetZaznamov));
            }
            fgets(line, 20, *zaznamyText);
            line[(int )strlen(line)-1]="\0";
            strcpy((*mena)[pocetZaznamov-1],line);

            fgets(line, 20, *zaznamyText);
            line[(int )strlen(line)-1]="\0";
            (*rodneCislo)[pocetZaznamov-1]=strtoll(line,&strol,10);

            fgets(line, 20, *zaznamyText);
            line[(int )strlen(line)-1]="\0";
            strcpy((*diagnoza)[pocetZaznamov-1],line);

            fgets(line, 20, *zaznamyText);
            line[(int )strlen(line)-1]="\0";
            strcpy((*vysetrenie)[pocetZaznamov-1],line);

            fgets(line, 20, *zaznamyText);
            line[(int )strlen(line)-1]="\0";
            (*vysledok)[pocetZaznamov-1]=strtof(line,&strof);

            fgets(line, 20, *zaznamyText);
            line[(int )strlen(line)-1]="\0";
            (*datum)[pocetZaznamov-1]=strtol(line,&strol,10);
        }
        while (fgets(line, 20, *zaznamyText)!=NULL);
    for (int i = 0; i < pocetZaznamov; ++i) {
        printf("%s\n",(*mena)[i]);
    }
    for (int i = 0; i < pocetZaznamov; ++i) {
        printf("%lld\n",(*rodneCislo)[i]);
    }
    for (int i = 0; i < pocetZaznamov; ++i) {
        printf("%s\n",(*diagnoza)[i]);
    }
    for (int i = 0; i < pocetZaznamov; ++i) {
        printf("%s\n",(*vysetrenie)[i]);
    }
    for (int i = 0; i < pocetZaznamov; ++i) {
        printf("%f\n",(*vysledok)[i]);
    }
    for (int i = 0; i < pocetZaznamov; ++i) {
        printf("%ld\n",(*datum)[i]);
    }

}




int main(){
    FILE *zaznamyText = NULL;
    char **mena;
    long long int *rodneCislo;
    char **diagnoza;
    char **vysetrenie;
    float *vysledok;
    long int *datum;
    while (true){
        char vstup;
        scanf("%c",&vstup);
        if (vstup=='v'){
            if (v(&zaznamyText)==false)break;
        }
        if (vstup=='o'){
            o(&diagnoza,&zaznamyText);
        }
        if (vstup=='n'){
            n(&mena,&rodneCislo,&diagnoza,&vysetrenie,&vysledok,&datum,&zaznamyText);
        }
        if (vstup=='k'){
            break;
        }
    }
    return 0;
}


