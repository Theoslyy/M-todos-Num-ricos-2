#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "operacoes.h"

void multiplicar_matriz_vetor(double **matriz, double *vetor, double *resultado, int n) {
    for (int i = 0; i < n; i++) {
        resultado[i] = 0.0;
        for (int j = 0; j < n; j++) {
            resultado[i] += matriz[i][j] * vetor[j];
        }
    }
}

double produto_escalar(double *v1, double *v2, int n) {
    double resultado = 0.0;
    for (int i = 0; i < n; i++) {
        resultado += v1[i] * v2[i];
    }
    return resultado;
}

void normalizar_vetor(double *vetor, int n) {
    double norma = sqrt(produto_escalar(vetor, vetor, n));
    for (int i = 0; i < n; i++) {
        vetor[i] /= norma;
    }
}
// calcula a inversa da matriz A via eliminação de Gauss (para pequenas matrizes)
// nao lembro aonde esta meu repositorio de metodos I para ir atras do que eu ja tinha feito :(
void calcular_inversa(double **A, double **A_inv, int n) {
    // inicializa A_inv como identidade
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            A_inv[i][j] = (i == j) ? 1.0 : 0.0;
        }
    }

    // temp
    double **temp = malloc(n * sizeof(double *));
    for (int i = 0; i < n; i++) {
        temp[i] = malloc(n * sizeof(double));
        for (int j = 0; j < n; j++) {
            temp[i][j] = A[i][j];
        }
    }

    // Gauss-Jordan
    for (int i = 0; i < n; i++) {
        double diag = temp[i][i];
        for (int j = 0; j < n; j++) {
            temp[i][j] /= diag;
            A_inv[i][j] /= diag;
        }

        for (int k = 0; k < n; k++) {
            if (k != i) {
                double fator = temp[k][i];
                for (int j = 0; j < n; j++) {
                    temp[k][j] -= fator * temp[i][j];
                    A_inv[k][j] -= fator * A_inv[i][j];
                }
            }
        }
    }

    for (int i = 0; i < n; i++) free(temp[i]);
    free(temp);
}