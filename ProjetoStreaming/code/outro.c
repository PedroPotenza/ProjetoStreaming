// outros tipos de funções
// funções que cadastram
#include "../header/tipos.h"
#include "../header/prototipos.h"

#include <stdio.h>
#include <string.h>

int carregaFilme(int max_cliente, int max_flime, HISTORICO mat_historico[max_cliente][max_flime], int* c_filme_cliente, CLIENTE* vet_cliente, int c_cliente, FILME* vet_filme, int c_filme, CONTRATO* vet_contrato, int c_contrato, PLANO_BASICO plano_basico){

    int cpf, codigo, genero_ou_classificacao, escolha;
    int posicao_cliente, posicao_contrato;

    printf("\nCPF: ");
    scanf("%d",&cpf);

    posicao_cliente = verificaCliente(cpf, vet_cliente, c_cliente);

    if(posicao_cliente){

        posicao_cliente--;

        if(vet_cliente[posicao_cliente].estado == ativo){

            if(c_filme_cliente[posicao_cliente] == max_flime){

                return 1; // caso o cliente tenha atingido a cota de filmes (30)
            
            }else{

                printf("Dia: ");
                mat_historico[posicao_cliente][c_filme_cliente[posicao_cliente]].data.dia = validaEscopo(1,31,"ERRO: Dia invalido\n");

                printf("Mes: ");
                mat_historico[posicao_cliente][c_filme_cliente[posicao_cliente]].data.mes = validaEscopo(1,12,"ERRO: Mes invalido\n");

                // precisamos especificar no texto qual escolha leva pro genero e qual leva pra classificação, to usando 0/1
                printf("Genero ou classificacao[0/1]: ");
                genero_ou_classificacao = validaEscopo(0,1,"ERRO: Escolha invalida\n");
                
                // genero
                if(genero_ou_classificacao == 0){

                    if(!listaGenero(vet_filme,c_filme)) return -1;

                // classificação
                }else{

                    if(!listaClassificacao(vet_filme,c_filme)) return -1;
                }

                printf("Codigo do filme: ");
                scanf("%d",&codigo);

                if(verificaFilme(codigo,vet_filme,c_filme)){

                    mat_historico[posicao_cliente][c_filme_cliente[posicao_cliente]].codigo = codigo;

                    posicao_contrato = verificaContrato(cpf,vet_contrato,c_contrato);
                    
                    if(!posicao_contrato){
                       
                        return 5; // cliente não possui contrato
                    
                    }

                    posicao_contrato--;

                    if(vet_contrato[posicao_contrato].plano_tipo == basico){

                        if(c_filme_cliente[posicao_cliente] > plano_basico.quantidade_de_filmes){

                            printf("Deseja assistir pagando o valor extra [0/1]: ");
                            escolha = validaEscopo(0,1,"ERRO: Escolha invalida\n");

                            if(escolha == 0){
                                
                                return 6; // filme não carregado;

                            }

                        }

                    }

                    c_filme_cliente[posicao_cliente]++;
                                
                    return 0;

                }else{
                    return 4; // filme não encontrado;
                }
            }   

        }else{

            return 3; // cliente não esta ativo;

        }

    }else{

        return 2; // caso o cliente não exista;
    }

}









