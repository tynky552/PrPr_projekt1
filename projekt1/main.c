#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>


bool v(){
    FILE *zaznamyText;
    zaznamyText = fopen("C:\\Users\\Fimas\\CLionProjects\\projekt1\\pacienti.txt", "r");
    if (zaznamyText == NULL) {
        printf("Neotvoreny subor");
        return false;
    }

    else{
        char *lineBuffer = (char *)malloc(sizeof(char) * 20);
        while (fgets(lineBuffer,20,zaznamyText)!=NULL){
            printf("meno priezvisko: %s",lineBuffer);
            printf("rodne cislo: %s",fgets(lineBuffer,20,zaznamyText));
            printf("diagnoza: %s",fgets(lineBuffer,20,zaznamyText));
            printf("vysetrenie: %s",fgets(lineBuffer,20,zaznamyText));
            printf("vysledok: %s",fgets(lineBuffer,20,zaznamyText));
            printf("datum: %s",fgets(lineBuffer,20,zaznamyText));
            if(fgets(lineBuffer,20,zaznamyText)!=NULL){
                printf("%s",lineBuffer);
            }
        }
    }
    fclose(zaznamyText);
    return true;
}

void o(){
    FILE *zaznamyText;
    zaznamyText = fopen("C:\\Users\\Fimas\\CLionProjects\\projekt1\\pacienti.txt", "r");
    char *line=(char*) calloc(20, sizeof(char));
    long long int datumNacitNeskor,datumNacitSkor;
    long long int datum;
    char *strol;
    char **diagnozy = calloc(1,sizeof(char*));
    int sizeOfDiagnozy = 1;
    diagnozy[0] = calloc(3,sizeof(char));
    
    printf("nacitajte 2 datumy\n");
    datumNacitNeskor=20200417;
    datumNacitSkor=20190703;

    if (datumNacitNeskor<datumNacitSkor){
        long long int pohar;
        pohar= datumNacitNeskor;
        datumNacitNeskor=datumNacitSkor;
        datumNacitSkor=pohar;
    }

    do {
        for (int i = 0; i < 6; ++i) {
            fgets(line, 20, zaznamyText);
        }
        line[(int )strlen(line)-1]="\0";
        datum=strtoll(line,&strol,10);
        fgets(line, 20, zaznamyText);
    }
    while (datum != datumNacitSkor);
    do {
        for (int i = 0; i < 2; ++i) {
            fgets(line, 20, zaznamyText);
        }
        fgets(line, 20, zaznamyText);
        strcpy(diagnozy[sizeOfDiagnozy-1],line);
        diagnozy = realloc(diagnozy,sizeof(char*)*(sizeOfDiagnozy+1));
        diagnozy[sizeOfDiagnozy] = calloc(3,sizeof(char));
        sizeOfDiagnozy++;
        for (int i = 0; i < 3; ++i) {
            fgets(line, 20, zaznamyText);
        }
        line[(int )strlen(line)-1]="\0";
        datum=strtoll(line,&strol,10);
    }
    while ((datum < datumNacitNeskor) && (fgets(line, 20, zaznamyText) != NULL));

    for (int i = 0; i < sizeOfDiagnozy-1; ++i) {
        printf("%s",diagnozy[i]);
    }

}

int main(){
    while (true){
        char vstup;
        scanf("%c\n",&vstup);
        if (vstup=='v'){
            if (v()==false)break;
        }
        if (vstup=='o'){
            o();
        }
        if (vstup=='k'){
            break;
        }
    }
    return 0;
}


