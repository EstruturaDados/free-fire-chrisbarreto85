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

// ========== FUNÇÕES DO VETOR ==========

void inserirVetor() {
    if (totalItensVetor >= 10) {
        printf("❌ Mochila (vetor) cheia!\n");
        return;
    }
    
    printf("\n--- Adicionar Item no VETOR ---\n");
    printf("Nome: ");
    scanf("%s", mochilaVetor[totalItensVetor].nome);
    printf("Tipo (arma/municao/cura): ");
    scanf("%s", mochilaVetor[totalItensVetor].tipo);
    printf("Quantidade: ");
    scanf("%d", &mochilaVetor[totalItensVetor].quantidade);
    
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
    scanf("%s", nome);
    
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
    comparacoesVetor = 0;
    char nome[30];
    printf("Nome para buscar: ");
    scanf("%s", nome);
    
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
    comparacoesVetor = 0;
    char nome[30];
    printf("Nome para busca binária: ");
    scanf("%s", nome);
    
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
    scanf("%s", novoNo->dados.nome);
    printf("Tipo (arma/municao/cura): ");
    scanf("%s", novoNo->dados.tipo);
    printf("Quantidade: ");
    scanf("%d", &novoNo->dados.quantidade);
    
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
    scanf("%s", nome);
    
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
    comparacoesLista = 0;
    char nome[30];
    printf("Nome para buscar: ");
    scanf("%s", nome);
    
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
    
    while (atual != NULL) {
        printf("%d. %s | %s | %d unidades\n", 
               contador, atual->dados.nome, atual->dados.tipo, atual->dados.quantidade);
        atual = atual->proximo;
        contador++;
    }
    
    if (contador == 1) {
        printf("Lista vazia!\n");
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
        scanf("%d", &opcao);
        
        switch (opcao) {
            case 1: inserirVetor(); break;
            case 2: removerVetor(); break;
            case 3: listarVetor(); break;
            case 4: ordenarVetor(); break;
            case 5: buscarSequencialVetor(); break;
            case 6: buscarBinariaVetor(); break;
            case 0: printf("Voltando...\n"); break;
            default: printf("❌ Opção inválida!\n");
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
        scanf("%d", &opcao);
        
        switch (opcao) {
            case 1: inserirLista(); break;
            case 2: removerLista(); break;
            case 3: listarLista(); break;
            case 4: buscarLista(); break;
            case 0: printf("Voltando...\n"); break;
            default: printf("❌ Opção inválida!\n");
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
        scanf("%d", &opcao);
        
        switch (opcao) {
            case 1: menuVetor(); break;
            case 2: menuLista(); break;
            case 0: printf("Saindo...\n"); break;
            default: printf("❌ Opção inválida!\n");
        }
    } while (opcao != 0);
    
    return 0;
}