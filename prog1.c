#include<stdio.h>

float E(int x);
float Derivative(float A, float deltaX);

int main()
{
    int operation;
    while(scanf("%d", &operation) > 0) {//считываем операции, чтобы выйти ввести -1
        if (operation == 1) { //если операция 1
            float A, deltaX;
            scanf("%f%f", &A, &deltaX); //считываем A, deltaX
            printf("%s(%f, %f) = %f\n", "Derivative", A, deltaX, Derivative(A, deltaX));
            //печатаем значение производной
        } else if (operation == 2) { //если операция 2
            int x;
            scanf("%d", &x); //считываем x
            printf("%s(%d) = %f\n", "E", x, E(x)); //печатаем значение е
        } else {
            printf("ERROR\n"); //иначе ошибка 
        }
    }
}
