// funções que listam
#include "../header/tipos.h"
#include "../header/prototipos.h"


#include <stdio.h>
#include <string.h>


int listaGenero(FILME* vet_filme, int c_filme){

    int escolha, valida = 0;

    escolha = validaEscopo(0,5, "ERRO: Genero invalido\n");

    for(int c=0; c<c_filme;c++){

        if(vet_filme[c].genero == escolha){

            valida = 1;

            // talvez printar genero e classificação dps, não sei
            printf("Codigo: %d\n", vet_filme[c].codigo);
            printf("Nome: %s\n",vet_filme[c].nome);
            
        }
        
    }

    if(!valida){
        printf("ERRO: Genero nao encontrado\n");
        return 0;
    }

    return 1;
}

int listaClassificacao(FILME* vet_filme, int c_filme){

    int escolha, valida = 0;

    escolha = validaEscopo(0,5, "ERRO: Classificacao invalida\n");

    for(int c=0; c<c_filme;c++){

        if(vet_filme[c].classificacao == escolha){

            valida = 1;

            printf("Codigo: %d\n", vet_filme[c].codigo);
            printf("Nome: %s\n",vet_filme[c].nome);

        }
        
    }

    if(!valida){
        printf("ERRO: Classificacao nao encontrado\n");
        return 0;
    }

    return 1;

}

void imprimeCliente(CLIENTE* vet_cliente, int c_cliente){

    int cpf_local, existe, i;

    if(existeCliente(vet_cliente, c_cliente)){
        printf("ERRO: Nenhum cliente cadastrado no sistema");
        return;
    }

    do{

        printf("\nCPF: ");
        scanf("%d", &cpf_local);

        existe = verificaCliente(cpf_local, vet_cliente, c_cliente);

        if(!existe) {
            printf("ERRO: Cliente nao cadastrado");
            continue;
        }

        if(existe=1){
            for(i=0; i<c_cliente; i++){
                if(cpf_local == vet_cliente[i].cpf){
//                    printf("CPF: %d\n", vet_cliente[i].cpf); 
                    printf("Nome: %s\n", vet_cliente[i].nome); 
                    printf("Email: %s\n", vet_cliente[i].email);
                    printf("Telefone: %s\n", vet_cliente[i].telefone);
                    printf("Status: %d\n", vet_cliente[i].estado);
        
                }
            }
        } 

    }while(existe!=1);
}
