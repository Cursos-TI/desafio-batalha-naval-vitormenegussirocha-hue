#include <stdio.h>

#define TAMANHO_TABULEIRO 10
#define TAMANHO_NAVIO 3

// Função para inicializar o tabuleiro com água (valor 0)
void inicializarTabuleiro(int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO]) {
    for (int i = 0; i < TAMANHO_TABULEIRO; i++) {
        for (int j = 0; j < TAMANHO_TABULEIRO; j++) {
            tabuleiro[i][j] = 0;  // 0 representa água
        }
    }
}

// Função para exibir o tabuleiro
void exibirTabuleiro(int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO]) {
    for (int i = 0; i < TAMANHO_TABULEIRO; i++) {
        for (int j = 0; j < TAMANHO_TABULEIRO; j++) {
            printf("%2d ", tabuleiro[i][j]);
        }
        printf("\n");
    }
}

// Função para posicionar um navio horizontalmente
int posicionarNavioHorizontal(int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO], int linha, int coluna) {
    if (coluna + TAMANHO_NAVIO > TAMANHO_TABULEIRO) {
        return 0;  // Não cabe o navio horizontalmente
    }
    for (int i = 0; i < TAMANHO_NAVIO; i++) {
        if (tabuleiro[linha][coluna + i] != 0) {
            return 0;  // Já há um navio na posição
        }
    }
    for (int i = 0; i < TAMANHO_NAVIO; i++) {
        tabuleiro[linha][coluna + i] = 3;  // Marca a posição do navio com 3
    }
    return 1;  // Navio posicionado com sucesso
}

// Função para posicionar um navio verticalmente
int posicionarNavioVertical(int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO], int linha, int coluna) {
    if (linha + TAMANHO_NAVIO > TAMANHO_TABULEIRO) {
        return 0;  // Não cabe o navio verticalmente
    }
    for (int i = 0; i < TAMANHO_NAVIO; i++) {
        if (tabuleiro[linha + i][coluna] != 0) {
            return 0;  // Já há um navio na posição
        }
    }
    for (int i = 0; i < TAMANHO_NAVIO; i++) {
        tabuleiro[linha + i][coluna] = 3;  // Marca a posição do navio com 3
    }
    return 1;  // Navio posicionado com sucesso
}

// Função para posicionar um navio diagonal (descendente)
int posicionarNavioDiagonalDescendente(int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO], int linha, int coluna) {
    if (linha + TAMANHO_NAVIO > TAMANHO_TABULEIRO || coluna + TAMANHO_NAVIO > TAMANHO_TABULEIRO) {
        return 0;  // Não cabe o navio diagonalmente
    }
    for (int i = 0; i < TAMANHO_NAVIO; i++) {
        if (tabuleiro[linha + i][coluna + i] != 0) {
            return 0;  // Já há um navio na posição
        }
    }
    for (int i = 0; i < TAMANHO_NAVIO; i++) {
        tabuleiro[linha + i][coluna + i] = 3;  // Marca a posição do navio com 3
    }
    return 1;  // Navio posicionado com sucesso
}

// Função para posicionar um navio diagonal (ascendente)
int posicionarNavioDiagonalAscendente(int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO], int linha, int coluna) {
    if (linha - TAMANHO_NAVIO < -1 || coluna + TAMANHO_NAVIO > TAMANHO_TABULEIRO) {
        return 0;  // Não cabe o navio diagonalmente
    }
    for (int i = 0; i < TAMANHO_NAVIO; i++) {
        if (tabuleiro[linha - i][coluna + i] != 0) {
            return 0;  // Já há um navio na posição
        }
    }
    for (int i = 0; i < TAMANHO_NAVIO; i++) {
        tabuleiro[linha - i][coluna + i] = 3;  // Marca a posição do navio com 3
    }
    return 1;  // Navio posicionado com sucesso
}

int main() {
    int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO];

    // Inicializar o tabuleiro
    inicializarTabuleiro(tabuleiro);

    // Posicionar os navios no tabuleiro
    if (!posicionarNavioHorizontal(tabuleiro, 0, 0)) {
        printf("Erro ao posicionar navio horizontal.\n");
    }
    if (!posicionarNavioVertical(tabuleiro, 2, 5)) {
        printf("Erro ao posicionar navio vertical.\n");
    }
    if (!posicionarNavioDiagonalDescendente(tabuleiro, 4, 4)) {
        printf("Erro ao posicionar navio diagonal descendente.\n");
    }
    if (!posicionarNavioDiagonalAscendente(tabuleiro, 8, 5)) {
        printf("Erro ao posicionar navio diagonal ascendente.\n");
    }

    // Exibir o tabuleiro com os navios
    printf("Tabuleiro do Batalha Naval:\n");
    exibirTabuleiro(tabuleiro);

    return 0;
}
