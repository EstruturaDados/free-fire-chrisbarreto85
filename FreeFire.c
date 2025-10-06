#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

// Código da Ilha – Edição Free Fire
// Nível: Mestre
// Este programa simula o gerenciamento avançado de uma mochila com componentes coletados durante a fuga de uma ilha.
// Ele introduz ordenação com critérios e busca binária para otimizar a gestão dos recursos.

// Definição da struct para armazenar os dados de cada item
struct Item {
    char nome[30];      // Nome do item (ex: "Faca", "Bandagem")
    char tipo[20];      // Tipo do item (ex: "arma", "municao", "cura")
    int quantidade;     // Quantidade do item
};

// Variáveis globais (simples para iniciantes)
struct Item mochila[10];  // Array para guardar até 10 itens
int totalItens = 0;       // Contador de quantos itens temos

// Função para cadastrar um novo item
void inserirItem() {
    // Verifica se ainda tem espaço na mochila
    if (totalItens >= 10) {
        printf("Mochila cheia! Não pode adicionar mais itens.\n");
        return;
    }
    
    printf("\n--- Cadastrar Novo Item ---\n");
    
    // Pede os dados do usuário
    printf("Digite o nome: ");
    scanf("%s", mochila[totalItens].nome);
    
    printf("Digite o tipo (arma/municao/cura): ");
    scanf("%s", mochila[totalItens].tipo);
    
    printf("Digite a quantidade: ");
    scanf("%d", &mochila[totalItens].quantidade);
    
    totalItens++; // Aumenta o contador
    printf("Item adicionado com sucesso!\n");
}

// Função para remover um item
void removerItem() {
    if (totalItens == 0) {
        printf("Mochila vazia! Não há itens para remover.\n");
        return;
    }
    
    printf("\n--- Remover Item ---\n");
    char nomeBusca[30];
    
    printf("Digite o nome do item para remover: ");
    scanf("%s", nomeBusca);
    
    // Procura o item na mochila
    for (int i = 0; i < totalItens; i++) {
        if (strcmp(mochila[i].nome, nomeBusca) == 0) {
            // Move todos os itens depois dele uma posição para frente
            for (int j = i; j < totalItens - 1; j++) {
                mochila[j] = mochila[j + 1];
            }
            totalItens--; // Diminui o contador
            printf("Item removido com sucesso!\n");
            return;
        }
    }
    
    printf("Item não encontrado!\n");
}

// Função para mostrar todos os itens
void listarItens() {
    printf("\n--- Itens na Mochila ---\n");
    
    if (totalItens == 0) {
        printf("Mochila vazia!\n");
        return;
    }
    
    // Mostra cada item um por um
    for (int i = 0; i < totalItens; i++) {
        printf("Item %d:\n", i + 1);
        printf("  Nome: %s\n", mochila[i].nome);
        printf("  Tipo: %s\n", mochila[i].tipo);
        printf("  Quantidade: %d\n", mochila[i].quantidade);
        printf("-------------------\n");
    }
}

// Função para buscar um item pelo nome
void buscarItem() {
    printf("\n--- Buscar Item ---\n");
    char nomeBusca[30];
    
    printf("Digite o nome do item para buscar: ");
    scanf("%s", nomeBusca);
    
    // Procura o item na mochila
    for (int i = 0; i < totalItens; i++) {
        if (strcmp(mochila[i].nome, nomeBusca) == 0) {
            printf("Item encontrado!\n");
            printf("Nome: %s\n", mochila[i].nome);
            printf("Tipo: %s\n", mochila[i].tipo);
            printf("Quantidade: %d\n", mochila[i].quantidade);
            return;
        }
    }
    
    printf("Item não encontrado!\n");
}

// Função principal com menu
int main() {
    int opcao;
    
    printf("=== SISTEMA DE MOCHILA - JOGO DE SOBREVIVÊNCIA ===\n");
    
    do {
        // Menu de opções
        printf("\nO que você quer fazer?\n");
        printf("1 - Adicionar item\n");
        printf("2 - Remover item\n");
        printf("3 - Ver todos os itens\n");
        printf("4 - Buscar item\n");
        printf("0 - Sair\n");
        printf("Escolha uma opção: ");
        scanf("%d", &opcao);
        
        // Executa a opção escolhida
        switch (opcao) {
            case 1:
                inserirItem();
                break;
            case 2:
                removerItem();
                break;
            case 3:
                listarItens();
                break;
            case 4:
                buscarItem();
                break;
            case 0:
                printf("Saindo do sistema... Até logo!\n");
                break;
            default:
                printf("Opção inválida! Tente novamente.\n");
        }
        
    } while (opcao != 0); // Repete até o usuário escolher sair
    
    return 0;
}