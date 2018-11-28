#include <stdio.h>
#include <string.h>

#define MAXL 80

void treat(char*,char*);


int main(){
char src[MAXL],dst[MAXL];

while (printf("Entry Your String: "), fgets(src,MAXL,stdin)){
fflush(stdin);
src[strlen(src)-1] = '\0';
printf("Your String: X%sX\n",src);
treat(src,dst);
printf("Final String: X%sX\n", dst);

}
return 0;
}


void treat(char* in, char* out){

int i = 0;
char tmp[MAXL], *p;

for(strcpy(out,""),p=in; *(p+=strspn(p," \t")); p+=i){
    i = strcspn(p," \t");
    strncpy(tmp,p,i);
    tmp[i]='\0';
    if(strlen(out) && strlen(tmp) % 2 != 0)
        strcat(out," ");
    if (strlen(tmp) % 2 != 0)
    strcat(out, tmp);
}
}
