#include <stdio.h>
#include <stdlib.h>

//o metodo consiste em fazer uma salada de funcoes de interpolacao (combinacao linear)
//e resolver a ed como um sistema linear usando integrais locais

#define N_NOS 201    // num nos: de 0 a 2 com passo 0.01. Antes estava usando so 20, mas nao era o suficiente. 
#define N_ELEM (N_NOS - 1)
#define DX 0.01 // passo

int main() {
    int i, j;
    //todas as matrizes abaixo vieram da solucao de integrais relacionadas com o sistema a ser resolvido 
    //wowe..
    double K[N_NOS][N_NOS] = {0};  // matriz de rigidez global 
    double F[N_NOS] = {0};         // vetor de forças
    double U[N_NOS];               // solucao

    // montando matriz K e vetor F usando elementos lineares
    for (i = 0; i < N_ELEM; i++) {
        // matriz de rigidez local (2x2)
        double k_local[2][2] = {
            {1.0/DX, -1.0/DX},
            {-1.0/DX, 1.0/DX}
        };

        // vetor de forcas local (considerando f(x)=2 constante no elemento) // nao estava no pdf da aula
        double f_local[2] = {2*DX/2.0, 2*DX/2.0};  // integral do f(x)*phi_i(x)

        // matriz do termo 7*u'(x), nao estava no pdf da aula
        double c_local[2][2] = {
            {-7.0/2.0, 7.0/2.0},
            {-7.0/2.0, 7.0/2.0}
        };

        // matriz do termo -u(x)
        double m_local[2][2] = {
            {DX/3.0, DX/6.0},
            {DX/6.0, DX/3.0}
        };

        // adicionar contribuicoes na matriz global
        for (j = 0; j < 2; j++) {
            for (int k = 0; k < 2; k++) {
                K[i+j][i+k] += k_local[j][k] + c_local[j][k] - m_local[j][k];
            }
            F[i+j] += f_local[j];
        }
    }

    // impor condicoes de contorno de dirichlet:
    // u(0)=10
    for (j = 0; j < N_NOS; j++) {
        if (j != 0) {
            F[j] -= K[j][0]*10;
            K[0][j] = 0;
            K[j][0] = 0;
        }
    }
    K[0][0] = 1.0;
    F[0] = 10;

    // u(2)=1
    for (j = 0; j < N_NOS; j++) {
        if (j != N_NOS-1) {
            F[j] -= K[j][N_NOS-1]*1;
            K[N_NOS-1][j] = 0;
            K[j][N_NOS-1] = 0;
        }
    }
    K[N_NOS-1][N_NOS-1] = 1.0;
    F[N_NOS-1] = 1;

    // Resolver o sistema K*U=F por eliminação de Gauss simples
    for (i = 0; i < N_NOS; i++) {
        for (j = i+1; j < N_NOS; j++) {
            double f = K[j][i]/K[i][i];
            for (int k = i; k < N_NOS; k++)
                K[j][k] -= f*K[i][k];
            F[j] -= f*F[i];
        }
    }
    for (i = N_NOS-1; i >= 0; i--) {
        U[i] = F[i];
        for (j = i+1; j < N_NOS; j++)
            U[i] -= K[i][j]*U[j];
        U[i] /= K[i][i];
    }

    //a saida da uma queda brusca, por causa de 7u'(x)
    printf("x\tU(x)\n");
    for (i = 0; i < N_NOS; i++) {
        double x = i*DX;
        printf("%.2lf\t%.8lf\n", x, U[i]);
    }

    return 0;
}
