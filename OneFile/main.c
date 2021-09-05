#include <stdio.h>
#include <string.h>

typedef enum STATUS{

    inativo=0, ativo

} STATUS;

typedef enum GENERO{

    aventura=0, comedia, drama, terror, acao, romance

} GENERO;

typedef enum CLASSIFICACAO{

    livre=0, proibido_10, proibido_12, proibido_14, proibido_16, proibido_18

} CLASSIFICACAO;

typedef enum PLANO_TIPO{

    basico, premium

} PLANO_TIPO;

typedef enum PAGAMENTO_TIPO{

    debito=0, credito

} PAGAMENTO_TIPO;

typedef struct DATA{

    int dia;
    int mes;

} DATA;

typedef struct CLIENTE{

    int cpf; // codigo do cliente // chave de busca
    char nome[50];
    char email[50];
    char telefone[15];
    STATUS estado; 

} CLIENTE;

typedef struct FILME{

    int codigo; // codigo do filme
    char nome[50];
    GENERO genero;
    CLASSIFICACAO classificacao;

} FILME;

typedef struct PLANO_BASICO{

    int quantidade_de_filmes;
    float valor_base;
    float valor_excedente;

} PLANO_BASICO;

typedef struct PLANO_PREMIUM{

    float valor_base;

} PLANO_PREMIUM;

typedef struct DEBITO{

    int agencia;
    int conta;

} DEBITO;

typedef struct CREDITO{

    int numero_do_cartao;

} CREDITO;

// STRUCTS ------------------------------------------------

// UNIONS -------------------------------------------------

// typedef union PLANO{

//     PLANO_BASICO basico;
//     PLANO_PREMIUM premium;

// } PLANO;

typedef union PAGAMENTO{

    DEBITO debito;
    CREDITO credito;

} PAGAMENTO;

// UNIONS -------------------------------------------------

// STRUCTS ------------------------------------------------

typedef struct CONTRATO{

    int cpf; // codigo do cliente
    PLANO_TIPO plano_tipo;
    DATA data_de_contratacao;
    DATA data_de_cancelamento;
    PAGAMENTO pagamento;
    PAGAMENTO_TIPO pagamento_tipo;

} CONTRATO;

typedef struct HISTORICO{

    int codigo; // codigo do filme
    DATA data; // data que o cliente assistiu

} HISTORICO;

// STRUCTS ------------------------------------------------

int verificaCliente(int cpf_local, CLIENTE* vet_cliente, int c_cliente);
int verificaContrato(int cpf_local, CONTRATO* vet_contrato, int c_contrato);
int verificaFilme(int codigo, FILME* vet_filme, int c_filme);

int existeCliente(CLIENTE* vet_cliente, int c_cliente);

int validaEscopo(int min, int max, char erro[]);
int validaCpf( CLIENTE* vet_cliente, int c_cliente, char erro[]);

int clienteAssistiu(CLIENTE* vet_cliente, int c_cliente, int cpf_local, FILME* vet_filme, int c_filme, int codigo, int max_cliente, int max_filme, HISTORICO mat_historico[max_cliente][max_filme], int *c_filme_cliente);

int cadastroCliente(CLIENTE* vet_cliente, int* c_cliente, int max_cliente, int* c_filme_cliente);
int cadastroFilme(FILME* vet_filme, int* c_filme, int max_filme);
int cadastroPlanoBasicao(PLANO_BASICO* plano_basico);
int cadastroPlanoPremium(PLANO_PREMIUM* plano_premium);
int cadastroContrato(CONTRATO* vet_contrato, int* c_contratos, int max_contratos, CLIENTE* vet_cliente, int c_cliente, int mes_atual);

int carregaFilme(int max_cliente, int max_flime, HISTORICO mat_historico[max_cliente][max_flime], int* c_filme_cliente, CLIENTE* vet_cliente, int c_cliente, FILME* vet_filme, int c_filme, CONTRATO* vet_contrato, int c_contrato, PLANO_BASICO plano_basico, int mes_atual);
int cancelarContrato(CONTRATO *vet_contrato, int c_contratos, CLIENTE *vet_cliente, int c_cliente, int mes_atual, PLANO_BASICO plano_basico, PLANO_PREMIUM plano_premium, int* c_filme_cliente);
int listaGenero(FILME* vet_filme, int c_filme, int escolha);
int listaClassificacao(FILME* vet_filme, int c_filme, int escolha);

