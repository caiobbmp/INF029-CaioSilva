#include <stdio.h>

#define NUM_NAVIOS 5

void imprimir(char tab[10][10], int esconder) {
    printf("    A  B  C  D  E  F  G  H  I  J\n");
    for (int i = 0; i < 10; i++) {
        printf("%2d ", i + 1);
        for (int j = 0; j < 10; j++) {
            char c = tab[i][j];
            if (esconder == 1 && c == 'N') {
                c = ' ';
            }
            printf("[%c]", c);
        }
        printf("\n");
    }
    printf("\n");
}

void posicionarNavios(int jogador, char tab[10][10], int tamanhos[]) {
    printf("\n=== JOGADOR %d: POSICIONE SEUS NAVIOS ===\n", jogador);
    
    for (int i = 0; i < NUM_NAVIOS; i++) {
        int tamanho = tamanhos[i];
        int valido = 0;

        while (valido == 0) {
            imprimir(tab, 0);
            char pos[10];
            char ori = 'H';

            printf("Navio %d (Tamanho: %d). Coordenada inicial (ex: A1): ", i + 1, tamanho);
            scanf("%s", pos);

            if (tamanho > 1) {
                printf("Orientacao (H - Horizontal, V - Vertical): ");
                scanf(" %c", &ori);
                if (ori >= 'a' && ori <= 'z') ori -= 32;
            }

            char c_char = pos[0];
            if (c_char >= 'a' && c_char <= 'z') c_char -= 32;
            int c = c_char - 'A';

            int l;
            if (pos[1] == '1' && pos[2] == '0') l = 9;
            else l = pos[1] - '1';

            int erro = 0;
            for (int k = 0; k < tamanho; k++) {
                int nl = l + (ori == 'V' ? k : 0);
                int nc = c + (ori == 'H' ? k : 0);

                if (nl < 0 || nl > 9 || nc < 0 || nc > 9) erro = 1;
                else if (tab[nl][nc] != ' ') erro = 1;
            }

            if (erro == 1) {
                printf("\n[!] Posicao invalida ou colidindo! Tente novamente.\n\n");
            } else {
                for (int k = 0; k < tamanho; k++) {
                    int nl = l + (ori == 'V' ? k : 0);
                    int nc = c + (ori == 'H' ? k : 0);
                    tab[nl][nc] = 'N';
                }
                valido = 1;
                printf("\nNavio posicionado com sucesso!\n\n");
            }
        }
    }
}

int realizarTiro(char tabAlvo[10][10]) {
    while (1) {
        char pos[10];
        printf("Sua vez de atirar! Coordenada (ex: C5): ");
        scanf("%s", pos);

        char c_char = pos[0];
        if (c_char >= 'a' && c_char <= 'z') c_char -= 32;
        int c = c_char - 'A';

        int l;
        if (pos[1] == '1' && pos[2] == '0') l = 9;
        else l = pos[1] - '1';

        if (l < 0 || l > 9 || c < 0 || c > 9) {
            printf("[!] Coordenada fora do mapa!\n");
            continue;
        }

        if (tabAlvo[l][c] == '0' || tabAlvo[l][c] == 'X') {
            printf("[!] Voce ja atirou nessa posicao!\n");
            continue;
        }

        if (tabAlvo[l][c] == 'N') {
            printf("\n=> BOOM! Tiro certeiro num navio inimigo!\n");
            tabAlvo[l][c] = '0';
            return 1;
        } else {
            printf("\n=> SPLASH! Tiro na agua.\n");
            tabAlvo[l][c] = 'X';
            return 0;
        }
    }
}

int main() {
    int tamanhosNavios[NUM_NAVIOS];
    int totalPartes = 0;

    for (int i = 0; i < NUM_NAVIOS; i++) {
        if (i == 0) tamanhosNavios[i] = 4;
        else if (i == 1) tamanhosNavios[i] = 3;
        else if (i >= 2 && i <= 4) tamanhosNavios[i] = 1;
        else tamanhosNavios[i] = 2; 
        
        totalPartes += tamanhosNavios[i];
    }

    char tab1[10][10], tab2[10][10];
    for (int i = 0; i < 10; i++) {
        for (int j = 0; j < 10; j++) {
            tab1[i][j] = ' ';
            tab2[i][j] = ' ';
        }
    }

    posicionarNavios(1, tab1, tamanhosNavios);
    for (int i = 0; i < 40; i++) printf("\n");
    
    posicionarNavios(2, tab2, tamanhosNavios);
    for (int i = 0; i < 40; i++) printf("\n");

    int acertos1 = 0, acertos2 = 0;
    int turno = 1;

    printf("=== BATALHA NAVAL INICIADA ===\n");

    while (acertos1 < totalPartes && acertos2 < totalPartes) {
        printf("\n-----------------------------------\n");
        printf(">>> TURNO DO JOGADOR %d <<<\n", turno);

        if (turno == 1) {
            printf("\nSEU TABULEIRO:\n");
            imprimir(tab1, 0); 
            printf("TABULEIRO DO OPONENTE (Seus Tiros):\n");
            imprimir(tab2, 1); 
            
            acertos1 += realizarTiro(tab2);
            turno = 2;
        } else {
            printf("\nSEU TABULEIRO:\n");
            imprimir(tab2, 0);
            printf("TABULEIRO DO OPONENTE (Seus Tiros):\n");
            imprimir(tab1, 1);
            
            acertos2 += realizarTiro(tab1);
            turno = 1;
        }
    }

    if (acertos1 == totalPartes) {
        printf("\nFROTA DESTRUIDA! O JOGADOR 1 VENCEU!\n");
    } else {
        printf("\nFROTA DESTRUIDA! O JOGADOR 2 VENCEU!\n");
    }

    return 0;
}