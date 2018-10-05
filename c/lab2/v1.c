/*
Дано вещественное число x в заданном диапазоне. Вычислить сумму n членов ряда. Вычислить значение библиотечной
функции sinh(x). Полученные результаты вывести на экран для сравнения
*/

#include <stdio.h>
#include <math.h>

int main(){
    int n;
    double result = 0, x, y, z;
    int i = 0;
    
//    while(1){

        printf("Введите вещественное число x\n");
        scanf("%d", &x);
//        if ( x <= 0) break;
        z = y = x;
        for (i = 1; i < n; i++){
            y *= -x * x;
        }

        printf("Результат = %f\n", y);
        printf("Результат = %f\n", sinh(x));
//    };

    return 1;
}
