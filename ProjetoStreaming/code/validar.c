// funções que validam
#include "../header/tipos.h"

#include <stdio.h>

int verificaCliente(int cpf_local, CLIENTE* vet_cliente, int c_cliente){

    int i;

    for(i=0; i<c_cliente; i++){
        if(cpf_local == vet_cliente[i].cpf){
            return i+1; //se existir retorna true 
        }
    }

    return 0; //se n existir retorna false
}

int verificaContrato(int cpf_local, CONTRATO* vet_contrato, int c_contrato){

    int i;

    for(i=0; i<c_contrato; i++){
        if(cpf_local == vet_contrato[i].cpf){
            return i+1; //se existir retorna true 
        }
    }

    return 0; //se n existir retorna false
}

int verificaFilme(int codigo, FILME* vet_filme, int c_filme){

    int i;

    for(i=0; i<c_filme; i++){
        if(codigo == vet_filme[i].codigo){
            return i+1; //se existir retorna true 
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

/*
verifica se existe algum cliente cadastrado no sistema
usado no cadastrar contrato, listar cliente, etc ... 
eh usado bastante pra evitar loop infinito de erro por causa dos do whiles
*/
int existeCliente(CLIENTE* vet_cliente, int c_cliente){

    if(c_cliente==0){
        return 1; //retorna 1 se n tiver nenhum cliente cadastrado
    }
    return 0; //retorna 0 se existir algum cliente
} 


// retorna 1 se o cliente assistiu a um filme e 0 se não assistiu, -1 para erro
int clienteAssistiu(CLIENTE* vet_cliente, int c_cliente, int cpf_local, FILME* vet_filme, int c_filme, int codigo, int max_cliente, int max_flime, HISTORICO mat_historico[max_cliente][max_flime], int *c_filme_cliente){

    int pos_cli = verificaCliente(cpf_local,vet_cliente,c_cliente);

    if(pos_cli){

        int pos_film = verificaFilme(codigo,vet_filme,c_filme);

        if(pos_film){

            pos_cli--;
            pos_film--;

            for(int c=0;c<c_filme_cliente[pos_cli];c++){

                if(mat_historico[pos_cli][c].codigo == codigo){
                    return 1;
                }

            }

        }else return -1;

    }else return -1;

    return 0;

}