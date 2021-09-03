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

                        // corrigi, pois estava valendo um filme à mais, troquei > por >=
                        if (c_filme_cliente[posicao_cliente] >= plano_basico.quantidade_de_filmes)
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

int cancelarContrato(CONTRATO *vet_contrato, int c_contratos, CLIENTE *vet_cliente, int c_cliente, int mes_atual, PLANO_BASICO plano_basico, PLANO_PREMIUM plano_premium, int* c_filme_cliente)
{

    int i, x, cpf, existe=0;
    int dia_local; 
    float valor;

    if (c_contratos == 0)
    {
        return 2; //não existe contratos
    }

    printf("\nCPF cadastrado no Contrato: ");
    scanf("%d", &cpf);

    x = verificaCliente(cpf, vet_cliente, c_cliente);
    if (x == 0)
    {
        return 4;//não existe esse contrato;
    }
    else
    {
        if (vet_cliente[x - 1].estado == 0)
        {
            return 3; //cliente inativo
        }
        else
        {

            for(i=0; i<c_contratos; i++){
                if(vet_contrato[i].cpf == vet_cliente[i].cpf)
                break;
            }   //Salvando a posição (index) que o contrato tem q consultar 

            //falta arrumar o fato que o dia de cancelamento não pode ser antes do dia de contratação se estiver no mesmo mês
            printf("Dia: ");
            dia_local = validaEscopo(1, 31, "ERRO: Dia invalido\n");
            if(vet_contrato[i].data_de_contratacao.mes == mes_atual){
                if(dia_local < vet_contrato[i].data_de_contratacao.dia){
                    return 1; //COLOCAR UM COMENTARIO EXPLICANDO QUE: 
                    /*
                        receber um dia valido é necessario um do-while, porem verificar 
                        se o dia é anterior ao dia de contratação não é um do-while

                        informar uma data anterior a data de contratação vai levar o usuario ao menu principal
                    */
                }
            }
            vet_contrato[i].data_de_cancelamento.dia = dia_local;
            vet_contrato[i].data_de_cancelamento.mes = mes_atual;

            switch(vet_contrato[i].plano_tipo){
                case basico:
                    if(vet_contrato[i].data_de_contratacao.mes == mes_atual)
                        valor = plano_basico.valor_base;
                    else
                        valor = plano_basico.valor_base*(vet_contrato[i].data_de_cancelamento.mes - vet_contrato[i].data_de_contratacao.mes);
                        
                    if(c_filme_cliente[i] > plano_basico.quantidade_de_filmes)
                        valor = valor + plano_basico.valor_excedente * (c_filme_cliente[i] - plano_basico.quantidade_de_filmes);
                break;

                case premium:
                    valor = plano_premium.valor_base * (vet_contrato[i].data_de_cancelamento.mes - vet_contrato[i].data_de_contratacao.mes);
            }

            printf("Valor devido: %.2f\n", valor);
            
            vet_cliente[x - 1].estado = inativo;

            return 0;
        }
    }
}

int frequenciaFilme(int max_cliente, int max_flime, HISTORICO mat_historico[max_cliente][max_flime], int *c_filme_cliente, FILME *vet_filme, int c_filme, int c_cliente){

    int codigo;
    float contador=0, total=0;

    printf("\nCodigo: ");
    scanf("%d",&codigo);
    
    if(verificaFilme(codigo,vet_filme,c_filme)){

        for(int c=0;c<c_cliente;c++){

            for(int d=0;d<c_filme_cliente[c];d++){

                if(mat_historico[c][d].codigo == codigo){
                    contador++;
                }

                total++;

            }

        }

        if(total == 0){

            return 2; // Nenhum filme assitido;

        }

        printf("Frequencia: %.2f%%",100.0*(contador/total));

    }else{

        return 1; // filme não existente;

    }

    return 0;

}

int recomendaFilme(CLIENTE* vet_cliente, int c_cliente,int max_cliente, int max_filme, HISTORICO mat_historico[max_cliente][max_filme], int *c_filme_cliente, FILME* vet_filme, int c_filme){

    int cpf, contador_genero[6] = {0};

    printf("\nCPF: ");
    scanf("%d",&cpf);

    int pos_cli = verificaCliente(cpf,vet_cliente,c_cliente);

    if(pos_cli){

        pos_cli--;

        if(vet_cliente[pos_cli].estado == ativo){

            for(int c=0;c<c_filme_cliente[pos_cli];c++){

                //printf("%d ",mat_historico[pos_cli][c].codigo);

                int pos_film = verificaFilme(mat_historico[pos_cli][c].codigo,vet_filme,c_filme);

                if(pos_film){
                    
                    pos_film--;

                    contador_genero[vet_filme[pos_film].genero]++;
                    //printf("%d ",vet_filme[pos_film].genero);

                }

            }

            int maior = contador_genero[0];
            int empates[6] = {-1,-1,-1,-1,-1,-1}, contador_empates=0;

            //printf("%d ",contador_genero[0]);

            for(int c=1;c<6;c++){

                if(contador_genero[c] > maior){
                    maior = contador_genero[c];
                }
               //printf("%d ",contador_genero[c]);

            }

            if(maior == 0){

                return 4; // Nenhum filme assistido;

            }

            for(int c=0;c<6;c++){

                if(contador_genero[c] == maior){
                    empates[contador_empates] = c;
                    contador_empates++;
                }

            }

            int contador_filmes = 0;

            for(int c=0;c<6;c++){

                //printf("empates: %d\n",empates[c]);

                if(empates[c] != -1){

                    for(int d=0;d<c_filme;d++){
                        //printf("%d ",c_filme);

                        if(vet_filme[d].genero == empates[c]){

                            //printf("%d || %d ",vet_filme[d].genero, empates[c]);

                            // clienteAssistiu verifica se um cliente assistiu um filme

                            if(!clienteAssistiu(vet_cliente,c_cliente,cpf,vet_filme,c_filme,vet_filme[d].codigo,max_cliente,max_filme,mat_historico,c_filme_cliente)){

                                contador_filmes++;
                                printf("Codigo: %d\n",vet_filme[d].codigo);
                                printf("Nome: %s\n",vet_filme[d].nome);
                                
                                // isso aqui provavelmente pode remover depois
                                printf("Genero: %s\n", retornaGenero(vet_filme[d].genero));
                                printf("Classificacao: %s\n", retornaClassificacao(vet_filme[d].genero));
                                //

                            }

                        }

                    }

                }

            }

            if(!contador_filmes){

                return 3; // Não é possivel fazer a recomendação, cliente já assistiu todos os filmes do genero

            }

        }else{

            return 2; // Cliente não ativo;

        }

    }else{

        return 1; // Cliente não cadastrado;
    
    }

    return 0;
}