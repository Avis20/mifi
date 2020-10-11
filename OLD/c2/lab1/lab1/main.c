#include <stdlib.h>
#include <malloc.h>

typedef struct Line {
    int n;
    double *items;  // массив эл.
} Line;

typedef struct Matrix {
    int lines;
    Line *lines_arr;
} Matrix;

int input_matr(Matrix *xmatr);
void clean_matr(Matrix *xmatr);
int getint(int *);

int main(){

    Matrix matr = {0, NULL};
    double result;

    input_matr(&matr);

    return 0;
}

int input_matr(Matrix *xmatr){
    char *error_msg = "";
    int count; // кол-во строк

    do {
        printf("%s\n", error_msg);
        printf("Введите кол-во строк матрицы: ");

        if ( getint(&count) == 0) return 0;

    } while ( count < 1 );

    xmatr->lines = count;
    xmatr->lines_arr = (Line *)calloc(count, sizeof(Line));

    for (int i = 0; i <= xmatr->lines; i++) {
        error_msg = "";
        do {
            printf("Введите кол-во солбцов %d-й строки матрицы: ", i+1);
            if ( getint(&count) == 0 ){
                xmatr->lines = i; // зачем?
                clean_matr(xmatr);
                return 0;
            }
            //printf("Введите %d-й эл. %d-й строки ")
        } while ( count < 1 );
    }

    return 1;
}

void clean_matr(Matrix *xmatr){
    for (int i = 0; i <= xmatr->lines; i++) {
        free(xmatr->lines_arr[i].items);
    }
    free(xmatr->lines_arr);
    xmatr->lines = 0;
    xmatr->lines_arr = NULL;
}

int getint(int *number ){
    int n;

    do {
        n = scanf("%d", number);
        if ( n < 0 ) return 0;

        if ( n == 0 ){
            printf("Error: Repeat input: ");
            n = scanf("%*c", 0);
        }

    } while ( n == 0 );

    return 1;
}
















