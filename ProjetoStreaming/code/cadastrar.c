// funções que cadastram
#include "../header/tipos.h"
#include "../header/prototipos.h"
#include "validar.c"

#include <stdio.h>
#include <string.h>

int cadastroCliente(CLIENTE* vet_cliente, int* c_cliente, int max_cliente, int* c_filme_cliente){

    int cpf_local;

    if((*c_cliente) == max_cliente)
        return 1; //numero maximo de clientes atingido
    else {

       do{
            printf("\nCPF: ");
            scanf("%d", &cpf_local);
            if(verificaCliente(cpf_local, vet_cliente, (*c_cliente))){
                printf("ERRO: CPF do cliente ja cadastrado");
                continue;
            }
            //se o numero max n foi atingido e o cliente n ta cadastrado
            vet_cliente[(*c_cliente)].cpf = cpf_local;
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

       }while(1);
        
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

        do{
            printf("Genero: ");
            scanf(" %d", &genero_local);
                if(genero_local > 6 || genero_local<0){
                    printf("ERRO: Genero invalido\n");
                } else { 
                    break;
                }
        }while(1);

        vet_filme[*c_filme].genero = genero_local;

        do{
        printf("Classificacao: ");
        scanf(" %d", &classificacao_local);
            if(classificacao_local == 0 ||
                classificacao_local == 10 ||
                classificacao_local == 12 ||
                classificacao_local == 14 ||
                classificacao_local == 16 ||
                classificacao_local == 18) //eh 5h da manha e eu n consigo pensar em um jeito emlhor
                {
                    vet_filme[*c_filme].classificacao = classificacao_local;
                    break;
                } else {
                    printf("ERRO: Classificao invalida\n");
                }  
        }while(1);

        (*c_filme)++;
        return 0;
    }

}