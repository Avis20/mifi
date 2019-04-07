#include <stdio.h>
#include <malloc.h>

typedef struct Line {
    int n;          // кол-во эл. в строке
    double *items;  // массив эл.
} Line;

typedef struct Matrix {
    int lines;  // кол-во строк
    Line *matr; // массив строк
} Matrix;

int get_int(int *number);      // ввод целого числа
int input(Matrix *matr);   // ввод матрицы
void output(char *msg, Matrix p_matr);
double get_double(double *a);    // ввод дробного числа
void erase(Matrix *matr);

int main (){
    Matrix matr = {0, NULL};
    if ( input(&matr) == 0){
        printf("Matrix is emply");
        return 1;
    }
    output("Source matrix", matr);

    return 0;
}

void output(char *msg, Matrix p_matr){
    int i,j;
    double *p;
    printf("%s:\n", msg);
    for (i = 0; i <= p_matr.lines; i++){
        p = p_matr.matr[i].items;
        for (j = 0; j < p_matr.matr[i].n ; j++) {
            printf("%10lf", *p);
        }
        printf("\n");
    }
}

int input(Matrix *p_matr){
    int i, j;
    int m = 0;
    double *p;
    do {
        printf("Enter number lines: ");
        if ( get_int(&m) == 0 ){
            return 0;
        }

    } while ( m < 1 );

    p_matr->lines = m;

    p_matr->matr = (Line *)calloc(m, sizeof(Line));

    for (i = 0; i < p_matr->lines; i++){
        do {
            printf("Input number items in line: ");
            if ( get_int(&m) == 0 ){
                p_matr->lines = i;
                erase(p_matr);
                return 0;
            }
        } while ( m < 1 );

        p_matr->matr[i].n = m;
        p = (double *)malloc(sizeof(double)* m);
        p_matr->matr[i].items = p;

        printf("Enter items for matrix line #%d:\n", i+1);
        for (int j = 0; j < m; j++) {
            if ( get_double(p) == 0){
                p_matr->lines = i+1;
                erase(p_matr);
                return 0;
            }
        }

    }
    return 1;
}


int get_int(int *num){

    int n;
    do {
        n = scanf("%d", num);
        if ( n < 0 ) return 0; // конец файла

        if ( n == 0 ){ // неизвестный символ
            printf("error: repeat input");
            scanf("%d", num);
        }
    } while ( n == 0 );

    return 1; // success
}

double get_double(double *a){
    int n;
    do {
        n = scanf("%lf", a);
        if ( n < 0 ) return 0;
        if ( n == 0 ){
            printf("error: repeat input\n");
            n = scanf("%lf", a);
        }
    } while ( n == 0 );
    return 1;
}

void erase(Matrix *p_matr){
    int i;
    for (i = 0; i <= p_matr->lines; i++) {
        free(p_matr->matr[i].items);
    }
    free( p_matr );
    p_matr->lines = 0;
    p_matr->matr = NULL;
}



