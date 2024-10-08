#include "sistema.h"

#define MAX_NOME 51
#define MAX_DOCUMENTO 12
#define MAX_TELEFONE 10
#define MAX_MODELO 16
#define ARQUIVO_CARROS "carros.txt"
#define ARQUIVO_CLIENTES "clientes.txt"

struct cliente {
    char nome[MAX_NOME];
    char documento_cliente[MAX_DOCUMENTO];
    char telefone_cliente[MAX_TELEFONE];
    char data_aluguel[11];
    int duracao_aluguel;
    struct cliente* prox_cliente;
    struct cliente* cliente_ant;
};

struct carro {
    int codigo_carro;
    char modelo[MAX_MODELO];
    float preco_carro;
    int disponibilidade;
    struct carro* carro_ant;
    struct carro* prox_carro;
};

struct sistema {
    Carro* carro;
    Cliente* cliente;
};

void menu(Sistema* sistema) {
    char nome_cliente[MAX_NOME];
    char documento_cliente[MAX_DOCUMENTO];
    char telefone_cliente[MAX_TELEFONE];
    char data_aluguel[11];
    int opcao, codigo_carro, duracao;

    do {
        printf("\n========== MENU DE OPCOES ==========\n");
        printf("[1] ADICIONAR CLIENTE\n");
        printf("[2] EXCLUIR CLIENTE\n");
        printf("[3] BUSCAR CLIENTE\n");
        printf("[4] CONSULTAR CLIENTES\n");
        printf("[5] EDITAR CLIENTE\n");
        printf("[6] ADICIONAR CARRO\n"); // Opção para adicionar carro
        printf("[7] LISTAR CARROS\n");
        printf("[8] CONSULTAR CARROS DISPONIVEIS\n");
        printf("[9] ALUGAR CARRO\n");
        printf("[10] SAIR DO MENU\n");
        printf("===================================\n");
        printf("DIGITE A OPCAO QUE DESEJA: ");
        scanf("%d", &opcao);
        getchar(); // Limpa o buffer

        switch (opcao) {
            case 1:
                // Adicionar cliente
                {
                    printf("\n===> ADICIONANDO CLIENTE\n");
                    printf("NOME: ");
                    fgets(nome_cliente, MAX_NOME, stdin);
                    nome_cliente[strcspn(nome_cliente, "\n")] = 0;

                    printf("DOCUMENTO: ");
                    fgets(documento_cliente, MAX_DOCUMENTO, stdin);
                    documento_cliente[strcspn(documento_cliente, "\n")] = 0;

                    printf("TELEFONE: ");
                    fgets(telefone_cliente, MAX_TELEFONE, stdin);
                    telefone_cliente[strcspn(telefone_cliente, " \n ")] = 0;

                    printf("DATA DO ALUGUEL (DD/MM/AAAA): ");
                    fgets(data_aluguel, sizeof(data_aluguel), stdin);
                    data_aluguel[strcspn(data_aluguel, " \n")] = 0;

                    printf("DURACAO DO ALUGUEL (DIAS): ");
                    scanf("%d", &duracao);
                    getchar(); // Limpa o buffer

                    Cliente* novo_cliente = cria_cliente(nome_cliente, documento_cliente, telefone_cliente, data_aluguel, duracao);
                    adiciona_cliente(sistema, novo_cliente);
                    salva_dados(sistema);
                }
                break;

            case 2:
                // Excluir cliente
                {
                    printf("\n===> EXCLUINDO CLIENTE\n");
                    printf("DOCUMENTO: ");
                    fgets(documento_cliente, MAX_DOCUMENTO, stdin);
                    documento_cliente[strcspn(documento_cliente, "\n")] = 0;
                    excluir_cliente(sistema, documento_cliente);
                    salva_dados(sistema);
                }
                break;

            case 3:
                // Buscar cliente
                {
                    printf("\n===> BUSCANDO CLIENTE\n");
                    printf("- DIGITE O NOME DO CLIENTE: ");
                    fgets(nome_cliente, MAX_NOME, stdin);
                    nome_cliente[strcspn(nome_cliente, "\n")] = 0;

                    Cliente* cliente = buscar_cliente(sistema, nome_cliente);
                    if (cliente) {
                        printf("\n>>> DADOS\nNOME: %s\nDOCUMENTO: %s\nTELEFONE: %s\nDATA DO ALUGUEL: %s\nDURACAO: %d DIAS\n",
                               cliente->nome,
                               cliente->documento_cliente,
                               cliente->telefone_cliente,
                               cliente->data_aluguel,
                               cliente->duracao_aluguel);
                    } else {
                        printf("CLIENTE NÃO ENCONTRADO!\n");
                    }
                }
                break;

            case 4:
                // Consultar clientes
                imprime_conta_clientes(sistema);
                break;

            case 5:
                // Editar cliente
                {
                    printf("\n===> EDITANDO CLIENTE\n");
                    printf("NOME DO CLIENTE A EDITAR: ");
                    fgets(nome_cliente, MAX_NOME, stdin);
                    nome_cliente[strcspn(nome_cliente, "\n")] = 0;
                    editar_cliente(sistema, nome_cliente);
                    salva_dados(sistema);
                }
                break;

            case 6: // Adicionar carro
                {
                    int codigo;
                    char modelo[MAX_MODELO];
                    float preco;

                    printf("\n===> ADICIONANDO CARRO\n");
                    printf("CODIGO: ");
                    scanf("%d", &codigo);
                    getchar(); // Limpa o buffer

                    printf("MODELO: ");
                    fgets(modelo, MAX_MODELO, stdin);
                    modelo[strcspn(modelo, "\n")] = 0;

                    printf("PRECO: ");
                    scanf("%f", &preco);
                    getchar(); // Limpa o buffer

                    Carro* novo_carro = criar_carro(codigo, modelo, preco);
                    inserir_carro(sistema, novo_carro);
                    salva_dados(sistema);
                }
                break;

            case 7:
                listar_carros(sistema);
                break;

            case 8:
                consulta_carros_disponiveis(sistema);
                break;

            case 9:
                // Alugar carro
                {
                    printf("\n===> ALUGANDO CARRO\n");
                    printf("DOCUMENTO DO CLIENTE: ");
                    fgets(documento_cliente, MAX_DOCUMENTO, stdin);
                    documento_cliente[strcspn(documento_cliente, "\n")] = 0;

                    printf("CODIGO DO CARRO: ");
                    scanf("%d", &codigo_carro);
                    getchar(); // Limpa o buffer

                    alugar_carro(sistema, documento_cliente, codigo_carro);
                    salva_dados(sistema);
                }
                break;

            case 10:
                printf("\nSAINDO DO PROGRAMA...\n");
                break;

            default:
                printf("OPCAO INVALIDA! TENTE NOVAMENTE.\n");
                break;
        }
    } while (opcao != 10);
}

