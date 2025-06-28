#ifndef OPERACOES_H
#define OPERACOES_H


double** aloca_matriz(int n);
void libera_matriz(double** mat, int n);
void identidade(double** I, int n);
void copia_matriz(double** A, double** B, int n);
void mult_mat_vec(double** A, double* x, double* y, int n);
void mult_mat_mat(double** A, double** B, double** C, int n);
double norma(double* v, int n);
void transposta(double** M, double** Mt, int n);

#endif