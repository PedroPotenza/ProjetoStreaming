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

}

int cancelarContrato(CONTRATO *vet_contrato, int c_contratos, CLIENTE *vet_cliente, int c_cliente, int mes_atual, PLANO_BASICO plano_basico, PLANO_PREMIUM plano_premium, int* c_filme_cliente)
{

    int i, x, cpf, existe=0;
    int dia_local; 
    float valor;

    //if (c_contratos == 0)
    //{
        //return 2; //não existe contratos
    //}

    printf("\nCPF cadastrado no Contrato: ");
    scanf("%d", &cpf);

    x = verificaCliente(cpf, vet_cliente, c_cliente);
    if (x == 0)
    {
        return 2;// Cliente não cadastrado
    }
    else
    {
        if (vet_cliente[x - 1].estado == inativo)
        {
            return 3; //cliente inativo
        }
        else
        {

            // for(i=0; i<c_contratos; i++){
            //     if(vet_contrato[i].cpf == vet_cliente[x-1].cpf)
            //     break;
            // }   //Salvando a posição (index) que o contrato tem q consultar 

            // na verdade, acho que por ele estar inativo ele não tem um contrato, então poderia retirar isso, mas não vamos, só pra n quebrar

            i = verificaContrato(vet_cliente[x-1].cpf,vet_contrato,c_contratos);

            if(i == 0) return 4; // Contrato não existe;

            i--;

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

            // switch(vet_contrato[i].plano_tipo){
            //     case basico:
            //         if(vet_contrato[i].data_de_contratacao.mes == mes_atual)
            //             valor = plano_basico.valor_base;
            //         else
            //             valor = plano_basico.valor_base*(vet_contrato[i].data_de_cancelamento.mes - vet_contrato[i].data_de_contratacao.mes);
                        
            //         if(c_filme_cliente[x-1] > plano_basico.quantidade_de_filmes)
            //             valor = valor + plano_basico.valor_excedente * (c_filme_cliente[x-1] - plano_basico.quantidade_de_filmes);
            //         break;

            //     case premium:
            //         valor = plano_premium.valor_base * (vet_contrato[i].data_de_cancelamento.mes - vet_contrato[i].data_de_contratacao.mes);
            //         break;
            // }

            printf("Valor devido: %.2f\n", valorDevido(plano_basico,plano_premium/*,vet_contrato[i].data_de_contratacao,vet_contrato[i].data_de_cancelamento*/,c_filme_cliente[x-1],vet_contrato[i].plano_tipo));
            
            vet_cliente[x - 1].estado = inativo;

            c_filme_cliente[x-1] = 0;

            return 0;
        }
    }
}

float valorDevido(PLANO_BASICO plano_basico, PLANO_PREMIUM plano_premium /*, DATA contratacao, DATA cancelamento*/, int quantidade_filmes, PLANO_TIPO tipo_plano){

    float valor = 0;

    if(tipo_plano == basico){

        valor = plano_basico.valor_base;//*(cancelamento.mes - contratacao.mes + 1);

        if(quantidade_filmes > plano_basico.quantidade_de_filmes) {

            valor += plano_basico.valor_excedente*(quantidade_filmes - plano_basico.quantidade_de_filmes);

        }
        
    }else{

        valor = plano_premium.valor_base;//*(cancelamento.mes-contratacao.mes + 1);

    }

    return valor;

}

int geraFatura(int max_cliente, int max_flime, HISTORICO mat_historico[max_cliente][max_flime], CONTRATO *vet_contrato, int c_contrato, CLIENTE *vet_cliente, int c_cliente, FILME* vet_filme, int c_filme, int* mes_atual, PLANO_BASICO plano_basico, PLANO_PREMIUM plano_premium, int* c_filme_cliente){

    int escolha, x=0;

    printf("\nFatura especifica ou de todos os clientes?[0/1]:");
    scanf("%d",&escolha);

    if(escolha == 0){

        int cpf;
        printf("\nCPF: ");
        scanf("%d",&cpf);

        x = faturaCliente(cpf,max_cliente,max_flime,mat_historico,vet_contrato,c_contrato,vet_cliente,c_cliente,vet_filme,c_filme,*mes_atual,plano_basico,plano_premium,c_filme_cliente);

    }else{

        x = faturaTodosClientes(max_cliente,max_flime,mat_historico,vet_contrato,c_contrato,vet_cliente,c_cliente,mes_atual,plano_basico,plano_premium,c_filme_cliente);

    }

    return x;

}

int faturaTodosClientes(int max_cliente, int max_flime, HISTORICO mat_historico[max_cliente][max_flime], CONTRATO *vet_contrato, int c_contrato, CLIENTE *vet_cliente, int c_cliente, int* mes_atual, PLANO_BASICO plano_basico, PLANO_PREMIUM plano_premium, int* c_filme_cliente){

    for(int c=0;c<c_contrato;c++){

        int pos_cliente = verificaCliente(vet_contrato[c].cpf,vet_cliente,c_cliente);
        pos_cliente--;

        if(vet_cliente[pos_cliente].estado == ativo){

            printf("CPF: %d\n",vet_cliente[pos_cliente].cpf);
            printf("Nome: %s\n",vet_cliente[pos_cliente].nome);
            printf("Valor devido: %.2f\n",valorDevido(plano_basico,plano_premium/*,vet_contrato[c].data_de_contratacao,vet_contrato[c].data_de_cancelamento*/,c_filme_cliente[pos_cliente],vet_contrato[c].plano_tipo));      
       
        }

    }

    (*mes_atual)++;

    for(int c=0;c<max_cliente;c++){

         for(int d=0;d<max_flime;d++){

            mat_historico[c][d].codigo = 0;
            mat_historico[c][d].data.dia = 0;
            mat_historico[c][d].data.mes = 0;


        }

        c_filme_cliente[c] = 0;
        //vet_cliente[c].estado = inativo;
    }


    return 0;

}

int faturaCliente(int cpf, int max_cliente, int max_flime, HISTORICO mat_historico[max_cliente][max_flime], CONTRATO *vet_contrato, int c_contrato, CLIENTE *vet_cliente, int c_cliente, FILME* vet_filme, int c_filme, int mes_atual, PLANO_BASICO plano_basico, PLANO_PREMIUM plano_premium, int* c_filme_cliente){

    int pos_cliente = verificaCliente(cpf,vet_cliente,c_cliente);

    if(pos_cliente){

        pos_cliente--;

        for(int c=0;c<c_filme_cliente[pos_cliente];c++){

            int pos_filme = verificaFilme(mat_historico[pos_cliente][c].codigo,vet_filme,c_filme);
            pos_filme--;

            printf("Nome: %s\n",vet_filme[pos_filme].nome);
            printf("Data: %d/%d\n",mat_historico[pos_cliente][c].data.dia,mat_historico[pos_cliente][c].data.mes);

        }

        int pos_contrato = verificaContrato(cpf,vet_contrato,c_contrato);

        if(pos_contrato == 0) return 2; // Não existe contrato

        pos_contrato--;

        printf("Valor devido: %.2f\n",valorDevido(plano_basico,plano_premium/*,vet_contrato[pos_contrato].data_de_contratacao,vet_contrato[pos_contrato].data_de_cancelamento*/,c_filme_cliente[pos_cliente],vet_contrato[pos_contrato].plano_tipo));

        c_filme_cliente[pos_cliente] = 0;
        //vet_cliente[pos_cliente].estado = inativo;

    }else return 1; // Cliente não cadastrado

    return 0;

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