#include <stdio.h>

#define TAMANHO_TABULEIRO 10
#define TAMANHO_NAVIO 3
#define TAMANHO_HABILIDADE 5   // As matrizes de habilidade serão 5x5

// ===========================
// Funções auxiliares do tabuleiro
// ===========================

// Inicializa o tabuleiro com água (valor 0)
void inicializarTabuleiro(int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO]) {
    for (int i = 0; i < TAMANHO_TABULEIRO; i++) {
        for (int j = 0; j < TAMANHO_TABULEIRO; j++) {
            tabuleiro[i][j] = 0;
        }
    }
}

// Exibe o tabuleiro, com diferentes símbolos para facilitar visualização
void exibirTabuleiro(int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO]) {
    printf("\n   ");
    for (int j = 0; j < TAMANHO_TABULEIRO; j++)
        printf("%2d ", j);
    printf("\n");

    for (int i = 0; i < TAMANHO_TABULEIRO; i++) {
        printf("%2d ", i);
        for (int j = 0; j < TAMANHO_TABULEIRO; j++) {
            if (tabuleiro[i][j] == 0)
                printf(" ~ ");   // Água
            else if (tabuleiro[i][j] == 3)
                printf(" N ");   // Navio
            else if (tabuleiro[i][j] == 5)
                printf(" * ");   // Área de habilidade
        }
        printf("\n");
    }
}

// ===========================
// Funções para posicionar navios
// ===========================

int posicionarNavioHorizontal(int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO], int linha, int coluna) {
    if (coluna + TAMANHO_NAVIO > TAMANHO_TABULEIRO) return 0;
    for (int i = 0; i < TAMANHO_NAVIO; i++)
        if (tabuleiro[linha][coluna + i] != 0) return 0;

    for (int i = 0; i < TAMANHO_NAVIO; i++)
        tabuleiro[linha][coluna + i] = 3;

    return 1;
}

int posicionarNavioVertical(int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO], int linha, int coluna) {
    if (linha + TAMANHO_NAVIO > TAMANHO_TABULEIRO) return 0;
    for (int i = 0; i < TAMANHO_NAVIO; i++)
        if (tabuleiro[linha + i][coluna] != 0) return 0;

    for (int i = 0; i < TAMANHO_NAVIO; i++)
        tabuleiro[linha + i][coluna] = 3;

    return 1;
}

int posicionarNavioDiagonalDescendente(int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO], int linha, int coluna) {
    if (linha + TAMANHO_NAVIO > TAMANHO_TABULEIRO || coluna + TAMANHO_NAVIO > TAMANHO_TABULEIRO) return 0;
    for (int i = 0; i < TAMANHO_NAVIO; i++)
        if (tabuleiro[linha + i][coluna + i] != 0) return 0;

    for (int i = 0; i < TAMANHO_NAVIO; i++)
        tabuleiro[linha + i][coluna + i] = 3;

    return 1;
}

int posicionarNavioDiagonalAscendente(int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO], int linha, int coluna) {
    if (linha - (TAMANHO_NAVIO - 1) < 0 || coluna + TAMANHO_NAVIO > TAMANHO_TABULEIRO) return 0;
    for (int i = 0; i < TAMANHO_NAVIO; i++)
        if (tabuleiro[linha - i][coluna + i] != 0) return 0;

    for (int i = 0; i < TAMANHO_NAVIO; i++)
        tabuleiro[linha - i][coluna + i] = 3;

    return 1;
}

// ===========================
// Criação dinâmica das habilidades
// ===========================

// Cria uma matriz em formato de cone apontando para baixo
void criarCone(int cone[TAMANHO_HABILIDADE][TAMANHO_HABILIDADE]) {
    for (int i = 0; i < TAMANHO_HABILIDADE; i++) {
        for (int j = 0; j < TAMANHO_HABILIDADE; j++) {
            if (j >= (TAMANHO_HABILIDADE / 2 - i) && j <= (TAMANHO_HABILIDADE / 2 + i))
                cone[i][j] = 1;
            else
                cone[i][j] = 0;
        }
    }
}

// Cria uma matriz em formato de cruz
void criarCruz(int cruz[TAMANHO_HABILIDADE][TAMANHO_HABILIDADE]) {
    int centro = TAMANHO_HABILIDADE / 2;
    for (int i = 0; i < TAMANHO_HABILIDADE; i++) {
        for (int j = 0; j < TAMANHO_HABILIDADE; j++) {
            if (i == centro || j == centro)
                cruz[i][j] = 1;
            else
                cruz[i][j] = 0;
        }
    }
}

// Cria uma matriz em formato de octaedro (losango)
void criarOctaedro(int octaedro[TAMANHO_HABILIDADE][TAMANHO_HABILIDADE]) {
    int centro = TAMANHO_HABILIDADE / 2;
    for (int i = 0; i < TAMANHO_HABILIDADE; i++) {
        for (int j = 0; j < TAMANHO_HABILIDADE; j++) {
            if (abs(i - centro) + abs(j - centro) <= centro)
                octaedro[i][j] = 1;
            else
                octaedro[i][j] = 0;
        }
    }
}

// ===========================
// Função para aplicar uma habilidade ao tabuleiro
// ===========================

void aplicarHabilidade(int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO],
                       int habilidade[TAMANHO_HABILIDADE][TAMANHO_HABILIDADE],
                       int origemLinha, int origemColuna) {
    int centro = TAMANHO_HABILIDADE / 2;

    for (int i = 0; i < TAMANHO_HABILIDADE; i++) {
        for (int j = 0; j < TAMANHO_HABILIDADE; j++) {
            if (habilidade[i][j] == 1) {
                int linhaTab = origemLinha - centro + i;
                int colunaTab = origemColuna - centro + j;

                // Verifica se está dentro dos limites do tabuleiro
                if (linhaTab >= 0 && linhaTab < TAMANHO_TABULEIRO &&
                    colunaTab >= 0 && colunaTab < TAMANHO_TABULEIRO) {
                    
                    // Marca o tabuleiro com valor 5 (área de habilidade)
                    if (tabuleiro[linhaTab][colunaTab] == 0)
                        tabuleiro[linhaTab][colunaTab] = 5;
                }
            }
        }
    }
}

// ===========================
// Função principal
// ===========================
int main() {
    int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO];
    int cone[TAMANHO_HABILIDADE][TAMANHO_HABILIDADE];
    int cruz[TAMANHO_HABILIDADE][TAMANHO_HABILIDADE];
    int octaedro[TAMANHO_HABILIDADE][TAMANHO_HABILIDADE];

    // Inicializa o tabuleiro
    inicializarTabuleiro(tabuleiro);

    // Posiciona navios
    posicionarNavioHorizontal(tabuleiro, 0, 0);
    posicionarNavioVertical(tabuleiro, 2, 5);
    posicionarNavioDiagonalDescendente(tabuleiro, 4, 4);
    posicionarNavioDiagonalAscendente(tabuleiro, 8, 5);

    // Cria as habilidades
    criarCone(cone);
    criarCruz(cruz);
    criarOctaedro(octaedro);

    // Aplica habilidades em posições específicas do tabuleiro
    aplicarHabilidade(tabuleiro, cone, 2, 2);
    aplicarHabilidade(tabuleiro, cruz, 6, 6);
    aplicarHabilidade(tabuleiro, octaedro, 8, 2);

    // Exibe o tabuleiro completo
    printf("\n=== TABULEIRO COM HABILIDADES ===\n");
    exibirTabuleiro(tabuleiro);

    return 0;
}
