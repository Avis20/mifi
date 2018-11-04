/*
Дана строка, содержащая слова, разделенные одним или несколькими разделительными символами (пробелами, табуляторами), в начале строки и в конце строки также могут находиться разделительные символы. Сформировать новую строку, в которой удалить из каждого слова исходной строки повторяющиеся символы. Слова в новой строке разделяются одним пробелом. В начале строки и в конце строки не должно быть разделительных символов.
*/

#include <stdio.h>
#include <string.h>
#define N 100

void work(char *, char *);

int main(){
//    char from[N], to[N];
    char from[] = " aabb abab   test1 test2 ", to[N];
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
    
    for ( i = 1; from += strspn(from, " \t"); i++ ){
        printf("%s\n", from);
        from += strcspn(from, " \t");
//       if (i > 2) break;
    }

//    for ( i = 0; from *= strspn(from, "\t") )
}
