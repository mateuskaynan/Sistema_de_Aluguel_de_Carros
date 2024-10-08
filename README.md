# Sistema de Gerenciamento de Aluguel de Carros

## Descrição

Este projeto implementa um sistema de gerenciamento de aluguel de carros, permitindo a adição, edição, exclusão e consulta de clientes e veículos. O sistema também possibilita o aluguel de carros e armazena os dados em arquivos de texto.

## Estrutura do Projeto

O código é dividido em três arquivos principais:

- `sistema.c`: Contém a implementação das funções do sistema.
- `sistema.h`: Declaração das funções e definições de estruturas.
- `main.c`: Ponto de entrada do programa, que inicializa o sistema.

## Estruturas de Dados

### Cliente

```c
struct cliente {
    char nome[MAX_NOME];
    char documento_cliente[MAX_DOCUMENTO];
    char telefone_cliente[MAX_TELEFONE];
    char data_aluguel[11];
    int duracao_aluguel;
    struct cliente* prox_cliente;
    struct cliente* cliente_ant;
};
```
- `nome`: nome do cliente
- `documento_cliente`: Documento de identificação do cliente.
- `telefoneo_cliente`: Telefone para contato.
- `data_aluguel`: Data do aluguel.
- `duracao_aluguel`: Duração do aluguel em dias.
- `prox_cliente`: Ponteiro para o próximo cliente na lista.
- `cliente_ant`: Ponteiro para cliente anterior.

### Carro

```c
struct carro {
    int codigo_carro;
    char modelo[MAX_MODELO];
    float preco_carro;
    int disponibilidade;
    struct carro* carro_ant;
    struct carro* prox_carro;
};
```
- `codigo_carro`: Código de identificação do carro
- `modelo`: Modelo do carro.
- `preco_carro`: Preço da diária do carro.
- `disponibilidade`: Disponibilidade do carro.
- `carro_ant`: Ponteiro para o carro anterior da lista.
- `prox_carro`: Ponteiro para o próximo carro da lista. 

## Sistema

```c
struct sistema {
    Carro* carro;
    Cliente* cliente;
};
```
- `carro`: Ponteiro para a lista de carros.
- `cliente`: Ponteiro para a lista de clientes.

# Funcionalidades
## Menu Principal
O sistema possui um menu com as seguintes opções: 
- Adicionar Cliente
- Excluir Cliente
- Buscar Cliente
- Consultar Clientes
- Editar Cliente
- Adicionar Carro
- Listar Carros
- Consultar Carros Disponíveis
- Alugar Carro
- Sair do Menu

## Operações 
- `Adicionar cliente:`: Permite adicionar um novo cliente ao sistema.
- `Excluir Cliente`: Remove um cliente existente com base no documento.
- `Buscar Cliente`: Pesquisa um cliente pelo nome.
- `Consultar Clientes`: Lista todos os clientes cadastrados.
- `Editar Cliente`: Atualiza os dados de um cliente.
- `Adicionar Carro`: Adiciona um novo carro ao sistema.
- `Listar Carros`: Exibe todos os carros cadastrados.
- `Consultar Carros Disponíveis`: Mostra os carros disponíveis para aluguel.
- `Alugar Carro`: Realiza o aluguel de um carro para um cliente.

## Persistência de Dados
Os dados de clientes e carros são salvos em arquivos de texto (`carros.txt` e `clientes.txt`). O sistema carrega esses dados na inicialização.

## Conclusão
Este sistema oferece uma maneira simples e eficiente de gerenciar o aluguel de carros e seus clientes, facilitando operações comuns em um ambiente de aluguel.
