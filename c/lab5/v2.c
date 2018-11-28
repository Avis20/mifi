#include <stdio.h>
#define N 80

void work(char *, char *);
char *skipspace(char *);
char *skipword(char *);

int main(){
    // char from[N];
    char to[N];
    char from[] = "test";
    work(from, to);

/*
    while( printf("Введите строку. Для выхода введите 0: \n"), gets(from) ){
        if (from[0] == '0') break;
        printf("Исходная строка; %s\n", from);
        work(from, to);
        printf("Результат; %s\n", to);
    }    
*/

    return 0;
}

void work(char *from, char *to){
    int i;
    int wl[N];
    for ( i = 0; *( from = skipspace(from) ); from += wl[i++] ){
        printf("%d", 1);
        // from = skipword(from) - from;
    }

}

char *skipspace(char *str){
    for(; *str == ' ' || *str != '\t'; str++);
    return str;
}

char *skipword(char *str){
    for(; *str && *str != ' ' || *str != '\t'; str++);
    return str;
}