// funções que validam
#include "../header/tipos.h"

#include <stdio.h>

int verificaCliente(int cpf_local, CLIENTE* vet_cliente, int c_cliente){

    int i;

    for(i=0; i<c_cliente; i++){
        if(cpf_local == vet_cliente[i].cpf){
            return 1; //se existir retorna true 
        }
    }

    return 0; //se n existir retorna false
}

int validaCpf(CLIENTE* vet_cliente, int c_cliente, char erro[]){

    int cpf;

    do{

        scanf("%d",&cpf);
        
        if(!verificaCliente(cpf,vet_cliente,c_cliente)) break;
        
        else printf("%s",erro);

    }while(1);

     return cpf;

}

int validaEscopo(int min, int max, char erro[]){

    int valor;

    do{

        scanf("%d", &valor);

        if(valor >= min && valor <= max) break;
        
        else printf("%s",erro);

    }while(1);

    return valor;

}
