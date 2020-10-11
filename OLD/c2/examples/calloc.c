#include <stdlib.h>
#include <stdio.h>

float *get_mem();

int main(){

    // Выделение и обнуления памяти для массива из 4 int
    printf("%d\n", sizeof(int));
    int* p1 = (int*)calloc(4, sizeof(int));
    p1[0] = 1;
    p1[1] = 1;
    // Тоже самое, но с указанием типа массива
    // int* p2 = (int*)calloc(1, sizeof(int[4]));
    // Тоже самое, но без повторного указания имени типа
    // int* p3 = (int*)calloc(4, sizeof *p3);
 
    for (int n = 0; n < 9; ++n){
        printf("%d\n", p1[n]);
    }

    // if(p2)
    //     for(int n=0; n<4; ++n) // Вывод массива
    //         cout << "p2[" << n << "] == " << p2[n] << '\n';
 
    free(p1);
    // free(p2);
    // free(p3);
    return 0;
}

//Следующая функция возвращает указатель на динамически выделенный массив для 100 чисел типа float:
float *get_mem() {
    float *p;
    p = (float *) calloc(100, sizeof(float));
    if(!p) {
        printf ("Allocation failure.");
        exit (1);
    }
    return p;
}