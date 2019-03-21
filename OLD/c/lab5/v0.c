/*
Дана строка, содержащая слова, разделенные одним или несколькими разделительными символами (пробелами, табуляторами), в
начале строки и в конце строки также могут находиться разделительные символы. Сформировать новую строку, состоящую
только из слов, начинающихся на тот же символ, что и последнее слово в исходной строке, разделенных одним пробелом. В
начале строки и в конце строки не должно быть разделительных символов.
*/

#include <stdio.h>
#define N 80

void work(char *, char *);
char *skipspace(char *);
char *skipword(char *);

int main(){

    if (0){ // debug
        char from[] = "abcd me efgh me";
        char to[N];
        printf("Исходная строка: %s\n", from);
        work(from, to);
        printf("Результат: %s\n", to);
    } else {
        char from[N], to[N];
        while (printf("Введите исходную строку. Для выхода введите 0: \n"), gets(from)){
            if (from[0] == '0') break;
            printf("Исходная строка: %s\n", from);
            work(from, to);
            printf("Результат: \"%s\"\n", to);
        }
    }

    return 0;
}

void work(char *from, char *to){
    char *words[N], last_char;
    int word_lenghts[N], i, j, last;
    for (i = 0; *( from = skipspace(from) ); from += word_lenghts[i++] ){
        words[i] = from;
        word_lenghts[i] = skipword(from) - from;
    }
    last = i;
    last_char = words[last-1][0];
    for( i = 0; i < last; i++ ){
        if ( last_char == words[i][0] ){
            if(i) *to++=' ';
            for( j = 0; j < word_lenghts[i]; j++ ){
                *to++ =  words[i][j];
            }
        }
    }
    *to = '\0';
}

char *skipspace(char *str){
    for(; *str == ' ' ||  *str == '\t'; str++);
    return str;
}

char *skipword(char *str){
    for(; *str && *str != ' ' && *str != '\t'; str++);
    return str;   
}
