#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>

// Código da Ilha – Edição Free Fire
// Nível: Mestre
// Este programa simula o gerenciamento avançado de uma mochila com componentes coletados durante a fuga de uma ilha.
// Ele introduz ordenação com critérios e busca binária para otimizar a gestão dos recursos.

// Estrutura do Item para a mochila
struct Item {
    char nome[30];
    char tipo[20];
    int quantidade;
    int prioridade; // Novo campo para ordenação
};

// Estrutura do Nó para lista encadeada
struct No {
    struct Item dados;
    struct No* proximo;
};

// Variáveis globais para o VETOR
struct Item mochilaVetor[10];
int totalItensVetor = 0;
int comparacoes = 0;
clock_t inicio, fim;

// Variáveis globais para a LISTA ENCADEADA
struct No* inicioLista = NULL;

// ========== FUNÇÕES DE LEITURA SEGURA ==========
int lerNumero() {
    char input[100];
    int numero;
    
    while (1) {
        if (fgets(input, sizeof(input), stdin) != NULL) {
            if (sscanf(input, "%d", &numero) == 1) {
                return numero;
            } else {
                printf("❌ Digite um número válido: ");
            }
        }
    }
}

void lerString(char* destino, int tamanho) {
    char input[100];
    
    if (fgets(input, sizeof(input), stdin) != NULL) {
        input[strcspn(input, "\n")] = 0;
        strncpy(destino, input, tamanho - 1);
        destino[tamanho - 1] = '\0';
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
    printf("Prioridade (1-10): ");
    mochilaVetor[totalItensVetor].prioridade = lerNumero();
    
    // Valida prioridade
    if (mochilaVetor[totalItensVetor].prioridade < 1) 
        mochilaVetor[totalItensVetor].prioridade = 1;
    if (mochilaVetor[totalItensVetor].prioridade > 10) 
        mochilaVetor[totalItensVetor].prioridade = 10;
    
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

// ========== ALGORITMOS DE ORDENAÇÃO PARA VETOR ==========

void bubbleSortNome() {
    if (totalItensVetor == 0) {
        printf("❌ Mochila vazia!\n");
        return;
    }
    
    comparacoes = 0;
    inicio = clock();
    
    printf("\n🔧 Ordenando com Bubble Sort (por nome)...\n");
    
    for (int i = 0; i < totalItensVetor - 1; i++) {
        for (int j = 0; j < totalItensVetor - i - 1; j++) {
            comparacoes++;
            if (strcmp(mochilaVetor[j].nome, mochilaVetor[j + 1].nome) > 0) {
                struct Item temp = mochilaVetor[j];
                mochilaVetor[j] = mochilaVetor[j + 1];
                mochilaVetor[j + 1] = temp;
            }
        }
    }
    
    fim = clock();
    double tempo = ((double)(fim - inicio)) / CLOCKS_PER_SEC;
    printf("✅ Ordenação concluída! Comparações: %d | Tempo: %.4f segundos\n", comparacoes, tempo);
}

void insertionSortTipo() {
    if (totalItensVetor == 0) {
        printf("❌ Mochila vazia!\n");
        return;
    }
    
    comparacoes = 0;
    inicio = clock();
    
    printf("\n🔧 Ordenando com Insertion Sort (por tipo)...\n");
    
    for (int i = 1; i < totalItensVetor; i++) {
        struct Item chave = mochilaVetor[i];
        int j = i - 1;
        
        while (j >= 0) {
            comparacoes++;
            if (strcmp(mochilaVetor[j].tipo, chave.tipo) > 0) {
                mochilaVetor[j + 1] = mochilaVetor[j];
                j--;
            } else {
                break;
            }
        }
        mochilaVetor[j + 1] = chave;
    }
    
    fim = clock();
    double tempo = ((double)(fim - inicio)) / CLOCKS_PER_SEC;
    printf("✅ Ordenação concluída! Comparações: %d | Tempo: %.4f segundos\n", comparacoes, tempo);
}

void selectionSortPrioridade() {
    if (totalItensVetor == 0) {
        printf("❌ Mochila vazia!\n");
        return;
    }
    
    comparacoes = 0;
    inicio = clock();
    
    printf("\n🔧 Ordenando com Selection Sort (por prioridade)...\n");
    
    for (int i = 0; i < totalItensVetor - 1; i++) {
        int maior = i;
        
        for (int j = i + 1; j < totalItensVetor; j++) {
            comparacoes++;
            if (mochilaVetor[j].prioridade > mochilaVetor[maior].prioridade) {
                maior = j;
            }
        }
        
        if (maior != i) {
            struct Item temp = mochilaVetor[i];
            mochilaVetor[i] = mochilaVetor[maior];
            mochilaVetor[maior] = temp;
        }
    }
    
    fim = clock();
    double tempo = ((double)(fim - inicio)) / CLOCKS_PER_SEC;
    printf("✅ Ordenação concluída! Comparações: %d | Tempo: %.4f segundos\n", comparacoes, tempo);
}

// ========== BUSCAS PARA VETOR ==========

void buscarSequencialVetor() {
    if (totalItensVetor == 0) {
        printf("❌ Mochila vazia!\n");
        return;
    }
    
    comparacoes = 0;
    char nome[30];
    printf("Nome para busca sequencial: ");
    lerString(nome, 30);
    
    inicio = clock();
    
    for (int i = 0; i < totalItensVetor; i++) {
        comparacoes++;
        if (strcmp(mochilaVetor[i].nome, nome) == 0) {
            fim = clock();
            double tempo = ((double)(fim - inicio)) / CLOCKS_PER_SEC;
            
            printf("✅ Item encontrado!\n");
            printf("Nome: %s | Tipo: %s | Quantidade: %d | Prioridade: %d\n", 
                   mochilaVetor[i].nome, mochilaVetor[i].tipo, 
                   mochilaVetor[i].quantidade, mochilaVetor[i].prioridade);
            printf("Comparações: %d | Tempo: %.4f segundos\n", comparacoes, tempo);
            return;
        }
    }
    
    fim = clock();
    double tempo = ((double)(fim - inicio)) / CLOCKS_PER_SEC;
    printf("❌ Item não encontrado! Comparações: %d | Tempo: %.4f segundos\n", comparacoes, tempo);
}

void buscarBinariaVetor() {
    if (totalItensVetor == 0) {
        printf("❌ Mochila vazia!\n");
        return;
    }
    
    // Verifica se está ordenado por nome
    int ordenado = 1;
    for (int i = 0; i < totalItensVetor - 1; i++) {
        if (strcmp(mochilaVetor[i].nome, mochilaVetor[i + 1].nome) > 0) {
            ordenado = 0;
            break;
        }
    }
    
    if (!ordenado) {
        printf("⚠️  Precisa ordenar por nome primeiro! Ordenando...\n");
        bubbleSortNome();
    }
    
    char nome[30];
    printf("Nome para busca binária: ");
    lerString(nome, 30);
    
    comparacoes = 0;
    inicio = clock();
    
    int inicioIdx = 0;
    int fimIdx = totalItensVetor - 1;
    int encontrado = -1;
    
    while (inicioIdx <= fimIdx) {
        int meio = (inicioIdx + fimIdx) / 2;
        comparacoes++;
        
        int resultado = strcmp(mochilaVetor[meio].nome, nome);
        
        if (resultado == 0) {
            encontrado = meio;
            break;
        } else if (resultado < 0) {
            inicioIdx = meio + 1;
        } else {
            fimIdx = meio - 1;
        }
    }
    
    fim = clock();
    double tempo = ((double)(fim - inicio)) / CLOCKS_PER_SEC;
    
    if (encontrado != -1) {
        printf("✅ Item encontrado (busca binária)!\n");
        printf("Nome: %s | Tipo: %s | Quantidade: %d | Prioridade: %d\n", 
               mochilaVetor[encontrado].nome, mochilaVetor[encontrado].tipo,
               mochilaVetor[encontrado].quantidade, mochilaVetor[encontrado].prioridade);
    } else {
        printf("❌ Item não encontrado!\n");
    }
    printf("Comparações: %d | Tempo: %.4f segundos\n", comparacoes, tempo);
}

void listarVetor() {
    printf("\n--- Itens no VETOR (%d/10) ---\n", totalItensVetor);
    if (totalItensVetor == 0) {
        printf("Mochila vazia!\n");
        return;
    }
    
    for (int i = 0; i < totalItensVetor; i++) {
        printf("%d. %s | %s | %d unidades | Prioridade: %d\n", 
               i + 1, mochilaVetor[i].nome, mochilaVetor[i].tipo, 
               mochilaVetor[i].quantidade, mochilaVetor[i].prioridade);
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
    printf("Prioridade (1-10): ");
    novoNo->dados.prioridade = lerNumero();
    
    // Valida prioridade
    if (novoNo->dados.prioridade < 1) novoNo->dados.prioridade = 1;
    if (novoNo->dados.prioridade > 10) novoNo->dados.prioridade = 10;
    
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
                inicioLista = atual->proximo;
            } else {
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
        printf("❌ Lista vazia!\n");
        return;
    }
    
    comparacoes = 0;
    char nome[30];
    printf("Nome para buscar: ");
    lerString(nome, 30);
    
    inicio = clock();
    struct No* atual = inicioLista;
    
    while (atual != NULL) {
        comparacoes++;
        if (strcmp(atual->dados.nome, nome) == 0) {
            fim = clock();
            double tempo = ((double)(fim - inicio)) / CLOCKS_PER_SEC;
            
            printf("✅ Item encontrado na lista!\n");
            printf("Nome: %s | Tipo: %s | Quantidade: %d | Prioridade: %d\n", 
                   atual->dados.nome, atual->dados.tipo, 
                   atual->dados.quantidade, atual->dados.prioridade);
            printf("Comparações: %d | Tempo: %.4f segundos\n", comparacoes, tempo);
            return;
        }
        atual = atual->proximo;
    }
    
    fim = clock();
    double tempo = ((double)(fim - inicio)) / CLOCKS_PER_SEC;
    printf("❌ Item não encontrado! Comparações: %d | Tempo: %.4f segundos\n", comparacoes, tempo);
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
        printf("%d. %s | %s | %d unidades | Prioridade: %d\n", 
               contador, atual->dados.nome, atual->dados.tipo, 
               atual->dados.quantidade, atual->dados.prioridade);
        atual = atual->proximo;
        contador++;
    }
}

// ========== MENUS ==========

void menuVetor() {
    int opcao;
    do {
        printf("\n=== 🎒 MENU VETOR (Mochila) ===\n");
        printf("1. ➕ Inserir item\n");
        printf("2. ❌ Remover item\n");
        printf("3. 👀 Listar itens\n");
        printf("4. 🔧 Ordenar por NOME (Bubble Sort)\n");
        printf("5. 🔧 Ordenar por TIPO (Insertion Sort)\n");
        printf("6. 🔧 Ordenar por PRIORIDADE (Selection Sort)\n");
        printf("7. 🔍 Busca sequencial\n");
        printf("8. 🔎 Busca binária (após ordenar)\n");
        printf("0. ↩️  Voltar\n");
        printf("Escolha: ");
        
        opcao = lerNumero();
        
        switch (opcao) {
            case 1: inserirVetor(); break;
            case 2: removerVetor(); break;
            case 3: listarVetor(); break;
            case 4: bubbleSortNome(); break;
            case 5: insertionSortTipo(); break;
            case 6: selectionSortPrioridade(); break;
            case 7: buscarSequencialVetor(); break;
            case 8: buscarBinariaVetor(); break;
            case 0: printf("Voltando...\n"); break;
            default: printf("❌ Opção inválida!\n");
        }
    } while (opcao != 0);
}

void menuLista() {
    int opcao;
    do {
        printf("\n=== 🎒 MENU LISTA ENCADEADA (Mochila) ===\n");
        printf("1. ➕ Inserir item\n");
        printf("2. ❌ Remover item\n");
        printf("3. 👀 Listar itens\n");
        printf("4. 🔍 Busca sequencial\n");
        printf("0. ↩️  Voltar\n");
        printf("Escolha: ");
        
        opcao = lerNumero();
        
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
    
    printf("=== 🎮 SISTEMA DE MOCHILA - JOGO DE SOBREVIVÊNCIA ===\n");
    printf("=== 🔧 Com Algoritmos de Ordenação e Busca ===\n");
    
    do {
        printf("\n=== 🏠 MENU PRINCIPAL ===\n");
        printf("1. 🎒 Trabalhar com VETOR\n");
        printf("2. 🎒 Trabalhar com LISTA ENCADEADA\n");
        printf("0. 🚪 Sair\n");
        printf("Escolha: ");
        
        opcao = lerNumero();
        
        switch (opcao) {
            case 1: menuVetor(); break;
            case 2: menuLista(); break;
            case 0: printf("👋 Saindo... Boa sorte na sobrevivência!\n"); break;
            default: printf("❌ Opção inválida!\n");
        }
    } while (opcao != 0);
    
    return 0;
}
