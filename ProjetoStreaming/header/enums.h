#ifndef ENUMS_H
#define ENUMS_H

// definição dos enums

typedef enum STATUS{

    inativo=0, ativo

} STATUS;

typedef enum GENERO{

    aventura=0, comedia, drama, terror, acao, romance

} GENERO;

typedef enum CLASSIFICACAO{

    livre=0, proibido_10, proibido_12, proibido_14, proibido_16, proibido_18

} CLASSIFICACAO;

typedef enum PLANO_TIPO{

    basico, premium

} PLANO_TIPO;

typedef enum PAGAMENTO_TIPO{

    debito=0, credito

} PAGAMENTO_TIPO;

#endif