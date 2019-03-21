#include <stdio.h>

void work(FILE *,FILE *,FILE *);

int main()
{
	char name[80];
        FILE *f,*f1,*f2;
        int a;
	while (printf("Enter start filename\n"),gets(name)&&name[0]){
        if ((f=fopen(name,"rb"))==NULL)
        {
                perror(name);
                continue;
        }
	printf("Enter odd filename\n");
	gets(name);
	if ((f1=fopen(name,"wb"))==NULL)
        {
                perror(name);
		fclose(f);
		fclose(f1);
                continue;
        }
    printf("Enter feven filename\n");
    gets(name);
	if ((f2=fopen(name,"wb"))==NULL)
        {
                perror(name);
                fclose(f);
                fclose(f2);
                continue;
        }
	work(f,f1,f2);
	fclose(f);
    fclose(f2);
 	fclose(f1);
        }
    return 0;
}

void work(FILE *f,FILE *f1,FILE *f2)
{
	int a;
	while(fread(&a,sizeof(int),1,f)==1)
	if(a%2)
		fwrite(&a,sizeof(int),1,f1);
	else
		fwrite(&a,sizeof(int),1,f2);
        
        }