int imprimeHistorico(int max_cliente, int max_flime, HISTORICO mat_historico[max_cliente][max_flime], int* c_filme_cliente, CLIENTE* vet_cliente, int c_cliente, FILME* vet_filme, int c_filme);
void imprimeCliente(CLIENTE* vet_cliente, int c_cliente);
void imprimeClienteExcedente(CLIENTE* vet_cliente, int c_cliente, FILME* vet_filme, int c_filme, CONTRATO* vet_contrato, int c_contrato, int* c_filme_cliente, PLANO_BASICO plano_basico);

int frequenciaFilme(int max_cliente, int max_flime, HISTORICO mat_historico[max_cliente][max_flime], int *c_filme_cliente, FILME *vet_filme, int c_filme, int c_cliente);

int recomendaFilme(CLIENTE* vet_cliente, int c_cliente,int max_cliente, int max_filme, HISTORICO mat_historico[max_cliente][max_filme], int *c_filme_cliente, FILME* vet_filme, int c_filme);

char* retornaGenero(GENERO genero);
char* retornaClassificacao(CLASSIFICACAO classificacao);

float valorDevido(PLANO_BASICO plano_basico, PLANO_PREMIUM plano_premium/*, DATA contratacao, DATA cancelamento*/, int quantidade_filmes, PLANO_TIPO tipo_plano);


int geraFatura(int max_cliente, int max_flime, HISTORICO mat_historico[max_cliente][max_flime], CONTRATO *vet_contrato, int c_contrato, CLIENTE *vet_cliente, int c_cliente, FILME* vet_filme, int c_filme, int* mes_atual, PLANO_BASICO plano_basico, PLANO_PREMIUM plano_premium, int* c_filme_cliente);
int faturaTodosClientes(int max_cliente, int max_flime, HISTORICO mat_historico[max_cliente][max_flime], CONTRATO *vet_contrato, int c_contrato, CLIENTE *vet_cliente, int c_cliente, int* mes_atual, PLANO_BASICO plano_basico, PLANO_PREMIUM plano_premium, int* c_filme_cliente);
int faturaCliente(int cpf, int max_cliente, int max_flime, HISTORICO mat_historico[max_cliente][max_flime], CONTRATO *vet_contrato, int c_contrato, CLIENTE *vet_cliente, int c_cliente, FILME* vet_filme, int c_filme, int mes_atual, PLANO_BASICO plano_basico, PLANO_PREMIUM plano_premium, int* c_filme_cliente);

// FUNÇÕES


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

    //int genero_local, classificacao_local;

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

