#include <stdio.h>

void imprimirTabuleiro(char tab[3][3]) {
    printf("\n    A   B   C\n");
    for (int i = 0; i < 3; i++) {
        printf(" %d  %c | %c | %c \n", i + 1, tab[i][0], tab[i][1], tab[i][2]);
        if (i < 2) printf("   ---|---|---\n");
    }
    printf("\n");
}

int checarVitoria(char tab[3][3], char marca) {
    for (int i = 0; i < 3; i++) {
        if (tab[i][0] == marca && tab[i][1] == marca && tab[i][2] == marca) return 1;
        if (tab[0][i] == marca && tab[1][i] == marca && tab[2][i] == marca) return 1;
    }
    if (tab[0][0] == marca && tab[1][1] == marca && tab[2][2] == marca) return 1;
    if (tab[0][2] == marca && tab[1][1] == marca && tab[2][0] == marca) return 1;
    
    return 0;
}

int main() {
    char tabuleiro[3][3] = {
        {' ', ' ', ' '},
        {' ', ' ', ' '},
        {' ', ' ', ' '}
    };
    
    int jogadorAtual = 1; 
    char marcaAtual;
    int jogadas = 0;
    int venceu = 0;
    
    printf("=== JOGO DA VELHA ===\n");
    
    while (jogadas < 9 && venceu == 0) {
        imprimirTabuleiro(tabuleiro);
        
        marcaAtual = (jogadorAtual == 1) ? 'X' : '0';
        
        char jogada[10];
        printf("Jogador %d (%c), informe sua jogada (ex: B3): ", jogadorAtual, marcaAtual);
        scanf(" %s", jogada);
        
        char colunaChar = jogada[0];
        if (colunaChar >= 'a' && colunaChar <= 'z') {
            colunaChar -= 32;
        }
        
        int coluna = colunaChar - 'A';
        int linha = jogada[1] - '1';
        
        if (coluna < 0 || coluna > 2 || linha < 0 || linha > 2 || jogada[2] != '\0') {
            printf("\n[!] Jogada invalida! Use letras de A a C e numeros de 1 a 3.\n");
            continue;
        }
        
        if (tabuleiro[linha][coluna] != ' ') {
            printf("\n[!] Essa celula ja esta ocupada! Escolha outra.\n");
            continue;
        }
        
        tabuleiro[linha][coluna] = marcaAtual;
        jogadas++;
        
        if (checarVitoria(tabuleiro, marcaAtual) == 1) {
            venceu = jogadorAtual;
        } else {
            jogadorAtual = (jogadorAtual == 1) ? 2 : 1;
        }
    }
    
    imprimirTabuleiro(tabuleiro);
    
    if (venceu != 0) {
        printf("PARABENS! O Jogador %d (%c) venceu o jogo!\n", venceu, marcaAtual);
    } else {
        printf("DEU VELHA! Ninguem venceu.\n");
    }
    
    return 0;
}