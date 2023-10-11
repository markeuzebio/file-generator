#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>

#include "gerar_arquivos_teste.h"

Registro* alocarRegistros(int n)
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

void preencheTxtComRegistros(FILE* arq, int n)
{
    Registro auxiliar;

    for(int i = 0 ; i < n ; i++)
    {
        gerarStringAleatoria(auxiliar.titulo);
        auxiliar.chave = i + 1;
        auxiliar.preco = (2000 + (rand() % 10000 + 1)) / 100.0;

        fprintf(arq, "%-30s\t%-4d\t%-6.2f\n", auxiliar.titulo, auxiliar.chave, auxiliar.preco);
    }
}

// PROPOSITOS DE TESTE
// void printR(Registro *registros, int n)
// {
//     for(int i = 0 ; i < n ; i++)
//         printf("%s\t%-4d\t%-6.2f\n", registros[i].titulo, registros[i].chave, registros[i].preco);
// }

// PROPOSITOS DE TESTE
// void printB(FILE *arq)
// {
//     Registro reg;

//     rewind(arq);

//     while(fread(&reg, sizeof(Registro), 1, arq) == 1)
//         printf("%s\t%-4d\t%-6.2f\n", reg.titulo, reg.chave, reg.preco);
// }

FILE* gerarArquivoBinario(char *nome, Registro *registros, int n)
{
    FILE* arq = fopen(nome, "wb");

    if(arq == NULL)
        return NULL;

    fwrite(registros, sizeof(Registro), n, arq);

    return arq;
}

int main(int argc, char** argv)
{
    FILE *arquivo_texto, *arquivo_binario;
    int quantidade_linhas;

    if(argc != 2)
    {
        printf("Utilizacao errada do programa! Execute de acordo:\n\n");
        printf("\"%s <quantidade de linhas para o arquivo gerado>\"\n", argv[0]);
        return 1;
    }

    if((quantidade_linhas = atoi(argv[1])) == 0)
    {
        printf("O segundo argumento deve ser um valor numerico valido!\n");
        return 1;
    }

    // PROPOSITOS DE TESTE
    // if((registros = alocarRegistros(TAM_PAGINA)) == NULL)
    // {
    //     printf("Algum erro ocorreu na alocacao de registros. Abortando o programa...\n");
    //     return 1;
    // }

    srand(time(NULL));

    if((arquivo_texto = fopen("livros.txt", "w+")) == NULL)
        printf("Algum erro ocorreu na tentativa de criar o arquivo livros.txt\n");

    preencheTxtComRegistros(arquivo_texto, quantidade_linhas);

    // printR(registros, quantidade_linhas);        // PROPOSITOS DE TESTE

    // else if((arquivo_binario = gerarArquivoBinario("livros.bin", registros, quantidade_linhas)) == NULL)
    //     printf("Algum erro ocorreu na tentativa de criar o arquivo livros.bin\n");
    // else
    //     printf("Arquivos \"livros.txt\" e \"livros.bin\" criados com sucesso! Encerrando a execução do programa...\n");

    // printB(arquivo_binario);     // PROPOSITOS DE TESTE
    
    // liberaRegistros(&registros); // PROPOSITOS DE TESTE
    fclose(arquivo_texto);
    // fclose(arquivo_binario);

    return 0;
}