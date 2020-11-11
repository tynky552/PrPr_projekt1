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

void n(char ***mena, char ***rodneCislo, char ***diagnoza, char ***vysetrenie, float **vysledok, long int **datum, FILE **zaznamyText,int *pocetZaznamov,bool *jeAlokovane){
    if (*zaznamyText == NULL) {
        printf("Prikaz v nebol vykonany");
        return;
    }
    else{
        rewind(*zaznamyText);
    }
    if (jeAlokovane){
        free(*mena);
        free(*rodneCislo);
        free(*diagnoza);
        free(*vysetrenie);
        free(*vysledok);
        free(*datum);
    }
    *mena = calloc(1,sizeof(char*));
    (*mena)[0]=calloc(50,sizeof(char));
    *rodneCislo= calloc(1,sizeof(char*));
    (*rodneCislo)[0]=calloc(11,sizeof(char));
    *diagnoza= calloc(1,sizeof(char*));
    (*diagnoza)[0]=calloc(3,sizeof(char));
    *vysetrenie= calloc(1,sizeof(char*));
    (*vysetrenie)[0]=calloc(50,sizeof(char));
    *vysledok= calloc(1,sizeof(float));
    *datum= calloc(1,sizeof(long int));

    *pocetZaznamov=0;
        char *line = calloc(50,sizeof(char));
        char *strol;
        char *strof;
        do {
            (*pocetZaznamov)++;
            if (*pocetZaznamov!=1){
                *mena = realloc(*mena,sizeof(char*)*((*pocetZaznamov)));
                (*mena)[(*pocetZaznamov)-1] = calloc(50,sizeof(char));
                *rodneCislo = realloc(*rodneCislo,sizeof(char*)*(*pocetZaznamov));
                (*rodneCislo)[(*pocetZaznamov)-1] = calloc(11,sizeof(char));
                *diagnoza = realloc(*diagnoza,sizeof(char*)*(*pocetZaznamov));
                (*diagnoza)[(*pocetZaznamov)-1] = calloc(3,sizeof(char));
                *vysetrenie = realloc(*vysetrenie,sizeof(char*)*(*pocetZaznamov));
                (*vysetrenie)[(*pocetZaznamov)-1] = calloc(50,sizeof(char));
                *vysledok = realloc(*vysledok,sizeof(float)*(*pocetZaznamov));
                *datum = realloc(*datum,sizeof(long int)*(*pocetZaznamov));
            }
            fgets(line, 20, *zaznamyText);
            line[(int)strlen(line)-1]='\0';
            strcpy((*mena)[(*pocetZaznamov)-1],line);

            fgets(line, 20, *zaznamyText);
            line[(int )strlen(line)-1]='\0';
            strcpy((*rodneCislo)[(*pocetZaznamov)-1],line);

            fgets(line, 20, *zaznamyText);
            line[(int )strlen(line)-1]='\0';
            strcpy((*diagnoza)[(*pocetZaznamov)-1],line);

            fgets(line, 20, *zaznamyText);
            line[(int )strlen(line)-1]='\0';
            strcpy((*vysetrenie)[(*pocetZaznamov)-1],line);

            fgets(line, 20, *zaznamyText);
            line[(int )strlen(line)-1]='\0';
            (*vysledok)[(*pocetZaznamov)-1]=strtof(line,&strof);

            fgets(line, 20, *zaznamyText);
            line[(int )strlen(line)-1]='\0';
            (*datum)[(*pocetZaznamov)-1]=strtol(line,&strol,10);
        }
        while (fgets(line, 20, *zaznamyText)!=NULL);
        *jeAlokovane=true;

    for (int i = 0; i < *pocetZaznamov; ++i) {
        printf("%s\n",(*mena)[i]);
    }
    for (int i = 0; i < *pocetZaznamov; ++i) {
        printf("%s\n",(*diagnoza)[i]);
    }
    for (int i = 0; i < *pocetZaznamov; ++i) {
        printf("%s\n",(*rodneCislo)[i]);
    }
}

