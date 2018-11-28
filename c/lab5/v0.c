/*
Дана строка, содержащая слова, разделенные одним или несколькими разделительными символами (пробелами, табуляторами), в
начале строки и в конце строки также могут находиться разделительные символы. Сформировать новую строку, состоящую
только из слов, начинающихся на тот же символ, что и последнее слово в исходной строке, разделенных одним пробелом. В
начале строки и в конце строки не должно быть разделительных символов.
*/

#include <stdio.h>
// #include <string.h>
#define N 100

char *skipspace(char *);
char *skipword(char *);
void work(char *, char *);

int main(){
//    char from[N], to[N];
    char to[N];
    char from[] = "help me!\0";
//    char from[] = "test                            fdfdf           hg       sgh sf sq xx     x     f xsgf ddd", to[N];
    work(from, to);
    printf("Результат: %s\n", to);
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

void work (char *from, char *to){
    char *w[80];
    int wl[80], i, l, j;
    // for(i=0; *( from=skipspace(from) ); from+=wl[i++] ){
    //     printf("%s", from);
    // }
    // for(i=0; *( from=skipspace(from) ); from+=wl[i++] ){
    //     w[i] = from;
    //     wl[i] = skipword(from)-from;
    // }
    // l=i;
    // for (i=0 ; i<l ;i++ ){
    //     for ( j=0; j<wl[i]; j++){
    //         printf("%d\n", w[i][j]);
    //     }
    // }
}

char *skipspace(char *str){
    for(; *str == ' ' || *str == '\t'; str++);
    return str;
}

char *skipword(char *str){
    for(; *str && *str != ' ' || *str != '\t'; str++);
    return str;
}

