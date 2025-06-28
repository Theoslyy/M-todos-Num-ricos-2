#include <stdio.h>
#include <stdlib.h>
#define _USE_MATH_DEFINES
#include <math.h>
#include "operacoes.c"


//definir pi com a precisao que voce quiser!
#define MAX_ITER 10000


double** matrizJacobiBaseadaNoElemento(double** A, int i, int j, int n) {
    double** J = aloca_matriz(n);
    identidade(J, n);

    double eps = 1e-6;
    double theta;

    if (fabs(A[i][j]) <= eps)
        return J;

    if (fabs(A[i][i] - A[j][j]) <= eps) {
        theta = M_PI / 4.0;
    } else {
        theta = 0.5 * atan2(-2 * A[i][j], A[i][i] - A[j][j]);
    }

    double c = cos(theta);
    double s = sin(theta);

    J[i][i] =  c;
    J[j][j] =  c;
    J[i][j] =  s;
    J[j][i] = -s;

    return J;
}

void varreduraDeJacobi(double** A, double** A_diag, double epsilon, double** J_out, int n) {
    int it = 0;
    double erro;

    double** J = aloca_matriz(n);
    identidade(J, n);
    double** A_velha = aloca_matriz(n);
    copia_matriz(A, A_velha, n);

    double** J_ij = NULL;
    double** J_ij_T = aloca_matriz(n);
    double** temp = aloca_matriz(n);
    double** A_nova = aloca_matriz(n);
    //aqui o do while e mais para ser chique, faco uma vez e checo se batemos um criterio bom o suficiente
    //se nao, fazemos outra varredura.
    do {
        erro = 0.0;
        for (int j = 0; j < n - 1; j++) {
            for (int i = j + 1; i < n; i++) {
                if (fabs(A_velha[i][j]) > epsilon) {
                    erro += fabs(A_velha[i][j]);

                    J_ij = matrizJacobiBaseadaNoElemento(A_velha, i, j, n);
                    transposta(J_ij, J_ij_T, n);

                    //A_nova = J_ij^T * A_velha * J_ij, yippe, a aplicacao do metodo.
                    mult_mat_mat(J_ij_T, A_velha, temp, n); //usamos o mesmo esquema de temp que no metodo de householder
                    mult_mat_mat(temp, J_ij, A_nova, n);
                    copia_matriz(A_nova, A_velha, n);

                    //atualiza J acumulado, que nem no metodo de householder!
                    mult_mat_mat(J, J_ij, temp, n);
                    copia_matriz(temp, J, n);

                    libera_matriz(J_ij, n);
                }
            }
        }
        it++;
    } while (erro > epsilon && it < MAX_ITER);

    copia_matriz(A_nova, A_diag, n);
    copia_matriz(J, J_out, n);

    libera_matriz(A_velha, n);
    libera_matriz(J_ij_T, n);
    libera_matriz(temp, n);
    libera_matriz(A_nova, n);
    libera_matriz(J, n);
}

int main() {
    int n = 3;
    const double epsilon = 1e-6;

    double** A = aloca_matriz(n);
    A[0][0] = 2; A[0][1] = -1; A[0][2] =  0;
    A[1][0] = -1; A[1][1] = 2; A[1][2] = -1;
    A[2][0] =  0; A[2][1] = -1; A[2][2] = 2;

    double** A_diag = aloca_matriz(n); 
    double** J = aloca_matriz(n);    

    varreduraDeJacobi(A, A_diag, epsilon, J, n);

    printf("Matriz diagonalizada (autovalores aproximados)/:\n");
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++)
            printf("%10.6f ", A_diag[i][j]);
        printf("\n");
    }
    printf("\nMatriz de autovetores (colunas são os autovetores):\n");
    for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++)
        printf("%10.6f ", J[i][j]);
    printf("\n");
    }

    libera_matriz(A, n);
    libera_matriz(A_diag, n);
    libera_matriz(J, n);
    return 0;

    }