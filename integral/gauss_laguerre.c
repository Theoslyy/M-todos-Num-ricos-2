#include <stdio.h>
#include <math.h>

double funcao_exemplo_laguerre(double x) {
    return x * x;
}

double gauss_laguerre(int n) {
    double pesos[4], pontos[4], valor_integral = 0.0;

    if (n == 2) {
        pesos[0] = 0.8535533906; pesos[1] = 0.1464466094;
        pontos[0] = 0.5857864376; pontos[1] = 3.4142135624;
    } else if (n == 3) {
        pesos[0] = 0.7110930099; pesos[1] = 0.2785177336; pesos[2] = 0.0103892565;
        pontos[0] = 0.4157745568; pontos[1] = 2.2942803603; pontos[2] = 6.2899450829;
    } else if (n == 4) {
        pesos[0] = 0.6031541043; pesos[1] = 0.3574186924;
        pesos[2] = 0.0388879085; pesos[3] = 0.0005392947;
        pontos[0] = 0.3225476896; pontos[1] = 1.7457611012;
        pontos[2] = 4.5366202969; pontos[3] = 9.3950709123;
    }

    for (int i = 0; i < n; i++) {
        valor_integral += pesos[i] * funcao_exemplo_laguerre(pontos[i]);
    }

    return valor_integral;
}
