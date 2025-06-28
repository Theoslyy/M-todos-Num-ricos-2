#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "operacoes.c"

void criaHouseholder(double** A, double** H, int n, int i) {
    double* w1  = calloc(n, sizeof(double)); // elementos abaixo da diagonal principal
    double* w2 = calloc(n, sizeof(double)); // norma de w1
    double* N  = calloc(n, sizeof(double)); // w - w'
    double* nvec = calloc(n, sizeof(double)); // N normalizado

    for (int k = i + 1; k < n; k++)
        w1[k] = A[k][i]; //pegando os elementos abaixo da diagonal principal 

    //calculando o resto
    double norma_w1 = norma(w1, n);
    w2[i + 1] = norma_w1;

    for (int k = 0; k < n; k++)
        N[k] = w1[k] - w2[k];

    double normN = norma(N, n);
    for (int k = 0; k < n; k++)
        nvec[k] = (normN == 0) ? 0 : N[k] / normN;

    //H = I - 2nnᵗ
    identidade(H, n);
    for (int r = 0; r < n; r++)
        for (int c = 0; c < n; c++)
            H[r][c] -= 2 * nvec[r] * nvec[c];

    free(w1); free(w2); free(N); free(nvec);
}

void metodoDeHouseholder(double** A, double** A_tridiag, double** H, int n) {
    double** A_prev = aloca_matriz(n);
    double** H_i = aloca_matriz(n);
    double** temp = aloca_matriz(n);
    identidade(H, n);
    copia_matriz(A, A_prev, n);

    for (int i = 0; i < n - 2; i++) {
        criaHouseholder(A_prev, H_i, n, i);

        // Aᵢ = Hit * A_prev * Hi
        // mas Hit == Hi, propriedade de simetria da matriz de householder
        mult_mat_mat(H_i, A_prev, temp, n);           // temp = Hi * A
        mult_mat_mat(temp, H_i, A_tridiag, n);        // A_tridiag = temp * Hi

        // H = H * Hi (acumula transformações)
        mult_mat_mat(H, H_i, temp, n);
        copia_matriz(temp, H, n);

        // Atualiza A_prev
        copia_matriz(A_tridiag, A_prev, n);
    }

    libera_matriz(A_prev, n);
    libera_matriz(H_i, n);
    libera_matriz(temp, n);
}
int main() {
    int n = 3;
    double** A = aloca_matriz(n);
    A[0][0] = 2; A[0][1] = -1; A[0][2] = 0;
    A[1][0] = -1; A[1][1] = 2; A[1][2] = -1;
    A[2][0] = 0; A[2][1] = -1; A[2][2] = 2;

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
