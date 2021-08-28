// funções que listam
#include "../header/tipos.h"
#include "../header/prototipos.h"


#include <stdio.h>
#include <string.h>

void imprimeCliente(CLIENTE* vet_cliente, int c_cliente){

    int cpf_local, existe, i;

    if(c_cliente==0){
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
