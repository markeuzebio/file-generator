#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>

#include "gerar_arquivos_teste.h"

void gerarArquivoTxt(FILE *arq)
{
    Registro reg;
    FILE *aux;

    aux = fopen("registros.txt", "w");

    rewind(arq);

    while(fread(&reg, sizeof(Registro), 1, arq) == 1)
        fprintf(aux, "%-10d\t%-15ld\t%s\n", reg.chave, reg.valor, reg.string);

    fclose(aux);
}

// void printB(FILE *arq)
// {
//     Registro reg;

//     rewind(arq);

//     while(fread(&reg, sizeof(Registro), 1, arq) == 1)
//         printf("%-10d\t%-15ld\t%s\n", reg.chave, reg.valor, reg.string);
// }

Registro* alocarRegistros(long n)
{
    Registro *registros = (Registro*) malloc(n * sizeof(Registro));

    return registros;
}

void liberaRegistros(Registro** registros)
{
    free(*registros);
}

void gerarStringAleatoria(char titulo[TAM_TITULO])
{
    for(int i = 0 ; i < TAM_TITULO - 1 ; i++)
        titulo[i] = caracteres_possiveis[rand() % qtde_caracteres_possiveis];

    titulo[TAM_TITULO - 1] = '\0';
}

void preencheArquivoBinario(FILE* arq, Registro *registros, int n)
{
    int i;

    for(i = 0 ; i < n ; i++)
    {
        if(i != 0 && i % TAM_REGISTRO == 0)
            fwrite(registros, sizeof(Registro), TAM_REGISTRO, arq);

        registros[i % TAM_REGISTRO].chave = i + 1;
        registros[i % TAM_REGISTRO].valor = (long int)rand() << sizeof (long int);
        gerarStringAleatoria(registros[i % TAM_REGISTRO].string);
    }

    fwrite(registros, sizeof(Registro), i % TAM_REGISTRO, arq);
}

int main(int argc, char** argv)
{
    int quantidade_linhas;
    FILE *arquivo_binario;
    Registro *registros;

    if(argc != 2)
    {
        printf("Utilizacao errada do programa! Execute de acordo:\n\n");
        printf("\"%s <quantidade de linhas para o arquivo gerado>\"\n", argv[0]);
        return 1;
    } 
    else if((quantidade_linhas = atoi(argv[1])) == 0)
    {
        printf("O segundo argumento deve ser um valor numerico valido!\n");
        return 1;
    }

    if((registros = alocarRegistros(TAM_REGISTRO)) == NULL)
    {
        printf("Erro na alocacao de registros!\n");
        return 1;
    }

    if((arquivo_binario = fopen("registros.bin", "w+b")) == NULL)
    {
        printf("Erro na abertura do arquivo binario!\n");
        return 1;
    }

    srand(time(NULL));

    preencheArquivoBinario(arquivo_binario, registros, quantidade_linhas);

    // printB(arquivo_binario);

    gerarArquivoTxt(arquivo_binario);

    liberaRegistros(&registros);

    fclose(arquivo_binario);

    return 0;
}