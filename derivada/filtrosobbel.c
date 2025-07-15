#include <stdio.h>
#include <stdlib.h>
#include <math.h>


// funcoes de matriz. poderia ter posto elas em um header e usar em comum nos dos arquivos. 
double** aloca_matriz_double(int linhas, int colunas) {
    double** matriz = malloc(linhas * sizeof(double*));
    for (int i = 0; i < linhas; i++)
        matriz[i] = malloc(colunas * sizeof(double));
    return matriz;
}

void libera_matriz_double(double** matriz, int linhas) {
    for (int i = 0; i < linhas; i++)
        free(matriz[i]);
    free(matriz);
}

int** aloca_matriz_int(int linhas, int colunas) {
    int** matriz = malloc(linhas * sizeof(int*));
    for (int i = 0; i < linhas; i++)
        matriz[i] = malloc(colunas * sizeof(int));
    return matriz;
}

void libera_matriz_int(int** matriz, int linhas) {
    for (int i = 0; i < linhas; i++)
        free(matriz[i]);
    free(matriz);
}

//mesma parte do filtro gauss
void normaliza_filtro(double filtro[3][3]) {
    double soma = 0.0;
    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
            soma += filtro[i][j];
    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
            filtro[i][j] /= soma;
}

void aplica_filtro(double** entrada, double** saida, int linhas, int colunas, double filtro[3][3]) {
    for (int i = 0; i < linhas - 2; i++) {
        for (int j = 0; j < colunas - 2; j++) {
            double soma = 0.0;
            for (int fi = 0; fi < 3; fi++)
                for (int fj = 0; fj < 3; fj++)
                    soma += entrada[i + fi][j + fj] * filtro[fi][fj];
            saida[i][j] = soma;
        }
    }
}

void diagonal_quadrada(double** matriz, int linhas, int colunas) {
    for (int i = 0; i < linhas; i++)
        for (int j = 0; j < colunas; j++)
            matriz[i][j] = matriz[i][j] * matriz[i][j];
}

void soma_matrizes(double** A, double** B, int linhas, int colunas) {
    for (int i = 0; i < linhas; i++)
        for (int j = 0; j < colunas; j++)
            A[i][j] += B[i][j];
}

void diagonal_raiz(double** matriz, int linhas, int colunas) {
    for (int i = 0; i < linhas; i++)
        for (int j = 0; j < colunas; j++)
            matriz[i][j] = sqrt(matriz[i][j]);
}

//passo final
void aplica_threshold(double** entrada, int** saida, int linhas, int colunas, double threshold) {
    for (int i = 0; i < linhas; i++)
        for (int j = 0; j < colunas; j++)
            saida[i][j] = (entrada[i][j] > threshold) ? 1 : 0; //operador ternario so cool...
}

int main() {
    int linhas = 6, colunas = 6;
    int linhas_saida = linhas - 2, colunas_saida = colunas - 2;

    double dados[6][6] = {
        {3, 0, 1, 2, 7, 4},
        {1, 5, 8, 9, 3, 1},
        {2, 7, 2, 5, 1, 3},
        {0, 1, 3, 1, 7, 8},
        {4, 2, 1, 6, 2, 8},
        {2, 4, 5, 2, 3, 9}
    };

    double** matriz = aloca_matriz_double(linhas, colunas);
    double** gauss_result = aloca_matriz_double(linhas_saida, colunas_saida);
    double** sobel_x = aloca_matriz_double(linhas_saida, colunas_saida);
    double** sobel_y = aloca_matriz_double(linhas_saida, colunas_saida);
    int** resultado_final = aloca_matriz_int(linhas_saida, colunas_saida);

    for (int i = 0; i < linhas; i++)
        for (int j = 0; j < colunas; j++)
            matriz[i][j] = dados[i][j];

    //alocacao dos filtros
    double filtro_gauss[3][3] = {
        {1, 2, 1},
        {2, 4, 2},
        {1, 2, 1}
    };
    double filtro_sobel_x[3][3] = {
        {-1, 0, 1},
        {-2, 0, 2},
        {-1, 0, 1}
    };
     double filtro_sobel_y[3][3] = {
        {-1, -2, -1},
        { 0,  0,  0},
        { 1,  2,  1}
    };
    normaliza_filtro(filtro_gauss);

    //passo a passo definido na tarefa
    // Passo 1: suavizar com gauss
    aplica_filtro(matriz, gauss_result, linhas, colunas, filtro_gauss);

    // Passo 2.1: filtro sobel x na matriz suavizada
    aplica_filtro(gauss_result, sobel_x, linhas_saida, colunas_saida, filtro_sobel_x);

    // Passo 2.2: filtro sobel y na matriz suavizada
    aplica_filtro(gauss_result, sobel_y, linhas_saida, colunas_saida, filtro_sobel_y);

    // Passo 2.3: eleva os valores ao quadrado
    diagonal_quadrada(sobel_x, linhas_saida, colunas_saida);
    diagonal_quadrada(sobel_y, linhas_saida, colunas_saida);

    // Passo 2.4: soma matrizes e calcula raiz quadrada
    soma_matrizes(sobel_x, sobel_y, linhas_saida, colunas_saida);
    diagonal_raiz(sobel_x, linhas_saida, colunas_saida);

    // Passo 3: define threshold
    double threshold;
    printf("threshold: ");
    scanf("%lf", &threshold);

    // Passo 4: aplica threshold para gerar matriz final
    aplica_threshold(sobel_x, resultado_final, linhas_saida, colunas_saida, threshold);

    printf("Matriz final com deteccao de bordas (0=sem borda, 1=borda):\n");
    for (int i = 0; i < linhas_saida; i++) {
        for (int j = 0; j < colunas_saida; j++)
            printf("%d ", resultado_final[i][j]);
        printf("\n");
    }

    libera_matriz_double(matriz, linhas);
    libera_matriz_double(gauss_result, linhas_saida);
    libera_matriz_double(sobel_x, linhas_saida);
    libera_matriz_double(sobel_y, linhas_saida);
    libera_matriz_int(resultado_final, linhas_saida);

    return 0;
}
