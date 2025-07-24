#include <stdio.h>
#define _USE_MATH_DEFINES
#include <math.h>

double funcao_exemplo_chebyshev(double x) {
    return x * x;
}

double gauss_chebyshev(int n) {
    double valor_integral = 0.0;
    double peso = M_PI / n;

    for (int i = 1; i <= n; i++) {
        double ponto = cos((2.0 * i - 1) * M_PI / (2.0 * n));
        valor_integral += peso * funcao_exemplo_chebyshev(ponto);
    }

    return valor_integral;
}
