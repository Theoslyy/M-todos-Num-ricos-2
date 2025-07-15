#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define TOLERANCIA 0.01

// FUNCOES PARA MATRIZ:
//a matriz de double serve para os filtros e a matriz de int e a matriz final

double** aloca_matriz_double(int linhas, int colunas) {
    double** matriz = malloc(linhas * sizeof(double*));
    for (int i = 0; i < linhas; ++i)
        matriz[i] = malloc(colunas * sizeof(double));
    return matriz;
}

int** aloca_matriz_int(int linhas, int colunas) {
    int** matriz = malloc(linhas * sizeof(int*));
    for (int i = 0; i < linhas; ++i)
        matriz[i] = malloc(colunas * sizeof(int));
    return matriz;
}

void libera_matriz_double(double** matriz, int linhas) {
    for (int i = 0; i < linhas; ++i)
        free(matriz[i]);
    free(matriz);
}

void libera_matriz_int(int** matriz, int linhas) {
    for (int i = 0; i < linhas; ++i)
        free(matriz[i]);
    free(matriz);
}

void imprime_matriz_double(double** matriz, int linhas, int colunas) {
    for (int i = 0; i < linhas; ++i) {
        for (int j = 0; j < colunas; ++j)
            printf("%8.2f ", matriz[i][j]);
        printf("\n");
    }
}

void imprime_matriz_int(int** matriz, int linhas, int colunas) {
    for (int i = 0; i < linhas; ++i) {
        for (int j = 0; j < colunas; ++j)
            printf("%4d ", matriz[i][j]);
        printf("\n");
    }
}

//filtros 3 por 3

void normaliza_filtro(double filtro[3][3]) {
    double soma = 0.0;
    for (int i = 0; i < 3; ++i)
        for (int j = 0; j < 3; ++j)
            soma += filtro[i][j];

    for (int i = 0; i < 3; ++i)
        for (int j = 0; j < 3; ++j)
            filtro[i][j] /= soma;
}

void aplica_filtro(double** entrada, double** saida, int linhas, int colunas, double filtro[3][3]) {
    for (int i = 0; i < linhas - 2; ++i) {
        for (int j = 0; j < colunas - 2; ++j) {
            double soma = 0.0;
            for (int fi = 0; fi < 3; ++fi)
                for (int fj = 0; fj < 3; ++fj)
                    soma += entrada[i + fi][j + fj] * filtro[fi][fj];
            saida[i][j] = soma;
        }
    }
}

void aplica_tolerancia(double** entrada, int** saida, int linhas, int colunas) {
    for (int i = 0; i < linhas; ++i) {
        for (int j = 0; j < colunas; ++j) {
            if (fabs(entrada[i][j]) > TOLERANCIA)
                saida[i][j] = 255;      
            else
                saida[i][j] = 0; 
        }
    }
}

int main() {
    int linhas = 6, colunas = 6;

    double** matriz = aloca_matriz_double(linhas, colunas);
    double dados[6][6] = {
        {3, 0, 1, 2, 7, 4},
        {1, 5, 8, 9, 3, 1},
        {2, 7, 2, 5, 1, 3},
        {0, 1, 3, 1, 7, 8},
        {4, 2, 1, 6, 2, 8},
        {2, 4, 5, 2, 3, 9}
    };
    for (int i = 0; i < linhas; ++i)
        for (int j = 0; j < colunas; ++j)
            matriz[i][j] = dados[i][j];

    //alocacao dos filtros de gauss e laplace seguindo as formulas.. brr.. scary
    double filtro_gauss[3][3] = {
        {1, 2, 1},
        {2, 4, 2},
        {1, 2, 1}
    };

    double filtro_laplace[3][3] = {
        {0,  1, 0},
        {1, -4, 1},
        {0,  1, 0}
    };

    normaliza_filtro(filtro_gauss);

    int linhas_suavizada = linhas - 2;      // 4
    int colunas_suavizada = colunas - 2;    // 4

    int linhas_laplace = linhas_suavizada - 2;    // 2
    int colunas_laplace = colunas_suavizada - 2;  // 2

    double** suavizada = aloca_matriz_double(linhas_suavizada, colunas_suavizada);
    double** laplace = aloca_matriz_double(linhas_laplace, colunas_laplace);
    int** resultado_final = aloca_matriz_int(linhas_laplace, colunas_laplace);

    //inicializa as matrizes (evita lixo, sempre esqueco de fazer isso, boas praticas?)
    for (int i = 0; i < linhas_suavizada; ++i)
        for (int j = 0; j < colunas_suavizada; ++j)
            suavizada[i][j] = 0.0;

    for (int i = 0; i < linhas_laplace; ++i)
        for (int j = 0; j < colunas_laplace; ++j) {
            laplace[i][j] = 0.0;
            resultado_final[i][j] = 255;
        }

    //parte principal, aplicacao dos filtros e da tolerancia. coloquei os headers pq sempre esqueco como eles estao
    //a funcao aplica_filtro e do tipo:
    //aplica_filtro(entrada, saida, n linhas, n colunas, filtro)
    aplica_filtro(matriz, suavizada, linhas, colunas, filtro_gauss);
    aplica_filtro(suavizada, laplace, linhas_suavizada, colunas_suavizada, filtro_laplace);
    //a funcao aplica_tolerancia e do tipo:
    //aplica_tolerancia(entrada, saida, n linhas, n colunas)
    aplica_tolerancia(laplace, resultado_final, linhas_laplace, colunas_laplace);

    printf("Matriz apos Laplaciano:\n");
    imprime_matriz_double(laplace, linhas_laplace, colunas_laplace);

    printf("\nMatriz final com tolerancia (bordas = preto):\n");
    imprime_matriz_int(resultado_final, linhas_laplace, colunas_laplace);

    libera_matriz_double(matriz, linhas);
    libera_matriz_double(suavizada, linhas_suavizada);
    libera_matriz_double(laplace, linhas_laplace);
    libera_matriz_int(resultado_final, linhas_laplace);

    return 0;
}
