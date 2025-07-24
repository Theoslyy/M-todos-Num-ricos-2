#include <stdio.h>
#include <math.h>

double f(double t, double y) {
    return (2.0 / 3.0) * y;
}

double solucao_exata_pvi1(double y0, double t) {
    return y0 * exp((2.0 / 3.0) * t);
}

double rk4_pvi1(double t, double y, double dt) {
    double k1 = f(t, y);
    double k2 = f(t + dt / 2.0, y + dt * k1 / 2.0);
    double k3 = f(t + dt / 2.0, y + dt * k2 / 2.0);
    double k4 = f(t + dt, y + dt * k3);

    return y + (dt / 6.0) * (k1 + 2*k2 + 2*k3 + k4);
}

int main() {
    double dt = 0.1;
    int passos = 20;
    double y0 = 1.0;

    double t[passos + 4];
    double y[passos + 4];

    //comecando com o rungekutta 
    t[0] = 0.0;
    y[0] = y0;
    for (int i = 1; i <= 3; i++) {
        t[i] = t[i - 1] + dt;
        y[i] = rk4_pvi1(t[i - 1], y[i - 1], dt);
    }

    printf(" i   t       y          y_exato     erro\n");
    for (int i = 0; i <= 3; i++) {
        double y_exato = solucao_exata_pvi1(y0, t[i]);
        printf("%2d  %.2f  %.8f  %.8f  %.8f\n", i, t[i], y[i], y_exato, fabs(y[i] - y_exato));
    }

    //metodo preditor corretor principal
    for (int i = 4; i <= passos; i++) {
        t[i] = t[i - 1] + dt;

        // derivadas anteriores
        double f_n   = f(t[i - 1], y[i - 1]);
        double f_n1  = f(t[i - 2], y[i - 2]);
        double f_n2  = f(t[i - 3], y[i - 3]);
        double f_n3  = f(t[i - 4], y[i - 4]);

        // predicao!!
        double y_pred = y[i - 1] + dt / 24.0 * (55 * f_n - 59 * f_n1 + 37 * f_n2 - 9 * f_n3);

        // correcao...
        double f_pred = f(t[i], y_pred);
        y[i] = y[i - 1] + dt / 24.0 * (9 * f_pred + 19 * f_n - 5 * f_n1 + f_n2);

        double y_exato = solucao_exata_pvi1(y0, t[i]);
        printf("%2d  %.2f  %.8f  %.8f  %.8f\n", i, t[i], y[i], y_exato, fabs(y[i] - y_exato));
    }

    return 0;
}
