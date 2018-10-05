/*
Дано вещественное число x в заданном диапазоне. Вычислить сумму n членов ряда. Вычислить значение библиотечной
функции pow(2.x). Полученные результаты вывести на экран для сравнения
*/

#include <stdio.h>
#include <math.h>

int main(){

    int i, x = 1;
    double res = 0, pow = 0, fact = 1;
    for (i = 0; i < 5; ++i){
//        res += pow / fact;
        pow += -x * x;
//        fact *= (2 * (i+1) ) * (2 * (i+1)+1);
        printf("fact = %f\n", pow);
    }

    printf("%f\n", res);
    printf("%f\n", sin(x));

    return 0;
}
