/*
Дан текстовый файл. Вывести на экран строки файла, имеющие четную длину. Программа должна производить проверку особых ситуаций при операциях ввода-вывода.
*/

#include <stdio.h>
#include <string.h>
#define N 80

int read(char *);

int main(){

    if (0){
        char filename[] = "./input.txt";
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
    char buf[N];
    int size_int = sizeof(int);
    if ( ( f = fopen(filename, "r") ) == NULL ){
        perror("Ошибка чтения файла");
        return 1;
    }
    
    while ( fgets(buf, 80, f) ){
        if ( ( strlen(buf)-1 ) % 2 == 0 ) printf("%s", buf);
        strcpy(buf, "");
    }

    fclose(f);
}
