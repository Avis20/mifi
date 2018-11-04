/*
Дана строка, содержащая слова, разделенные одним или несколькими разделительными символами (пробелами, табуляторами), в начале строки и в конце строки также могут находиться разделительные символы. Сформировать новую строку, в которой удалить из каждого слова исходной строки повторяющиеся символы. Слова в новой строке разделяются одним пробелом. В начале строки и в конце строки не должно быть разделительных символов.
*/

#include <stdio.h>
#include <string.h>
#define N 100

void work(char *, char *);
char *skipspace(char *);
char *skipword(char *);

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

char *skipspace(char *str){
    while ( *str == ' ' || *str == '\t' ) str++;
    return str;
}

char *skipword(char *str){
    while ( *str && *str != ' ' && *str != '\t' ) str++;
    return str;
}

void work(char *from, char *to){
    int i, l;
    char *next;
    strcpy(to, "");

    for ( i = 0; *( from = skipspace(from) ); i++ ){
        str = from;
        next = skipword(from);
        printf("next = %s, from = %s\n", next, from);
        from += strcspn(from, " \t");
//       if (i > 2) break;
    }

//    for ( i = 0; from *= strspn(from, "\t") )
}
