#include <stdio.h>  
#include <stdlib.h> // Para a função atoi (converter texto para inteiro)
#include <ctype.h>  // Para a função toupper (converter para maiúscula)

int main() {
    printf("**** BATALHA NAVAL ****\n\n");

    char linha_letras[10] = {'A','B','C','D','E','F','G','H','I','J'};
    /* Estados do Tabuleiro:
     * 0 = Água Intacta, 1 = Navio Intacto
     * 2 = Tiro na Água (Erro), 3 = Navio Atingido (Acerto)
    */
    int tabuleiro[10][10];
    int x, y, i;

    // ========================= 1. INICIALIZAÇÃO DO TABULEIRO =========================
    // Preenche todo o tabuleiro com 0 (água) para começar.
    for (y = 0; y < 10; y++) {
        for (x = 0; x < 10; x++) {
            tabuleiro[x][y] = 0;
        }
    }

    // ======================= 2. FASE DE POSICIONAMENTO DOS NAVIOS =======================

    // --- PARTE A: 2 Navios em Linha (Horizontal/Vertical) ---
    printf("FASE 1: Posicione 2 Cruzadores (3 casas em linha).\n");
    for (i = 0; i < 2; i++) {
        char coordenada[4];
        int dir_linha, x_s, y_s, x_m, y_m, x_e, y_e;
        int loop_valido = 0; // Controla se a posição do navio é válida.

        // Exibe o tabuleiro antes de pedir a coordenada.
        printf("\n   1 2 3 4 5 6 7 8 9 10\n");
        for (y = 0; y < 10; y++) {
            printf("%c  ", linha_letras[y]);
            for (x = 0; x < 10; x++) { if (tabuleiro[x][y] == 0) printf("~ "); else printf("N "); }
            printf("\n");
        }

        // Loop `do-while` para garantir que o usuário insira uma posição válida.
        do {
            printf("\nDigite a coordenada INICIAL para o Cruzador #%d (ex: A1): ", i + 1);
            scanf("%3s", coordenada);
            printf("Escolha a direção (1: Direita, 2: Baixo, 3: Esquerda, 4: Cima): ");
            scanf("%d", &dir_linha);

            // Converte a coordenada do usuário (ex: "A1") para índices do array (y=0, x=0).
            y_s = toupper(coordenada[0]) - 'A';
            x_s = atoi(&coordenada[1]) - 1;

            // Calcula as 3 partes do navio com base na direção escolhida.
            switch(dir_linha) {
                case 1: x_m=x_s+1; y_m=y_s;   x_e=x_s+2; y_e=y_s;   break; // Direita
                case 2: x_m=x_s;   y_m=y_s+1; x_e=x_s;   y_e=y_s+2; break; // Baixo
                case 3: x_m=x_s-1; y_m=y_s;   x_e=x_s-2; y_e=y_s;   break; // Esquerda
                case 4: x_m=x_s;   y_m=y_s-1; x_e=x_s;   y_e=y_s-2; break; // Cima
                default: x_s = -1; break; // Força um erro de validação se a direção for inválida.
            }

            // Valida se o navio cabe no tabuleiro e não sobrepõe outro.
            if (x_s<0||x_s>9||y_s<0||y_s>9||x_m<0||x_m>9||y_m<0||y_m>9||x_e<0||x_e>9||y_e<0||y_e>9) {
                printf("Posição inválida! O navio sai do tabuleiro.\n");
                loop_valido = 0;
            } else if (tabuleiro[x_s][y_s] != 0 || tabuleiro[x_m][y_m] != 0 || tabuleiro[x_e][y_e] != 0) {
                printf("Posição inválida! O navio sobrepõe outro.\n");
                loop_valido = 0;
            } else {
                // Se a posição for válida, coloca o navio no tabuleiro.
                tabuleiro[x_s][y_s] = 1; tabuleiro[x_m][y_m] = 1; tabuleiro[x_e][y_e] = 1;
                loop_valido = 1; // Termina o loop de validação.
            }
        } while (loop_valido == 0);
    }

    // --- PARTE B: 2 Navios na Diagonal ---
    printf("\nFASE 2: Posicione 2 Submarinos (3 casas na diagonal).\n");
    for (i = 0; i < 2; i++) {
        char coordenada[4];
        int dir_diag, x_s, y_s, x_m, y_m, x_e, y_e;
        int loop_valido = 0;

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

            switch(dir_diag) {
                case 1: x_m=x_s+1; y_m=y_s+1; x_e=x_s+2; y_e=y_s+2; break; // Baixo-Direita
                case 2: x_m=x_s-1; y_m=y_s+1; x_e=x_s-2; y_e=y_s+2; break; // Baixo-Esquerda
                case 3: x_m=x_s+1; y_m=y_s-1; x_e=x_s+2; y_e=y_s-2; break; // Cima-Direita
                case 4: x_m=x_s-1; y_m=y_s-1; x_e=x_s-2; y_e=y_s-2; break; // Cima-Esquerda
                default: x_s = -1; break;
            }

            if (x_s<0||x_s>9||y_s<0||y_s>9||x_m<0||x_m>9||y_m<0||y_m>9||x_e<0||x_e>9||y_e<0||y_e>9) {
                printf("Posição inválida! O navio sai do tabuleiro.\n");
                loop_valido = 0;
            } else if (tabuleiro[x_s][y_s] != 0 || tabuleiro[x_m][y_m] != 0 || tabuleiro[x_e][y_e] != 0) {
                printf("Posição inválida! O navio sobrepõe outro.\n");
                loop_valido = 0;
            } else {
                tabuleiro[x_s][y_s] = 1; tabuleiro[x_m][y_m] = 1; tabuleiro[x_e][y_e] = 1;
                loop_valido = 1;
            }
        } while (loop_valido == 0);
    }

    // ============================= 3. FASE DE BATALHA =============================
    printf("\n*** POSICIONAMENTO CONCLUÍDO! INICIANDO FASE DE BATALHA! ***\n");

    // Matrizes 5x5 que definem o padrão de cada habilidade.
    int padrao_cruz[5][5]     = { {0,0,1,0,0}, {0,0,1,0,0}, {1,1,1,1,1}, {0,0,1,0,0}, {0,0,1,0,0} };
    int padrao_cone[5][5]     = { {0,0,1,0,0}, {0,1,1,1,0}, {1,1,1,1,1}, {0,0,0,0,0}, {0,0,0,0,0} };
    int padrao_octaedro[5][5] = { {0,0,1,0,0}, {0,1,1,1,0}, {1,1,1,1,1}, {0,1,1,1,0}, {0,0,1,0,0} };

    // Loop para 3 turnos de ataque.
    for (int turno = 1; turno <= 3; turno++) {
        int habilidade, x_centro, y_centro;
        char coordenada[4];

        printf("\n--- TURNO DE ATAQUE #%d ---\n", turno);
        printf("   1 2 3 4 5 6 7 8 9 10   (Legenda: N=Navio, ~=Agua, *=Erro, X=Acerto)\n");
        for (y = 0; y < 10; y++) {
            printf("%c  ", linha_letras[y]);
            for (x = 0; x < 10; x++) {
                switch(tabuleiro[x][y]) {
                    case 0: printf("~ "); break; // Água Intacta
                    case 1: printf("N "); break; // Navio Intacto
                    case 2: printf("* "); break; // Tiro na Água
                    case 3: printf("X "); break; // Navio Atingido
                }
            }
            printf("\n");
        }

        printf("\nEscolha sua habilidade de ataque:\n");
        printf("1. Cruz | 2. Cone | 3. Octaedro\n");
        scanf("%d", &habilidade);
        printf("Digite a coordenada CENTRAL do ataque (ex: D5): ");
        scanf("%3s", coordenada);

        y_centro = toupper(coordenada[0]) - 'A';
        x_centro = atoi(&coordenada[1]) - 1;

        // Ponteiro que aponta para o padrão de ataque escolhido.
        int (*p_ataque)[5] = NULL;
        switch(habilidade) {
            case 1: p_ataque = padrao_cruz; break;
            case 2: p_ataque = padrao_cone; break;
            case 3: p_ataque = padrao_octaedro; break;
            default: printf("Habilidade inválida! Turno perdido.\n"); continue; // Pula para o próximo turno.
        }

        printf("Lançando ataque...\n");
        // Itera sobre a matriz de ataque 5x5.
        for (int j = 0; j < 5; j++) {
            for (int k = 0; k < 5; k++) {
                // Se a célula do padrão for 1, aplica o ataque.
                if (p_ataque[j][k] == 1) {
                    // Calcula a coordenada real no tabuleiro, centralizando o padrão.
                    int x_alvo = x_centro + (k - 2);
                    int y_alvo = y_centro + (j - 2);

                    // Verifica se o alvo está dentro dos limites do tabuleiro.
                    if (x_alvo >= 0 && x_alvo < 10 && y_alvo >= 0 && y_alvo < 10) {
                        if (tabuleiro[x_alvo][y_alvo] == 0) { tabuleiro[x_alvo][y_alvo] = 2; } // Água -> Erro
                        else if (tabuleiro[x_alvo][y_alvo] == 1) { tabuleiro[x_alvo][y_alvo] = 3; } // Navio -> Acerto
                    }
                }
            }
        }
    }
    printf("\n*** FIM DA FASE DE BATALHA! ***\n");
    return 0;
}
