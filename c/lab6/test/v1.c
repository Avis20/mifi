#include <stdio.h>
#include <string.h>



int main () {
    FILE *f;
    int i;
    char c[100],ch[30],cname[40];
    for (;;){
    printf("Введитe имя файла, для выхода ввeдитe 0: ");
    scanf("%s",cname);
    for (;;){
    if (*cname == '0') return 0;
    f = fopen (cname,"r");
    if (f==NULL) { perror("Ошибка открытиe файла; повторите ввод "); scanf("%s",cname);} else break;
            }
    strcpy(c,"");i=0;
    while (!feof(f)){strcpy(ch,"");fgets(ch,30,f);if (i%2==1) strcat(c,ch);i++;}
    printf("%s",c);
    fclose(f);
    printf ("Введите имя файла для сохранения: ");
    scanf("%s",cname);
    f = fopen (cname,"w");
    fprintf(f,"%s",c);
    fclose(f);
    }   
    return 0;
}
