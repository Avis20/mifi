/*
Дан двоичный файл, содержащий целые числа. Сформировать текстовый файл, в котором эти числа записаны в одну строку в порядке возрастания без повторяющихся значений. Программа должна производить проверку особых ситуаций при операциях ввода-вывода.
*/

#include <stdio.h>
#include <string.h>
#define N 80

int read(char *);

int main(){

    if (1){
        char filename[] = "./as";
        read(filename);
    } else {
        char filename[N];
        while(1){
            printf("Введитe имя файла, для выхода ввeдитe 0: \n");
            scanf("%s", filename);
            if (filename[0] == '0') break;
            read(filename);
        }
    }

    return 0;
}

int read(char *filename){

    FILE *f;
    int symbol;
    int size_int = sizeof(int);
    if ( ( f = fopen(filename, "rb") ) == NULL ){
        perror("Ошибка чтения файла");
        return 1;
    }
    
    while( fread(&symbol, sizeof(int), 1, f) == 1){
        printf("%d ", symbol);
    }

    fclose(f);
}