// Funções para carros
Carro* criar_carro(int codigo, const char* modelo, float preco) {
    Carro* novo_carro = (Carro*)malloc(sizeof(Carro));
    if (novo_carro == NULL) {
        printf("ERRO NA ALOCACAOO!\n");
        exit(1);
    }

    novo_carro->codigo_carro = codigo;
    strcpy(novo_carro->modelo, modelo);
    novo_carro->preco_carro = preco;
    novo_carro->disponibilidade = 1;
    novo_carro->carro_ant = NULL;
    novo_carro->prox_carro = NULL;
    return novo_carro;
}

void inserir_carro(Sistema* sistema, Carro* carro) {
    if (!sistema->carro || carro->codigo_carro < sistema->carro->codigo_carro) {
        carro->prox_carro = sistema->carro;
        if (sistema->carro) {
            sistema->carro->carro_ant = carro;
        }
        sistema->carro = carro;
        carro->carro_ant = NULL;
    } else {
        Carro* carro_posicao = sistema->carro;
        while (carro_posicao->prox_carro && carro_posicao->prox_carro->codigo_carro < carro->codigo_carro) {
            carro_posicao = carro_posicao->prox_carro;
        }
        carro->prox_carro = carro_posicao->prox_carro;
        carro->carro_ant = carro_posicao;
        if (carro_posicao->prox_carro) {
            carro_posicao->prox_carro->carro_ant = carro;
        }
        carro_posicao->prox_carro = carro;
    }
}

void listar_carros(Sistema* sistema) {
    Carro* carro_atual = sistema->carro;
    if (!carro_atual) {
        printf("NENHUM CARRO CADASTRADO!\n");
        return;
    }

    printf("\n===> CARROS CADASTRADOS\n");
    while (carro_atual != NULL) {
        printf("CODIGO: %d\nMODELO: %s\nPRECO: %.2f\nDISPONIBILIDADE: %s\n",
               carro_atual->codigo_carro,
               carro_atual->modelo,
               carro_atual->preco_carro,
               carro_atual->disponibilidade ? "DisponIvel" : "IndIsponIvel");
        carro_atual = carro_atual->prox_carro;
    }
}

void alugar_carro(Sistema* sistema, const char *documento_cliente, int codigo_carro) {
    Carro* carro_atual = sistema->carro;
    while (carro_atual != NULL) {
        if (carro_atual->codigo_carro == codigo_carro) {
            if (carro_atual->disponibilidade) {
                carro_atual->disponibilidade = 0; // Indisponível após aluguel
                printf("CARRO ALUGADO COM SUCESSO!\n");
            } else {
                printf("CARRO JA ESTA ALUGADO!\n");
            }
            return;
        }
        carro_atual = carro_atual->prox_carro;
    }
    printf("CARRO NAO ENCONTRADO!\n");
}

