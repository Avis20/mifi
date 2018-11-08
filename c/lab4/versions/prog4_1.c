#include <string.h>
#include <stdio.h>

void work (char *, char *);

void soft (char *, char *,int );

int main(){
    char to[80],from[80];
    while (printf("Введите строку : "),gets(from)){
        printf ("\nВведеная строка : %s \n",from);
        work (from,to);
        printf ("Получившаяся строка : %s \n",to);
    }
}

void work (char *from, char *to ){
    int i,n,l;
    int wl[40];
    char *w[40];
    strcpy(to,"");
    n=strlen(from);
    for (i=0; *(from+=strspn(from," \t"));i++){
        w[i]=from; wl[i]=strcspn(from," \t");
        from+=wl[i];}
    l=i-1;
    for (i=l;i>=0;i--){
        if (i!=l) strcat(to," ");
        strncat(to,w[i],wl[i]);
    }
    }
