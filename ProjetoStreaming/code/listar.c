// funções que listam
#include "../header/tipos.h"
#include "../header/prototipos.h"


#include <stdio.h>
#include <string.h>

// estou passando escolha como parametro agora
int listaGenero(FILME* vet_filme, int c_filme, int escolha){

    int valida = 0;

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

// estou passando escolha como parametro agora
int listaClassificacao(FILME* vet_filme, int c_filme, int escolha){

    int valida = 0;

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

void imprimeCliente(CLIENTE *vet_cliente, int c_cliente)
{

    int cpf_local, existe, i;

    if (existeCliente(vet_cliente, c_cliente))
    {
        printf("ERRO: Nenhum cliente cadastrado no sistema\n");
        return;
    }

    printf("\nCPF: ");
    scanf("%d", &cpf_local);

    existe = verificaCliente(cpf_local, vet_cliente, c_cliente);

    if (!existe)
    {
        printf("ERRO: Cliente nao cadastrado\n");
        return;
    }

    if (existe = 1)
    {
        for (i = 0; i < c_cliente; i++)
        {
            if (cpf_local == vet_cliente[i].cpf)
            {
                //printf("CPF: %d\n", vet_cliente[i].cpf);
                printf("Nome: %s\n", vet_cliente[i].nome);
                printf("Email: %s\n", vet_cliente[i].email);
                printf("Telefone: %s\n", vet_cliente[i].telefone);
                printf("Status: %d\n", vet_cliente[i].estado);
            }
        }
    }
}

int imprimeHistorico(int max_cliente, int max_flime, HISTORICO mat_historico[max_cliente][max_flime], int* c_filme_cliente, CLIENTE* vet_cliente, int c_cliente, FILME* vet_filme, int c_filme){

    int cpf;

    if(c_cliente == 0)
        return 3;

    printf("\nCPF: ");
    scanf("%d",&cpf);

    int posicao_cliente = verificaCliente(cpf, vet_cliente, c_cliente);

    if (posicao_cliente == 0)
            return 1; //printf("ERRO: Cliente nao cadastrado\n");

    posicao_cliente--;

    if(vet_cliente[posicao_cliente].estado == ativo){
        printf("Estado: Ativo\n");
    }else{
        printf("Estado: Inativo\n");
    }

    int posicao_filme;

    if(c_filme_cliente[posicao_cliente] == 0){
        return 2; //printf("ERRO: Nenhum filme assistido\n"); 
    }


    // printa os filmes que ele assistiu
    for(int c=0;c<c_filme_cliente[posicao_cliente];c++){
        
        posicao_filme = verificaFilme(mat_historico[posicao_cliente][c].codigo,vet_filme,c_filme);
        posicao_filme--;
        printf("Codigo: %d\n",vet_filme[posicao_filme].codigo);
        printf("Nome: %s\n",vet_filme[posicao_filme].nome);
        
        // isso aqui provavelmente pode remover depois
        printf("Genero: %s\n", retornaGenero(vet_filme[posicao_filme].genero));
        printf("Classificacao: %s\n", retornaClassificacao(vet_filme[posicao_filme].classificacao));
        //

        printf("Data do carregamento: %d/%d\n\n",mat_historico[posicao_cliente][c].data.dia, mat_historico[posicao_cliente][c].data.mes);

    }
    
    return 0;

}

void imprimeClienteExcedente(CLIENTE* vet_cliente, int c_cliente, FILME* vet_filme, int c_filme, CONTRATO* vet_contrato, int c_contrato, int* c_filme_cliente, PLANO_BASICO plano_basico){

    int clientes_excedentes=0;

    for(int c=0;c<c_contrato;c++){

        if(vet_contrato[c].plano_tipo == basico){

            int posicao_cliente = verificaCliente(vet_contrato[c].cpf,vet_cliente,c_cliente);
            posicao_cliente--;

            if(vet_cliente[posicao_cliente].estado == ativo){
                
                if(c_filme_cliente[posicao_cliente] > plano_basico.quantidade_de_filmes){

                    clientes_excedentes = 1;
                    printf("CPF: %d\n",vet_cliente[posicao_cliente].cpf);
                    printf("Nome: %s\n",vet_cliente[posicao_cliente].nome);
                    //printf("%.2f || %d\n",plano_basico.valor_excedente,(c_filme_cliente[posicao_cliente] - plano_basico.quantidade_de_filmes));
                    float excesso = (plano_basico.valor_excedente)*(c_filme_cliente[posicao_cliente] - plano_basico.quantidade_de_filmes);
                    printf("Valor excedente: %.2f\n\n",excesso);

                }
            }

        }

    }

    if(!clientes_excedentes){

        printf("ERRO: Nenhum cliente excedente\n");

    }

}
