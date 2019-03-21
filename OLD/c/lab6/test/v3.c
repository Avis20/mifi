#include <stdio.h>
#include <string.h>
void work(FILE*);
int main(){
    char name[80];
    FILE* f;
    while(printf("Имя исходного файла: \n"), gets(name)&&name[0]){
        if((f=fopen(name,"wr"))==NULL){
        perror(name);
        continue;
        } 
        work(f);
        fclose(f);
    }
    return 0;
}
void work(FILE* f){
    int a=0;
    char buf[80];
    while(fgets(buf,80,f)){
        if(a%2) printf("%s",buf);
        a++;
        strcpy(buf,"");
    }
}
