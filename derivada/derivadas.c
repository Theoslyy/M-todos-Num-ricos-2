#include <stdio.h>
#include <math.h>
#include <string.h>

double funcao_exemplo(double x) {
    return x * x;
}

// Derivada Primeira
double derivada_primeira_forward(const char* erro, double x, double Dx) {
    if (strcmp(erro, "linear") == 0)
        return (funcao_exemplo(x + Dx) - funcao_exemplo(x)) / Dx;

    else if (strcmp(erro, "quadratico") == 0)
        return (-funcao_exemplo(x + 2*Dx) + 4*funcao_exemplo(x + Dx) - 3*funcao_exemplo(x)) / (2*Dx);

    else if (strcmp(erro, "cubico") == 0)
        return (-11*funcao_exemplo(x) + 18*funcao_exemplo(x + Dx) - 9*funcao_exemplo(x + 2*Dx) + 2*funcao_exemplo(x + 3*Dx)) / (6*Dx);

    else if (strcmp(erro, "quarta_ordem") == 0)
        return (-25*funcao_exemplo(x) + 48*funcao_exemplo(x + Dx) - 36*funcao_exemplo(x + 2*Dx) + 16*funcao_exemplo(x + 3*Dx) - 3*funcao_exemplo(x + 4*Dx)) / (12*Dx);

    return 0;
}

double derivada_primeira_backward(const char* erro, double x, double Dx) {
    if (strcmp(erro, "linear") == 0)
        return (funcao_exemplo(x) - funcao_exemplo(x - Dx)) / Dx;

    else if (strcmp(erro, "quadratico") == 0)
        return (3*funcao_exemplo(x) - 4*funcao_exemplo(x - Dx) + funcao_exemplo(x - 2*Dx)) / (2*Dx);

    else if (strcmp(erro, "cubico") == 0)
        return (11*funcao_exemplo(x) - 18*funcao_exemplo(x - Dx) + 9*funcao_exemplo(x - 2*Dx) - 2*funcao_exemplo(x - 3*Dx)) / (6*Dx);

    else if (strcmp(erro, "quarta_ordem") == 0)
        return (25*funcao_exemplo(x) - 48*funcao_exemplo(x - Dx) + 36*funcao_exemplo(x - 2*Dx) - 16*funcao_exemplo(x - 3*Dx) + 3*funcao_exemplo(x - 4*Dx)) / (12*Dx);

    return 0;
}

double derivada_primeira_central(const char* erro, double x, double Dx) {
    if (strcmp(erro, "quadratico") == 0)
        return (funcao_exemplo(x + Dx) - funcao_exemplo(x - Dx)) / (2*Dx);

    else if (strcmp(erro, "quarta_ordem") == 0)
        return (-funcao_exemplo(x + 2*Dx) + 8*funcao_exemplo(x + Dx) - 8*funcao_exemplo(x - Dx) + funcao_exemplo(x - 2*Dx)) / (12*Dx);

    return 0;
}

// Derivada Segunda
double derivada_segunda_forward(const char* erro, double x, double Dx) {
    if (strcmp(erro, "linear") == 0)
        return (funcao_exemplo(x) - 2*funcao_exemplo(x + Dx) + funcao_exemplo(x + 2*Dx)) / (Dx * Dx);

    else if (strcmp(erro, "quadratico") == 0)
        return (2*funcao_exemplo(x) - 5*funcao_exemplo(x + Dx) + 4*funcao_exemplo(x + 2*Dx) - funcao_exemplo(x + 3*Dx)) / (Dx * Dx);

    else if (strcmp(erro, "cubico") == 0)
        return (35*funcao_exemplo(x) - 104*funcao_exemplo(x + Dx) + 114*funcao_exemplo(x + 2*Dx) - 56*funcao_exemplo(x + 3*Dx) + 11*funcao_exemplo(x + 4*Dx)) / (12 * Dx * Dx);

    return 0;
}

