#include <stdio.h>

#define TAM 10   // Tamanho fixo do tabuleiro (10x10)
#define NAVIO 3  // Valor que representa o navio no tabuleiro
#define TAM_NAVIO 3  // Cada navio ocupa 3 posições

int main() {
    int tabuleiro[TAM][TAM] = {0}; // Inicializa o tabuleiro com 0 (água)
    
    // Coordenadas iniciais dos dois navios
    int linhaNavio1 = 2, colunaNavio1 = 4; // Navio 1 (horizontal)
    int linhaNavio2 = 5, colunaNavio2 = 7; // Navio 2 (vertical)
    
    int i;
    
    // --- Posicionar Navio 1 (horizontal) ---
    // Verifica se cabe no tabuleiro
    if (colunaNavio1 + TAM_NAVIO <= TAM) {
        for (i = 0; i < TAM_NAVIO; i++) {
            tabuleiro[linhaNavio1][colunaNavio1 + i] = NAVIO;
        }
    } else {
        printf("Erro: Navio 1 ultrapassa os limites do tabuleiro.\n");
        return 1;
    }
    
    // --- Posicionar Navio 2 (vertical) ---
    // Verifica se cabe no tabuleiro e não sobrepõe o outro navio
    if (linhaNavio2 + TAM_NAVIO <= TAM) {
        for (i = 0; i < TAM_NAVIO; i++) {
            if (tabuleiro[linhaNavio2 + i][colunaNavio2] == NAVIO) {
                printf("Erro: Navio 2 sobrepoe o Navio 1.\n");
                return 1;
            }
            tabuleiro[linhaNavio2 + i][colunaNavio2] = NAVIO;
        }
    } else {
        printf("Erro: Navio 2 ultrapassa os limites do tabuleiro.\n");
        return 1;
    }
    
    // --- Exibir o Tabuleiro ---
    printf("\n=== TABULEIRO BATALHA NAVAL ===\n\n");
    for (int linha = 0; linha < TAM; linha++) {
        for (int coluna = 0; coluna < TAM; coluna++) {
            printf("%d ", tabuleiro[linha][coluna]);
        }
        printf("\n");
    }

    printf("\nLegenda: 0 = Água | 3 = Navio\n");
    
    return 0;
}
