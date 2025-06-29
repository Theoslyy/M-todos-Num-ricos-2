#include <stdio.h>
#include <stdlib.h>
#define _USE_MATH_DEFINES
#include <math.h>
#include "operacoes.c"

#define EPS 1e-6

double** matriz_jacobi(double** A, int i, int j, int n) {
    double** J = aloca_matriz(n);
    identidade(J, n);

    if (fabs(A[i][j]) <= EPS)
        return J;

    double theta;
    if (fabs(A[j][j]) <= EPS) {
        theta = (A[i][j] < 0) ? M_PI / 2 : -M_PI / 2;
    } else {
        theta = atan2(-A[i][j], A[j][j]);
    }

    J[i][i] = cos(theta);
    J[j][j] = cos(theta);
    J[i][j] = sin(theta);
    J[j][i] = -sin(theta);

    return J;
}

void decomposicaoQR(double** A, double*** Q_out, double*** R_out, int n) {
    double** QT = aloca_matriz(n);
    identidade(QT, n);
    double** R = aloca_matriz(n);
    copia_matriz(A, R, n);

    for (int j = 0; j < n - 1; j++) {
        for (int i = j + 1; i < n; i++) {
            double** J = matriz_jacobi(R, i, j, n);
            double** Rt = aloca_matriz(n);
            mult_mat_mat(J, R, Rt, n); // R nova <- JRvelha
            libera_matriz(R, n);
            R = Rt;

            double** QTt = aloca_matriz(n);
            mult_mat_mat(J, QT, QTt, n); //acumulando os produtos
            libera_matriz(QT, n);
            QT = QTt;
            libera_matriz(J, n);
        }
    }

    *Q_out = aloca_matriz(n);
    transposta(QT, *Q_out, n);
    *R_out = R;
    libera_matriz(QT, n);
}

double soma_abaixo_diagonal(double** A, int n) {
    double soma = 0.0;
    for (int i = 1; i < n; i++)
        for (int j = 0; j < i; j++)
            soma += A[i][j] * A[i][j];
    return soma;
}

void metodoQR(double** A, double*** autovetores, double*** matriz_diagonal, int n, double epsilon) {
    double** P = aloca_matriz(n);
    identidade(P, n);

    double** Avelha = aloca_matriz(n);
    copia_matriz(A, Avelha, n);
    double val = 100.0;

    while (val > epsilon) {
        double **Q, **R;
        decomposicaoQR(Avelha, &Q, &R, n);
        double** A_nova = aloca_matriz(n);
        mult_mat_mat(R, Q, A_nova, n); // o mesmo que Anova <- QtAvelhaQ

        double** Ptemp = aloca_matriz(n);
        mult_mat_mat(P, Q, Ptemp, n); // acumula matriz, novamente que nem o jacobi e o householder
        libera_matriz(P, n);
        P = Ptemp;

        libera_matriz(Avelha, n);
        Avelha = A_nova;
        libera_matriz(Q, n);
        libera_matriz(R, n);

        val = soma_abaixo_diagonal(A_nova, n); //check de convergencia
    }

    *matriz_diagonal = Avelha;
    *autovetores = P;
}

int main() {
    int n = 3;
    double** A = aloca_matriz(n);
    A[0][0] = 2; A[0][1] = -1; A[0][2] = 0;
    A[1][0] = -1; A[1][1] = 2; A[1][2] = -1;
    A[2][0] = 0; A[2][1] = -1; A[2][2] = 2;

    double** matriz_diagonal;
    double** autovetores;

    metodoQR(A, &autovetores, &matriz_diagonal, n, 1e-6);

    printf("Matriz diagonalizada (autovalores na diagonal):\n");
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++)
            printf("% .6f ", matriz_diagonal[i][j]);
        printf("\n");
    }

    printf("\nAutovetores (colunas):\n");
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++)
            printf("% .6f ", autovetores[i][j]);
        printf("\n");
    }

    libera_matriz(A, n);
    libera_matriz(autovetores, n);
    libera_matriz(matriz_diagonal, n);
    return 0;
}
