#include <stdio.h>
#include <stdlib.h>
#include "operacoes.c"
#define MAX_ITER 10000

//metodos:
//seguindo o pseudocodigo fornecido pelo professor
//funcao principal, ao inves de retornar diretamente o autovelor e o autovetor, eu passo pra funcao
//e so atribuo no final. 
void metodo_potencia(double **A, double *v0, int n, double epsilon, double *autovalor, double *autovetor) {
    double *vk_novo = (double *)malloc(n * sizeof(double));
    double *vk_velho = (double *)malloc(n * sizeof(double));
    double lambda_novo = 0.0, lambda_velho = 0.0; //passo 1, autovalor comeca como 0
    double erro = 10.0;
    int iter = 0; //passos da iteracao para que o programa nao rode pra sempre!

    // passo 2, inicializa vk_novo com v0
    for (int i = 0; i < n; i++) {
        vk_novo[i] = v0[i];
    }

    while (erro > epsilon && iter < MAX_ITER) {
        lambda_velho = lambda_novo; //comeca como 0!

        for (int i = 0; i < n; i++)
            vk_velho[i] = vk_novo[i]; //passo 3, velho recebe o que era novo e nao e mais

        normalizar_vetor(vk_velho, n); //passo 4, normaliza o velho

        multiplicar_matriz_vetor(A, vk_velho, vk_novo, n); //passo 5, faz o passo da multiplicacao de A por vk_velho
        //e coloca o resultado em vk_novo. 

        lambda_novo = produto_escalar(vk_velho, vk_novo, n); //passo 6, gera o novo possivel autovalor pelo dot prouct

        erro = fabs((lambda_novo - lambda_velho) / lambda_novo); //passo 7, testa convergencia 
        iter++;
    }

    *autovalor = lambda_novo; //atualiza o autovalor para o resultado final
    for (int i = 0; i < n; i++)
        autovetor[i] = vk_velho[i]; //atualiza o autovetor para o resultado final. 

    free(vk_novo);
    free(vk_velho);
}

//novamente seguindo o pseudocodigo fornecido pelo professor
//para o metodo da potencia inversa, basta aplicarmos o metodo da potencia regular sobre a inversa da matriz A
void metodo_potencia_inversa(double **A, double *v0, int n, double epsilon, double *autovalor, double *autovetor) {
    //alocacao dinamica da matriz inversa
    double **A_inv = malloc(n * sizeof(double *));
    for (int i = 0; i < n; i++) {
        A_inv[i] = malloc(n * sizeof(double));
    }

    //passo 1, calculando a inversa
    _inversa(A, A_inv, n);

    //passo 2, aplicando a potencia regular sobre a inversa (poderiamos só chamar a funcao potregular, aqui)
    double *vk_velho = malloc(n * sizeof(double));
    double *vk_novo = malloc(n * sizeof(double));
    double lambda_novo = 0.0, lambda_velho = 0.0, erro = 10.0;
    int iter = 0;

    for (int i = 0; i < n; i++)
        vk_velho[i] = v0[i];

    while (erro > epsilon && iter < MAX_ITER) {
        lambda_velho = lambda_novo;

        normalizar_vetor(vk_velho, n); // x1_velho
        multiplicar_matriz_vetor(A_inv, vk_velho, vk_novo, n); // A⁻¹ * x1_velho

        lambda_novo = produto_escalar(vk_velho, vk_novo, n);
        erro = fabs((lambda_novo - lambda_velho) / lambda_novo);

        for (int i = 0; i < n; i++)
            vk_velho[i] = vk_novo[i];

        iter++;
    }

    // passo 3, calcula o 1/resultado do dominante da inversa 
    *autovalor = 1.0 / lambda_novo;

    // passo 4, pega o autovetor da inversa e normaliza-o 
    normalizar_vetor(vk_velho, n);
    for (int i = 0; i < n; i++)
        autovetor[i] = vk_velho[i];

    // Liberação
    for (int i = 0; i < n; i++) free(A_inv[i]);
    free(A_inv);
    free(vk_velho);
    free(vk_novo);
}

//tambem seguindo o pseudocodigo fornecido pelo professor
void metodo_potencia_deslocamento(double **A, double *v0, int n, double epsilon, double u, double *autovalor, double *autovetor) {
    // passo 1: matriz Â = A - u * I
    double **A_deslocada = malloc(n * sizeof(double *));
    for (int i = 0; i < n; i++) {
        A_deslocada[i] = malloc(n * sizeof(double)); //atribuimos memoria a matriz enquanto vamos alocando A em Â 
        for (int j = 0; j < n; j++) {
            A_deslocada[i][j] = A[i][j];
            if (i == j)
                A_deslocada[i][j] -= u; //subtraimos u da diagonal principal 
        }
    }
    // passo 2, chama a potencia inversa
    double lambda_deslocado;
    double *x_deslocado = malloc(n * sizeof(double));
    metodo_potencia_inversa(A_deslocada, v0, n, epsilon, &lambda_deslocado, x_deslocado);

    // passo 3, corrige o autovalor com o deslocamento
    *autovalor = lambda_deslocado + u;

    // Normaliza e copia o autovetor. O vetor ja e normalizado na potencia inversa, mas é sempre bom.
    // renormalizar? nao muda nada... garantias!
    normalizar_vetor(x_deslocado, n);
    for (int i = 0; i < n; i++) {
        autovetor[i] = x_deslocado[i];
    }
    // Libera memória
    for (int i = 0; i < n; i++) free(A_deslocada[i]);
    free(A_deslocada);
    free(x_deslocado);
}

int main() {
    int n = 3;
    double **A = (double **)malloc(n * sizeof(double *));
    for (int i = 0; i < n; i++)
        A[i] = (double *)malloc(n * sizeof(double));

    
    A[0][0] = 2; A[0][1] = -1; A[0][2] = 0;
    A[1][0] = -1; A[1][1] = 2; A[1][2] = -1;
    A[2][0] = 0; A[2][1] = -1; A[2][2] = 2;

    double v0[] = {1, 1, 1};
    double epsilon = 1e-6;
    double autovalor;
    double *autovetor = (double *)malloc(n * sizeof(double));

    //basta chamar a funcao especifica aqui! 
    
    metodo_potencia_deslocamento(A, v0, n, epsilon, 2.1, &autovalor, autovetor);

    printf("Autovalor: %.6f\n", autovalor);
    printf("Autovetor correspondente:\n");
    for (int i = 0; i < n; i++) {
        printf("%.6f\n", autovetor[i]);
    }

    for (int i = 0; i < n; i++)
        free(A[i]);
    free(A);
    free(autovetor);

    return 0;
}
