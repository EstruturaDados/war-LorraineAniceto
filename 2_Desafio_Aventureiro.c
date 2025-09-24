#include <stdio.h>
#include <string.h>

// ==============================
// Definição da struct Territorio
// ==============================
typedef struct {
    char nome[30];
    char cor[10];
    int tropas;
} Territorio;

int main() {
    Territorio territorios[5]; // Vetor para armazenar 5 territórios
    int i;

    printf("=== Cadastro de Territorios ===\n");

    // Entrada de dados
    for (i = 0; i < 5; i++) {
        printf("\nTerritorio %d\n", i + 1);

        printf("Digite o nome do territorio: ");
        getchar(); // Limpa buffer antes de usar fgets
        fgets(territorios[i].nome, sizeof(territorios[i].nome), stdin);
        territorios[i].nome[strcspn(territorios[i].nome, "\n")] = '\0';

        printf("Digite a cor do exercito: ");
        scanf("%9s", territorios[i].cor);

        printf("Digite a quantidade de tropas: ");
        scanf("%d", &territorios[i].tropas);
    }

    // Exibição dos dados
    printf("\n=== Dados dos Territorios Cadastrados ===\n");
    for (i = 0; i < 5; i++) {
        printf("\nTerritorio %d\n", i + 1);
        printf("Nome: %s\n", territorios[i].nome);
        printf("Cor do exercito: %s\n", territorios[i].cor);
        printf("Quantidade de tropas: %d\n", territorios[i].tropas);
    }

    return 0;
}
