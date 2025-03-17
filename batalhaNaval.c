#include <stdio.h>

#define tamanho 10
#define tam_navio 3

void imprimeTabuleiro(int tabuleiro[tamanho][tamanho]) {
    printf("   ");
    // impre as letras das colunas
    for (int i = 0; i < 10; i++) { 
        printf("%c ", 'A' + i);
    }
    printf("\n");

    // imprime os números das linhas junto com os valores do tabuleiro
    for (int i = 0; i < 10; i++) {
        printf("%2d ", i + 1); // imprime o número da linha utilizando 2 casas
        for (int j = 0; j < 10; j++) {
            printf("%d ", tabuleiro[i][j]); // imprime o valor da posição no tabuleiro
        }
        printf("\n");
    }
    return;
};

// procedimento para posicionar o navio no tabuleiro na vertical ou horizontal
void posicionaNavio(int tabuleiro[tamanho][tamanho], int linhaInicial, int colunaInicial, char orientacaoNavio) {
    if (orientacaoNavio == 'V') {
        for (int i = 0; i < tam_navio; i++) {
            tabuleiro[linhaInicial - 1 + i][colunaInicial-1] = 3;
        }
    } else if (orientacaoNavio == 'H'){
        for (int i = 0; i < tam_navio; i++) {
            tabuleiro[linhaInicial - 1][colunaInicial - 1 + i] = 3;
        }
    } else {
        printf("Orientação inválida\n");
    }
    return;
};

void posicionaNavioDiagonal(int tabuleiro[tamanho][tamanho], int linhaInicial, int colunaInicial, char orientacaoDiag) {
    if (orientacaoDiag == 'D'){
        for (int i = 0; i < tam_navio; i++) {
            tabuleiro[linhaInicial - 1 + i][colunaInicial - 1 + i] = 3;
        }
    }
    else if (orientacaoDiag == 'E'){
        for (int i = 0; i < tam_navio; i++) {
            tabuleiro[linhaInicial - 1 + i][colunaInicial - 1 - i] = 3;
        }
    }
    else {
        printf("Orientação inválida\n");
    }
    return;
    
};

int main() {
    int tabuleiro[tamanho][tamanho] = {0}; // declaração do tabuleiro 10x10 com valor 0
    int linhaInicialDiagonal, colunaInicialDiagonal; // linha e coluna inicial para posicionar o navio diagonalmente
    char orientacao; // orientação do navio
    char orientacaoDiagonal; // orientação do navio diagonal


    //posiciona o navio na vertical
    int linhaInicialVertical = 3, colunaVertical = 5; // linha e coluna inicial para posicionar o navio verticalmente
    orientacao = 'V';
    posicionaNavio(tabuleiro, linhaInicialVertical, colunaVertical, orientacao);

    //posiciona o navio na horizontal
    int linhaHorizontal = 9, colunaInicialHorizontal = 2; // linha e coluna inicial para posicionar o navio horizontalmente
    orientacao = 'H';
    posicionaNavio(tabuleiro, linhaHorizontal, colunaInicialHorizontal, orientacao);

    //posiciona o navio na diagonal direita
    orientacaoDiagonal = 'D';
    linhaInicialDiagonal = 1, colunaInicialDiagonal = 1;
    posicionaNavioDiagonal(tabuleiro, linhaInicialDiagonal, colunaInicialDiagonal, orientacaoDiagonal);

    //posiciona o navio na diagonal esquerda
    orientacaoDiagonal = 'E';
    linhaInicialDiagonal = 7, colunaInicialDiagonal = 8;
    posicionaNavioDiagonal(tabuleiro, linhaInicialDiagonal, colunaInicialDiagonal, orientacaoDiagonal);

    // imprime o tabuleiro
    imprimeTabuleiro(tabuleiro);

    return 0;
}