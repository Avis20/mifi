#include <stdio.h>
#include <malloc.h>

struct Line {
    int n;     // кол-во эл. в строке
    double *a;  // массив эл.
};

struct Matrix {
    int lines;  // кол-во строк
    Line *matr; // массив строк
};

void get_int( int *number );  // ввод целого числа
void get_double( int *number );  // ввод целого числа
int input(Matrix *matr); // ввод матрицы 

int main (){
    Matrix matr = {0, NULL};
    double res;

    input(&matr);

    return 0;
}

void get_int( int *number ){
    scanf("%d", &number);
}

int input(Matrix *matr){
    int i, j, m;
    double *p;
    // get_int(&m);
    m = 5;
    matr->lines = m;
    matr->matr = (Line *) calloc(m, sizeof(int));
    
}