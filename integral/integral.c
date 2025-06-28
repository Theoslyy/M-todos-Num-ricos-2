#include <stdio.h>
#include <stdlib.h>
#include <math.h>

float integra (float a, float b, int N, float (*f)(float)){
    float Dx = (b-a)/N;
    float Area = 0;
    for(int i = 0; i < N; i++){
        float xi = a + Dx/2 + i*Dx;  
        Area = Area + Dx*f(xi); 
    }
    return Area; 
}
float integral_com_erro(float a, float b, float eps, float (*f)(float)){
    int N = 1; float erro = 1; float areaOld = 0; float Area; 
    while(erro > eps){
        N = N*2;
        Area = integra(a,b,N,f); 
        erro = fabs((Area - areaOld)/Area);
        areaOld = Area; 
    }
    return Area; 
}

int main(){
    // teste das funções estaria aqui
}