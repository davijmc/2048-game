#include <iostream>
#include <cstring>
#include <ctime>
#include <iomanip>
#include <conio.h>

using namespace std;

// Função para mover para cima
void up(int mat[4][4]) {
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 4; j++) {
            for (int h = 0; h < 3; h++) {
                if (mat[h][j] == 0) {
                    mat[h][j] = mat[h+1][j];
                    mat[h+1][j] = 0;
                }
            }
            
            if (mat[i][j] == mat[i+1][j]) {
                mat[i][j] += mat[i+1][j];
                for (int k = i+1; k < 3; k++) {
                    mat[k][j] = mat[k+1][j];
                }
                mat[3][j] = 0;
            }
        }
    }
}

// Função para mover para baixo
void down(int mat[4][4]) {
    for (int i = 3; i > 0; i--) {  // Começar da última linha (3) até a linha 1
        for (int j = 0; j < 4; j++) {
            for (int h = 3; h > 0; h--) {  // Mover os números para baixo
                if (mat[h][j] == 0) {
                    mat[h][j] = mat[h-1][j];
                    mat[h-1][j] = 0;
                }
            }
            
            if (mat[i][j] == mat[i-1][j]) {  // Verifica se é possível somar
                mat[i][j] += mat[i-1][j];
                for (int k = i-1; k > 0; k--) {
                    mat[k][j] = mat[k-1][j];
                }
                mat[0][j] = 0;
            }
        }
    }
}

// Função para mover para a esquerda
void left(int mat[4][4]) {
    for (int i = 0; i < 4; i++) {  // Para cada linha
        for (int j = 0; j < 3; j++) {  // Para cada coluna da linha
            for (int h = 0; h < 3; h++) {  // Mover os números para a esquerda
                if (mat[i][h] == 0) {
                    mat[i][h] = mat[i][h+1];
                    mat[i][h+1] = 0;
                }
            }
            
            if (mat[i][j] == mat[i][j+1]) {  // Verifica se é possível somar
                mat[i][j] += mat[i][j+1];
                for (int k = j+1; k < 3; k++) {
                    mat[i][k] = mat[i][k+1];
                }
                mat[i][3] = 0;
            }
        }
    }
}

// Função para mover para a direita
void right(int mat[4][4]) {
    for (int i = 0; i < 4; i++) {  // Para cada linha
        for (int j = 3; j > 0; j--) {  // Para cada coluna da linha, começando da última
            for (int h = 3; h > 0; h--) {  // Mover os números para a direita
                if (mat[i][h] == 0) {
                    mat[i][h] = mat[i][h-1];
                    mat[i][h-1] = 0;
                }
            }
            
            if (mat[i][j] == mat[i][j-1]) {  // Verifica se é possível somar
                mat[i][j] += mat[i][j-1];
                for (int k = j-1; k > 0; k--) {
                    mat[i][k] = mat[i][k-1];
                }
                mat[i][0] = 0;
            }
        }
    }
}

// Função de undo (desfazer movimento)
void undo(int mat[4][4], int old[4][4]) {
    memcpy(mat, old, sizeof(int) * 16);  // Copiar o estado antigo da matriz
}

char checkFlag(int mat[4][4]) {
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            if (mat[i][j] == 0) {
                return 'T';
            }else if ((i > 0 && mat[i][j] == mat[i-1][j]) ||
                        (i < 3 && mat[i][j] == mat[i+1][j]) ||
                        (j > 0 && mat[i][j] == mat[i][j-1]) ||
                        (j < 3 && mat[i][j] == mat[i][j+1])) {
                return 'T';
            }
        }
    }
    return 'F';
}

// Função para imprimir a matriz
void printMatrix(int mat[4][4]) {
    cout << endl << endl << endl << endl << endl << endl;
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            cout << setw(4) << mat[i][j] << " ";
        }
        cout << endl;
    }
}

// Função para adicionar um número à matriz
/*
char addNum(int mat[4][4], int *maxP) {
    int vetLin[4] = {0, 1, 2, 3};
    int vetCol[4] = {0, 1, 2, 3};
    int ctrl = 4, ctrc = 4;
    unsigned seed = time(NULL);
    srand(seed);

    while (1) {
        for (int k = 0; k < 4; k++) {
            int lin = rand() % ctrl;
            lin = vetLin[lin];
            for (int i = 0; i < ctrl; i++) {
                if (vetLin[i] == lin) {
                    vetLin[i] = vetLin[i+1];
                    vetLin[i+1] = lin;
                }
            }
            ctrl--;

            for (int j = 0; j < 4; j++) {
                int col = rand() % ctrc;
                col = vetCol[col];
                for (int i = 0; i < ctrc; i++) {
                    if (vetCol[i] == col) {
                        vetCol[i] = vetCol[i+1];
                        vetCol[i+1] = col;
                    }
                }
                ctrc--;

                if (mat[lin][col] == 0) {
                    int sum = 0, rnd;
                    rnd = rand() % 100;
                    if (*maxP > 2048) {
                        if (*maxP > 4090) {
                            sum = (rnd > 50) ? 4 : 2;
                        } else {
                            sum = (rnd > 75) ? 4 : 2;
                        }
                    } else {
                        sum = (rnd > 90) ? 4 : 2;
                    }

                    mat[lin][col] = sum;
                    *maxP += sum;
                    return 'T';
                } else if ((lin > 0 && mat[lin][col] == mat[lin-1][col]) ||
                           (lin < 3 && mat[lin][col] == mat[lin+1][col]) ||
                           (col > 0 && mat[lin][col] == mat[lin][col-1]) ||
                           (col < 3 && mat[lin][col] == mat[lin][col+1])) {
                    return 'T';
                }
            }
            ctrc = 4;
        }
        return 'F';
    }
}
*/
void addNum(int mat[4][4], int *maxP) {
    char teste = 'F';
    unsigned seed = time(NULL);
    srand(seed);
    int lin, col, sum, rnd;
    while (teste == 'F')
    {
        lin = rand() % 4;
    col = rand() % 4;
    if (mat[lin][col] == 0) {
        rnd = rand() % 100;
        if (*maxP > 2048) {
            if (*maxP > 4090) {
                sum = (rnd > 50) ? 4 : 2;
            } else {
                sum = (rnd > 75) ? 4 : 2;
            }
        } else {
            sum = (rnd > 90) ? 4 : 2;
        }
        mat[lin][col] = sum;
        *maxP += sum;
        teste = 'T';
    }
    }
}

int main() {
    int mat[4][4], old[4][4], aux[4][4], maxP = 0;
    char mov, flag = 'T';
    memset(mat, 0, sizeof(mat));
    memset(aux, 0, sizeof(aux));

    while (flag == 'T') {
        memcpy(old, aux, sizeof(mat));
        memcpy(aux, mat, sizeof(mat));
        addNum(mat, &maxP);
        printMatrix(mat);
        mov = getch();

        switch (mov) {
            case 'w':
                up(mat);
                break;
            case 'd':
                right(mat);
                break;
            case 'a':
                left(mat);
                break;
            case 's':
                down(mat);
                break;
            case 'f':
                undo(mat, old);
                break;
            default:
                break;
        }
        flag = checkFlag(mat);
    }

    cout << "Sua pontuacao foi: " << maxP << endl;

    return 0;
}
