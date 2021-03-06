// funções que cadastram
#include "../header/tipos.h"
#include "../header/prototipos.h"

#include <stdio.h>
#include <string.h>

int cadastroCliente(CLIENTE* vet_cliente, int* c_cliente, int max_cliente, int* c_filme_cliente){

    int cpf_local,i;

    if((*c_cliente) == max_cliente) return 1; //numero maximo de clientes atingido
    
    else {

        printf("\nCPF: ");
        scanf("%d", &cpf_local);

        for(i=0; i<(*c_cliente); i++){
            if(cpf_local == vet_cliente[i].cpf){
                return 2; //cliente ja cadastrado
            }
        }

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

        vet_cliente[(*c_cliente)].estado = inativo;
        c_filme_cliente[(*c_cliente)]=0; // cliente assistiu 0 filmes ao ser cadastrado
        (*c_cliente)++;
        return 0; //cadastrado com sucesso

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

        printf("Genero: ");
 
        vet_filme[*c_filme].genero = (GENERO)validaEscopo(0,5,"ERRO: Genero invalido\n");
        
        printf("Classificacao: ");

        vet_filme[*c_filme].classificacao = (CLASSIFICACAO)validaEscopo(0,5,"ERRO: Classificao invalida\n");

        (*c_filme)++;
        return 0;
    }

}
// alterei dnv, desculpa asuhdsahudahu
// os valores não estavam sendo registrados, então troquei pra ponteiro, agora vai
int cadastroPlanoBasicao(PLANO_BASICO* plano_basico){

    printf("\nQuantos filmes o usuario pode assistir? ");
    scanf("%d", &plano_basico->quantidade_de_filmes);

    printf("Valor Base: ");
    scanf("%f", &plano_basico->valor_base);

    printf("Valor Excedente: ");
    scanf("%f", &plano_basico->valor_excedente);

    return 0;
}
// mesma coisa aqui
int cadastroPlanoPremium(PLANO_PREMIUM* plano_premium){

    printf("\nValor Base: ");
    scanf("%f", &plano_premium->valor_base);
    return 0;
}

int cadastroContrato(CONTRATO* vet_contrato, int* c_contratos, int max_contratos, CLIENTE* vet_cliente, int c_cliente, int mes_atual){

    if((*c_contratos)==max_contratos){
        return 1; //numero maximo de contratos atingido
    }else{

        if(existeCliente(vet_cliente, c_cliente))
            return 2; //nenhum cliente cadastrado no sistema

        int cpf;
            
            printf("\nCPF: ");
            scanf("%d",&cpf);

            int posicao_cliente = verificaCliente(cpf,vet_cliente,c_cliente);
            
            if(posicao_cliente){

                posicao_cliente--;

                if(vet_cliente[posicao_cliente].estado == ativo){
                    return 4; // contrato já existente
                }

                    int pos_contrato = verificaContrato(cpf, vet_contrato, *c_contratos);

                    if(!pos_contrato){

                        pos_contrato = (*c_contratos);
                        (*c_contratos)++;

                    }else pos_contrato--;

                    vet_contrato[pos_contrato].cpf = cpf;

                    printf("Tipo de plano: ");
                    vet_contrato[pos_contrato].plano_tipo = validaEscopo(0,1,"ERRO: Tipo de plano invalido\n");

                    // removi o campo plano, pois só existe um plano, basico ou premium

                    printf("Tipo de pagamento (Debito (0) ou Credito (1)): ");
                    vet_contrato[pos_contrato].pagamento_tipo = validaEscopo(0,1,"ERRO: Tipo de pagamento invalido\n");
                    
                    if(vet_contrato[pos_contrato].pagamento_tipo == debito){

                        printf("Ag: ");
                        scanf("%d",&vet_contrato[pos_contrato].pagamento.debito.agencia);
                        printf("Conta: ");
                        scanf("%d",&vet_contrato[pos_contrato].pagamento.debito.conta);
                    }else{
                        printf("Numero do Cartao: ");
                        scanf("%d",&vet_contrato[pos_contrato].pagamento.credito.numero_do_cartao);
                    }

                    vet_contrato[pos_contrato].data_de_cancelamento.dia = 0;
                    vet_contrato[pos_contrato].data_de_cancelamento.mes = 0;

                    printf("Dia: ");
                    vet_contrato[pos_contrato].data_de_contratacao.dia = validaEscopo(1,31,"ERRO: Dia invalido\n");

                    vet_contrato[pos_contrato].data_de_contratacao.mes = mes_atual;
                    //validaEscopo(1,12,"ERRO: Mes invalido\n");

                    vet_cliente[posicao_cliente].estado = ativo;

                    return 0;
                
            }else{
                return 3;
            }

    }

}