int listaGenero(FILME* vet_filme, int c_filme, int escolha){

    int valida = 0;

    for(int c=0; c<c_filme;c++){

        if(vet_filme[c].genero == (GENERO)escolha){

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

        if(vet_filme[c].classificacao == (CLASSIFICACAO)escolha){

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

    if (existe == 1)
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
        printf("Classificacao: %s\n", retornaClassificacao(vet_filme[posicao_filme].genero));
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
            return 6; // printf("ERRO: Cliente nao ativo\n"); 
        }

}

int cancelarContrato(CONTRATO *vet_contrato, int c_contratos, CLIENTE *vet_cliente, int c_cliente, int mes_atual, PLANO_BASICO plano_basico, PLANO_PREMIUM plano_premium, int* c_filme_cliente)
{

    int i, x, cpf;// existe=0;
    int dia_local; 
    //float valor;

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

                        if(vet_filme[d].genero == (GENERO)empates[c]){

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
// comando para compilar: gcc main.c code/*.c -o main

/*anotações

 - não tem como ficar verificando se um cliente ja foi cadastrado ou não, pensei em colocar o CPF como algo para verificar
 isso alem do id autoincrementado, ai a ordem de leitura/processamento dos dados seria: 
 CPF (verifica se ja ta cadastrado)-> ID (autoincrementa) -> NOME -> EMAIL -> TELEFONE -> STATUS

 ai no filme não precisa fazer verificação nenhuma não, uma verificação dessas eu ja acho bom para avaliar se eles sabem
 fazer isso, pq se n verificar a existencia eh muito facil (só ver se o valor informado ta entre 1001 até 1001 + contador)

 ou talvez tirar o autoincremento do cliente, deixar apenas o CPF e usar o autoincremento no cod do filme 


*/

// depois precisamos mudar o texto do readme, por exemplo trocar o codigo do cliente por cpf do cliente

int main(void){

    //CONSTANTES
    const int max_cliente = 10;
    const int max_filme = 10;
    const int max_contratos = 10;

    //CONTADORES
    int c_cliente=0, c_filme=0, c_contratos=0;
    // troquei pra 10 pq se n n deixa inicializar com {0}
    int c_filme_cliente[10] = {0}; //contador de quantos filmes aquele (index) cliente viu 

    //VETORES E MATRIZ
    CLIENTE vet_cliente[max_cliente];
    FILME vet_filme[max_filme];
    CONTRATO vet_contrato[max_contratos];
    HISTORICO mat_historico[max_cliente][3*max_filme];

    PLANO_BASICO plano_basico;
    PLANO_PREMIUM plano_premium;

    //MES VIGENTE
    int mes_atual=1;

    //DIVERSAS
    int x;
    int opcao=99;//inicializa com 99 só pra n dar problema do lixo de memoria ser 0

	printf("--------------- MENU --------------- \n");
	printf("    1 - Cadastrar Cliente\n");
	printf("    2 - Cadastrar Filme\n");  
	printf("    3 - Cadastrar plano basico\n");  
	printf("    4 - Cadastrar plano premium\n");  
	printf("    5 - Cadastrar contrato\n");  
	printf("    6 - Carregar filme\n");  
	printf("    7 - Cancelar contrato\n");  
	printf("    8 - Gerar fatura\n");  
	printf("    9 - Listar os dados de um dado cliente\n");  
	printf("   10 - Listar o historico de uma dado cliente\n");  
	printf("   11 - Listar clientes que excederam a cota mensal\n");  
	printf("   12 - Frequencia de um dado filme\n");  
	printf("   13 - Recomendar filme\n");   
	printf("    0 - Sair\n"); 
	printf("---------------------------------- \n");

    do{
        printf("\nOpcao do Menu: ");
        scanf("%d", &opcao);

        switch(opcao){

            case 1:{
                x = cadastroCliente(vet_cliente, &c_cliente, max_cliente, c_filme_cliente);
                if(x==2){
                    printf("ERRO: CPF do cliente ja cadastrado\n");
                } else if(x==1){
                    printf("ERRO: Numero maximo de clientes no sistema atingido\n");
                } else {
                    printf("Cliente cadastrado com sucesso\n");
                }
                break;
            }

            case 2:{
                x = cadastroFilme(vet_filme, &c_filme, max_filme);
                if(x==1){
                    printf("ERRO: Numero maximo de filmes no sistema atingido\n");
                } else { 
                    printf("Filme cadastrado com sucesso\n");
                }
                break;

            }

            case 3:{
                x = cadastroPlanoBasicao(&plano_basico);
                if(x==0){
                    printf("Plano Basico cadastrado com sucesso\n");
                }
                //printf("%f",plano_basico.valor_excedente);
                break;
            }

            case 4:{
                x = cadastroPlanoPremium(&plano_premium);
                if(x==0){
                    printf("Plano Premium cadastrado com sucesso\n");
                }
                //printf("%f",plano_premium.valor_base);
                break;
            }

            case 5:{
                x = cadastroContrato(vet_contrato,&c_contratos,max_contratos,vet_cliente,c_cliente, mes_atual);
                switch(x){

                    case 0:
                        printf("Contrato cadastrado com sucesso\n");
                        break;
                    case 1:
                        printf("ERRO: Numero maximo de contratos no sistema atingido\n");
                        break;
                    case 2: 
                        printf("ERRO: Nenhum cliente cadastrado no sistema");
                        break;
                    case 3:
                        printf("ERRO: Cliente nao cadastrado\n");
                        break;
                    case 4:
                        printf("ERRO: Cliente com contrato existente\n");
                        break;
                }
                //Nenhum cliente cadastrado no sistema
                    //Cliente ja possui um contrato
                //Contrato cadastrado com sucesso

                //obs: Cada cliente so pode ter apenas um contrato, isso n ta especificado no enunciado
                break;
            }

            case 6:{
                
                x = carregaFilme(max_cliente,3*max_filme,mat_historico,c_filme_cliente,vet_cliente,c_cliente,vet_filme,c_filme,vet_contrato,c_contratos,plano_basico, mes_atual);
                switch(x){

                    case 0:
                        printf("Filme carregado com sucesso\n");
                        break;
                    case 1:
                        printf("ERRO: Numero maximo de filmes no sistema atingido\n");
                        break;
                    case 2: 
                        printf("ERRO: Cliente nao cadastrado\n");
                        break;
                    case 4:
                        printf("ERRO: Filme nao encontrado\n");
                        break;
                    case 5:
                        printf("ERRO: Cliente nao possui contrato\n");
                        break;
                    case 6:
                        printf("ERRO: Cliente nao ativo\n");
                        break;
                }

                break;
            }

            case 7:{

                x = cancelarContrato(vet_contrato, c_contratos, vet_cliente, c_cliente, mes_atual, plano_basico, plano_premium, c_filme_cliente);
                switch(x){

                    case 0: 
                        printf("Cancelamento feito com sucesso\n");
                        break;
                    case 1:
                        printf("ERRO: Data de cancelamente anteiror a cata de contratacao\n");
                        break;
                    case 2: 
                        printf("ERRO: Cliente nao cadastrado\n");//printf("ERRO: Nenhum contrato cadastrado no sistema\n");
                        break;
                    case 3: 
                        printf("ERRO: Cliente inativo\n");
                        break;
                    case 4: 
                        printf("ERRO: Cliente nao possui contrato\n"); // printf("ERRO: Contrato nao existente\n");
                        break;
                }

                break;
            }

            case 8:{
                x = geraFatura(max_cliente,3*max_filme,mat_historico,vet_contrato,c_contratos,vet_cliente,c_cliente,vet_filme,c_filme,&mes_atual,plano_basico,plano_premium,c_filme_cliente);
                
                switch(x){

                    case 1:
                        printf("ERRO: Cliente nao cadastrado\n");
                        break;
                    case 2:
                        printf("ERRO: Nenhum filme assistido\n");
                        break;

                }
                break;
            }

            case 9:{
                imprimeCliente(vet_cliente, c_cliente);
                break;
            }

            case 10:{

                x = imprimeHistorico(max_cliente,3*max_filme,mat_historico,c_filme_cliente,vet_cliente,c_cliente,vet_filme,c_filme);
                
                switch(x){

                    case 1:
                        printf("ERRO: Cliente nao cadastrado\n");
                        break;
                    case 2:
                        printf("ERRO: Nenhum filme assistido\n");
                        break;

                }
                
                break;
            }

            case 11:{
                imprimeClienteExcedente(vet_cliente,c_cliente,vet_filme,c_filme,vet_contrato,c_contratos,c_filme_cliente,plano_basico);
                break;
            }

            case 12:{
                x = frequenciaFilme(max_cliente,3*max_filme,mat_historico,c_filme_cliente,vet_filme,c_filme,c_cliente);
                if(x == 1) printf("ERRO: Codigo invalido\n");
                if(x == 2) printf("ERRO: Nenhum filme assistido\n");
                break;
            }

            case 13:{
                x = recomendaFilme(vet_cliente,c_cliente,max_cliente,max_filme,mat_historico,c_filme_cliente,vet_filme,c_filme);
                switch(x){

                    case 1:
                        printf("ERRO: Cliente nao cadastrado\n");
                        break;
                    case 2:
                        printf("ERRO: Cliente nao ativo\n");
                        break;
                    case 3:
                        printf("ERRO: Todos os filmes do genero foram assistidos\n");
                        break;
                    case 4:
                        printf("ERRO: Nenhum filme assistido\n");

                }
                break;
            }

            case 0:{
                printf("c_cliente: %d\n", c_cliente);
                printf("c_filme: %d\n", c_filme);
                printf("c_filme_cliente: %d\n", c_filme_cliente[0]);

                printf("Finalizando programa...");
                break;
            }

            default: printf("ERRO: opcao invalida\n");
        }

    }while(opcao != 0);



    return 0;
}