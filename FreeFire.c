#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

// Código da Ilha – Edição Free Fire
// Nível: Mestre
// Este programa simula o gerenciamento avançado de uma mochila com componentes coletados durante a fuga de uma ilha.
// Ele introduz ordenação com critérios e busca binária para otimizar a gestão dos recursos.

// Estrutura do Item
struct Item {
    char nome[30];
    char tipo[20];
    int quantidade;
};

// Estrutura do Nó para lista encadeada
struct No {
    struct Item dados;
    struct No* proximo;
};

// Variáveis globais para o VETOR
struct Item mochilaVetor[10];
int totalItensVetor = 0;
int comparacoesVetor = 0;

// Variáveis globais para a LISTA ENCADEADA
struct No* inicioLista = NULL;
int comparacoesLista = 0;

// ========== FUNÇÃO PARA LER NÚMEROS COM SEGURANÇA ==========
int lerNumero() {
    char input[100];
    int numero;
    int resultado;
    
    while (1) {
        if (fgets(input, sizeof(input), stdin) != NULL) {
            // Remove o \n do final se existir
            input[strcspn(input, "\n")] = 0;
            
            // Tenta converter para número
            resultado = sscanf(input, "%d", &numero);
            
            if (resultado == 1) {
                return numero;  // Número válido
            } else {
                printf("❌ Entrada inválida! Digite um número: ");
            }
        }
    }
}

// ========== FUNÇÃO PARA LER STRINGS COM SEGURANÇA ==========
void lerString(char* destino, int tamanho) {
    char input[100];
    
    if (fgets(input, sizeof(input), stdin) != NULL) {
        // Remove o \n do final
        input[strcspn(input, "\n")] = 0;
        
        // Copia apenas o que couber
        strncpy(destino, input, tamanho - 1);
        destino[tamanho - 1] = '\0'; // Garante que termina com \0
    }
}

// ========== FUNÇÕES DO VETOR ==========

void inserirVetor() {
    if (totalItensVetor >= 10) {
        printf("❌ Mochila (vetor) cheia!\n");
        return;
    }
    
    printf("\n--- Adicionar Item no VETOR ---\n");
    
    printf("Nome: ");
    lerString(mochilaVetor[totalItensVetor].nome, 30);
    
    printf("Tipo (arma/municao/cura): ");
    lerString(mochilaVetor[totalItensVetor].tipo, 20);
    
    printf("Quantidade: ");
    mochilaVetor[totalItensVetor].quantidade = lerNumero();
    
    totalItensVetor++;
    printf("✅ Item adicionado no vetor!\n");
}

void removerVetor() {
    if (totalItensVetor == 0) {
        printf("❌ Mochila (vetor) vazia!\n");
        return;
    }
    
    char nome[30];
    printf("Nome do item para remover: ");
    lerString(nome, 30);
    
    for (int i = 0; i < totalItensVetor; i++) {
        if (strcmp(mochilaVetor[i].nome, nome) == 0) {
            // Move todos os itens para preencher o espaço
            for (int j = i; j < totalItensVetor - 1; j++) {
                mochilaVetor[j] = mochilaVetor[j + 1];
            }
            totalItensVetor--;
            printf("✅ Item removido do vetor!\n");
            return;
        }
    }
    printf("❌ Item não encontrado no vetor!\n");
}

void ordenarVetor() {
    if (totalItensVetor == 0) {
        printf("❌ Vetor vazio! Não há itens para ordenar.\n");
        return;
    }
    
    // Bubble Sort simples para ordenar por nome
    for (int i = 0; i < totalItensVetor - 1; i++) {
        for (int j = 0; j < totalItensVetor - i - 1; j++) {
            if (strcmp(mochilaVetor[j].nome, mochilaVetor[j + 1].nome) > 0) {
                // Troca os itens
                struct Item temp = mochilaVetor[j];
                mochilaVetor[j] = mochilaVetor[j + 1];
                mochilaVetor[j + 1] = temp;
            }
        }
    }
    printf("✅ Vetor ordenado por nome!\n");
}

