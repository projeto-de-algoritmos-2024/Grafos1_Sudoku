#include <stdio.h>
#include <stdbool.h>
#define N 9

// Estrutura para representar um nó no grafo
typedef struct {
    int lin, col;
} Node;

// Printa a tabela de sudoku
void printTabela(int tabela[N][N]) {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            printf("%d ", tabela[i][j]);
        }
        printf("\n");
    }
}

bool numerosIguais(int tabela[N][N], int lin, int col, int num) {
    // Verifica se o número já existe na linha ou coluna
    for (int x = 0; x < N; x++) {
        if (tabela[lin][x] == num || tabela[x][col] == num) {
            return true;
        }
    }
    // Verifica se o número já existe no bloco 3x3
    int initLin = lin - lin % 3;
    int initCol = col - col % 3;
    
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (tabela[i + initLin][j + initCol] == num) {
                return true;
            }
        }
    }
    return false;
}

// Resolve a tabela de sudoku
bool resolverSudoku(int tabela[N][N]) {
    int lin, col;
    bool vazioEncontrado = false;
    // Encontra uma célula vazia na tabela
    for (lin = 0; lin < N; lin++) {
        for (col = 0; col < N; col++) {
            if (tabela[lin][col] == 0) {
                vazioEncontrado = true;
                break;
            }
        }
        if (vazioEncontrado) {
            break;
        }
    }
    // Se não houver células vazias, o Sudoku está resolvido
    if (!vazioEncontrado) {
        return true;
    }
    // Tenta preencher a célula vazia com números de 1 a 9
    for (int num = 1; num <= 9; num++) {
        if (!numerosIguais(tabela, lin, col, num)) {
            tabela[lin][col] = num;
            // Chama recursivamente para continuar a resolução
            if (resolverSudoku(tabela)) {
                return true;
            }
            // Se a recursão não der certo, volta a posição original
            tabela[lin][col] = 0;
        }
    }
    // Retorna falso se não conseguir resolver
    return false;
}

int main() {
    int sudoku[N][N] = {
        {5, 3, 0, 0, 7, 0, 0, 0, 0},
        {6, 0, 0, 1, 9, 5, 0, 0, 0},
        {0, 9, 8, 0, 0, 0, 0, 6, 0},
        {8, 0, 0, 0, 6, 0, 0, 0, 3},
        {4, 0, 0, 8, 0, 3, 0, 0, 1},
        {7, 0, 0, 0, 2, 0, 0, 0, 6},
        {0, 6, 0, 0, 0, 0, 2, 8, 0},
        {0, 0, 0, 4, 1, 9, 0, 0, 5},
        {0, 0, 0, 0, 8, 0, 0, 7, 9}};

    printf("Sudoku original:\n");
    printTabela(sudoku);

    if (resolverSudoku(sudoku)) {
        printf("\nSudoku resolvido:\n");
        printTabela(sudoku);
    }
    else {
        printf("O Sudoku não pôde ser resolvido.\n");
    }
    return 0;
}
