#include <iostream>
#include <cstring>
#include <ctime>
#include <iomanip>
#include <conio.h>
#include <vector>

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

/*
char checkFlag(int mat[4][4]) {
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            if (mat[i][j] == 0) {
                return 'Z';
            }
        }
    }
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            if ((i > 0 && mat[i][j] == mat[i-1][j]) ||
                        (i < 3 && mat[i][j] == mat[i+1][j]) ||
                        (j > 0 && mat[i][j] == mat[i][j-1]) ||
                        (j < 3 && mat[i][j] == mat[i][j+1])) {
                return 'T';
            }
        }
    }
    return 'F';
}
*/

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
char addNum(int mat[4][4], int *maxP) {
    vector<int> lin = {0, 1, 2, 3};
    vector<int> col = {0, 1, 2, 3};
    char flag = 'F';
    int ctrl = 4, ctrc = 4, x, y;
    unsigned seed = time(NULL);
    srand(seed);

    while (1) {
        for (int k = 0; k < 4; k++) {
            int rlin = rand() % ctrl;
            ctrl--;
            x = lin.at(rlin);
            lin.erase(lin.begin() + rlin);
            for(int i = 0; i < 4; i++) {
                int rcol = rand() % ctrc;
                ctrc--;
                y = col.at(rcol);
                col.erase(col.begin() + rcol);
                if (mat[x][y] == 0) {
                    int sum = 0, rnd;
                    rnd = rand() % 100;
                    if (*maxP > 2048) {
                        if (*maxP > 4090) {
                            sum = (rnd > 50) ? 4 : 2;
                        } else {
                            sum = (rnd > 75) ? 4 : 2;
                        }
                    } else {
                        sum = (rnd > 95) ? 4 : 2;
                    }

                    mat[x][y] = sum;
                    *maxP += sum;
                    return 'T';
                } else if ((x > 0 && mat[x][y] == mat[x-1][y]) ||
                            (x < 3 && mat[x][y] == mat[x+1][y]) ||
                            (y > 0 && mat[x][y] == mat[x][y-1]) ||
                            (y < 3 && mat[x][y] == mat[x][y+1])){
                    flag = 'T';
                }
            }
            ctrc = 4;
            col = {0, 1, 2, 3};
        }
        return flag;
    }
}

/*
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
*/

int main() {
    int mat[4][4], old[4][4], aux[4][4], maxP = 0;
    int record; //read from file
    FILE *file;
    if ((file = fopen("record.txt", "r")) == NULL) {
        file = fopen("record.txt", "w");
        fprintf(file, "%d", 0);
        record = 0;
        fclose(file);
    } else {
        fscanf(file, "%d", &record);
        fclose(file);
    }
    char mov, flag = 'Z';
    memset(mat, 0, sizeof(mat));
    memset(aux, 0, sizeof(aux));

    while (flag != 'F') {
        memcpy(old, aux, sizeof(mat));
        memcpy(aux, mat, sizeof(mat));
        /*if(flag == 'Z'){
            addNum(mat, &maxP);
        }*/
        flag = addNum(mat, &maxP);
        if(maxP > record){
            record = maxP;
            file = fopen("record.txt", "w");
            fprintf(file, "%d", record);
            fclose(file);
        }
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
        //flag = checkFlag(mat);
    }

    cout << "Sua pontuacao foi: " << maxP << endl;
    cout << "Seu record eh: " << record << endl;
    return 0;
}