double derivada_segunda_backward(const char* erro, double x, double Dx) {
    if (strcmp(erro, "linear") == 0)
        return (funcao_exemplo(x) - 2*funcao_exemplo(x - Dx) + funcao_exemplo(x - 2*Dx)) / (Dx * Dx);

    else if (strcmp(erro, "quadratico") == 0)
        return (2*funcao_exemplo(x) - 5*funcao_exemplo(x - Dx) + 4*funcao_exemplo(x - 2*Dx) - funcao_exemplo(x - 3*Dx)) / (Dx * Dx);

    else if (strcmp(erro, "cubico") == 0)
        return (35*funcao_exemplo(x) - 104*funcao_exemplo(x - Dx) + 114*funcao_exemplo(x - 2*Dx) - 56*funcao_exemplo(x - 3*Dx) + 11*funcao_exemplo(x - 4*Dx)) / (12 * Dx * Dx);

    return 0;
}

double derivada_segunda_central(const char* erro, double x, double Dx) {
    if (strcmp(erro, "quadratico") == 0)
        return (funcao_exemplo(x + Dx) - 2*funcao_exemplo(x) + funcao_exemplo(x - Dx)) / (Dx * Dx);

    else if (strcmp(erro, "quarta_ordem") == 0)
        return (-funcao_exemplo(x + 2*Dx) + 16*funcao_exemplo(x + Dx) - 30*funcao_exemplo(x) + 16*funcao_exemplo(x - Dx) - funcao_exemplo(x - 2*Dx)) / (12 * Dx * Dx);

    return 0;
}

// Derivada Terceira
double derivada_terceira_forward(const char* erro, double x, double Dx) {
    if (strcmp(erro, "linear") == 0)
        return (funcao_exemplo(x + 3*Dx) - 3*funcao_exemplo(x + 2*Dx) + 3*funcao_exemplo(x + Dx) - funcao_exemplo(x)) / (Dx * Dx * Dx);

    else if (strcmp(erro, "quadratico") == 0)
        return (-5*funcao_exemplo(x) + 18*funcao_exemplo(x + Dx) - 24*funcao_exemplo(x + 2*Dx) + 14*funcao_exemplo(x + 3*Dx) - 3*funcao_exemplo(x + 4*Dx)) / (2 * Dx * Dx * Dx);

    return 0;
}

double derivada_terceira_backward(const char* erro, double x, double Dx) {
    if (strcmp(erro, "linear") == 0)
        return (funcao_exemplo(x) - 3*funcao_exemplo(x - Dx) + 3*funcao_exemplo(x - 2*Dx) - funcao_exemplo(x - 3*Dx)) / (Dx * Dx * Dx);

    else if (strcmp(erro, "quadratico") == 0)
        return (5*funcao_exemplo(x) - 18*funcao_exemplo(x - Dx) + 24*funcao_exemplo(x - 2*Dx) - 14*funcao_exemplo(x - 3*Dx) + 3*funcao_exemplo(x - 4*Dx)) / (2 * Dx * Dx * Dx);

    return 0;
}

double derivada_terceira_central(const char* erro, double x, double Dx) {
    if (strcmp(erro, "quadratico") == 0)
        return (funcao_exemplo(x + 2*Dx) - 2*funcao_exemplo(x + Dx) + 2*funcao_exemplo(x - Dx) - funcao_exemplo(x - 2*Dx)) / (2 * Dx * Dx * Dx);

    else if (strcmp(erro, "quarta_ordem") == 0)
        return (-funcao_exemplo(x + 3*Dx) + 8*funcao_exemplo(x + 2*Dx) - 13*funcao_exemplo(x + Dx) + 13*funcao_exemplo(x - Dx) - 8*funcao_exemplo(x - 2*Dx) + funcao_exemplo(x - 3*Dx)) / (8 * Dx * Dx * Dx);

    return 0;
}

int main() {
    double x = 8.0;
    double Dx = 0.5;

    printf("Derivada Primeira Forward (linear): %lf\n", derivada_primeira_forward("linear", x, Dx));
    printf("Derivada Segunda Central (quarta_ordem): %lf\n", derivada_segunda_central("quarta_ordem", x, Dx));
    printf("Derivada Terceira Backward (quadratico): %lf\n", derivada_terceira_backward("quadratico", x, Dx));

    return 0;
}
