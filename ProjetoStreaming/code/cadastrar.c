// funções que cadastram
#include "../header/tipos.h"
#include "../header/prototipos.h"

#include <stdio.h>
#include <string.h>

int cadastroCliente(CLIENTE* vet_cliente, int* c_cliente, int max_cliente, int* c_filme_cliente){

    int cpf_local;

    if((*c_cliente) == max_cliente) return 1; //numero maximo de clientes atingido
    
    else {

        printf("\nCPF: ");
        vet_cliente[(*c_cliente)].cpf = validaCpf(vet_cliente,(*c_cliente),"ERRO: CPF do cliente ja cadastrado\n");
        //strcpy(vet_cliente[(*c_cliente)].cpf, cpf_local) //caso CPF for um array de char

        printf("Nome: ");
        //leitura de strings https://www.knowprogram.com/c-programming/read-and-display-the-string-in-c-programming/
        //gets(vet_cliente[(*c_cliente)].nome);
        scanf(" %[^\n]%*c", vet_cliente[(*c_cliente)].nome);
        printf("Email: ");
        scanf(" %[^\n]%*c", vet_cliente[(*c_cliente)].email);
        printf("Telefone: ");
        scanf(" %[^\n]%*c", vet_cliente[(*c_cliente)].telefone);

        vet_cliente[(*c_cliente)].estado = ativo;
        c_filme_cliente[(*c_cliente)]=0; // cliente assistiu 0 filmes ao ser cadastrado
        (*c_cliente)++;
        return 0; //cadastrado com sucesso

    }

}

int cadastroFilme(FILME* vet_filme, int* c_filme, int max_filme){

    int genero_local, classificacao_local;

    if((*c_filme)==max_filme){
        return 1; //numero maximo de filmes atingido
    } else {

        vet_filme[(*c_filme)].codigo = 1001 + (*c_filme);
        printf("\nCodigo do Filme: %d\n", vet_filme[(*c_filme)].codigo);
        printf("Nome: ");
        scanf(" %[^\n]%*c", vet_filme[(*c_filme)].nome);

        printf("Genero: ");
 
        vet_filme[*c_filme].genero = (GENERO)validaEscopo(0,5,"ERRO: Genero invalido\n");
        
        printf("Classificacao: ");

        vet_filme[*c_filme].classificacao = (CLASSIFICACAO)validaEscopo(0,5,"ERRO: Classificao invalida\n");

        (*c_filme)++;
        return 0;
    }

}

int cadastroPlanoBasicao(PLANO_BASICO* plano_basico){

    printf("\nQuantos filmes o usuario pode assistir? ");
    scanf("%d", plano_basico->quantidade_de_filmes);

    printf("Valor Base: ");
    scanf("%f", plano_basico->valor_base);

    printf("Valor Excedente: ");
    scanf("%f", plano_basico->valor_excedente);

    return 0;
}

int cadastroPlanoPremium(PLANO_PREMIUM* plano_premium){

    printf("\nValor Base: ");
    scanf("%f", plano_premium->valor_base);
    return 0;
}

















