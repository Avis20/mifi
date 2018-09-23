// Дано натуральное число n. Подсчитать кол-во и сумму цифр, стоящих на четных местах

#include <stdio.h>

int main(){
    int n, i, s1, s2, count;

    for (;;){

        s1 = s2 = count = 0;
        printf("Введите натуральное число n\n");
        scanf("%d", &n);
        if ( n <= 0) break;

        for ( i = 1; n > 0; n /= 10, i++ ){
            if ( i % 2 == 0 ){
                s1 += n % 10;
                count++;
            } else {
                s2 += n % 10;
            }
        }
        printf("Кол-во цифр = %d; Сумма цифр = %d\n\n", count, ( i % 2 ? s2 : s1 ));

    }

    return 0;
}
