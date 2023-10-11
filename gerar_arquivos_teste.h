#ifndef __TESTE__
#define __TESTE__

// 512MB alocados na memoria RAM por vez
#define TAM_TITULO 5001
#define MAX_TAM_CHAVE 1000


typedef struct {
    char titulo[TAM_TITULO];
    int chave;
    float preco;
} Registro;

const long TAM_PAGINA =  (512 * 1024 * 1024) / sizeof(Registro);

char caracteres_possiveis [] = {
    'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z',
    'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z',
    '1', '2', '3', '4', '5', '6', '7', '8', '9',
    ' '
};

int qtde_caracteres_possiveis = sizeof(caracteres_possiveis);

#endif