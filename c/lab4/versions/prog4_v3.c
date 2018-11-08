#include <stdio.h>
#include <string.h>

#define N 80

void work(char* from, char* to);

int main() {
    char from[N], to[N];
    while(printf("Введите строку: \n"), gets(from)) {
       printf("Исходная строка: '%s'\n", from);
        work(from, to);
        printf("Результат: '%s'\n", to);
    }
    return 0;
}

void work(char* from, char* to) {
    int j;
    strcpy(to,"");
    for(j=0;*(from+=strspn(from," \t"));) {
//        if(!i) c=*from;
//        ch = 
//        printf("%s",ch);
//if(i) strcat(to," ");
        if(*from == *(from+strcspn(from," \t")-1)) {
            if(j++) strcat(to," ");
            strncat(to,from,strcspn(from," \t"));
        } 
        from+=strcspn(from," \t");
    } 
    //strcpy(from,"");
    //strncpy(from,to,strlen(to)-1);
}
