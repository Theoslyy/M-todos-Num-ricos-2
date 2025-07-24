#include <stdio.h>
#include <stdlib.h>
#include <math.h>


//formulas basicas de newton cottes (sem divisao de intervalos)
//o padrao do header: a , b, f*. Com a, b sendo os valores do intervalo de integracao e f a funcao. 
double nc_fechado_trapezio(double a, double b, double (*f)(double)) {
    return (b - a) * (f(a) + f(b)) / 2.0;
}

double nc_fechado_simpson(double a, double b, double (*f)(double)) {
    double m = (a + b) / 2.0;
    return (b - a) * (f(a) + 4*f(m) + f(b)) / 6.0;
}

double nc_fechado_3_8(double a, double b, double (*f)(double)) {
    double h = (b - a)/3.0;
    return (3.*h/8.0) * (f(a) + 3*f(a+h) + 3*f(a+2*h) + f(b));
}

//ponto medio, 2 ponto, 3 pontos e quatro pontos:
    
double nc_aberto_meio(double a, double b, double (*f)(double)) {
    double m = (a + b) / 2.0;
    return (b - a) * f(m);
}
//grau 1, 2 pontos
double nc_aberto_2(double a, double b, double (*f)(double)) {
    double h = (b - a) / 3.0;
    return (3.0/2.0) * h * (f(a+h) + f(a+2*h));
}
//grau 2, 3 pontos
double nc_aberto_3(double a, double b, double (*f)(double)) {
    double h = (b - a) / 4.0;
    return (4.0/3.0) * h * (2*f(a+h) - f(a+2*h) + 2*f(a+3*h));
}

//grau 3, 4 pontos
double nc_aberto_4(double a, double b, double (*f)(double)) {
    double h = (b - a) / 5.0; 
    return (5.0/24.0) * h * (11*f(a+h) + f(a+2*h) + f(a+3*h) + 11*f(a+4*h));
}



//formulas compostas. Todas sao basicamente iguais, daria para fazer isso de uma forma mais esperta -> fazendo um integral_comoposta generico.
 
double nc_fechado_trapezio_comp(double a, double b, int n, double (*f)(double)) {
    double h = (b - a) / n;
    double sum = (f(a) + f(b)) / 2.0;
    for (int i = 1; i < n; i++) {
        sum += f(a + i*h);
    }
    return h * sum;
}

double nc_fechado_simpson_comp(double a, double b, int n, double (*f)(double)) {
    if (n % 2 != 0) {
        printf("Erro: n deve ser par para Simpson composto.\n");
        return NAN;
    }
    double h = (b - a) / n;
    double sum = f(a) + f(b);
    for (int i = 1; i < n; i++) {
        double x = a + i*h;
        sum += (i % 2 == 0) ? 2*f(x) : 4*f(x);
    }
    return h * sum / 3.0;
}

double nc_fechado_3_8_comp(double a, double b, int n, double (*f)(double)) {
    if (n % 3 != 0) {
        printf("Erro: n deve ser multiplo de 3 para 3/8 composto.\n");
        return NAN;
    }
    double h = (b - a) / n;
    double sum = f(a) + f(b);
    for (int i = 1; i < n; i++) {
        double x = a + i*h;
        sum += (i % 3 == 0) ? 2*f(x) : 3*f(x);
    }
    return 3*h * sum / 8.0;
}

double nc_aberto_meio_comp(double a, double b, int n, double (*f)(double)) {
    double h = (b - a) / n;
    double sum = 0.0;
    for (int i = 0; i < n; i++) {
        double x0 = a + i*h;
        double x1 = x0 + h;
        sum += nc_aberto_meio(x0, x1, f);
    }
    return sum;
}

double nc_aberto_2_comp(double a, double b, int n, double (*f)(double)) {
    double h = (b - a) / n;
    double sum = 0.0;
    for (int i = 0; i < n; i++) {
        double x0 = a + i*h;
        double x1 = x0 + h;
        sum += nc_aberto_2(x0, x1, f);
    }
    return sum;
}

double nc_aberto_3_comp(double a, double b, int n, double (*f)(double)) {
    double h = (b - a) / n;
    double sum = 0.0;
    for (int i = 0; i < n; i++) {
        double x0 = a + i*h;
        double x1 = x0 + h;
        sum += nc_aberto_3(x0, x1, f);
    }
    return sum;
}

double nc_aberto_4_comp(double a, double b, int n, double (*f)(double)) {
    double h = (b - a) / n;
    double sum = 0.0;
    for (int i = 0; i < n; i++) {
        double x0 = a + i*h;
        double x1 = x0 + h;
        sum += nc_aberto_4(x0, x1, f);
    }
    return sum;
}


double f1(double x) { return x*x*x; }

int main() {
    int n = 12;

    printf("Trapezio composto x^3 [0,1], n=%d: %.10f\n", n, nc_fechado_trapezio_comp(0, 1, n, f1));
    printf("Simpson composto x^3 [0,1], n=%d: %.10f\n", n, nc_fechado_simpson_comp(0, 1, n, f1));
    printf("3/8 composto x^3 [0,1], n=%d: %.10f\n", n, nc_fechado_3_8_comp(0, 1, n, f1));
    printf("Aberta (ponto medio) composta x^3 [0,1], n=%d: %.10f\n", n, nc_aberto_meio_comp(0, 1, n, f1));
    printf("Aberta grau 1 composta x^3 [0,1], n=%d: %.10f\n", n, nc_aberto_2_comp(0, 1, n, f1));
    printf("Aberta grau 2 composta x^3 [0,1], n=%d: %.10f\n", n, nc_aberto_3_comp(0, 1, n, f1));
    printf("Aberta grau 3 composta x^3 [0,1], n=%d: %.10f\n", n, nc_aberto_4_comp(0, 1, n, f1));


    return 0;
}
