#include <stdio.h>
#include <stdlib.h>
#include <string.h>
/*le proxima palavra */
char* leproxpalavra (FILE *fp){
    char *palavra;
    palavra = (char *)malloc(sizeof(char)*50);
    fscanf(fp, "%s", palavra);
    return palavra;                           /*falta pensar como irei dar o free desse malloc */
}
/*le proximo caracter */
int leprox (FILE* fp){
    int proxvar;
    proxvar = fgetc(fp);
    return proxvar;
}
int linhasArquivo(FILE *fp){
    fpos_t position;
    int linha = 0, a;
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
    return linha;
}
int main(){
    char novoArquivo[20];
    double *axis1, *ord1, *axis2, *ord2, *axis3, *ord3;
    char xstring[20], ystring[20];
    int i = 0, pontos = 0;
    FILE *fp;
    FILE *fp2;
    FILE *fp3;
    fp = fopen("MCT_fabricante.ref", "r");
  /*  printf("Entre com o nome desejado para o arquivo de saida:\n");
    scanf("%s", novoArquivo); */
    fp2 = fopen(novoArquivo, "w");
    if (fp == NULL){
        return -1;
    }
    if (fp2 == NULL){
        return -1;
    }
    pontos = linhasArquivo(fp);
    axis1 = (double*)malloc(sizeof(double)*pontos);
    ord1 = (double*)malloc(sizeof(double)*pontos);
    for(i = 0; i < pontos-1; i++){
        fscanf(fp, "%s %s", xstring, ystring);
        axis1[i] = atof(xstring);  /*atof eh uma funcao da stdlib que transforma string em double*/
        ord1[i] = atof(ystring);
}
    for (i = 0; i < pontos-1; i++){
        fprintf(fp2, "%f %f\n", axis1[i], ord1[i]);
    }
    fclose(fp2);
    fclose(fp);
    free(ord1);
    free(axis1);
return 0;
}