void buscarSequencialVetor() {
    if (totalItensVetor == 0) {
        printf("❌ Vetor vazio! Não há itens para buscar.\n");
        return;
    }
    
    comparacoesVetor = 0;
    char nome[30];
    printf("Nome para buscar: ");
    lerString(nome, 30);
    
    for (int i = 0; i < totalItensVetor; i++) {
        comparacoesVetor++;
        if (strcmp(mochilaVetor[i].nome, nome) == 0) {
            printf("✅ Item encontrado no vetor!\n");
            printf("Nome: %s, Tipo: %s, Quantidade: %d\n", 
                   mochilaVetor[i].nome, mochilaVetor[i].tipo, mochilaVetor[i].quantidade);
            printf("Comparações: %d\n", comparacoesVetor);
            return;
        }
    }
    printf("❌ Item não encontrado! Comparações: %d\n", comparacoesVetor);
}

void buscarBinariaVetor() {
    if (totalItensVetor == 0) {
        printf("❌ Vetor vazio! Não há itens para buscar.\n");
        return;
    }
    
    comparacoesVetor = 0;
    char nome[30];
    printf("Nome para busca binária: ");
    lerString(nome, 30);
    
    int inicio = 0;
    int fim = totalItensVetor - 1;
    
    while (inicio <= fim) {
        int meio = (inicio + fim) / 2;
        comparacoesVetor++;
        
        int comparacao = strcmp(mochilaVetor[meio].nome, nome);
        
        if (comparacao == 0) {
            printf("✅ Item encontrado (busca binária)!\n");
            printf("Nome: %s, Tipo: %s, Quantidade: %d\n", 
                   mochilaVetor[meio].nome, mochilaVetor[meio].tipo, mochilaVetor[meio].quantidade);
            printf("Comparações: %d\n", comparacoesVetor);
            return;
        }
        else if (comparacao < 0) {
            inicio = meio + 1;
        }
        else {
            fim = meio - 1;
        }
    }
    printf("❌ Item não encontrado! Comparações: %d\n", comparacoesVetor);
}

void listarVetor() {
    printf("\n--- Itens no VETOR (%d itens) ---\n", totalItensVetor);
    if (totalItensVetor == 0) {
        printf("Vetor vazio!\n");
        return;
    }
    
    for (int i = 0; i < totalItensVetor; i++) {
        printf("%d. %s | %s | %d unidades\n", 
               i + 1, mochilaVetor[i].nome, mochilaVetor[i].tipo, mochilaVetor[i].quantidade);
    }
}

// ========== FUNÇÕES DA LISTA ENCADEADA ==========

void inserirLista() {
    struct No* novoNo = (struct No*)malloc(sizeof(struct No));
    
    printf("\n--- Adicionar Item na LISTA ---\n");
    
    printf("Nome: ");
    lerString(novoNo->dados.nome, 30);
    
    printf("Tipo (arma/municao/cura): ");
    lerString(novoNo->dados.tipo, 20);
    
    printf("Quantidade: ");
    novoNo->dados.quantidade = lerNumero();
    
    novoNo->proximo = inicioLista;
    inicioLista = novoNo;
    
    printf("✅ Item adicionado na lista!\n");
}

void removerLista() {
    if (inicioLista == NULL) {
        printf("❌ Lista vazia!\n");
        return;
    }
    
    char nome[30];
    printf("Nome do item para remover: ");
    lerString(nome, 30);
    
    struct No* atual = inicioLista;
    struct No* anterior = NULL;
    
    while (atual != NULL) {
        if (strcmp(atual->dados.nome, nome) == 0) {
            if (anterior == NULL) {
                // Remove o primeiro item
                inicioLista = atual->proximo;
            } else {
                // Remove item do meio/final
                anterior->proximo = atual->proximo;
            }
            free(atual);
            printf("✅ Item removido da lista!\n");
            return;
        }
        anterior = atual;
        atual = atual->proximo;
    }
    printf("❌ Item não encontrado na lista!\n");
}

