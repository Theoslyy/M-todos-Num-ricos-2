#include <stdio.h>
#include <stdlib.h>

#define N 20  // u(0) e u(2) sao os elem. conhecidos. fornecido pelo problema
#define DX 0.1

int main() {
    double a[N][N] = {0};  // matriz de coeficientes
    double b[N];           // vetor do lado direito
    double u[N];           // solucao aproximada nos pontos internos

    //auxs
    double dx2 = DX * DX;
    double central = -2.0 / dx2 - 1.0;
    double esquerda = 1.0 / dx2 - 7.0 / (2.0 * DX);
    double direita = 1.0 / dx2 + 7.0 / (2.0 * DX);

    for (int i = 0; i < N; i++) {
        if (i > 0)
            a[i][i - 1] = esquerda;

        a[i][i] = central;

        if (i < N - 1)
            a[i][i + 1] = direita;

        b[i] = -2.0;

        if (i == 0)
            b[i] -= esquerda * 10.0;  // u(0) = 10, fornecido pelo problema
        if (i == N - 1)
            b[i] -= direita * 1.0;    // u(2) = 1, tambem fornecido pelo problema
    }

    //gauss simples p resolver o sistema
    for (int i = 0; i < N; i++) {
        for (int j = i + 1; j < N; j++) {
            double f = a[j][i] / a[i][i];
            for (int k = 0; k < N; k++)
                a[j][k] -= f * a[i][k];
            b[j] -= f * b[i];
        }
    }
    for (int i = N - 1; i >= 0; i--) {
        u[i] = b[i];
        for (int j = i + 1; j < N; j++)
            u[i] -= a[i][j] * u[j];
        u[i] /= a[i][i];
    }

    printf("x\t\tu(x)\n");
    printf("--------------------\n");
    printf("0.0\t\t10.000000\n");  // condicao dada de contorno
    for (int i = 0; i < N - 1; i++) {
        printf("%.1f\t\t%.6f\n", (i + 1) * DX, u[i]);
    }
    printf("2.0\t\t1.000000\n");   // condicao dada de contorno

    return 0;
}
