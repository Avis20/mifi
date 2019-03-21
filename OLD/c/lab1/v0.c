#include <stdio.h>

int main(){
    int s, n = 123456;

    for (s = 0; n > 0; n /= 10) s = s * 10 + n % 10;

    printf("result = %d\n", s);

    return 0;
}