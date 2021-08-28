#ifndef PROTOTIPOS_H
#define PROTOTIPOS_H

int cadastroCliente(CLIENTE* vet_cliente, int* c_cliente, int max_cliente, int* c_filme_cliente);
int verificaCliente(int cpf_local, CLIENTE* vet_cliente, int c_cliente);

int cadastroFilme(FILME* vet_filme, int* c_filme, int max_filme);
int cadastroPlanoBasicao(PLANO_BASICO plano_basico);
int cadastroPlanoPremium(PLANO_PREMIUM plano_premium);

#endif