#include <stdio.h>

int main(){
    int n, i, s1, s2, c1, c2;
    
    for (;;){

        printf("Введите натуральное число n\n");
        scanf("%d", &n);

        for ( i = 1, c1 = c2 = s1 = s2 = 0; n > 0; n /= 10, i++ ){
            // printf("i = %d; n = %d; i\%2 = %d; n\%10 = %d; s1 = %d; s2 = %d \n", i, n, i % 2, n % 10, s1, s2);
            if ( i % 2 == 0 ){
                s1 += n % 10;
                c1++;
            } else {
                s2 += n % 10;
                c2++;
            }
        }
        if ( c1 % 2 ){
            printf("Кол-во цифр - %d; Сумма цифр на s1 %d\n\n", c1, s1);
        } else {
            printf("Кол-во цифр - %d; Сумма цифр на s2 %d\n\n", c2, s2);
        }
 //       printf("%d, %d, n = %d", s1, s2, i);
        // printf("Кол-во цифр - %d; Сумма цифр на %d %d\n\n", c, s1, s2);
    }

    return 0;
}
