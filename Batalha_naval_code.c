#include <stdio.h>
#include <string.h>

int main() {
    printf("**** BATALHA NAVAL ****\n\n");
    
    char linha[10] = {'A','B','C','D','E','F','G','H','I','J'};
    int tabuleiro[10][10];
    
    int x;
    int y;
    
    /* Inicializa o tabuleiro com 0 (água) */
    for (y = 0; y < 10; y++) {
        for (x = 0; x < 10; x++) {
            tabuleiro[x][y] = 0;
        }
    }
    
    /* --- LÓGICA PARA EXIBIR O TABULEIRO --- */

    /* 1. Imprime os números das colunas (cabeçalho) */
    printf("   1 2 3 4 5 6 7 8 9 10\n");
    
    /* 2. Loop pelas linhas */
    for (y = 0; y < 10; y++) {
        /* Imprime a letra da linha (cabeçalho) */
        printf("%c  ", linha[y]);
        
        /* Loop pelas colunas da linha atual */
        for (x = 0; x < 10; x++) {
            /* 
               Verifica o valor no tabuleiro. 
               Por enquanto, só temos 0 (água), então exibimos '~'.
            */
            if (tabuleiro[x][y] == 0) {
                printf("~ ");
            } else {

                printf("%d ", tabuleiro[x][y]);
            }
        }

        printf("\n");
    }
    
    return 0;
}
