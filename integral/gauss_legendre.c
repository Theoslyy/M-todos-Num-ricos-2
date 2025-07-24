#include <stdio.h>
#include <math.h>

double funcao_exemplo_legendre(double x) {
    //return x * x * log(x) + exp(x);
    return sin(x); 
}

double converter_intervalo(double alpha, double a, double b) {
    return ((b + a) / 2) + ((b - a) / 2) * alpha;
}

double gauss_legendre(double a, double b, int n) {
    double pesos[4], pontos[4], valor_integral = 0.0, valores_x[4];

    if (n == 2) {
        pesos[0] = 1.0; pesos[1] = 1.0;
        pontos[0] = -0.5773502692; pontos[1] = 0.5773502692;
    } else if (n == 3) {
        pesos[0] = 0.5555555556; pesos[1] = 0.8888888889; pesos[2] = 0.5555555556;
        pontos[0] = -0.7745966692; pontos[1] = 0.0; pontos[2] = 0.7745966692;
    } else if (n == 4) {
        pesos[0] = 0.3478548451; pesos[1] = 0.6521451549;
        pesos[2] = 0.6521451549; pesos[3] = 0.3478548451;
        pontos[0] = -0.8611363116; pontos[1] = -0.3399810436;
        pontos[2] = 0.3399810436; pontos[3] = 0.8611363116;
    }

    for (int i = 0; i < n; i++) {
        valores_x[i] = converter_intervalo(pontos[i], a, b);
        valor_integral += pesos[i] * funcao_exemplo_legendre(valores_x[i]);
    }

    valor_integral *= (b - a) / 2;
    return valor_integral;
}
