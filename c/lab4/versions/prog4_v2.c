#include <stdio.h>
#include <string.h>

int main(){
char str[100];
char tmp[100];
char strNew[100];
int start, end;
int i,j,k, mNew=0;
int size;
    
    for(;;){
    fflush(stdin);
    printf("\nВведите строку:\n");
    fgets(str,100,stdin);
    if(str[0]=='0' ) break;
    fflush(stdin);
    printf("Вы ввели строку: \n");
    puts(str);
    printf("strlen = %d, my = %d\n",strlen(str), myStrLen(str) );


    while(i < myStrLen(str)-1)
    {
        if (str[i] !=' ' && str[i]!='\t')
        {
            start = i;
            end=i;
            i++;
            while(i<myStrLen(str)-1 && str[i]!=' ' && str[i]!='\t')
            {
                end = i;
                i++;
            }
          
        for(j=start; j<=end; j+=2){
            strNew[mNew++] = str[j];
        }
        strNew[mNew++] = ' ';    
        }
        i++;
    }
    strNew[--mNew]='\0';
    //strNew[mNew] = '\0';
    
    printf("\nОбработанная строка\n");
    puts(strNew);printf("X");
}
    return 0;

}


int myStrLen(char *str)
{
    int i=0;
    while(str[i]!='\0'){
        i++;
    }

    return i;
}


