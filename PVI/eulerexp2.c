#include <stdio.h>
#include <math.h>

typedef struct {
    int i; //indice do passo
    double t; //tempo
    double v; //velocidade
    double y; //espaco 
} Estado;
//problema de segunda ordem:
/*
dv/dt = - g - (k/m)v
dy/dt = v 
*/
void F(double k, double m, double g, Estado s, double* dv, double* dy) {
    *dv = -g - (k / m) * s.v;
    *dy = s.v;
}

//estado exato tal qual o feito em eulerexp1 
Estado estado_exato(double k, double m, double g, double t, double y0) {
    Estado s;
    s.t = t;
    s.i = 0;

    double fator = m / k;
    s.v = -g * fator + (3 + g * fator) * exp(- (k / m) * t);
    s.y = y0 - g * fator * t - (3 + g * fator) * fator * (exp(- (k / m) * t) - 1);
    return s;
}

Estado euler_explicito(double k, double m, double g, Estado s_atual, double delta_t, int i) {
    Estado s_proximo;
    s_proximo.i = i;
    s_proximo.t = s_atual.t + delta_t;

    double dv, dy;
    F(k, m, g, s_atual, &dv, &dy);

    s_proximo.v = s_atual.v + delta_t * dv;
    s_proximo.y = s_atual.y + delta_t * dy;

    return s_proximo;
}

int main() {
    double k = 1.0;
    double m = 1.0;
    double g = 9.8;
    double t0 = 0.0;
    double v0 = 3.0;
    double y0 = 1.0;
    double delta_t = 0.1;
    int passos = 10;

    Estado s_atual = {0, t0, v0, y0};

    printf(" i   t         y (Euler)     y (Exato)     Erro Y     v (Euler)     v (Exato)     Erro V\n");
    printf("-------------------------------------------------------------------------------------------\n");

    for (int i = 0; i <= passos; i++) {
        Estado s_exato = estado_exato(k, m, g, s_atual.t, y0);
        double erro_y = fabs(s_atual.y - s_exato.y);
        double erro_v = fabs(s_atual.v - s_exato.v);

        printf("%2d  %.4f   %.8f   %.8f   %.6f   %.8f   %.8f   %.6f\n",
               s_atual.i, s_atual.t,
               s_atual.y, s_exato.y, erro_y,
               s_atual.v, s_exato.v, erro_v);

        s_atual = euler_explicito(k, m, g, s_atual, delta_t, i + 1);
    }

    return 0;
}
