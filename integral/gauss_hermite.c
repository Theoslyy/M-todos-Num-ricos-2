#include <stdio.h>
#include <math.h>

double funcao_exemplo_hermite(double x) {
    return x * x;
}

double gauss_hermite(int n) {
    double pesos[4], pontos[4], valor_integral = 0.0;

    if (n == 2) {
        pesos[0] = pesos[1] = 0.8862269255;
        pontos[0] = -0.7071067812; pontos[1] = 0.7071067812;
    } else if (n == 3) {
        pesos[0] = 0.2954089756; pesos[1] = 1.1816359006; pesos[2] = 0.2954089752;
        pontos[0] = -1.2247448714; pontos[1] = 0.0; pontos[2] = 1.2247448714;
    } else if (n == 4) {
        pesos[0] = 0.0813128354; pesos[1] = 0.8049140900;
        pesos[2] = 0.8049140900; pesos[3] = 0.0813128354;
        pontos[0] = -1.6506801239; pontos[1] = -0.5246476233;
        pontos[2] = 0.5246476233; pontos[3] = 1.6506801239;
    }

    for (int i = 0; i < n; i++) {
        valor_integral += pesos[i] * funcao_exemplo_hermite(pontos[i]);
    }

    return valor_integral;
}
