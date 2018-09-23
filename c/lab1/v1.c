// Дано натуральное число n. Подсчитать кол-во цифр и нулей

#include <stdio.h>

int main(){
    int n, count_zero, count_numbers;

    while(1){

        count_zero = count_numbers = 0;
        printf("Введите натуральное число \n");
        scanf("%d", &n);

        if ( n <= 0) break;
        while ( n > 0 ){
            if ( n % 10 == 0) count_zero++;
            n /= 10;
            count_numbers++;
        };
        printf("\nчисло нулей: %d\n", count_zero);
        printf("число цифр: %d\n", count_numbers);
     };
     return 1;
}
