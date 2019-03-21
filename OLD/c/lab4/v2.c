/*
Дана строка, содержащая слова, разделенные одним или несколькими разделительными символами (пробелами, табуляторами), в
начале строки и в конце строки также могут находиться разделительные символы. Сформировать новую строку, состоящую
только из слов, начинающихся и заканчивающихся на один и тот же символ, разделенных одним пробелом. В начале строки и в
конце строки не должно быть разделительных символов.
*/

#include <stdio.h>
#include <string.h>
#define N 100

void work(char *, char *);

int main(){
    char from[N], to[N];
/*    
    char from[] = "test                            fdfdf           hg       sgh sf sq xx     x     f xsgf ddd", to[N];
    work(from, to);
    printf("Результат: %s\n", to);
*/

    while( printf("Введите строку. Для выхода введите 0: \n"), gets(from) ){
        if (from[0] == '0') break;
        printf("Исходная строка; %s\n", from);
        work(from, to);
        printf("Результат; %s\n", to);
    }

    return 0;
}

void work (char *from, char *to){
    int i, n, j, lenght;
    char start_letter, end_letter;
    strcpy(to, "");
    for (i = 0; *( from += strspn(from, " \t") ); i++){
        //if (!i) strcat(to, " ");
//    while (*( from += strspn(from, " \t"))){
        start_letter = from[0];
        lenght = strcspn(from," \t");
        end_letter = from[lenght-1];
        if ( start_letter == end_letter ){ 
            strncat(to, from, lenght);
            strcat(to, " ");
        }
        from += strcspn(from, " \t");
    }
}

