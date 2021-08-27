#include "header/tipos.h"
#include "header/prototipos.h"

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

int main(void){

    //CONSTANTES
    const int max_cliente = 10;
    const int max_filme = 10;
    const int max_contratos = 10;

    //CONTADORES
    int c_cliente=0, c_filme=0, c_contratos=0;
    int c_filme_cliente[max_cliente]; //contador de quantos filmes aquele (index) cliente viu 

    //VETORES E MATRIZ
    CLIENTE vet_cliente[max_cliente];
    FILME vet_filme[max_filme];
    CONTRATO vet_contrato[max_contratos];
    HISTORICO mat_historico[max_cliente][3*max_filme];

    PLANO_BASICO plano_basico;
    PLANO_PREMIUM plano_premium;

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
	printf("   0 - Sair\n"); 
	printf("---------------------------------- \n");

    do{
        scanf("%d", &opcao);

        switch(opcao){

            case 1:{
                x = cadastroCliente(vet_cliente, &c_cliente, max_cliente, c_filme_cliente);
                if(x==1){
                    printf("ERRO: Numero maximo de clientes no sistema atingido");
                } else {
                    printf("Cadastrado com sucesso");
                }
                break;
            }

            case 2:{

                break;

            }

            case 3:{

                break;
            }

            case 4:{

                break;
            }

            case 5:{

                break;
            }

            case 6:{

                break;
            }

            case 7:{

                break;
            }

            case 8:{

                break;
            }

            case 9:{

                break;
            }

            case 10:{

                break;
            }

            case 11:{

                break;
            }

            case 12:{

                break;
            }

            case 13:{

                break;
            }

            case 14:{

                break;
            }

            case 0:{
                printf("c_cliente: %d\n", c_cliente);
                printf("c_filme_cliente: %d\n", c_cliente);

                printf("Finalizando programa...");
                break;
            }

            default: printf("ERRO: opcao invalida\n");
        }

    }while(opcao != 0);



    return 0;
}