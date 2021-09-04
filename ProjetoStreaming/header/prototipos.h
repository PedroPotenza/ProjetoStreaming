#ifndef PROTOTIPOS_H
#define PROTOTIPOS_H

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

#endif