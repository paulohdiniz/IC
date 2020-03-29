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

int menorque(double valor, double *vector){
    int i = 0;
    while(vector[i] < valor){
        i++;
    }
    return i-1;
}
int main(){
    char novoArquivo[30], xstring[30], ystring[30];
    double *abs1, *ord1, *abs2, *ord2, *abs3, *ord3, *Potencia, *absinterpolado, *responsividade;
    int i = 0, pontos1, pontos2, pontos3, indice;
    FILE *fp, *fp2, *fp3, *fp4;
    fp = fopen("Silicio_fabricante.ref", "r");
    fp2 = fopen("thales_silicio_med1_141119.med", "r");
    fp3 = fopen("thales_3950_mesa1_141119.med", "r");
    printf("Entre com o nome desejado para o arquivo de saida:\n");
    scanf("%s", novoArquivo);
    fp4 = fopen(novoArquivo, "w");
    if (fp == NULL) return -1;
    if (fp2 == NULL) return -1;
    if (fp3 == NULL) return -1;
    if (fp4 == NULL) return -1;
    /*arquivo 1 = referencia de fábrica (silício ou MCT)*/
    pontos1 = linhasArquivo(fp);
    abs1 = (double*)malloc(sizeof(double)*pontos1);
    ord1 = (double*)malloc(sizeof(double)*pontos1);
    for(i = 0; i < pontos1-1; i++){
        fscanf(fp, "%s %s", xstring, ystring);
        abs1[i] = atof(xstring);  /*atof eh uma funcao da stdlib que transforma string em double*/
        ord1[i] = atof(ystring);
    }
    /*arquivo 2 = calibração (silicio ou MCT)*/
    pontos2 = linhasArquivo(fp2);
    abs2 = (double*)malloc(sizeof(double)*pontos2);
    ord2 = (double*)malloc(sizeof(double)*pontos2);
    for(i = 0; i < pontos2-1; i++){
        fscanf(fp2, "%s %s", xstring, ystring);
        abs2[i] = atof(xstring);  /*atof eh uma funcao da stdlib que transforma string em double*/
        ord2[i] = atof(ystring);
    }
    /*arquivo 3 = nossa mostra*/
    pontos3 = linhasArquivo(fp3);
    abs3 = (double*)malloc(sizeof(double)*pontos2);
    ord3 = (double*)malloc(sizeof(double)*pontos2);  /*colocou-se pontos2 pq a referencia que é limitadora */
    for(i = 0; i < pontos2-1; i++){
        fscanf(fp3, "%s %s", xstring, ystring);
        abs3[i] = atof(xstring);  /*atof eh uma funcao da stdlib que transforma string em double*/
        ord3[i] = atof(ystring);
    }
    /* */
    Potencia = (double*)malloc(sizeof(double)*pontos2);
    absinterpolado = (double*)malloc(sizeof(double)*pontos2);
    for(i = 0; i < pontos2-1; i++){
        indice = menorque(ord2[i], ord1);
        absinterpolado[i] = (ord2[i]*(abs1[indice + 1] - abs1[indice]) + abs1[indice]*ord1[indice + 1] - ord1[indice]*abs1[indice+1])
            /(ord1[indice + 1] - ord1[indice]);
        printf("%f %f %d\n", ord2[54], ord1[174], menorque(ord2[54], ord1));
        Potencia[i] = abs2[i]/absinterpolado[i];
    }
    responsividade = (double*)malloc(sizeof(double)*pontos2);
    for(i = 0; i < pontos2-1; i++){
        responsividade[i] = abs3[i]/Potencia[i];
    }
    for (i = 0; i < pontos2-1; i++){
        fprintf(fp4, "%f %f\n", responsividade[i], ord2[i]);
    }
    fclose(fp);
    fclose(fp2);
    fclose(fp3);
    fclose(fp4);
    free(ord1);
    free(abs1);
    free(ord2);
    free(abs2);
    free(ord3);
    free(abs3);
    free(Potencia);
    free(absinterpolado);
    free(responsividade);
return 0;
}


/*Janela pop-up de avisos:

Para a calibração do MCT coloque valores de comprimento de onda(nm) entre 2031 e 15208.
Para a calibração do Sílicio coloque valores de comprimento de onda(nm) entre 204 e 1099.

Para medir sua mostra comece e termine no comprimento de onda IGUAL ao da calibração e mantenha o MESMO PASSO!*/
