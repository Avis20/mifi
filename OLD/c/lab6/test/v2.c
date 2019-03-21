#include <stdio.h>
#include <string.h>
#define LEN 100
#define ERROR_FILE_OPEN -3

int main(){

char str[LEN];
char name[LEN] = "Some string \n One more string\n Third string";
int i = 1;
FILE *file_ptr;

file_ptr = fopen("newFile.txt", "r+");

if(file_ptr != NULL){

    printf("Данные считались из файла: \n");
    
    if (fgets(str, LEN, file_ptr) == NULL)
    {
        puts("Ошибка при чтении из файла\n");
    }
    else
    {   
     fseek(file_ptr, 0, SEEK_SET);
     while(fgets(str, LEN, file_ptr))
        {
            if (i % 2 != 0)
                fprintf(stdout, "%s", str);
            i++;
        }
    }
    fflush(stdout);

    printf("Считывание завершено\n");
    

}
else {

    fprintf(stderr, "Не удалось открыть или создать файл\n");
    return ERROR_FILE_OPEN;
        
}

if (fclose(file_ptr) == EOF)
    puts("Ошибка\n");
else 
    puts("Успешно\n");

return 0;
}

