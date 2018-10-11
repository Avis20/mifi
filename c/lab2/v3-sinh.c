#include <stdio.h>
#include <math.h>

int main(){
    int i, n;
    double p, s, x;

    // n = 5; x = 1;

    while(1){

        printf("Введите шаг n. Для выхода введите 0\n");
        scanf("%d", &n);
        if (n < 0) break;

        printf("Введите вещественное число x\n");
        scanf("%lf", &x);

        p = s = x;
        for (i = 1; i <= n; i++){
            p = p * x * x / ( (2*i+1)*(2*i) );
            s += p;
        }

        printf("s = %lf\n", s);
        printf("sinh(%lf) = %lf\n\n", x, sinh(x));

    }

    return 0;
}