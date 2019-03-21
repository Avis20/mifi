
// НЕ РАБОТАЕТ

#include <stdio.h>
#include <math.h>

int main(){
    int i, n;
    double p, s, x;

    n = 5; x = 1;

    // while(1){

    //     printf("Введите шаг n. Для выхода введите 0\n");
    //     scanf("%d", &n);
    //     if (n < 0) break;

    //     printf("Введите вещественное число x\n");
    //     scanf("%lf", &x);

        p = s = x;
        for (i = 1; i <= n; i++){
            // p = p * (2*i-1) / (2*i) * x * x * (2*i-1)/(2*i+1);
            p = p*(2*i-1)/(2*i)*x*x/(2*i+1);
            s += p;
        }

        printf("s = %lf\n", s);
        printf("asin(%lf) = %lf\n\n", x, asin(x));

    // }

    return 0;
}