// Попарно поменять местами цифры, начиная с верхнего порядка. Если пары нет, поменять на ноль.

#include <stdio.h>

int main(){
    int n, i, p, res, pre, tmp;

    for (;;){

        tmp = res = 0;
        printf("Введите натуральное число n\n");
        scanf("%d", &n);
        if ( n <= 0) break;
        
        for ( tmp = n, i = 0; tmp > 0; tmp /= 10, i++ );
        if ( i % 2 ) n *= 10;
        
        for ( p = 1, i = 1; n > 0; n /= 10, i++, p *= 10 ){
            if ( i % 2 == 0 ) res += pre * p + n % 10 * p / 10;
            pre = n % 10;
            // printf("i = %d; p = %d; n10 = %d; pre = %d; res = %d\n", i, p, n % 10, pre, res);
        }
        printf("Результат = %d\n", res);

    }

    return 0;
}
