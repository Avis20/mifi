#include <stdio.h>
#include <math.h>

int main(){
    int i, n;
    double p, s, x, k;
//    n = 100; x = 1;
    while(1){

        printf("Введите шаг n. Для выхода введите 0\n");
        scanf("%d", &n);
        if (n == 0) break;

        printf("Введите вещественное число x\n");
        scanf("%lf", &x);

        for (i = 2, s = p = x; i <= n; i++){
            p *= -x * x;
            k = p/(2*i-1);
            s += k;
            // printf("i = %d; p=%f; k=%f; s=%f\n", i, p, s );
        }

        printf("s = %lf\n", s);
        printf("atan(%lf) = %lf\n\n", x, atan(x));

    }

    return 0;
}
