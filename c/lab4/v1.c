/*
Дана строка, содержащая слова, разделенные одним или несколькими разделительными символами (пробелами, табуляторами), в начале строки и в конце строки также могут находиться разделительные символы. Сформировать новую строку, в которой удалить из каждого слова исходной строки повторяющиеся символы. Слова в новой строке разделяются одним пробелом. В начале строки и в конце строки не должно быть разделительных символов.
*/

#include <stdio.h>
#include <string.h>
#define N 100

void work(char *, char *);
void work2(char *, char *);

int main(){
    // char from[N], to[N];
    char from[] = "test", to[N];
    work2(from, to);
    printf("Результат: %s\n", to);
/*
    while( printf("Введите строку: \n"), gets(from) ){
        printf("Исходная строка; %s\n", from);
        work(from, to);
        printf("Результат; %s\n", to);
    }
*/
    return 0;
}


void work2 (char *from, char *to){
    int i, n, j, b, k = 0;
    strcpy(to, "");
    // for (i = 0; *( from += strspn(from, " \t") ); i++){
    while (*( from += strspn(from, " \t"))){
        for ( i = 0; i < strcspn(from, " \t"); i++ ){
            for ( j = 1; j <= i; j++ ){
                printf("%c", from[j]);
            }
            // printf("-%c-", from[i]);
        }
        from += strcspn(from, " \t");
    }
}


void work (char *from, char *to){
    int i, n, lenght, space = 0;
    strcpy(to, "");
    for (i = 0; *( from += strspn(from, " \t") ); i++){
        if ( space++ ) strcat(to, " ");
        if ( i % 2 == 0 ){
            lenght = strcspn(from," \t");
            strncat(to, from, lenght);
        }
        from += strcspn(from, " \t");
    }
}