void consulta_carros_disponiveis(Sistema* sistema) {
    Carro* carro_atual = sistema->carro;
    printf("\n===> CARROS DISPONIVEIS\n");
    while (carro_atual != NULL) {
        if (carro_atual->disponibilidade) {
            printf("CODIGO: %d\nMODELO: %s\nPRECO: %.2f\n",
                   carro_atual->codigo_carro,
                   carro_atual->modelo,
                   carro_atual->preco_carro);
        }
        carro_atual = carro_atual->prox_carro;
    }
}

// Funções para clientes
Cliente* cria_cliente(const char* nome, const char* documento, const char* telefone, const char* data_aluguel, int duracao) {
    Cliente* novo_cliente = (Cliente*)malloc(sizeof(Cliente));
    if (!novo_cliente) {
        printf("ERRO NA ALOCACAO DO CLIENTE!\n");
        exit(1);
    }

    strcpy(novo_cliente->nome, nome);
    strcpy(novo_cliente->documento_cliente, documento);
    strcpy(novo_cliente->telefone_cliente, telefone);
    strcpy(novo_cliente->data_aluguel, data_aluguel);
    novo_cliente->duracao_aluguel = duracao;
    novo_cliente->prox_cliente = NULL;
    novo_cliente->cliente_ant = NULL;
    return novo_cliente;
}

void adiciona_cliente(Sistema* sistema, Cliente* cliente) {
    if (!sistema->cliente || strcmp(cliente->documento_cliente, sistema->cliente->documento_cliente) < 0) {
        cliente->prox_cliente = sistema->cliente;
        if (sistema->cliente) {
            sistema->cliente->cliente_ant = cliente;
        }
        sistema->cliente = cliente;
        cliente->cliente_ant = NULL;
    } else {
        Cliente* cliente_posicao = sistema->cliente;
        while (cliente_posicao->prox_cliente && strcmp(cliente_posicao->prox_cliente->documento_cliente, cliente->documento_cliente) < 0) {
            cliente_posicao = cliente_posicao->prox_cliente;
        }
        cliente->prox_cliente = cliente_posicao->prox_cliente;
        cliente->cliente_ant = cliente_posicao;
        if (cliente_posicao->prox_cliente) {
            cliente_posicao->prox_cliente->cliente_ant = cliente;
        }
        cliente_posicao->prox_cliente = cliente;
    }
}

Cliente* buscar_cliente(Sistema* sistema, const char* nome) {
    Cliente* cliente_atual = sistema->cliente;
    while (cliente_atual != NULL) {
        if (strcmp(cliente_atual->nome, nome) == 0) {
            return cliente_atual;
        }
        cliente_atual = cliente_atual->prox_cliente;
    }
    return NULL;
}

void editar_cliente(Sistema* sistema, const char* nome) {
    Cliente* cliente = buscar_cliente(sistema, nome);
    if (!cliente) {
        printf("CLIENTE NAO ENCONTRADO!\n");
        return;
    }

    printf("NOVO NOME (ATUAL: %s): ", cliente->nome);
    char novo_nome[MAX_NOME];
    fgets(novo_nome, MAX_NOME, stdin);
    novo_nome[strcspn(novo_nome, "\n")] = 0;
    if (strlen(novo_nome) > 0) {
        strcpy(cliente->nome, novo_nome);
    }

    printf("NOVO TELEFONE (ATUAL: %s): ", cliente->telefone_cliente);
    char novo_telefone[MAX_TELEFONE];
    fgets(novo_telefone, MAX_TELEFONE, stdin);
    novo_telefone[strcspn(novo_telefone, "\n")] = 0;
    if (strlen(novo_telefone) > 0) {
        strcpy(cliente->telefone_cliente, novo_telefone);
    }

    printf("NOVA DATA DO ALUGUEL (ATUAL: %s): ", cliente->data_aluguel);
    char nova_data[11];
    fgets(nova_data, sizeof(nova_data), stdin);
    nova_data[strcspn(nova_data, "\n")] = 0;
    if (strlen(nova_data) > 0) {
        strcpy(cliente->data_aluguel, nova_data);
    }

    printf("NOVO PERÍODO DE ALUGUEL (ATUAL: %d DIAS): ", cliente->duracao_aluguel);
    int nova_duracao;
    scanf("%d", &nova_duracao);
    cliente->duracao_aluguel = nova_duracao;

    printf("CLIENTE EDITADO COM SUCESSO!\n");
}

