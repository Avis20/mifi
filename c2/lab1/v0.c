#include <stdio.h>
#include <malloc.h>

struct Line {
    int n;     // кол-во эл. в строке
    double *a;  // массив эл.
};

typedef struct Matrix {
    int lines;  // кол-во строк
    Line *matr; // массив строк
} HUETA;

void get_int( int *number );  // ввод целого числа
void get_double( int *number );  // ввод целого числа
int input(Matrix *matr); // ввод матрицы 

int main (){
    HUETA matr = {0, NULL};
    double res;
    // matr.lines = 5;
    // printf("%d\n", matr.lines);
    
    input(&matr);

    return 0;
}

int input(Matrix *p_matr){
    int i, j, m;
    double *p;
    get_int(&m);
    // m = 5;
    p_matr->lines = 10;
    printf("%d\n", p_matr->lines);
    // p_matr->matr = (Line *) calloc(m, sizeof(int));    
}


void get_int( int *number ){
    scanf("%d", &number);
}
