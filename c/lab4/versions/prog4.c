#include <stdio.h>
#include <string.h>

void work (char *,char *);

int main (){
    char s[80],sr[80];
   while (printf("Ввeдитe строку: "),gets(s))
    {
        strcpy(sr,"");
        printf("Ввeдeнная строка:' %s ' \n",s);
        work(s,sr);
        printf("Рeзультат:' %s ' \n",sr);
        }
        return 0;
}

void work (char *a, char *b ){
 int i;
     strcat(b," ");
     strncat(a,b,1);
}