void s(char ***vysetrenie,float **vysledok,char ***rodneCislo,int *pocetZaznamov,bool *jeAlokovane){
    int *rIndexy=calloc(1,sizeof(int));
    int pocetIndexov=0;
    if (!(*jeAlokovane)){
        printf("Polia nie su vytvorene");
        return;
    }
    else{
        char *rCislo=calloc(50,sizeof(char));
        printf("Nacitajte rodne cislo\n");
        scanf("%s",rCislo);
        for (int i = 0; i < (*pocetZaznamov); ++i) {
            if (strcmp((*rodneCislo)[i],rCislo)==0){
                pocetIndexov++;
                rIndexy[pocetIndexov-1]=i;
                rIndexy=realloc(rIndexy,sizeof(int)*(pocetIndexov+1));
            }
        }
        if (pocetIndexov==0){
            printf("Nenaslo sa zadane rodne cislo");
            return;
        }
        printf("Vysledky vysetreni, ktore boli vykonane pacientovi s rodnym cislom %s su nasledovne:\n", rCislo);
        for (int i = 0; i < pocetIndexov; ++i) {
            printf("%s : %0.2f \n",(*vysetrenie)[rIndexy[i]],(*vysledok)[rIndexy[i]]);
        }
    }
}

void h(bool *jeAlokovane,char ***diagnoza,char ***rodneCislo,int *pocetZaznamov){
    if (!(*jeAlokovane)){
        printf("Polia nie su vytvorene\n");
        return ;
    }
    int *dIndexy=calloc(1,sizeof(int));
    int pocetIndexov=0;
    char *stroll;
    char *rCisloInString=calloc(11,sizeof(char));
    char *diagnozaNacit = calloc(3,sizeof(char));
    printf("Nacitajte diagnozu\n");
    scanf("%s",diagnozaNacit);
    for (int i = 0; i < (*pocetZaznamov); ++i) {
        if (strcmp((*diagnoza)[i],diagnozaNacit)==0){
            pocetIndexov++;
            dIndexy[pocetIndexov-1]=i;
            dIndexy=realloc(dIndexy,sizeof(int)*(pocetIndexov+1));
        }
    }
    int *rokyM=calloc(1,sizeof(int));
    int *rokyZ=calloc(1,sizeof(int));
    char *ciselkoPohlaviaChar=calloc(1,sizeof(char));
    int ciselkoPohlavia=0;
    int iM=0;
    int iZ=0;
    int rok;
    if (pocetIndexov==0){
        printf("Nenasla sa zadana diagnoza");
        return;
    }
    for (int i = 0; i < pocetIndexov; ++i) {
        rCisloInString = (*rodneCislo)[dIndexy[i]];
        ciselkoPohlaviaChar[0]=rCisloInString[2];
        ciselkoPohlavia=atoi(ciselkoPohlaviaChar);
        if (ciselkoPohlavia<2){
            rCisloInString[2]='\0';
            rok = atoi(rCisloInString);
            if ((rok<100)&&(rok>20))rokyM[iM]=120-rok;
            else rokyM[iM]=20-rok;
            iM++;
            rokyM=realloc(rokyM,sizeof(int)*(iM+1));
        }
        else{
            rCisloInString[2]='\0';
            rok = atoi(rCisloInString);
            if ((rok<100)&&(rok>20))rokyZ[iZ]=120-rok;
            else rokyZ[iZ]=20-rok;
            iZ++;
            rokyZ=realloc(rokyZ,sizeof(int)*(iZ+1));
        }
    }
    for (int i = 0; i < iM; ++i) {
        printf("%d\n",rokyM[i]);
    }
    int *najdene=malloc(sizeof(int)*1);
    int iNajdene = 0;
    int pocet=0;
    bool naslo=false;
    printf("Muzi\n");
    for (int i = 0; i < iM; ++i) {
        for (int j = 0; j < iNajdene; ++j) {
            if (najdene[j]==rokyM[i])naslo=true;
        }
        if (!naslo){
            for (int j = 0; j < iM; ++j) {
                if (rokyM[i]==rokyM[j])pocet++;
            }
        }
        if (pocet>0){
            najdene[iNajdene]=rokyM[i];
            iNajdene++;
            najdene=realloc(najdene,sizeof(int)*(iNajdene+1));
            printf("%d : %d\n",rokyM[i],pocet);
            pocet=0;
        }
        naslo=false;
    }
    free(najdene);
    najdene=malloc(sizeof(int)*1);
    iNajdene = 0;
    pocet=0;
    naslo=false;
    printf("Zeny\n");
    for (int i = 0; i < iZ; ++i) {
        for (int j = 0; j < iNajdene; ++j) {
            if (najdene[j]==rokyZ[i])naslo=true;
        }
        if (!naslo){
            for (int j = 0; j < iM; ++j) {
                if (rokyZ[i]==rokyZ[j])pocet++;
            }
        }
        if (pocet>0){
            najdene[iNajdene]=rokyZ[i];
            iNajdene++;
            najdene=realloc(najdene,sizeof(int)*(iNajdene+1));
            printf("%d : %d\n",rokyZ[i],pocet);
            pocet=0;
        }
        naslo=false;
    }

}

