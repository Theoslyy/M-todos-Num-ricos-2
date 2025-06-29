#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "operacoes.c"

void criaHouseholder(double** A, double** H, int n, int i) {
    double* w = calloc(n, sizeof(double)); //elementos abaixo da diagonal de i
    double* w_ = calloc(n, sizeof(double)); // norma do vetor w na posição i+1
    double* N = calloc(n, sizeof(double)); // N = w - w'
    double* nvec = calloc(n, sizeof(double)); // N normalizado

    for (int k = i + 1; k < n; k++) {
        w[k] = A[k][i];
    }
    double Lw = norma(w, n);
    w_[i + 1] = Lw;
    for (int k = 0; k < n; k++)
        N[k] = w[k] - w_[k];
    double normN = norma(N, n);

    if (normN < 1e-12) { // check norma é muito proxima de zero, a matriz de reflexao é a identidade. 
        identidade(H, n);
        free(w);
        free(w_);
        free(N);
        free(nvec);
    }
    else{
        for (int k = 0; k < n; k++)
            nvec[k] = N[k] / normN; //construindo nvec 

        //construindo a matriz em si H = I - 2nnt
        for (int r = 0; r < n; r++) {
            for (int c = 0; c < n; c++) {
                H[r][c] = -2.0 * nvec[r] * nvec[c];
                if (r == c)
                    H[r][c] += 1.0;
                }
        }
        free(w);
        free(w_);
        free(N);
        free(nvec);
    }
}

void metodoDeHouseholder(double** A, double** A_tridiag, double** H, int n) {
    double** A_prev = aloca_matriz(n);
    double** H_i = aloca_matriz(n);
    double** temp = aloca_matriz(n);
    identidade(H, n);
    copia_matriz(A, A_prev, n);

    for (int i = 0; i < n - 2; i++) {
        criaHouseholder(A_prev, H_i, n, i);

        //Ai = Hit * A_prev * Hi
        //mas Hit == Hi, propriedade de simetria da matriz de householder!! 
        //nos proximos metodos teremos que calcular a transposta :(
        mult_mat_mat(H_i, A_prev, temp, n);           //temp = Hi * A
        mult_mat_mat(temp, H_i, A_tridiag, n);        //A_tridiag = temp * Hi

        //H = H * Hi (acumula transformações)
        mult_mat_mat(H, H_i, temp, n);
        copia_matriz(temp, H, n);

        copia_matriz(A_tridiag, A_prev, n);
    }

    libera_matriz(A_prev, n);
    libera_matriz(H_i, n);
    libera_matriz(temp, n);
}
int main() {
    int n = 5;
    double** A = aloca_matriz(n);
    A[0][0] = 10;  A[0][1] =  2;  A[0][2] =  3;  A[0][3] =  4;  A[0][4] = 5;
    A[1][0] =  2;  A[1][1] =  9;  A[1][2] =  4;  A[1][3] =  1;  A[1][4] = 2;
    A[2][0] =  3;  A[2][1] =  4;  A[2][2] =  8;  A[2][3] =  6;  A[2][4] = 3;
    A[3][0] =  4;  A[3][1] =  1;  A[3][2] =  6;  A[3][3] =  7;  A[3][4] = 4;
    A[4][0] =  5;  A[4][1] =  2;  A[4][2] =  3;  A[4][3] =  4;  A[4][4] = 6;

    double** A_tridiag = aloca_matriz(n);
    double** H = aloca_matriz(n);

    metodoDeHouseholder(A, A_tridiag, H, n);

    printf("Matriz tridiagonal:\n");
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++)
            printf("%7.4f ", A_tridiag[i][j]);
        printf("\n");
    }

    libera_matriz(A, n);
    libera_matriz(A_tridiag, n);
    libera_matriz(H, n);
    return 0;
}
