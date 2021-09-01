// outros tipos de funções
// funções que cadastram
#include "../header/tipos.h"
#include "../header/prototipos.h"

#include <stdio.h>
#include <string.h>

// retorna o nome do genero com o valor do enum

char* retornaGenero(GENERO genero){

    switch(genero){
        case 0:
            return "aventura";
            break;
        case 1:
            return "comedia";
            break;
        case 2:
            return "drama";
            break;
        case 3:
            return "terror";
            break;
        case 4:
            return "acao";
            break;
        case 5:
            return "romance";
            break;

    }
    
    return "";

}

// retorna o nome da classificação com o valor do enum

char* retornaClassificacao(CLASSIFICACAO classificacao){

    switch(classificacao){
        case 0:
            return "livre";
            break;
        case 1:
            return "+10";
            break;
        case 2:
            return "+12";
            break;
        case 3:
            return "+14";
            break;
        case 4:
            return "+16";
            break;
        case 5:
            return "+18";
            break;

    }
    
    return "";

}

int carregaFilme(int max_cliente, int max_flime, HISTORICO mat_historico[max_cliente][max_flime], int *c_filme_cliente, CLIENTE *vet_cliente, int c_cliente, FILME *vet_filme, int c_filme, CONTRATO *vet_contrato, int c_contrato, PLANO_BASICO plano_basico, int mes_atual)
{

    int cpf, codigo, genero_ou_classificacao, escolha;
    int posicao_cliente, posicao_contrato;

    do
    {
        printf("\nCPF: ");
        scanf("%d", &cpf);

        posicao_cliente = verificaCliente(cpf, vet_cliente, c_cliente);

        if (posicao_cliente == 0)
            printf("ERRO: Cliente nao cadastrado\n");

        posicao_cliente--;

        if (vet_cliente[posicao_cliente].estado == ativo)
        {

            if (c_filme_cliente[posicao_cliente] == max_flime)
            {

                return 1; // caso o cliente tenha atingido a cota de filmes (30)
            }
            else
            {

                printf("Dia: ");
                mat_historico[posicao_cliente][c_filme_cliente[posicao_cliente]].data.dia = validaEscopo(1, 31, "ERRO: Dia invalido\n");

                mat_historico[posicao_cliente][c_filme_cliente[posicao_cliente]].data.mes = mes_atual;

                // precisamos especificar no texto qual escolha leva pro genero e qual leva pra classificação, to usando 0/1
                printf("Genero ou classificacao[0/1]: ");
                genero_ou_classificacao = validaEscopo(0, 1, "ERRO: Escolha invalida\n");

                printf("Escolha:");

                escolha = validaEscopo(0, 5, "ERRO: Escolha invalida\n");

                // genero
                if (genero_ou_classificacao == 0)
                {
                    // estou passando escolha como parametro agora
                    if (!listaGenero(vet_filme, c_filme, escolha))
                        return -1;

                    // classificação
                }
                else
                {
                    // estou passando escolha como parametro agora
                    if (!listaClassificacao(vet_filme, c_filme, escolha))
                        return -1;
                }

                printf("Codigo do filme: ");
                scanf("%d", &codigo);

                if (verificaFilme(codigo, vet_filme, c_filme))
                {

                    mat_historico[posicao_cliente][c_filme_cliente[posicao_cliente]].codigo = codigo;

                    posicao_contrato = verificaContrato(cpf, vet_contrato, c_contrato);

                    if (!posicao_contrato)
                    {

                        return 5; // cliente não possui contrato
                    }

                    posicao_contrato--;

                    if (vet_contrato[posicao_contrato].plano_tipo == basico)
                    {

                        if (c_filme_cliente[posicao_cliente] > plano_basico.quantidade_de_filmes)
                        {

                            printf("Deseja assistir pagando o valor extra [0/1]: ");
                            escolha = validaEscopo(0, 1, "ERRO: Escolha invalida\n");

                            if (escolha == 0)
                            {

                                return 6; // filme não carregado;
                            }
                        }
                    }

                    c_filme_cliente[posicao_cliente]++;

                    return 0;
                }
                else
                {
                    return 4; // filme não encontrado;
                }
            }
        }
        else
        {

            printf("ERRO: Cliente nao ativo\n");
        }

    } while (1);
}

int cancelarContrato(CONTRATO* vet_contrato, int c_contratos, CLIENTE* vet_cliente, int c_cliente, int mes_atual){

    int i, x, cpf;

    if(c_contratos == 0){
        return 2; //não existe contratos
    }
    do
    {
        printf("\nCPF cadastrado no Contrato: ");
        scanf("%d", &cpf);

        x = verificaCliente(cpf, vet_cliente, c_cliente);
        if(x == 0){
            //não existe esse cliente;
            printf("ERRO: Contrato nao existente");
        } else {
            if(vet_cliente[x-1].estado == 0){
                return 3; //cliente inativo
            } else {

                for(i=0; i<c_contratos; i++){
                    if(vet_contrato->cpf == vet_cliente->cpf)
                    break;
                }

                //falta arrumar o fato que o dia de cancelamento não pode ser antes do dia de contratação se estiver no mesmo mês
                printf("Dia: ");
                vet_contrato[i].data_de_cancelamento.dia = validaEscopo(1,31,"ERRO: Dia invalido\n");
                vet_contrato[i].data_de_cancelamento.mes = mes_atual;

                //
                //
                //
                //
                // calcular e informar o valor devido 
                //
                //
                //
                //
                //

                vet_cliente[x-1].estado = inativo; 

                return 0;
            }
        }

    }while(1);

}