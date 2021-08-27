// funções que cadastram
#include "../header/tipos.h"
#include "../header/prototipos.h"

#include <stdio.h>

int cadastroCliente(CLIENTE* vet_cliente, int* c_cliente, int max_cliente, int* c_filme_cliente){

    int cpf_local;

    if(c_cliente == max_cliente)
        return 1; //numero maximo de clientes atingido
    else {

       do{
            printf("\nCPF: ");
            scanf("%d", &cpf_local);
            if(verificaCliente(cpf_local, vet_cliente, &c_cliente)){
                printf("ERRO: CPF do cliente ja cadastrado");
                continue;
            }
            //se o numero max n foi atingido e o cliente n ta cadastrado
            vet_cliente[(*c_cliente)]->cpf = cpf_local;

            printf("Nome: ");
            scanf(" %[^n]%*c", vet_cliente[(*c_cliente)]->nome);
            printf("Email: ");
            scanf(" %[^n]%*c", vet_cliente[(*c_cliente)]->email);
            printf("Telefone: ");
            scanf(" %[^n]%*c", vet_cliente[(*c_cliente)]->telefone);

            vet_cliente[(*c_cliente)]->estado = ativo;
            c_filme_cliente[(*c_cliente)]=0; // cliente assistiu 0 filmes ao ser cadastrado
            (*c_cliente)++;
            return 0; //cadastrado com sucesso

       }while(1)
        
    }

    scanf(" %[^\n]%*c", vet_cliente[c_cliente].cliente.cliente_CPF.pessoa.nome);


}