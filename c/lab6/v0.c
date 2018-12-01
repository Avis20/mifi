/*
Дан двоичный файл, содержащий целые числа. Сформировать текстовый файл, в котором эти числа записаны в одну строку в порядке возрастания без повторяющихся значений. Программа должна производить проверку особых ситуаций при операциях ввода-вывода.
*/

#include <stdio.h>
#include <string.h>
#define N 80

void read(char *);

int main(){

    if (1){
        char filename[] = "./input.bin";
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

void read(char *filename){

    FILE *f;
    char str[N];
    printf("%s\n", filename);

    f = fopen(filename, "r");
    if (f == NULL){
        perror("Ошибка чтения файла");
    }

    while ( !feof(f) ){
        fgets(str, 30, f);
        printf("%s", str);
    }

//    printf("%s\n", strlen(str));
}
