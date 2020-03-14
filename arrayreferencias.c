#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*le proxima palavra */
char* leproxpalavra (FILE *fp){
    char palavra[50];
    fscanf(fp, "%s", palavra);
    return palavra;
}
/*le proximo caracter */
int leprox (FILE* fp){
    int proxvar;
    proxvar = fgetc(fp);
    return proxvar;
}
int main(){
    char xstring[20], ystring[20];
    char novoArquivo[20];
    int ch1, i,a, linha = 0;
    double axis[330], ord[330];
    fpos_t position;
    FILE *fp;
    fp = fopen("Silicio_fabricante.ref", "r");
    FILE *fp2;
    printf("Entre com o nome desejado para o arquivo de saida:\n");
    scanf("%s", novoArquivo);
    fp2 = fopen(novoArquivo, "w");
    if (fp == NULL){
        return -1;
    }
    if (fp2 == NULL){
        printf("entrou");
        return -1;
    }
    while ( strcmp(leproxpalavra(fp), "onda(nm)") ){
        continue;
    }
    fgetpos(fp, &position); /*marcando posicao do pointer do comeco dos dados */
    while ( ( a = leprox(fp)) != EOF){
        if (a == '\n'){
            linha++;
        }
    }
    fsetpos(fp, &position); /*devolvendo posição do pointer do comeco dos dados para comecar armazenamento */
        for(i = 0; i < linha-1; i++){
            fscanf(fp, "%s %s", xstring, ystring);
            axis[i] = atof(xstring);  /*atof eh uma funcao da stdlib que transforma string em double*/
            ord[i] = atof(ystring);
        }
    fclose(fp);
    for (i = 0; i < linha-1; i++){
        fprintf(fp2, "%f %f\n", axis[i], ord[i]);
    }
    fclose(fp2);
return 0;
}
