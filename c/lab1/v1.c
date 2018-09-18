#include <stdio.h>

int main(){
    int n, k1, k2;
    while(1){
        printf("Введите натуральное число \n");
        scanf("%d", &n);
        printf("%d", n);
        if ( n <= 0) break;
        k1 = k2 = 0;
        while ( n > 0 ){
            if ( n % 10 == 0) k1++;
            n /= 10;
            k2++;
        };
        printf("\nчисло нулей: %d\n", k1);
        printf("число цифр: %d\n", k2);
     };
     return 1;
}
