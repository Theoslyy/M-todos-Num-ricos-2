#include <stdio.h>
#include <math.h>

//problema 1
double euler_implicito_pvi1(double y_n, double dt) {
    return y_n / (1 - (2.0 / 3.0) * dt);
}

double solucao_exata_pvi1(double y0, double t) {
    return y0 * exp((2.0 / 3.0) * t);
}

//problema 2
typedef struct {
    int i;
    double t;
    double v;
    double y;
} Estado;

Estado euler_implicito_pvi2(Estado s_n, double dt, double k, double m, double g, int i) {
    Estado s_next;
    s_next.i = i;
    s_next.t = s_n.t + dt;

    // formulas resolvidas (notas de aula pags. 14 e 15)
    double coef = 1 + (k / m) * dt;
    s_next.v = (s_n.v - g * dt) / coef;
    s_next.y = s_n.y + dt * s_next.v;

    return s_next;
}

Estado solucao_exata_pvi2(double t, double k, double m, double g, double y0) {
    Estado s;
    double fator = m / k;
    s.v = -g * fator + (3 + g * fator) * exp(-(k / m) * t);
    s.y = y0 - g * fator * t - (3 + g * fator) * fator * (exp(-(k / m) * t) - 1);
    s.t = t;
    return s;
}

int main() {
    double dt = 0.1;
    int passos = 10;
    printf("=== PVI-1: dy/dt = (2/3)*y ===\n");
    double y0 = 2.0;
    double y_n = y0;
    for (int i = 0; i <= passos; i++) {
        double t = i * dt;
        double y_exato = solucao_exata_pvi1(y0, t);
        double erro = fabs(y_n - y_exato);
        printf("t=%.2f | y (implicito)=%.6f | y (exato)=%.6f | erro=%.6f\n", t, y_n, y_exato, erro);
        y_n = euler_implicito_pvi1(y_n, dt);
    }
    printf("\n=== PVI-2: Queda com resistencia ===\n");
    double k = 1.0, m = 1.0, g = 9.8;
    Estado s = {0, 0.0, 3.0, 150.0};

    for (int i = 0; i <= passos; i++) {
        Estado s_exato = solucao_exata_pvi2(s.t, k, m, g, 150.0);
        double erro_v = fabs(s.v - s_exato.v);
        double erro_y = fabs(s.y - s_exato.y);
        printf("t=%.2f | v=%.6f (ex=%.6f) | y=%.6f (ex=%.6f) | ev=%.6f | ey=%.6f\n",
               s.t, s.v, s_exato.v, s.y, s_exato.y, erro_v, erro_y);
        s = euler_implicito_pvi2(s, dt, k, m, g, i + 1);
    }

    return 0;
}
