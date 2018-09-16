#include <stdio.h>

int main (){

    int i, n = 1234;
/*    
    for (;;){
        printf("Введите натуральное число n\n");
        scanf("%d", &n);
    }
*/

    for ( i = 1; i < n; n %= 10, i++ ){
        printf("%d\n", n);
    }

    return 0;
}
