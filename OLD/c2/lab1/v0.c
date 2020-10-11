#include <stdio.h>
#include <malloc.h>

typedef struct Line {
    int n;     // кол-во эл. в строке
    double *a;  // массив эл.
} Line;

typedef struct Matrix {
    int lines;  // кол-во строк
    Line *matr; // массив строк
} Matrix;

void get_int( int *number );  // ввод целого числа
void get_double( int *number );  // ввод целого числа
int input_matr(Matrix *matr); // ввод матрицы 

int main (){
    Matrix matr = {0, NULL};
    input_matr(&matr);

    return 0;
}

int input_matr(Matrix *p_matr){
    int i, j;
    int m = 0;
    double *p;
    get_int(&m);
    printf("number = %d", m);
    p_matr->lines = m;
    printf("%d\n", p_matr->lines);
    // p_matr->matr = (Line *) calloc(m, sizeof(int));    
}


void get_int( int *number ){
    scanf("%d", &number);
}
