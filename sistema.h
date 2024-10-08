#ifndef SISTEMA_H
#define SISTEMA_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct cliente Cliente;
typedef struct carro Carro;
typedef struct sistema Sistema;

void menu(Sistema* sistema);
Carro* criar_carro(int codigo, const char* modelo, float preco);
void inserir_carro(Sistema* sistema, Carro* carro);
void listar_carros(Sistema* sistema);
void alugar_carro(Sistema* sistema, const char* documento_cliente, int codigo_carro);
void consulta_carros_disponiveis(Sistema* sistema);
Cliente* cria_cliente(const char* nome, const char* documento, const char* telefone, const char* data_aluguel, int duracao);
Cliente* buscar_cliente(Sistema* sistema, const char* nome);
void editar_cliente(Sistema* sistema, const char* nome);
void excluir_cliente(Sistema* sistema, const char* documento);
void adiciona_cliente(Sistema* sistema, Cliente* cliente);
int imprime_conta_clientes(Sistema* sistema);
void salva_dados(Sistema* sistema);
void carrega_dados(Sistema* sistema);
void libera_memoria(Sistema* sistema);

#endif