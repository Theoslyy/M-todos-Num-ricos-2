#include <stdio.h>
#include <math.h>

//mapear pontos de [-1,1] para [xi, xf]
float mapear_no_intervalo(float a, float xi, float xf) {
    return 0.5 * (xi + xf) + 0.5 * (xf - xi) * a;
}
float f(float x) {
    float qt = 9.0f + 4.0f * powf(cosf(0.4f * x), 2.0f);
    float ct = 5.0f * expf(-0.5f * x) + 2.0f * expf(0.15f * x);
    return qt * ct;
}
int main() {
    int xi = 2;   
    int xf = 8;   
    const float pontos[] = {
        -sqrtf((15.0f + 2.0f*sqrtf(30.0f))/35.0f),
        -sqrtf((15.0f - 2.0f*sqrtf(30.0f))/35.0f),
         sqrtf((15.0f - 2.0f*sqrtf(30.0f))/35.0f),
         sqrtf((15.0f + 2.0f*sqrtf(30.0f))/35.0f)
    };
    const float pesos[] = {
        (18.0f - sqrtf(30.0f))/36.0f,
        (18.0f + sqrtf(30.0f))/36.0f,
        (18.0f + sqrtf(30.0f))/36.0f,
        (18.0f - sqrtf(30.0f))/36.0f
    };
    float integral = 0.0f;
    // Calcular a soma ponderada
    for (int i = 0; i < 4; i++) {
        float mapeado = mapear_no_intervalo(pontos[i], xi, xf);
        integral += pesos[i] * f(mapeado);
    }
    integral *= 0.5f * (xf - xi);    
    printf("Integral aproximada: %.5f\n", integral);
    return 0;
}