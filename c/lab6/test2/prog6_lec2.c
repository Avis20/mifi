//Программа, которая выводит на экран содержимое двоичного файла (в столбик)

#include <stdio.h>

int main(){
    char name[80];
    int a;
    FILE* f;
    for(;;){
    printf("Введите имя файла\n");
    scanf("%s",name);
    if ((f=fopen(name, "rb"))==NULL){
        perror(name);
        return 1;
    }
    while(fread(&a,sizeof(int),1,f)==1)
        printf("%d ",a);
  
        fclose(f);

       printf("%d\n",a);
}
        return 0;
}