void p(char ***mena, char ***rodneCislo, char ***diagnoza, char ***vysetrenie, float **vysledok, long int **datum, int *pocetZaznamov, bool *jeAlokovane, FILE **zaznamyText){
    if (!(*jeAlokovane)){
        printf("Polia nie su vytvorene\n");
        return;
    }
    FILE *tempFile;
    tempFile = fopen("tempPacienti.txt" , "a");
    if (tempFile == NULL){
        printf("Neotvorilo temp subor");
    }
    char *rCisloNacit=calloc(10,sizeof(char));
    char *vysetrenieNacit=calloc(3,sizeof(char));
    long int datumNacit;
    float vysledokVysetrenia;
    int spravnyIndex=(-2);
    printf("Nacitajte rodne cislo\n");
    scanf("%s",rCisloNacit);
    printf("Nacitajte vysetrenie\n");
    scanf("%s",vysetrenieNacit);
    printf("Nacitajte datum\n");
    scanf("%ld",&datumNacit);

    for (int i = 0; i < (*pocetZaznamov); ++i) {
        if (strcmp(rCisloNacit,(*rodneCislo)[i])==0){
            if (strcmp(vysetrenieNacit,(*vysetrenie)[i])==0){
                if (datumNacit==(*datum)[i]){
                    spravnyIndex=i;
                }
            }
        }
    }
    if (spravnyIndex==(-2)){
        printf("Zaznam so zadanymi udajmi nebol najdeny");
        return;
    }

    printf("Nacitajte vysledok vysetrenia\n");
    scanf("%f",&vysledokVysetrenia);

    float vysledokPredosli=(*vysledok)[spravnyIndex];
    (*vysledok)[spravnyIndex]=vysledokVysetrenia;

    char *line=calloc(50,sizeof(char));
    char enter='\n';
    for (int i = 0; i < (*pocetZaznamov); ++i) {
        line = (*mena)[i];
        strncat(line,&enter,1);
        fputs(line, tempFile);

        line = (*rodneCislo)[i];
        strncat(line,&enter,1);
        fputs(line, tempFile);

        line = (*diagnoza)[i];
        strncat(line,&enter,1);
        fputs(line, tempFile);

        line = (*vysetrenie)[i];
        strncat(line,&enter,1);
        fputs(line, tempFile);

        sprintf(line,"%g",(*vysledok)[i]);
        strncat(line,&enter,1);
        fputs(line, tempFile);

        sprintf(line,"%ld",(*datum)[i]);
        strncat(line,&enter,1);
        fputs(line, tempFile);

        if (i!=(*pocetZaznamov)-1) {
            line = "\n";
            fputs(line, tempFile);
        }
    }
    fclose(tempFile);
    fclose(*zaznamyText);
    remove("pacienti.txt");
    rename("tempPacienti.txt","pacienti.txt");
    printf("Pacientovi s rodnym cislom %s bol zmeneny vysledok vysetrenia %s z povodnej hodnoty %.2f na novu hodnotu %.2f.",(*rodneCislo)[spravnyIndex],vysetrenieNacit,vysledokPredosli,vysledokVysetrenia);
    *zaznamyText=fopen("pacienti.txt","r");
}

