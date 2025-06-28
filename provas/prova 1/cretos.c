#include <stdio.h>
#include <math.h>

float x(int xi, int xf, float a){
    return ((xi+xf)/2 - (((xf-xi)/2)*a));
}
float f(float x){
    float qt = 9 + 4*(pow(cos(0.4*x),2));
    float ct = 5*exp(-0.5*x) + 2*exp(0.15*x);
    return (qt*ct); 
}

int main(){
    int i = 0; int xf = 8; int xi = 2;
    float integral = 0.0; 
    float a = pow(30., 1./2.)/36.;
    float b1 = pow((15.+a)/2.0, 1./2.);
    float b2 =  pow((15.-a)/2.0, 1./2.);
    float wk[4] = {1.0/2.0 - a, 1./2. + a, 1./2. + a, 1./2. - a};
    float ak[4] = {-b1, -b2, b2, b1};
    while(i < 4){
        printf("passo: %d : %f \n", i, integral); 
        integral =  f(x(xi, xf, ak[i]))*wk[i] + integral;
        i++;
    }
    integral = integral*((xf - xi)/2);
    printf("%f", integral); 
    return integral; 
}