#ifndef PROTOTIPOS_H
#define PROTOTIPOS_H

int verificaCliente(int cpf_local, CLIENTE* vet_cliente, int c_cliente);
int verificaContrato(int cpf_local, CONTRATO* vet_contrato, int c_contrato);
int verificaFilme(int codigo, FILME* vet_filme, int c_filme);

int validaEscopo(int min, int max, char erro[]);
int validaCpf( CLIENTE* vet_cliente, int c_cliente, char erro[]);

int cadastroCliente(CLIENTE* vet_cliente, int* c_cliente, int max_cliente, int* c_filme_cliente);
int cadastroFilme(FILME* vet_filme, int* c_filme, int max_filme);
int cadastroPlanoBasicao(PLANO_BASICO plano_basico);
int cadastroPlanoPremium(PLANO_PREMIUM plano_premium);
int cadastroContrato(CONTRATO* vet_contrato, int* c_contratos, int max_contratos, CLIENTE* vet_cliente, int c_cliente, int mes_atual);

int carregaFilme(int max_cliente, int max_flime, HISTORICO mat[max_cliente][max_flime], int* c_filme_cliente, CLIENTE* vet_cliente, int c_cliente, FILME* vet_filme, int c_filme, CONTRATO* vet_contrato, int c_contrato, PLANO_BASICO plano_basico, int mes_atual);
int cancelarContrato(CONTRATO* vet_contrato, int c_contratos, CLIENTE* vet_cliente, int c_cliente, int mes_atual);

int listaGenero(FILME* vet_filme, int c_filme);
int listaClassificacao(FILME* vet_filme, int c_filme);

void imprimeCliente(CLIENTE* vet_cliente, int c_cliente);

#endif