#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_PRODUTOS 100
#define ARQUIVO_ENTRADA "entrada_produtos.txt"
#define ARQUIVO_SAIDA "saida_produtos.txt"

typedef struct {
    int codigo;
    char nome[50];
    int quantidade;
    time_t data_hora;
} Produto;

typedef struct {
    Produto produtos[MAX_PRODUTOS];
    int inicio;
    int fim;
} Fila;

void inicializarFila(Fila *f) {
    f->inicio = 0;
    f->fim = 0;
}

int filaVazia(Fila *f) {
    return f->inicio == f->fim;
}

int filaCheia(Fila *f) {
    return (f->fim + 1) % MAX_PRODUTOS == f->inicio;
}

void enfileirar(Fila *f, Produto p) {
    if (!filaCheia(f)) {
        f->produtos[f->fim] = p;
        f->fim = (f->fim + 1) % MAX_PRODUTOS;
    } else {
        printf("Fila de produtos cheia!\n");
    }
}

Produto desenfileirar(Fila *f) {
    Produto p;
    if (!filaVazia(f)) {
        p = f->produtos[f->inicio];
        f->inicio = (f->inicio + 1) % MAX_PRODUTOS;
        return p;
    } else {
        printf("Fila de produtos vazia!\n");
        p.codigo = -1;
        return p;
    }
}

void registrarEntrada(Fila *f) {
    Produto p;
    
    printf("\n=== Registrar Entrada de Produto ===\n");
    printf("Codigo do produto: ");
    scanf("%d", &p.codigo);
    printf("Nome do produto: ");
    scanf("%s", p.nome);
    printf("Quantidade: ");
    scanf("%d", &p.quantidade);
    
    p.data_hora = time(NULL);
    enfileirar(f, p);
     FILE *arquivo = fopen(ARQUIVO_ENTRADA, "a");
    if (arquivo == NULL) {
        printf("Erro ao abrir arquivo de entrada!\n");
        return;
    }
    
    char data_hora_str[50];
    strftime(data_hora_str, sizeof(data_hora_str), "%d/%m/%Y %H:%M:%S", localtime(&p.data_hora));
    fprintf(arquivo, "ENTRADA - Código: %d | Nome: %s | Quantidade: %d | Data/Hora: %s\n", 
            p.codigo, p.nome, p.quantidade, data_hora_str);
    fclose(arquivo);
    printf("Entrada registrada com sucesso!\n");
}

void registrarSaida(Fila *f) {
    if (filaVazia(f)) {
        printf("Nao tem produtos disponíveis para saida!\n");
        return;
    }
    
    Produto p = desenfileirar(f);
    if (p.codigo == -1) return;
    FILE *arquivo = fopen(ARQUIVO_SAIDA, "a");
    if (arquivo == NULL) {
        printf("Erro ao abrir arquivo de saida!\n");
        return;
    }
    
    char data_hora_str[50];
    strftime(data_hora_str, sizeof(data_hora_str), "%d/%m/%Y %H:%M:%S", localtime(&p.data_hora));
     fprintf(arquivo, "SAÍDA - Código: %d | Nome: %s | Quantidade: %d | Data/Hora: %s\n", 
            p.codigo, p.nome, p.quantidade, data_hora_str);
    fclose(arquivo);
    
    printf("\n=== Saida de Produto Registrada ===\n");
    printf("Codigo: %d\n", p.codigo);
    printf("Nome: %s\n", p.nome);
    printf("Quantidade: %d\n", p.quantidade);
    printf("Data/Hora: %s\n", data_hora_str);
}

void menu() {
    printf("\n=== SISTEMA DE CONTROLE DE PRODUTOS ===\n");
    printf("1. Registrar entrada de produto\n");
    printf("2. Registrar saida de produto\n");
    printf("3. Sair\n");
    printf("Escolha uma opcao: ");
}

int main() {
    Fila fila;
    inicializarFila(&fila);
    int opcao;
    
    do {
        menu();
        scanf("%d", &opcao);
        
        switch(opcao) {
            case 1:
                registrarEntrada(&fila);
                break;
            case 2:
                registrarSaida(&fila);
                break;
            case 3:
                printf("Saindo do sistema...\n");
                break;
            default:
                printf("Opcao invalida!\n");
        }
    } while(opcao != 3);
    
    return 0;
}
