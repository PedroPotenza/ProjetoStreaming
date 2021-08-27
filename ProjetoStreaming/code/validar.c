// funções que validam
#include "../header/tipos.h"

#include <stdio.h>

int verificaCliente(int cpf_local, CLIENTE* vet_cliente, int* c_cliente){

    int i;

    for(i=0; i<(*c_cliente); i++){
        if(cpf_local == vet_cliente[i].cpf){
            return 1; //se existir retorna true 
        }
    }

    return 0; //se n existir retorna false
}