void z(char ***mena, char ***vysetrenie, float **vysledok, long int **datum, int *pocetZaznamov, bool *jeAlokovane){
    if (!(*jeAlokovane)){
        printf("Polia nie su vytvorene\n");
        return;
    }

    long int skorsiDatum,neskorsiDatum;
    char *vysetrenieNacit=calloc(50,sizeof(char));
    printf("Nacitajte pociatocny datum\n");
    scanf("%ld",&skorsiDatum);
    printf("Nacitajte koncovy datum\n");
    scanf("%ld",&neskorsiDatum);
    if (skorsiDatum>neskorsiDatum){
        printf("Koncovy datum sa nachadza pred pociatocnym");
        return;
    }
    printf("Nacitajte vysetrenie\n");
    scanf("%s",vysetrenieNacit);

    char *menoNajviac=calloc(50,sizeof(char));
    char *menoStred=calloc(50,sizeof(char));
    char *menoNajmenej=calloc(50,sizeof(char));
    float vysledokNajviac=0,vysledokStred=0,vysledokNajmenej=0;
    bool nasielZaznam=false;
    for (int i = 0; i < *pocetZaznamov; ++i) {
        if ( ((*datum)[i]>=skorsiDatum)&&((*datum)[i]<=neskorsiDatum) ){
            if (strcmp(vysetrenieNacit,(*vysetrenie)[i])==0){
                if ((*vysledok)[i]>vysledokNajviac){
                    vysledokNajmenej=vysledokStred;
                    vysledokStred=vysledokNajviac;
                    vysledokNajviac=(*vysledok)[i];
                    menoNajmenej=menoStred;
                    menoStred=menoNajviac;
                    menoNajviac=(*mena)[i];
                }
                else if ((*vysledok)[i]>vysledokStred){
                    vysledokNajmenej=vysledokStred;
                    vysledokStred=(*vysledok)[i];
                    menoNajmenej=menoStred;
                    menoStred=(*mena)[i];
                }
                else if((*vysledok)[i]>vysledokNajmenej){
                    vysledokNajmenej=(*vysledok)[i];
                    menoNajmenej=(*mena)[i];
                }
                nasielZaznam=true;
            }
        }
        if ((*datum)[i]>neskorsiDatum)break;
    }
    if (!nasielZaznam){
        printf("Nenasiel sa zaznam pre zadane vysetrenie\n");
        return;
    }
    printf("Traja pacienti s najvyssimi hodnotami %s za obdobie %ld - %ld su: (namerana hodnota v zatvorke)\n",vysetrenieNacit,skorsiDatum,neskorsiDatum);
    printf("%s (%g)\n",menoNajviac,vysledokNajviac);
    if (vysledokStred==0)printf("Druhy zaznam sa nenasiel\n");
    else printf("%s (%g)\n",menoStred,vysledokStred);
    if (vysledokNajmenej==0)printf("Treti zaznam sa nenasiel");
    else printf("%s (%g)",menoNajmenej,vysledokNajmenej);
}



int main(){
    FILE *zaznamyText = NULL;
    char **mena;
    char **rodneCislo;
    char **diagnoza;
    char **vysetrenie;
    float *vysledok;
    long int *datum;
    int pocetZaznamov;
    bool jeAlokovane=false;
    while (true){
        char vstup;
        printf("\nNacitajte prikaz\n");
        scanf("%c",&vstup);
        if (vstup=='v'){
            if (v(&zaznamyText)==false)break;
        }
        if (vstup=='o'){
            o(&diagnoza,&zaznamyText);
        }
        if (vstup=='n'){
            n(&mena,&rodneCislo,&diagnoza,&vysetrenie,&vysledok,&datum,&zaznamyText,&pocetZaznamov,&jeAlokovane);
        }
        if (vstup=='s'){
            s(&vysetrenie,&vysledok,&rodneCislo,&pocetZaznamov,&jeAlokovane);
        }
        if (vstup=='h'){
            h(&jeAlokovane,&diagnoza,&rodneCislo,&pocetZaznamov);
        }
        if (vstup=='p'){
            p(&mena, &rodneCislo, &diagnoza, &vysetrenie, &vysledok, &datum, &pocetZaznamov, &jeAlokovane, &zaznamyText);
        }
        if (vstup=='z'){
            z(&mena, &vysetrenie, &vysledok, &datum, &pocetZaznamov, &jeAlokovane);
        }
        if (vstup=='k'){
            break;
        }
    }
    return 0;
}


