#ifndef TIPOS_H
#define TIPOS_H

// definição dos tipos (structs e unions)

#include "enums.h"

// STRUCTS ------------------------------------------------

typedef struct DATA{

    int dia;
    int mes;

} DATA;

typedef struct CLIENTE{

    int cpf; // codigo do cliente // chave de busca
    char nome[50];
    char email[50];
    char telefone[15];
    STATUS estado; 

} CLIENTE;

typedef struct FILME{

    int codigo; // codigo do filme
    char nome[50];
    GENERO genero;
    CLASSIFICACAO classificacao;

} FILME;

typedef struct PLANO_BASICO{

    int quantidade_de_filmes;
    float valor_base;
    float valor_excedente;

} PLANO_BASICO;

typedef struct PLANO_PREMIUM{

    float valor_base;

} PLANO_PREMIUM;

typedef struct DEBITO{

    int agencia;
    int conta;

} DEBITO;

typedef struct CREDITO{

    int numero_do_cartao;

} CREDITO;

// STRUCTS ------------------------------------------------

// UNIONS -------------------------------------------------

// typedef union PLANO{

//     PLANO_BASICO basico;
//     PLANO_PREMIUM premium;

// } PLANO;

typedef union PAGAMENTO{

    DEBITO debito;
    CREDITO credito;

} PAGAMENTO;

// UNIONS -------------------------------------------------

// STRUCTS ------------------------------------------------

typedef struct CONTRATO{

    int cpf; // codigo do cliente
    PLANO_TIPO plano_tipo;
    DATA data_de_contratacao;
    DATA data_de_cancelamento;
    PAGAMENTO pagamento;
    PAGAMENTO_TIPO pagamento_tipo;

} CONTRATO;

typedef struct HISTORICO{

    int codigo; // codigo do filme
    DATA data; // data que o cliente assistiu

} HISTORICO;

// STRUCTS ------------------------------------------------

#endif