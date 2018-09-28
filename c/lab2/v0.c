/*
Дано вещественное число x в заданном диапазоне. Вычислить сумму n членов ряда. Вычислить значение библиотечной
функции pow(2.x). Полученные результаты вывести на экран для сравнения
*/

#include <stdio.h>
#include <math.h>

int main(){
    int n;
    double result = 0, x;

//    while(1){

        printf("Введите вещественное число x\n");
        scanf("%d", &x);
//        if ( x <= 0) break;

 //       result = pow(2., x);

        printf("Результат = %f\n", result);
        printf("Результат = %f\n", pow(2., x));
//    };
     
    return 1;
}
