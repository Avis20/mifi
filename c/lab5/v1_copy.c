#include <stdio.h>

char * skipspace( char * );
char * skipword( char * );
void work(char*, char*);
void sort(char**, int*, int);
int isswap(int, int);

int main() {
    char from[80], to[80];
    while(printf("Введите строку: \n"), gets(from)) {
        printf("Исходная строка: %s \n", from);
        work(from, to);
        printf("Полученная строка: %s \n", to);
    }
    return 0;
}

char* skipspace(char* p) {
    for(; *p == ' ' || *p == '\t'; p++);
    return p;
}

char* skipword(char* p) {
    for(; *p && *p != ' ' && *p != '\t'; p++);
    return p;
}

void work(char* from, char* to) {
    char *w[80];
    int wl[80], i, l, j;
    for(i=0;*(from=skipspace(from));from+=wl[i++]) {
        w[i] = from;
        wl[i] = skipword(from)-from;
    }
    l=i;
    sort(w,wl,l);
    for(i=0;i<l;i++) {
        if(i) *to++=' ';
        for (j=0;j<wl[i];j++){
            *to++=w[i][j];
        }
    }
    *to='\0';
}

void sort(char* w[], int wl[], int l) {
    int i, j, tmpl, f;
    char* tmpw;
    for(f=1,i=l-1; f&&i>0; i--) {
        for(f=j=0; j<i; j++) {
            if(isswap(wl[j],wl[j+1])) {
                f=1;
                tmpw=w[j];
                w[j]=w[j+1];
                w[j+1]=tmpw;
                tmpl=wl[j];
                wl[j]=wl[j+1];
                wl[j+1]=tmpl;
            }
        }
    }
}

int isswap(int l1, int l2) {
    int l = l1>l2;
    return l;
}
