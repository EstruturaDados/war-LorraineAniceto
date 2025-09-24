#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// ==============================
// Estrutura Territorio
// ==============================
typedef struct {
    char nome[30];
    char cor[10];
    int tropas;
} Territorio;

// ==============================
// Cadastro de territórios dinamicamente
// ==============================
Territorio* cadastrarTerritorios(int n) {
    Territorio* mapa = (Territorio*) calloc(n, sizeof(Territorio));
    if (!mapa) {
        printf("Erro na alocacao de memoria!\n");
        exit(1);
    }

    for (int i = 0; i < n; i++) {
        printf("\nTerritorio %d\n", i + 1);

        printf("Nome do territorio: ");
        getchar(); // Limpa buffer
        fgets(mapa[i].nome, sizeof(mapa[i].nome), stdin);
        mapa[i].nome[strcspn(mapa[i].nome, "\n")] = '\0';

        printf("Cor do exercito: ");
        scanf("%9s", mapa[i].cor);

        printf("Quantidade de tropas: ");
        scanf("%d", &mapa[i].tropas);
    }
    return mapa;
}

// ==============================
// Exibição do mapa
// ==============================
void exibirMapa(Territorio* mapa, int n) {
    printf("\n=== Mapa de Territorios ===\n");
    for (int i = 0; i < n; i++) {
        printf("%d. %s (%s) - Tropas: %d\n", i + 1, mapa[i].nome, mapa[i].cor, mapa[i].tropas);
    }
}

// ==============================
// Simulação de ataque
// ==============================
void atacar(Territorio* atacante, Territorio* defensor) {
    int dadoAtacante = rand() % 6 + 1;
    int dadoDefensor = rand() % 6 + 1;

    printf("\nAtaque: %s (%s) -> %s (%s)\n", atacante->nome, atacante->cor, defensor->nome, defensor->cor);
    printf("Dado atacante: %d | Dado defensor: %d\n", dadoAtacante, dadoDefensor);

    if (dadoAtacante > dadoDefensor) {
        printf("Atacante venceu!\n");
        defensor->tropas = atacante->tropas / 2;
        strcpy(defensor->cor, atacante->cor);
    } else {
        printf("Defensor venceu!\n");
        atacante->tropas -= 1;
        if (atacante->tropas < 0) atacante->tropas = 0;
    }
}

// ==============================
// Atribuir missão a um jogador
// ==============================
void atribuirMissao(char** destino, char* missoes[], int totalMissoes) {
    int idx = rand() % totalMissoes;
    strcpy(*destino, missoes[idx]);
}

// ==============================
// Verificar missão cumprida (exemplo simples)
// ==============================
int verificarMissao(char* missao, Territorio* mapa, int n) {
    // Exemplo simples: missão contém "vermelha", verifica se não há territórios vermelhos
    if (strstr(missao, "vermelha")) {
        for (int i = 0; i < n; i++) {
            if (strcmp(mapa[i].cor, "vermelha") == 0) return 0; // Missão não cumprida
        }
        return 1; // Missão cumprida
    }
    // Exemplo: missão "5 ou mais tropas"
    if (strstr(missao, "5 ou mais tropas")) {
        for (int i = 0; i < n; i++) {
            if (mapa[i].tropas >= 5) return 1;
        }
        return 0;
    }
    // Outras missões podem ser adicionadas aqui
    return 0;
}

// ==============================
// Liberar memória
// ==============================
void liberarMemoria(Territorio* mapa, char* missao) {
    free(mapa);
    free(missao);
}

int main() {
    srand(time(NULL));

    // ==============================
    // Cadastro de territórios
    // ==============================
    int n;
    printf("Digite o numero de territorios: ");
    scanf("%d", &n);

    Territorio* mapa = cadastrarTerritorios(n);
    exibirMapa(mapa, n);

    // ==============================
    // Vetor de missões
    // ==============================
    char* missoes[5] = {
        "Conquistar 3 territorios seguidos",
        "Eliminar todas as tropas da cor vermelha",
        "Ter 5 ou mais tropas em um territorio",
        "Controlar todos os territorios azuis",
        "Atacar pelo menos 2 vezes em um turno"
    };

    // ==============================
    // Missão do jogador
    // ==============================
    char* missaoJogador = (char*) malloc(100 * sizeof(char));
    atribuirMissao(&missaoJogador, missoes, 5);
    printf("\nMissao atribuida ao jogador: %s\n", missaoJogador);

    // ==============================
    // Loop de ataques
    // ==============================
    char continuar = 's';
    while (continuar == 's') {
        int atacanteIdx, defensorIdx;

        printf("\nEscolha o territorio atacante (1 a %d): ", n);
        scanf("%d", &atacanteIdx);
        atacanteIdx--;

        printf("Escolha o territorio defensor (1 a %d): ", n);
        scanf("%d", &defensorIdx);
        defensorIdx--;

        if (strcmp(mapa[atacanteIdx].cor, mapa[defensorIdx].cor) == 0) {
            printf("Nao pode atacar um territorio da mesma cor!\n");
        } else {
            atacar(&mapa[atacanteIdx], &mapa[defensorIdx]);
        }

        exibirMapa(mapa, n);

        // ==============================
        // Verificação da missão
        // ==============================
        if (verificarMissao(missaoJogador, mapa, n)) {
            printf("\nParabens! Missao cumprida: %s\n", missaoJogador);
            break;
        }

        printf("\nDeseja realizar outro ataque? (s/n): ");
        getchar();
        scanf("%c", &continuar);
    }

    liberarMemoria(mapa, missaoJogador);
    return 0;
}
