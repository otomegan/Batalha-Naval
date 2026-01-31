#include <stdio.h>
#include <stdlib.h> /* Necessária para a função atoi(), que converte texto para número. */
#include <ctype.h>  /* necessária para a função toupper(), que converte letras para maiúsculas. */

int main() {

    printf("**** BATALHA NAVAL ****\n\n");
    
    // --- DECLARAÇÃO DE VARIÁVEIS PRINCIPAIS ---
    
    // Array de caracteres para ser usado como legenda das linhas (A-J).
    char linha_letras[10] = {'A','B','C','D','E','F','G','H','I','J'};
    
    // O tabuleiro do jogo em si. É uma matriz 10x10 de inteiros.
    // 0 = Água
    // 1 = Navio
    int tabuleiro[10][10];

    // Variáveis de controle para os loops (iteradores).
    int x, y, i;
    
    /* 
     * =======================================================================
     *                          1. INICIALIZAÇÃO DO TABULEIRO
     * =======================================================================
     */
    // Este loop duplo percorre cada casa do tabuleiro.
    for (y = 0; y < 10; y++) {        // Loop pelas linhas (y)
        for (x = 0; x < 10; x++) {    // Loop pelas colunas (x)
            // Define o valor de cada casa como 0, representando "água".

            tabuleiro[x][y] = 0;
        }
    }
    
    /* 
     * =======================================================================
     *                  2. FASE DE POSICIONAMENTO DOS NAVIOS
     * =======================================================================
     */

    /* 
     * --- POSICIONA 2 NAVIOS EM LINHA (Horizontal/Vertical) ---
     * Cada navio terá 3 casas de comprimento.
     */
    printf("FASE 1: Posicione 2 Cruzadores (3 casas em linha).\n");
    // Loop principal para posicionar os 2 navios desta fase.
    for (i = 0; i < 2; i++) {
        // Variáveis temporárias para esta iteração do loop.
        char coordenada[4]; // Armazena a entrada do usuário (ex: "A1", "C10").
        int dir_linha;      // Armazena a direção escolhida (1-4).
        int x_s, y_s, x_m, y_m, x_e, y_e; // Coordenadas para o início(s), meio(m) e fim(e) do navio.
        int loop_valido = 0; // Variável de controle para o loop de validação (0=inválido, 1=válido).

        // Antes de cada posicionamento, exibe o estado atual do tabuleiro.
        printf("\n   1 2 3 4 5 6 7 8 9 10\n");
        for (y = 0; y < 10; y++) {
            printf("%c  ", linha_letras[y]);
            for (x = 0; x < 10; x++) { if (tabuleiro[x][y] == 0) printf("~ "); else printf("3 "); }
            printf("\n");
        }

        // Loop de validação: continua pedindo a coordenada até que uma válida seja inserida.
        do {
            // Pede a coordenada inicial do navio.
            printf("\nDigite a coordenada INICIAL para o Cruzador #%d (ex: A1): ", i + 1);
            scanf("%3s", coordenada);
            // Pede a direção do navio.
            printf("Escolha a direção (1: Direita, 2: Baixo, 3: Esquerda, 4: Cima): ");
            scanf("%d", &dir_linha);

            // --- TRADUÇÃO E CÁLCULO DAS COORDENADAS ---
            // Converte a letra da coordenada (ex: 'A') para o índice da linha (0).
            y_s = toupper(coordenada[0]) - 'A';
            // Converte o número da coordenada (ex: "1") para o índice da coluna (0).
            x_s = atoi(&coordenada[1]) - 1;

            // Calcula as posições do meio e do fim do navio com base na direção.
            switch(dir_linha) {
                case 1: x_m=x_s+1; y_m=y_s;   x_e=x_s+2; y_e=y_s;   break; // Direita: y fica constante, x aumenta
                case 2: x_m=x_s;   y_m=y_s+1; x_e=x_s;   y_e=y_s+2; break; // Baixo:   x fica constante, y aumenta
                case 3: x_m=x_s-1; y_m=y_s;   x_e=x_s-2; y_e=y_s;   break; // Esquerda:y fica constante, x diminui
                case 4: x_m=x_s;   y_m=y_s-1; x_e=x_s;   y_e=y_s-2; break; // Cima:    x fica constante, y diminui
                default: x_s = -1; break; // Se digitar uma direção inválida, dá erro de validação.
            }

            // --- VALIDAÇÃO DA POSIÇÃO ---

            if (x_s<0||x_s>9||y_s<0||y_s>9||x_m<0||x_m>9||y_m<0||y_m>9||x_e<0||x_e>9||y_e<0||y_e>9) {
                printf("Posição inválida! O navio sai do tabuleiro.\n");
                loop_valido = 0; // Mantém o loop rodando.

            // O navio sobrepõe outro navio já existente? aqui com o else if irá comparar e validar.
            } else if (tabuleiro[x_s][y_s]==1 || tabuleiro[x_m][y_m]==1 || tabuleiro[x_e][y_e]==1) {
                printf("Posição inválida! O navio sobrepõe outro.\n");
                loop_valido = 0; // Mantém o loop rodando.

            // Se passou em todas as validações:
            } else {

                // Posiciona as 3 partes do navio no tabuleiro.
                tabuleiro[x_s][y_s] = 1; tabuleiro[x_m][y_m] = 1; tabuleiro[x_e][y_e] = 1;
                loop_valido = 1; // Sinaliza que a posição é válida e quebra o loop `do-while`.
            }
        } while (loop_valido == 0); // O loop continua enquanto `loop_valido` for 0.
    }

    /* 
     * --- AGORA É HORA DE POSICIONAR 2 NAVIOS NA DIAGONAL (3 casas) --- */

    printf("\nFASE 2: Posicione 2 Submarinos (3 casas na diagonal).\n");
    // Loop principal para os 2 navios diagonais.
    for (i = 0; i < 2; i++) {
        char coordenada[4];
        int dir_diag, x_s, y_s, x_m, y_m, x_e, y_e;
        int loop_valido = 0; // igual o anterior, mantém o loop rodando.


        printf("\n   1 2 3 4 5 6 7 8 9 10\n");
        for (y = 0; y < 10; y++) {
            printf("%c  ", linha_letras[y]);
            for (x = 0; x < 10; x++) { if (tabuleiro[x][y] == 0) printf("~ "); else printf("N "); }
            printf("\n");
        }

        do {
            printf("\nDigite a coordenada INICIAL para o Submarino #%d (ex: B2): ", i + 1);
            scanf("%3s", coordenada);
            printf("Escolha a direção (1: Baixo-Dir, 2: Baixo-Esq, 3: Cima-Dir, 4: Cima-Esq): ");
            scanf("%d", &dir_diag);

            y_s = toupper(coordenada[0]) - 'A';
            x_s = atoi(&coordenada[1]) - 1;
            
            // Calcula as posições do navio na diagonal.
            switch(dir_diag) {
                case 1: x_m=x_s+1; y_m=y_s+1; x_e=x_s+2; y_e=y_s+2; break; // Baixo-Direita: x e y aumentam
                case 2: x_m=x_s-1; y_m=y_s+1; x_e=x_s-2; y_e=y_s+2; break; // Baixo-Esquerda: x diminui, y aumenta
                case 3: x_m=x_s+1; y_m=y_s-1; x_e=x_s+2; y_e=y_s-2; break; // Cima-Direita: x aumenta, y diminui
                case 4: x_m=x_s-1; y_m=y_s-1; x_e=x_s-2; y_e=y_s-2; break; // Cima-Esquerda: x e y diminuem
                default: x_s = -1; break; // Força um erro de validação.
            }

            // Validação igual ao dos navios em linha, só que cruzado.
            if (x_s<0||x_s>9||y_s<0||y_s>9||x_m<0||x_m>9||y_m<0||y_m>9||x_e<0||x_e>9||y_e<0||y_e>9) {
                printf("Posição inválida! O navio sai do tabuleiro.\n");
                loop_valido = 0;
            } else if (tabuleiro[x_s][y_s]==1 || tabuleiro[x_m][y_m]==1 || tabuleiro[x_e][y_e]==1) {
                printf("Posição inválida! O navio sobrepõe outro.\n");
                loop_valido = 0;
            } else {
                tabuleiro[x_s][y_s] = 1; tabuleiro[x_m][y_m] = 1; tabuleiro[x_e][y_e] = 1;
                loop_valido = 1;
            }
        } while (loop_valido == 0);
    }

    /* 
     * =======================================================================
     *                          3. EXIBIÇÃO DO TABULEIRO FINAL
     * =======================================================================
     */
    printf("\n*** SEU TABULEIRO FINAL ESTÁ PRONTO PARA A BATALHA! ***\n");

    printf("   1 2 3 4 5 6 7 8 9 10\n");
    // Loop para imprimir cada linha do tabuleiro.
    for (y = 0; y < 10; y++) {
        // Imprime a legenda da linha (A, B, C...) a cada troca da linha.
        printf("%c  ", linha_letras[y]);
        // Loop para imprimir cada casa da linha atual.
        for (x = 0; x < 10; x++) {
            // Se o valor for 0, imprime água (~). Se não, imprime navio.
            if (tabuleiro[x][y] == 0) printf("~ ");
            else printf("3 ");
        }

        printf("\n");
    }
    
    // fimmmm
    return 0;
}
