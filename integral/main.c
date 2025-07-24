#include "gauss_chebyshev.c"
#include "gauss_hermite.c"
#include "gauss_laguerre.c"
#include "gauss_legendre.c"
#include <stdio.h>

double gauss_legendre(double a, double b, int n);
double gauss_hermite(int n);
double gauss_laguerre(int n);
double gauss_chebyshev(int n);

int main() {
    printf("Gauss-Legendre: %.8f\n", gauss_legendre(1, 3, 3));
    printf("Gauss-Hermite: %.8f\n", gauss_hermite(3));
    printf("Gauss-Laguerre: %.8f\n", gauss_laguerre(3));
    printf("Gauss-Chebyshev: %.8f\n", gauss_chebyshev(4));
    return 0;
}
