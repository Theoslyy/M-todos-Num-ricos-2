#include <stdio.h>
#include <math.h>

typedef struct {
    int i; //indice do passo 
    double t; //tempo
    double y; //espaco
} Estado;
//problema:
/*
dy/dt = 2/3y; y(to) = yo
solucao exata conhecida
y(t) = yo * e ^ 2/3(t-t0)
*/

//  dy/dt = (2/3) * y
double F(double y) {
    return (2.0 / 3.0) * y;
}

//sabemos o estado exato para comprar o erro
double estado_exato(double y0, double t0, double t) {
    return y0 * exp((2.0 / 3.0) * (t - t0));
}

Estado euler_explicito(Estado atual, double delta_t, int i) {
    Estado proximo;
    proximo.i = i;
    proximo.t = atual.t + delta_t;
    proximo.y = atual.y + delta_t * F(atual.y);
    return proximo;
}

int main() {
    double t0 = 0.0;
    double y0 = 1.0;
    double delta_t = 0.1;
    int passos = 10;

    Estado estado_atual = {0, t0, y0};

    printf(" i   t         y (Euler)     y (Exato)     Erro Absoluto\n");
    printf("---------------------------------------------------------\n");

    for (int i = 0; i <= passos; i++) {
        double y_exato = estado_exato(y0, t0, estado_atual.t);
        double erro = fabs(estado_atual.y - y_exato);
        printf("%2d  %.4f   %.8f   %.8f   %.8f\n", estado_atual.i, estado_atual.t, estado_atual.y, y_exato, erro);
        estado_atual = euler_explicito(estado_atual, delta_t, i + 1);
    }

    return 0;
}
