/*
Дана строка, содержащая слова, разделенные одним или несколькими разделительными символами (пробелами, табуляторами), в
начале строки и в конце строки также могут находиться разделительные символы. Сформировать новую строку на основе
исходной строки, из которой удалены слова, встречающиеся в исходной строке только один раз. Оставшиеся слова разделяются
одним пробелом. В начале строки и в конце строки не должно быть разделительных символов.
*/


#include <stdio.h>
#include <string.h>
#define N 100

void work(char *, char *);

int main(){

//    char from[N], to[N];
    char from[] = " ab ba aba ", to[N];
    work(from, to);
    printf("Результат; %s\n", to);
/*
    while( printf("Введите строку: \n"), gets(from) ){
        work(from, to);
        printf("Результат; %s\n", to);
    }
*/
    return 0;
}

void work(char *from, char *to){
    int i, l;
    strcpy(to, "");
    printf(strspn(from, "\t") );
//    for ( i = 0; from *= strspn(from, "\t") )
}
