#ifndef OPERACOES_H
#define OPERACOES_H

void multiplicar_matriz_vetor(double **matriz, double *vetor, double *resultado, int n);
double produto_escalar(double *v1, double *v2, int n);
void normalizar_vetor(double *vetor, int n);
void calcular_inversa(double **A, double **A_inv, int n);

#endif
