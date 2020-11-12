#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>


bool v(FILE **zaznamyText){
    *zaznamyText = fopen("pacienti.txt", "r");      /*otvori sa subor*/
    if (*zaznamyText == NULL) {
        printf("Neotvoreny subor");
        return false;
    }
    else{
        char *lineBuffer = (char *)malloc(sizeof(char) * 50);
        int *nespravneIndexy=calloc(1,sizeof(int));
        int pocetIndexov=1;                                         /*inicializuju sa tu premenne potrebne k praci*/
        int iPolozka=1;
        char *stroll;
        long long int rCisloInt;

        do {                                                        /*v tomto do while sa kontroluje spravnost suboru*/
            fgets(lineBuffer, 50, *zaznamyText);
            if (strlen(lineBuffer) < 50) {
                for (int i = 0; i < strlen(lineBuffer); ++i) {
                    if (!((65 <= lineBuffer[i] && lineBuffer[i] <= 90) ||
                          (97 <= lineBuffer[i] && lineBuffer[i] <= 122) || (lineBuffer[i] == 32) ||
                          (lineBuffer[i] == 10))) {
                        nespravneIndexy[pocetIndexov - 1] = iPolozka;
                    }
                }
            } else nespravneIndexy[pocetIndexov - 1] = iPolozka;
            if (nespravneIndexy[pocetIndexov - 1] < 0)nespravneIndexy[pocetIndexov - 1] = 0;
            iPolozka++;
            pocetIndexov++;
            nespravneIndexy = realloc(nespravneIndexy, sizeof(int) * pocetIndexov);

            fgets(lineBuffer, 50, *zaznamyText);
            if (strlen(lineBuffer) == 11) {
                lineBuffer[strlen(lineBuffer) - 1] = '\0';
                rCisloInt = strtoll(lineBuffer, &stroll, 10);
                if (rCisloInt % 11 != 0) {
                    nespravneIndexy[pocetIndexov - 1] = iPolozka;
                }
            } else nespravneIndexy[pocetIndexov - 1] = iPolozka;
            if (nespravneIndexy[pocetIndexov - 1] < 0)nespravneIndexy[pocetIndexov - 1] = 0;
            iPolozka++;
            pocetIndexov++;
            nespravneIndexy = realloc(nespravneIndexy, sizeof(int) * pocetIndexov);

            fgets(lineBuffer, 50, *zaznamyText);
            if (strlen(lineBuffer) <= 4) {
                if (65 <= lineBuffer[0] && lineBuffer[0] <= 90) {
                    if (48 <= lineBuffer[1] && lineBuffer[1] <= 57) {
                        if ((lineBuffer[2] != '\0') && (48 < lineBuffer[2] || lineBuffer[2] > 57)) {
                            nespravneIndexy[pocetIndexov - 1] = iPolozka;
                        }
                    } else nespravneIndexy[pocetIndexov - 1] = iPolozka;
                } else nespravneIndexy[pocetIndexov - 1] = iPolozka;
            } else nespravneIndexy[pocetIndexov - 1] = iPolozka;
            if (nespravneIndexy[pocetIndexov - 1] < 0)nespravneIndexy[pocetIndexov - 1] = 0;
            iPolozka++;
            pocetIndexov++;
            nespravneIndexy = realloc(nespravneIndexy, sizeof(int) * pocetIndexov);

            fgets(lineBuffer, 50, *zaznamyText);
            if (strlen(lineBuffer) > 50) {
                nespravneIndexy[pocetIndexov - 1] = iPolozka;
            }
            if (nespravneIndexy[pocetIndexov - 1] < 0)nespravneIndexy[pocetIndexov - 1] = 0;
            iPolozka++;
            pocetIndexov++;
            nespravneIndexy = realloc(nespravneIndexy, sizeof(int) * pocetIndexov);

            float vysledok;
            fgets(lineBuffer, 50, *zaznamyText);
            vysledok = atof(lineBuffer);
            if ((vysledok < 0) || (vysledok > 1000)) {
                nespravneIndexy[pocetIndexov - 1] = iPolozka;
            }
            if (nespravneIndexy[pocetIndexov - 1] < 0)nespravneIndexy[pocetIndexov - 1] = 0;
            iPolozka++;
            pocetIndexov++;
            nespravneIndexy = realloc(nespravneIndexy, sizeof(int) * pocetIndexov);

            fgets(lineBuffer, 50, *zaznamyText);
            rCisloInt = atol(lineBuffer);
            if (!(rCisloInt < 0)) {
                if ((lineBuffer[4] == 48) || (lineBuffer[4] == 49)) {
                    if ((lineBuffer[5] >= 48) || (lineBuffer[5] <= 57)) {
                        if ((lineBuffer[6] <= 51) && (lineBuffer[6] >= 48)) {
                            if ((lineBuffer[7] <= 48) && (lineBuffer[7] >= 57)) {
                                nespravneIndexy[pocetIndexov - 1] = iPolozka;
                            }
                        } else nespravneIndexy[pocetIndexov - 1] = iPolozka;
                    } else nespravneIndexy[pocetIndexov - 1] = iPolozka;
                } else nespravneIndexy[pocetIndexov - 1] = iPolozka;
            } else nespravneIndexy[pocetIndexov - 1] = iPolozka;
            if (nespravneIndexy[pocetIndexov - 1] < 0)nespravneIndexy[pocetIndexov - 1] = 0;

            bool spravne = true;
            for (int i = 0; i < iPolozka; ++i) {
                if (nespravneIndexy[i] != 0) {
                    if (nespravneIndexy[i] == 1) {
                        printf("Nespravne zadany vstup: Meno\n");
                        spravne = false;
                    }
                    if (nespravneIndexy[i] == 2) {
                        printf("Nespravne zadany vstup: Rodne cislo\n");
                        spravne = false;
                    }
                    if (nespravneIndexy[i] == 3) {
                        printf("Nespravne zadany vstup: Diagnoza\n");
                        spravne = false;
                    }
                    if (nespravneIndexy[i] == 4) {
                        printf("Nespravne zadany vstup: Vysetrenie\n");
                        spravne = false;
                    }
                    if (nespravneIndexy[i] == 5) {
                        printf("Nespravne zadany vstup: Vysledok\n");
                        spravne = false;
                    }
                    if (nespravneIndexy[i] == 6) {
                        printf("Nespravne zadany vstup: Datum\n");
                        spravne = false;
                    }
                }
            }
            if (!spravne) {                 /*ak spravne je false to znamena ze nejaky prvok bol nespravny a returne z funkcie*/
                return false;
            }
        }while (fgets(lineBuffer, 50, *zaznamyText)!=NULL);


        rewind(*zaznamyText);
        while (fgets(lineBuffer,20,*zaznamyText)!=NULL){                /*v tomto while sa vypisu zaznamy do konzoly*/
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
    char *strol;                                                   /*inicializuju sa premenne*/
    *diagnozy = calloc(1,sizeof(char*));
    int sizeOfDiagnozy = 1;
    (*diagnozy)[0] = calloc(3,sizeof(char));

    printf("nacitajte datum\n");
    scanf("%lld",&datumNacitNeskor);

    do {                                                /*v tomto do while sa ziskavaju riadku zo suboru*/
        for (int i = 0; i < 2; ++i) {                   /* v tomto fore sa ziskaju 2 riadky meno a rodne cislo ktore nepotrebujeme*/
            fgets(line, 20, *zaznamyText);
        }
        fgets(line, 20, *zaznamyText);              /* tu sa precita diagnoza zo suboru, odstrihne sa z konca znak newline a zapise sa do pola diagnoz*/
        strcpy((*diagnozy)[sizeOfDiagnozy-1],line);
        *diagnozy = realloc(*diagnozy,sizeof(char*)*(sizeOfDiagnozy+1));
        (*diagnozy)[sizeOfDiagnozy] = calloc(3,sizeof(char));
        sizeOfDiagnozy++;
        for (int i = 0; i < 3; ++i) {
            fgets(line, 20, *zaznamyText);          /*ziskaju sa 3 riadky vysetrenie, vyseldok a datum, posledny ziskany riadok datum potrebujeme*/
        }
        line[(int )strlen(line)-1]="\0";                        /*odstrihne sa znak newline a prepise sa string do long intu datumu*/
        datum=strtoll(line,&strol,10);
    }
    while ((datum < datumNacitNeskor) && (fgets(line, 20, *zaznamyText) != NULL));

    int pocetNajvecsi =1;
    int pocet=1;
    int indexNaj=0;
    for (int i = 0; i < sizeOfDiagnozy-1; ++i) {                /*skotroluje sa kolko krat sa v riadku nachadza kazda diagnoza a ta s najvecsim poctom sa vypise*/
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
        return;
    }
    else{
        rewind(*zaznamyText);
    }
    if (jeAlokovane){           /*ak jeAlokovane je true dealokuju sa polia*/
        free(*mena);
        free(*rodneCislo);
        free(*diagnoza);
        free(*vysetrenie);
        free(*vysledok);
        free(*datum);
    }
    *mena = calloc(1,sizeof(char*));            /*tu sa alokuju polia*/
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
            if (*pocetZaznamov!=1){                                                      /*pokial je to prvy krat co sme vosli do do while tak sa nerealokuju polia, dalsie razy uz sa relokuju*/
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
            fgets(line, 20, *zaznamyText);                  /*tu sa cita riadok zo suboru a nasledne sa ulozi do prislusneho pola*/
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
        printf("Nacitajte rodne cislo\n");                  /*nacita sa rodne cislo a sleduje na kotorom indexe zaznamov sa nachadza dane nacitane rodne cislo*/
        scanf("%s",rCislo);                                    /*ak sa najde dane rodne cislo, index na ktorom sa nachadza sa zapise do pola indexov*/
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
            printf("%s : %0.2f \n",(*vysetrenie)[rIndexy[i]],(*vysledok)[rIndexy[i]]);          /*vypisu sa vysetrenia vykonane ktorych indexy zaznamov sa zhoduju s indexami zaznamov rodneho cisla*/
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
    for (int i = 0; i < (*pocetZaznamov); ++i) {                /*nacita sa diagnoza a zistuje sa na ktorom indexe zaznamov sa nachadza dana diagnoza*/
        if (strcmp((*diagnoza)[i],diagnozaNacit)==0){           /*ak sa diagnoza najde zapise sa index do pola indexovs*/
            pocetIndexov++;
            dIndexy[pocetIndexov-1]=i;
            dIndexy=realloc(dIndexy,sizeof(int)*(pocetIndexov+1));
        }
    }
    int *rokyM=calloc(1,sizeof(int));                   /*vytvoria sa polia rokov pre muzov a pre zeny*/
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
    for (int i = 0; i < pocetIndexov; ++i) {                    /*pre muzov*/
        rCisloInString = (*rodneCislo)[dIndexy[i]];
        ciselkoPohlaviaChar[0]=rCisloInString[2];               /*zapise sa rodne cislo do premennej, podla tretie charakteru rodneho cisla zistime pohlavie*/
        ciselkoPohlavia=atoi(ciselkoPohlaviaChar);
        if (ciselkoPohlavia<2){
            rCisloInString[2]='\0';                                /*odstrihneme si treti charakter z rodneho cisla a tie prve dva si premenime na int*/
            rok = atoi(rCisloInString);                             /*zistime ci sa dane cislo nachadza od 20 do 100 ak hej odpocitame ho od 120 a ziskame vec cloveka ak nie odpocitame ho od 20 a ziskame vek sloveka tiez*/
            if ((rok<100)&&(rok>20))rokyM[iM]=120-rok;
            else rokyM[iM]=20-rok;                                  /*potom sa vek zapise do prsilusneho pola podla pohlavia*/
            iM++;
            rokyM=realloc(rokyM,sizeof(int)*(iM+1));
        }
        else{                                                   /*pre zeny*/
            rCisloInString[2]='\0';
            rok = atoi(rCisloInString);
            if ((rok<100)&&(rok>20))rokyZ[iZ]=120-rok;
            else rokyZ[iZ]=20-rok;
            iZ++;
            rokyZ=realloc(rokyZ,sizeof(int)*(iZ+1));
        }
    }
    int *najdene=malloc(sizeof(int)*1);
    int iNajdene = 0;
    int pocet=0;
    bool naslo=false;
    printf("Muzi\n");                               /*pre muzov*/
    for (int i = 0; i < iM; ++i) {                         /*porovnavame jednotlive prvky pola rokov ci sa rovnaku*/
        for (int j = 0; j < iNajdene; ++j) {               /*do pola najdenych sa zapise index cisla ktore uz bolo kontrolovane a potom sa uz nebude pre neho kontrolovat druhy krat*/
            if (najdene[j]==rokyM[i])naslo=true;
        }
        if (!naslo){
            for (int j = 0; j < iM; ++j) {
                if (rokyM[i]==rokyM[j])pocet++;
            }
        }
        if (pocet>0){                                       /*skontroluje sa kolko krat sa nasiel pre dany vek a vypise sa to a nastavia sa pocet na novo*/
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
    printf("Zeny\n");                               /*pre zeny*/
    for (int i = 0; i < iZ; ++i) {
        for (int j = 0; j < iNajdene; ++j) {
            if (najdene[j]==rokyZ[i])naslo=true;
        }
        if (!naslo){
            for (int j = 0; j < iZ; ++j) {
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

    fclose(*zaznamyText);
    fopen("pacienti.txt","w");              /*zavrie sa subor a otvori na vpisovanie*/
    if (*zaznamyText == NULL){
        printf("Neotvorilo temp subor");
    }
    char *rCisloNacit=calloc(10,sizeof(char));
    char *vysetrenieNacit=calloc(3,sizeof(char));
    long int datumNacit;
    float vysledokVysetrenia;
    int spravnyIndex=(-2);
    printf("Nacitajte rodne cislo\n");              /*nacitaju sa premenne*/
    scanf("%s",rCisloNacit);
    printf("Nacitajte vysetrenie\n");
    scanf("%s",vysetrenieNacit);
    printf("Nacitajte datum\n");
    scanf("%ld",&datumNacit);

    for (int i = 0; i < (*pocetZaznamov); ++i) {                    /*zisti sa ci sa tam nachadza dana kombinacia rodneho cisla, vysetrenia a datumu, ak hej zapise sa jeho index zaznamu*/
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

    float vysledokPredosli=(*vysledok)[spravnyIndex];               /*zapise sa nacitany vysledok do pola vysledkov*/
    (*vysledok)[spravnyIndex]=vysledokVysetrenia;

    char *line=calloc(50,sizeof(char));
    char *linePreCisla=calloc(10,sizeof(char));
    char enter='\n';
    for (int i = 0; i < (*pocetZaznamov); ++i) {
        line = (*mena)[i];
        strncat(line,&enter,1);
        fputs(line, *zaznamyText);                                  /* tomto fore sa zoberie riadok z uz existujucich poli, prilepi sa k nemu charakter newline, zapise sa do suboru tento riadok a nasledne sa charakter newline odlepi z riadku*/
        line[strlen(line)-1]='\0';                                  /*to sa deje pre kazde existujuce pole*/
        (*mena)[i]=line;

        line = (*rodneCislo)[i];
        strncat(line,&enter,1);
        fputs(line, *zaznamyText);
        line[strlen(line)-1]='\0';
        (*rodneCislo)[i]=line;

        line = (*diagnoza)[i];
        strncat(line,&enter,1);
        fputs(line, *zaznamyText);
        line[strlen(line)-1]='\0';
        (*diagnoza)[i]=line;

        line = (*vysetrenie)[i];
        strncat(line,&enter,1);
        fputs(line, *zaznamyText);
        line[strlen(line)-1]='\0';
        (*vysetrenie)[i]=line;

        sprintf(linePreCisla,"%g",(*vysledok)[i]);
        strncat(linePreCisla,&enter,1);
        fputs(linePreCisla, *zaznamyText);

        sprintf(linePreCisla,"%ld",(*datum)[i]);
        strncat(linePreCisla,&enter,1);
        fputs(linePreCisla, *zaznamyText);

        if (i!=(*pocetZaznamov)-1) {
            line = "\n";
            fputs(line, *zaznamyText);
        }
    }
    fclose(*zaznamyText);
    fopen("pacienti.txt","r");               /*zavrie sa subor a otvori sa znova na citanie*/
    free(rCisloNacit);
    free(vysetrenieNacit);
    free(line);
}

void z(char ***mena, char ***vysetrenie, float **vysledok, long int **datum, int *pocetZaznamov, bool *jeAlokovane){
    if (!(*jeAlokovane)){
        printf("Polia nie su vytvorene\n");
        return;
    }

    long int skorsiDatum,neskorsiDatum;
    char *vysetrenieNacit=calloc(50,sizeof(char));                  /*nacitaju sa datumy a skontroluju sa ci nie je skorsi datum za neskorsim*/
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
    char *menoStred=calloc(50,sizeof(char));                /*alokuju sa stringy pre mena pacientov s najviac hodnotami*/
    char *menoNajmenej=calloc(50,sizeof(char));
    float vysledokNajviac=0,vysledokStred=0,vysledokNajmenej=0;
    bool nasielZaznam=false;
    for (int i = 0; i < *pocetZaznamov; ++i) {
        if ( ((*datum)[i]>=skorsiDatum)&&((*datum)[i]<=neskorsiDatum) ){            /*tu sa sleduje ci sa dane vysetrenie rovna s vysetrenim v zazname ak ako*/
            if (strcmp(vysetrenieNacit,(*vysetrenie)[i])==0){                       /*tak sa pozrie sa vysledok na danom indexe zaznamu a porovna sa ci je najvecsi, druhy najvecsi alebo treti najvecsi*/
                if ((*vysledok)[i]>vysledokNajviac){                                /*ako ano zapise sa na prislusne miesta a ostatne sa posunu nizsie*/
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
    }                                                                           /*vypisu sa ti traja pacienti s hodnotami najvyssimi*/
    printf("Traja pacienti s najvyssimi hodnotami %s za obdobie %ld - %ld su: (namerana hodnota v zatvorke)\n",vysetrenieNacit,skorsiDatum,neskorsiDatum);
    printf("%s (%g)\n",menoNajviac,vysledokNajviac);
    if (vysledokStred==0)printf("Druhy zaznam sa nenasiel\n");
    else printf("%s (%g)\n",menoStred,vysledokStred);
    if (vysledokNajmenej==0)printf("Treti zaznam sa nenasiel");
    else printf("%s (%g)",menoNajmenej,vysledokNajmenej);
}

void k(char ***mena, char ***rodneCislo, char ***diagnoza, char ***vysetrenie, float **vysledok, long int **datum, bool *jeAlokovane){
    if (jeAlokovane){
        free(*mena);
        free(*rodneCislo);          /*pozrie sa ci su alokovane ak hej tak sa dealokuju ak nie tak sa len returne funkcia*/
        free(*diagnoza);
        free(*vysetrenie);
        free(*vysledok);
        free(*datum);
    }
    else return;
}



int main(){
    FILE *zaznamyText = NULL;
    char **mena;
    char **rodneCislo;
    char **diagnoza;
    char **vysetrenie;                      /*vytvoria sa polia a sleduje sa ake pismeno bolo nacitane*/
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
            k(&mena,&rodneCislo,&diagnoza,&vysetrenie,&vysledok,&datum,&jeAlokovane);
            break;
        }
    }
    return 0;
}


