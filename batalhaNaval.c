#include <stdio.h>

#define TAMANHO 10
#define TAM_NAVIO 3
#define AREA_EFEITO 5

void imprimeTabuleiro(int tabuleiro[TAMANHO][TAMANHO]) {
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
}

// função para verificar se a posição é válida e não está ocupada
int posicaoValida(int tabuleiro[TAMANHO][TAMANHO], int linha, int coluna) {
    if (linha < 0 || linha >= TAMANHO || coluna < 0 || coluna >= TAMANHO) {
        return 0; // coordenada inválida
    }
    if (tabuleiro[linha][coluna] != 0) {
        return 0; // posição ocupada
    }
    return 1; // posição válida
}

// função para posicionar o navio no tabuleiro na vertical ou horizontal
void posicionaNavio(int tabuleiro[TAMANHO][TAMANHO], int linhaInicial, int colunaInicial, char orientacaoNavio) {
    for (int i = 0; i < TAM_NAVIO; i++) {
        if (orientacaoNavio == 'V' && !posicaoValida(tabuleiro, linhaInicial - 1 + i, colunaInicial - 1)) {
            printf("Posição ocupada/inválida, navio vertical não posicionado\n");
            return;
        } else if (orientacaoNavio == 'H' && !posicaoValida(tabuleiro, linhaInicial - 1, colunaInicial - 1 + i)) {
            printf("Posição ocupada/inválida, navio horizontal não posicionado\n");
            return;
        }
    }
    // preenche o tabuleiro com o navio após a verificação
    for (int i = 0; i < TAM_NAVIO; i++) {
        if (orientacaoNavio == 'V') {
            tabuleiro[linhaInicial - 1 + i][colunaInicial - 1] = 3;
        } else if (orientacaoNavio == 'H') {
            tabuleiro[linhaInicial - 1][colunaInicial - 1 + i] = 3;
        }
    }
}

// função para posicionar o navio no tabuleiro na diagonal
void posicionaNavioDiagonal(int tabuleiro[TAMANHO][TAMANHO], int linhaInicial, int colunaInicial, char orientacaoDiag) {
    for (int i = 0; i < TAM_NAVIO; i++) {
        if (orientacaoDiag == 'D' && !posicaoValida(tabuleiro, linhaInicial - 1 + i, colunaInicial - 1 + i)) {
            printf("Posição ocupada/inválida, navio diagonal não posicionado\n");
            return;
        } else if (orientacaoDiag == 'E' && !posicaoValida(tabuleiro, linhaInicial - 1 + i, colunaInicial - 1 - i)) {
            printf("Posição ocupada/inválida, navio diagonal não posicionado\n");
            return;
        }
    }
    // preenche o tabuleiro com o navio após a verificação
    for (int i = 0; i < TAM_NAVIO; i++) {
        if (orientacaoDiag == 'D') {
            tabuleiro[linhaInicial - 1 + i][colunaInicial - 1 + i] = 3;
        } else if (orientacaoDiag == 'E') {
            tabuleiro[linhaInicial - 1 + i][colunaInicial - 1 - i] = 3;
        }
    }
}

// função para aplicar a habilidade cone
void habilidadeCone(int tabuleiro[TAMANHO][TAMANHO], int linha, int coluna) {
    int origemLinha = linha - 1;
    int origemColuna = coluna - 1;

    for (int i = 0; i < 3; i++) {
        for (int j = origemColuna - i; j <= origemColuna + i; j++) {
            if (origemLinha + i >= 0 && origemLinha + i < TAMANHO && j >= 0 && j < TAMANHO) {
                if (tabuleiro[origemLinha + i][j] == 3) { // verifica se é um navio
                    tabuleiro[origemLinha + i][j] = 5; // define como área de navio afetado
                } else {
                    tabuleiro[origemLinha + i][j] = 1; // define como área afetada
                }
            }
        }
    }
}

// função para aplicar a habilidade cruz
void habilidadeCruz(int tabuleiro[TAMANHO][TAMANHO], int linha, int coluna) {
    int origemLinha = linha - 1;
    int origemColuna = coluna - 1;

    for (int i = -1; i <= 1; i++) {
        for (int j = -2; j <= 2; j++) {
            if (origemLinha + i >= 0 && origemLinha + i < TAMANHO && origemColuna + j >= 0 && origemColuna + j < TAMANHO) {
                if (i == 0 || j == 0) { // aplica apenas na linha central e na coluna central
                    if (tabuleiro[origemLinha + i][origemColuna + j] == 3) { // verifica se é um navio
                        tabuleiro[origemLinha + i][origemColuna + j] = 5; // define como área de navio afetado
                    } else {
                        tabuleiro[origemLinha + i][origemColuna + j] = 1; // define como área afetada
                    }
                }
            }
        }
    }
}

// função para aplicar a habilidade octaedro
void habilidadeOctaedro(int tabuleiro[TAMANHO][TAMANHO], int linha, int coluna) {
    int origemLinha = linha - 1;
    int origemColuna = coluna - 1;

    for (int i = -1; i <= 1; i++) {
        int valorAbsolutoI = (i < 0) ? -i : i; // calcula o valor absoluto de i
        for (int j = -1 + valorAbsolutoI; j <= 1 - valorAbsolutoI; j++) {
            if (origemLinha + i >= 0 && origemLinha + i < TAMANHO && origemColuna + j >= 0 && origemColuna + j < TAMANHO) {
                if (tabuleiro[origemLinha + i][origemColuna + j] == 3) { // verifica se é um navio
                    tabuleiro[origemLinha + i][origemColuna + j] = 5; // define como área de navio afetado
                } else {
                    tabuleiro[origemLinha + i][origemColuna + j] = 1; // define como área afetada
                }
            }
        }
    }
}

int main() {
    int tabuleiro[TAMANHO][TAMANHO] = {0}; // declaração do tabuleiro 10x10 com valor 0
    int linhaInicialDiagonal, colunaInicialDiagonal; // linha e coluna inicial para posicionar o navio diagonalmente
    char orientacao; // orientação do navio
    char orientacaoDiagonal; // orientação do navio diagonal
    int cone[AREA_EFEITO][AREA_EFEITO], cruz[AREA_EFEITO][AREA_EFEITO], octaedro[AREA_EFEITO][AREA_EFEITO]; // declaração da área de efeito das habilidades

    //posiciona o navio na vertical
    int linhaInicialVertical = 2, colunaVertical = 9; // linha e coluna inicial para posicionar o navio verticalmente
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

    // aplica a habilidade cone, que possue uma área de efeito de 3 de altura e 5 de largura, conforme exemplo da atividade no módulo
    habilidadeCone(tabuleiro, 3, 3);
    // aplica a habilidade cruz, que possue uma área de efeito de 3 de altura e 5 de largura, conforme exemplo da atividade no módulo
    habilidadeCruz(tabuleiro, 7, 7);
    // aplica a habilidade octaedro que possue uma área de efeito de 3 de altura e 3 de largura, conforme exemplo da atividade no módulo
    habilidadeOctaedro(tabuleiro, 7, 2);

    //imprime o tabuleiro
    imprimeTabuleiro(tabuleiro);

    return 0;
}