void buscarLista() {
    if (inicioLista == NULL) {
        printf("❌ Lista vazia! Não há itens para buscar.\n");
        return;
    }
    
    comparacoesLista = 0;
    char nome[30];
    printf("Nome para buscar: ");
    lerString(nome, 30);
    
    struct No* atual = inicioLista;
    
    while (atual != NULL) {
        comparacoesLista++;
        if (strcmp(atual->dados.nome, nome) == 0) {
            printf("✅ Item encontrado na lista!\n");
            printf("Nome: %s, Tipo: %s, Quantidade: %d\n", 
                   atual->dados.nome, atual->dados.tipo, atual->dados.quantidade);
            printf("Comparações: %d\n", comparacoesLista);
            return;
        }
        atual = atual->proximo;
    }
    printf("❌ Item não encontrado! Comparações: %d\n", comparacoesLista);
}

void listarLista() {
    printf("\n--- Itens na LISTA ENCADEADA ---\n");
    struct No* atual = inicioLista;
    int contador = 1;
    
    if (atual == NULL) {
        printf("Lista vazia!\n");
        return;
    }
    
    while (atual != NULL) {
        printf("%d. %s | %s | %d unidades\n", 
               contador, atual->dados.nome, atual->dados.tipo, atual->dados.quantidade);
        atual = atual->proximo;
        contador++;
    }
}

// ========== MENU PRINCIPAL ==========

void menuVetor() {
    int opcao;
    do {
        printf("\n=== MENU VETOR ===\n");
        printf("1. Inserir item\n");
        printf("2. Remover item\n");
        printf("3. Listar itens\n");
        printf("4. Ordenar vetor (por nome)\n");
        printf("5. Busca sequencial\n");
        printf("6. Busca binária (após ordenar)\n");
        printf("0. Voltar\n");
        printf("Escolha: ");
        
        opcao = lerNumero();
        
        switch (opcao) {
            case 1: inserirVetor(); break;
            case 2: removerVetor(); break;
            case 3: listarVetor(); break;
            case 4: ordenarVetor(); break;
            case 5: buscarSequencialVetor(); break;
            case 6: buscarBinariaVetor(); break;
            case 0: printf("Voltando ao menu principal...\n"); break;
            default: printf("❌ Opção inválida! Digite 0-6.\n");
        }
    } while (opcao != 0);
}

void menuLista() {
    int opcao;
    do {
        printf("\n=== MENU LISTA ENCADEADA ===\n");
        printf("1. Inserir item\n");
        printf("2. Remover item\n");
        printf("3. Listar itens\n");
        printf("4. Busca sequencial\n");
        printf("0. Voltar\n");
        printf("Escolha: ");
        
        opcao = lerNumero();
        
        switch (opcao) {
            case 1: inserirLista(); break;
            case 2: removerLista(); break;
            case 3: listarLista(); break;
            case 4: buscarLista(); break;
            case 0: printf("Voltando ao menu principal...\n"); break;
            default: printf("❌ Opção inválida! Digite 0-4.\n");
        }
    } while (opcao != 0);
}

int main() {
    int opcao;
    
    printf("=== SISTEMA DE MOCHILA - VETOR vs LISTA ENCADEADA ===\n");
    
    do {
        printf("\n=== MENU PRINCIPAL ===\n");
        printf("1. Trabalhar com VETOR\n");
        printf("2. Trabalhar com LISTA ENCADEADA\n");
        printf("0. Sair\n");
        printf("Escolha: ");
        
        opcao = lerNumero();
        
        switch (opcao) {
            case 1: menuVetor(); break;
            case 2: menuLista(); break;
            case 0: printf("Saindo... Até logo!\n"); break;
            default: printf("❌ Opção inválida! Digite 0, 1 ou 2.\n");
        }
    } while (opcao != 0);
    
    return 0;
}