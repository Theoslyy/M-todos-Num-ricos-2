#include <stdio.h>
#include <math.h>

//f(t, y) = (2/3) * y, mesmos dois PV1 e PV2
double f(double t, double y) {
    return (2.0 / 3.0) * y;
}

double solucao_exata_pvi1(double y0, double t) {
    return y0 * exp((2.0 / 3.0) * t);
}

double runge_kutta4_pvi1(double t, double y, double dt) {
    double k1 = f(t, y);
    double k2 = f(t + dt / 2.0, y + dt * k1 / 2.0);
    double k3 = f(t + dt / 2.0, y + dt * k2 / 2.0);
    double k4 = f(t + dt, y + dt * k3);
    return y + (dt / 6.0) * (k1 + 2*k2 + 2*k3 + k4);
}

typedef struct {
    int i;
    double t;
    double v;
    double y;
} Estado;

Estado solucao_exata_pvi2(double t, double k, double m, double g, double y0) {
    Estado s;
    double fator = m / k;
    s.v = -g * fator + (3 + g * fator) * exp(-(k / m) * t);
    s.y = y0 - g * fator * t - (3 + g * fator) * fator * (exp(-(k / m) * t) - 1);
    s.t = t;
    return s;
}

double dvdt(double v, double g, double k, double m) {
    return -g - (k / m) * v;
}

double dydt(double v) {
    return v;
}

Estado runge_kutta4_pvi2(Estado s, double dt, double g, double k, double m, int i) {
    Estado sn;
    sn.i = i;
    sn.t = s.t + dt;

    // v
    double k1v = dvdt(s.v, g, k, m);
    double k1y = dydt(s.v);

    double k2v = dvdt(s.v + dt * k1v / 2.0, g, k, m);
    double k2y = dydt(s.v + dt * k1v / 2.0);

    double k3v = dvdt(s.v + dt * k2v / 2.0, g, k, m);
    double k3y = dydt(s.v + dt * k2v / 2.0);

    double k4v = dvdt(s.v + dt * k3v, g, k, m);
    double k4y = dydt(s.v + dt * k3v);

    sn.v = s.v + (dt / 6.0) * (k1v + 2*k2v + 2*k3v + k4v);
    sn.y = s.y + (dt / 6.0) * (k1y + 2*k2y + 2*k3y + k4y);

    return sn;
}
int main() {
    double dt = 0.1;
    int passos = 10;

    printf("=== PVI-1: dy/dt = (2/3)*y ===\n");
    double y0 = 1.0;
    double y = y0;

    for (int i = 0; i <= passos; i++) {
        double t = i * dt;
        double y_exato = solucao_exata_pvi1(y0, t);
        double erro = fabs(y - y_exato);
        printf("t=%.2f | y (RK4)=%.8f | y (exato)=%.8f | erro=%.8f\n", t, y, y_exato, erro);
        y = runge_kutta4_pvi1(t, y, dt);
    }

    printf("\n=== PVI-2: Queda com resistencia ===\n");
    double g = 9.8, k = 1.0, m = 1.0;
    Estado s = {0, 0.0, 3.0, 150.0};

    for (int i = 0; i <= passos; i++) {
        Estado s_exato = solucao_exata_pvi2(s.t, k, m, g, 150.0);
        double ev = fabs(s.v - s_exato.v);
        double ey = fabs(s.y - s_exato.y);
        printf("t=%.2f | v=%.6f (ex=%.6f) | y=%.6f (ex=%.6f) | ev=%.6f | ey=%.6f\n",
               s.t, s.v, s_exato.v, s.y, s_exato.y, ev, ey);
        s = runge_kutta4_pvi2(s, dt, g, k, m, i + 1);
    }

    return 0;
}
