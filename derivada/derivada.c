#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>


//Exemxlo de sala foi seno, logo, usarei seno. 
float func(float x){
    return sin(x);
}

float derivada(float x, float deltax, int direction){
    float dx;
    /*
    Aqui, estamos usando a definição de derivada baseando-se no limite:
    lim (f(x) - f(p))/(x-p), com x sendo o nosso ponto da derivada e p sendo o 'próximo ponto'
    x->p                     o limite serve para dizermos que p está o quão próximo
                             quisermos de x.
    É por isso que usamos deltax ao invés de p diretamente no header dessa função, 
    usar x + deltaX foi o que o professor ensinou em sala agora então faz
    mais sentido usar a mesma 'nomenclatura'.
    Como estamos fazendo uma abordagem simples, não aproximaremos o deltaX, não
    há um estudo de convergência, aqui, simplesmente usamos o deltaX passado pelo usuário.
    */
    switch(direction){
        case 0: //central
           return dx = (func((x + deltax)) - func((x - deltax)))/(2*deltax);

        case 1: // esquerda
            return dx = (func(x) - func(x - deltax))/(deltax); 

        case 2: // direita
            return dx = (func(x + deltax) - func(x))/(deltax);
        default: 
            printf("Entrada inválida.");
            return NAN;
    }
}


int main(){
    printf("A função a ser derivada será sen(x). \n");
    printf("Por favor, informe os parâmetros a seguir: \n");
    printf("Ponto x da derivada: ");
    float x; 
    scanf("%f", &x);
    printf("Delta x: ");
    float delta;
    scanf("%f", &delta);
    int direcao; 
    float resultado; 
    while(true){ 
        printf("Digite 0 para escolher derivada central, \n");
        printf("1 para escolher derivada à esquerda, \n");
        printf("2 para escolher derivada à direita.");
        scanf("%i", &direcao);  
        resultado = derivada(x, delta, direcao);
        if (!(_isnanf(resultado))) {
            // Poderia ter feito esse teste de 'direcao' valida de forma mais segura, porém 
            // Isso basta. 
            break;
        }
    }
    printf("O resultado da derivada da função sen(x) no ponto %f é igual a %f", x, resultado);
}