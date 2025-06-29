#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "operacoes.h"


double** aloca_matriz(int n) {
    double** mat = malloc(n * sizeof(double*));
    for (int i = 0; i < n; i++)
        mat[i] = calloc(n, sizeof(double));
    return mat;
}

void libera_matriz(double** mat, int n) {
    for (int i = 0; i < n; i++) free(mat[i]);
    free(mat);
}

void identidade(double** I, int n) {
    for (int i = 0; i < n; i++)
        I[i][i] = 1.0;
}

void copia_matriz(double** A, double** B, int n) {
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            B[i][j] = A[i][j];
}

void mult_mat_vec(double** A, double* x, double* y, int n) {
    for (int i = 0; i < n; i++) {
        y[i] = 0;
        for (int j = 0; j < n; j++)
            y[i] += A[i][j] * x[j];
    }
}

void mult_mat_mat(double** A, double** B, double** C, int n) {
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++) {
            C[i][j] = 0;
            for (int k = 0; k < n; k++)
                C[i][j] += A[i][k] * B[k][j];
        }
}

double norma(double* v, int n) {
    double soma = 0;
    for (int i = 0; i < n; i++) soma += v[i] * v[i];
    return sqrt(soma);
}

void transposta(double** M, double** Mt, int n) {
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            Mt[i][j] = M[j][i];
}