void excluir_cliente(Sistema* sistema, const char* documento) {
    Cliente* cliente_atual = sistema->cliente;
    while (cliente_atual != NULL) {
        if (strcmp(cliente_atual->documento_cliente, documento) == 0) {
            if (cliente_atual->cliente_ant) {
                cliente_atual->cliente_ant->prox_cliente = cliente_atual->prox_cliente;
            } else {
                sistema->cliente = cliente_atual->prox_cliente;
            }
            if (cliente_atual->prox_cliente) {
                cliente_atual->prox_cliente->cliente_ant = cliente_atual->cliente_ant;
            }
            free(cliente_atual);
            printf("CLIENTE EXCLUIDO COM SUCESSO!\n");
            return;
        }
        cliente_atual = cliente_atual->prox_cliente;
    }
    printf("CLIENTE NAO ENCONTRADO!\n");
}

int imprime_conta_clientes(Sistema* sistema) {
    Cliente* cliente_atual = sistema->cliente;
    if (!cliente_atual) {
        printf("NENHUM CLIENTE CADASTRADO!\n");
        return 0;
    }

    printf("\n===> CLIENTES CADASTRADOS\n");
    int quantidade = 0; 
    while (cliente_atual != NULL) {
        printf("\nNOME: %s\nDOCUMENTO: %s\nTELEFONE: %s\nDATA DO ALUGUEL: %s\nDURACAO: %d DIAS\n",
               cliente_atual->nome,
               cliente_atual->documento_cliente,
               cliente_atual->telefone_cliente,
               cliente_atual->data_aluguel,
               cliente_atual->duracao_aluguel);
        cliente_atual = cliente_atual->prox_cliente;
        quantidade++; 
    }
    
    printf("\n'%d' CLIENTES CADASTRADOS.", quantidade); 
    return 1;
}

// Funções para salvar e carregar dados
void salva_dados(Sistema* sistema) {
    FILE* arquivo_carros = fopen(ARQUIVO_CARROS, "w");
    FILE* arquivo_clientes = fopen(ARQUIVO_CLIENTES, "w");
    
    if (!arquivo_carros || !arquivo_clientes) {
        printf("ERRO AO ABRIR ARQUIVO PARA SALVAR DADOS!\n");
        return;
    }

    Carro* carro_atual = sistema->carro;
    while (carro_atual) {
        fprintf(arquivo_carros, "%d;%s;%.2f;%d\n", carro_atual->codigo_carro, carro_atual->modelo, carro_atual->preco_carro, carro_atual->disponibilidade);
        carro_atual = carro_atual->prox_carro;
    }

    Cliente* cliente_atual = sistema->cliente;
    while (cliente_atual) {
        fprintf(arquivo_clientes, "%s;%s;%s;%s;%d\n", cliente_atual->nome, cliente_atual->documento_cliente, cliente_atual->telefone_cliente, cliente_atual->data_aluguel, cliente_atual->duracao_aluguel);
        cliente_atual = cliente_atual->prox_cliente;
    }

    fclose(arquivo_carros);
    fclose(arquivo_clientes);
}

void carrega_dados(Sistema* sistema) {
    FILE* arquivo_carros = fopen(ARQUIVO_CARROS, "r");
    FILE* arquivo_clientes = fopen(ARQUIVO_CLIENTES, "r");

    if (!arquivo_carros || !arquivo_clientes) {
        printf("ERRO AO ABRIR ARQUIVO PARA CARREGAR DADOS!\n");
        return;
    }

    while (!feof(arquivo_carros)) {
        Carro* carro = (Carro*)malloc(sizeof(Carro));
        fscanf(arquivo_carros, "%d;%15[^;];%f;%d\n", &carro->codigo_carro, carro->modelo, &carro->preco_carro, &carro->disponibilidade);
        carro->prox_carro = sistema->carro;
        sistema->carro = carro;
    }

    while (!feof(arquivo_clientes)) {
        Cliente* cliente = (Cliente*)malloc(sizeof(Cliente));
        fscanf(arquivo_clientes, "%50[^;];%11[^;];%10[^;];%10[^;];%d\n", cliente->nome, cliente->documento_cliente, cliente->telefone_cliente, cliente->data_aluguel, &cliente->duracao_aluguel);
        cliente->prox_cliente = sistema->cliente;
        sistema->cliente = cliente;
    }

    fclose(arquivo_carros);
    fclose(arquivo_clientes);
}

void libera_memoria(Sistema* sistema) {
    // Libera memória de carros
    Carro* carro_atual = sistema->carro;
    while (carro_atual) {
        Carro* temp = carro_atual;
        carro_atual = carro_atual->prox_carro;
        free(temp);
    }

    // Libera memória de clientes
    Cliente* cliente_atual = sistema->cliente;
    while (cliente_atual) {
        Cliente* temp = cliente_atual;
        cliente_atual = cliente_atual->prox_cliente;
        free(temp);
    }
}