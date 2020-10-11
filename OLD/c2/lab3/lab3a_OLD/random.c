#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(){

    int c;
    int max = 122, min = 97;
    for (int j = 0; j < 10; j++){
        int v = rand() % (max - min + 1) + min;
        printf("%d -> %c\n", v, v);
    }

/*
    for (int i = 0; i < 10; i++){
        int key = rand() % 20;
        
        char val[10];
        for (int j = 0; j < 10; j++){
            int v = 97 + rand() % 122;
            if ( v > 122 ) v -= 97;
            val[j] = v;
        }
        
        printf("%d = %s\n", key, val);
    }
*/

    return 0;
}
