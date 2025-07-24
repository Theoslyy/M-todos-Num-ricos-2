#include <stdio.h>
#include <math.h>

typedef struct {
    int i;
    double t;
    double v;
    double y;
} Estado;

void F(double k, double m, double g, Estado s, double* dv, double* dy) {
    *dv = -g - (k / m) * s.v;
    *dy = s.v;
}

Estado estado_exato(double k, double m, double g, double t, double y0) {
    Estado s;
    s.i = 0;
    s.t = t;

    double fator = m / k;
    s.v = -g * fator + (3 + g * fator) * exp(-(k / m) * t);
    s.y = y0 - g * fator * t - (3 + g * fator) * fator * (exp(-(k / m) * t) - 1);
    return s;
}

Estado runge_kutta4(Estado s, double dt, double g, double k, double m, int i) {
    Estado sn;
    sn.i = i;
    sn.t = s.t + dt;

    double k1v = -g - (k / m) * s.v;
    double k1y = s.v;

    double k2v = -g - (k / m) * (s.v + dt * k1v / 2.0);
    double k2y = s.v + dt * k1v / 2.0;

    double k3v = -g - (k / m) * (s.v + dt * k2v / 2.0);
    double k3y = s.v + dt * k2v / 2.0;

    double k4v = -g - (k / m) * (s.v + dt * k3v);
    double k4y = s.v + dt * k3v;

    sn.v = s.v + (dt / 6.0) * (k1v + 2 * k2v + 2 * k3v + k4v);
    sn.y = s.y + (dt / 6.0) * (k1y + 2 * k2y + 2 * k3y + k4y);

    return sn;
}

int main() {
    double g = 9.8, k = 1.0, m = 1.0;
    double dt = 0.1;
    int passos = 20;
    double y0 = 150.0;

    Estado s[passos + 4];
    s[0] = (Estado){0, 0.0, 3.0, y0};

    //runge kutta pro comeco
    for (int i = 1; i <= 3; i++) {
        s[i] = runge_kutta4(s[i - 1], dt, g, k, m, i);
    }

    printf(" i   t       y         y(exato)    erro(y)     v        v(exato)    erro(v)\n");
    for (int i = 0; i <= 3; i++) {
        Estado exato = estado_exato(k, m, g, s[i].t, y0);
        printf("%2d  %.2f  %.6f  %.6f  %.6f  %.6f  %.6f  %.6f\n",
               s[i].i, s[i].t, s[i].y, exato.y, fabs(s[i].y - exato.y),
               s[i].v, exato.v, fabs(s[i].v - exato.v));
    }

    // preditor corretor em si
    for (int i = 4; i <= passos; i++) {
        Estado sp;
        double fvm3, fvm2, fvm1, fv0;
        double fym3, fym2, fym1, fy0;

        F(k, m, g, s[i - 4], &fvm3, &fym3);
        F(k, m, g, s[i - 3], &fvm2, &fym2);
        F(k, m, g, s[i - 2], &fvm1, &fym1);
        F(k, m, g, s[i - 1], &fv0, &fy0);

        //pred.
        sp.i = i;
        sp.t = s[i - 1].t + dt;
        sp.v = s[i - 1].v + dt / 24.0 * (55 * fv0 - 59 * fvm1 + 37 * fvm2 - 9 * fvm3);
        sp.y = s[i - 1].y + dt / 24.0 * (55 * fy0 - 59 * fym1 + 37 * fym2 - 9 * fym3);

        //corrige
        double fvp, fyp;
        F(k, m, g, sp, &fvp, &fyp);
        s[i].i = i;
        s[i].t = sp.t;
        s[i].v = s[i - 1].v + dt / 24.0 * (9 * fvp + 19 * fv0 - 5 * fvm1 + fvm2);
        s[i].y = s[i - 1].y + dt / 24.0 * (9 * fyp + 19 * fy0 - 5 * fym1 + fym2);

        Estado exato = estado_exato(k, m, g, s[i].t, y0);
        printf("%2d  %.2f  %.6f  %.6f  %.6f  %.6f  %.6f  %.6f\n",
               s[i].i, s[i].t, s[i].y, exato.y, fabs(s[i].y - exato.y),
               s[i].v, exato.v, fabs(s[i].v - exato.v));
    }

    return 0;
}
