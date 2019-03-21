#include <stdio.h>
#include <math.h>

int main(){
    int i, n, f;
    double p, s, x;

    n = 5; x = 1;

    // while(1){

    //     printf("Введите шаг n. Для выхода введите 0\n");
    //     scanf("%d", &n);
    //     if (n < 0) break;

    //     printf("Введите вещественное число x\n");
    //     scanf("%lf", &x);

        s = 0;
        p = f = 1;
        for (i = 0; i <= n; i++){
            printf("i = %d; %d\n", i, f);
            f *= i;
            printf("%d", f);
            // p *= x;
            // printf("i = %d;p = %f;f = %d\n", i, p, f);
            // s += p;
        }

        // for (i=0,s=0,f=1,p=1;i<=n;p*=x,f*=++i)
        // {
        //     s += p / f;
        // }


        printf("s = %lf\n", s);
        printf("exp(%lf) = %lf\n\n", x, exp(x));

    // }

    return 0;
}