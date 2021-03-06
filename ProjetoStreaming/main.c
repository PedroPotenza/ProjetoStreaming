#include "header/tipos.h"
#include "header/prototipos.h"
#include "code/cadastrar.c"
#include "code/listar.c"
#include "code/validar.c"
#include "code/outro.c"

#include <stdio.h>

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
                        printf("ERRO: Nenhum cliente cadastrado no sistema\n");
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
                    case 7:
                        printf("ERRO: Taxa adicional negada\n");
                        break;
                    case 8: 
                        printf("ERRO: Nenhum cliente cadastrado no sistema\n");
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
                        printf("ERRO: Data de cancelamente anteiror a data de contratacao\n");
                        break;
                    case 2: 
                        printf("ERRO: Cliente nao cadastrado\n");
                        break;
                    case 3: 
                        printf("ERRO: Cliente inativo\n");
                        break;
                    case 4: 
                        printf("ERRO: Cliente nao possui contrato\n"); // printf("ERRO: Contrato nao existente\n");
                        //nao roda nunca //retirar no enunciado
                        break;
                    case 5: 
                        printf("ERRO: Nenhum contrato cadastrado no sistema\n");
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
                        printf("ERRO: Cliente nao possui contrato\n");
                        break;
                    case 3: 
                        printf("ERRO: Nenhum cliente cadastrado no sistema\n");
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
                    case 3: 
                        printf("ERRO: Nenhum cliente cadastrado no sistema\n");
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
                if(x == 3) printf("ERRO: Nenhum filme cadastrado no sistema\n");
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
                        printf("ERRO: Todos os filmes do(s) genero(s) foram assistidos\n");
                        break;
                    case 4:
                        printf("ERRO: Nenhum filme assistido\n");
                    case 5: 
                        printf("ERRO: Nenhum cliente cadastrado no sistema\n");
                        break;

                }
                break;
            }

            case 0:{
                printf("Finalizando programa...");
                break;
            }

            default: printf("ERRO: Opcao invalida\n");
        }

    }while(opcao != 0);



    return 0;
}