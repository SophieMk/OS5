#include <math.h>

//реализация 1

float E(int x) { //рассчёт значения числа е
    return pow(1 + 1. / x, x);
}

float Derivative(float A, float deltaX) { //функция рассчёта производной функции 
                                          //cos(x) в точке А с приращением deltaX 
    float ans;
    ans = (cos(A + deltaX) - cos(A)) / deltaX;
    return ans;
}