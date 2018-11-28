#include <stdio.h>
#define N 80

char finds (char *,int );

void work (char *,char*);

char* skipword(char*);

char* skipspace(char*);

int main (){
    char s[N], t[N];
    int g[N];
    while (printf("Введите строку, для выхода прожмите ctrl+d : "),gets(s))
    {   
        printf ("Оригинал '%s' \n",s);
        work(s,t);
        printf ("Рeзультат '%s' \n",t);
    }

}



void work(char *from, char *to){
    int i,j,l,wl[40];
    char *w[40];
    for (i=0;*(from=skipspace(from));from+=wl[i++]){
        w[i]=from;
        wl[i]=skipword(from)-from;
    }
    l=i-1;
    for (i=l;i>=0;i--){
        if (i!=l) *to++=' ';
        for (j=0;j<wl[i];j++) *to++=w[i][j];
    }
    *to='\0';
   }    


char* skipspace (char *p){
    for (;(*p)&&(*p==' ')||(*p=='\t');p++);
    return (char*) p;
}

char* skipword (char *p){
    for (;(*p)&&(*p!=' ')&&(*p!='\t');p++);
    return (char*) p;
}
