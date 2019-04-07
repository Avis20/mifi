#include <stdio.h>
#include <malloc.h>

typedef struct Line{
    int count_items;    // Кол-во эл. в строке
    double *items;      // массив эл.
} Line;

typedef struct Matrix{
    int lines;          // Кол-во строк матрицы
    Line *matr;         // массив строк матрицы
} Matrix;

typedef struct Vector {
    int count_items;    // Кол-во эл. в массиве
    double *items;      // Массив эл.
} Vector;

int get_int(int *);
int get_double(double *);
int input(Matrix *a);
void output(const char *msg, Matrix p_matr);
void erase(Matrix *a);
void work(Matrix matr, Vector *b);
void print_vector(Vector b);

int main(){
    Matrix matr = {0, NULL};
    double arr[] = {1,2,3,4,5,6,7,8};
    Vector b = {0, NULL};
    double *pv;
/*
    b.count_items = 8;
    pv = (double *)malloc(sizeof(double)* b.count_items);
    b.items = pv;

    for (int i = 0; i < 8; ++i, ++pv) {
        pv[i] = i + 10;
    }
*/

    if ( input(&matr) == 0 ){
        printf("Matrix is empty\n");
        return 1;
    }

    work(matr, &b);
    output("Source matrix", matr);
    print_vector(b);
//    printf("Result: %f\n", res);
    erase(&matr);

    return 0;
}

void print_vector(Vector v){
    int i, j;
    double *p;

    for (i = 0; i < v.count_items; ++i){
        p = v.items;
        printf("%10lf\n", *p);
    }
}

void work(Matrix p_matr, Vector *v){
    int i, j;

    double *p;
    double *pv;

    v->count_items = p_matr.lines;   // Сколько строк, столько и эл. в векторе
    pv = (double *)malloc(sizeof(double)* v->count_items);
    v->items = pv;

    for (i = 0; i < p_matr.lines; ++i, ++pv){
        p = p_matr.matr[i].items;
        for (j = 0; j < p_matr.matr[i].count_items; ++j, ++p){
            *pv += *p;
//            printf("%10lf ", *p);
        }
        printf("\n");
    }
}

int get_int(int *num){
    int n;

    do {
        n = scanf("%d", num);
        if (n < 0) return 0;
        if (n == 0){
            printf("Error! Repeat input\n");
            scanf("%*c");
        }
    } while (n == 0);

    return 1;
}

int get_double(double *num){
    int n;
    do {
        n = scanf("%lf", num);
        if (n < 0) return 0;
        if (n == 0){
            printf("Error! Repeat input\n");
            scanf("%*c");
        }
    } while (n == 0);

    return 1;
}

int input(Matrix *p_matr){
    const char *pr = "";
    int m;
    int i, j;
    double *p;

    do {
        printf("%s\n", pr);
        printf("Enter number of lines: ");
        pr = "You are wrong; repeat input";
        if( get_int(&m) == 0 ) return 0;
    } while (m < 1);

    p_matr->lines = m;
    p_matr->matr = (Line *)calloc(m, sizeof(Line));

    for ( i = 0; i < p_matr->lines; ++i ){
        pr = "";
        do {
            printf("%s\n", pr);
            printf("Enter number of items in line %d: ", i + 1);
            pr = "You are wrong; repeat input";
            if ( get_int(&m) == 0 ){
                p_matr->lines = i;
                erase(p_matr);
                return 0;
            }
        } while (m < 1);

        p_matr->matr[i].count_items = m;
        p = (double *)malloc(sizeof(double)* m);
        p_matr->matr[i].items = p;

        printf("Enter items for matrix line #%d:\n", i + 1);
        for (j = 0; j < m; ++j, ++p){
            if (get_double(p) == 0){
                p_matr->lines = i + 1;
                erase(p_matr);
                return 0;
            }
        }
    }

    return 1;
}

void output(const char *msg, Matrix p_matr){
    int i, j;
    double *p;
    printf("%s:\n", msg);
    for (i = 0; i < p_matr.lines; ++i){
        p = p_matr.matr[i].items;
        for (j = 0; j < p_matr.matr[i].count_items; ++j, ++p){
            printf("%10lf ", *p);

        }
        printf("\n");
    }
}

void erase(Matrix *p_matr){
    int i;
    for (i = 0; i < p_matr->lines; ++i)
    free(p_matr->matr[i].items);
    free(p_matr->matr);
    p_matr->lines = 0;
    p_matr->matr = NULL;
}

/*
double minmax(Matrix pm){
    double *s = (double *)malloc(sizeof(double)* pm.lines);
    double res;
    double *p = s;
    int i;
    for (i = 0; i < pm.lines; ++i){
        *p++ = max(pm.matr[i].a, pm.matr[i].n);
    }

    res = min(s, pm.lines);
    res = mm(s, pm.lines, -1);
    free(s);
    return res;
}

double max(double a[], int m){
    double res = *a;
    for (; m-- > 0; ++a){
        if (*a > res) res = *a;
    }

    return res;
}

double min(double a[], int m){
    double res = *a;
    for (; m-- > 0; ++a){
        if (*a < res) res = *a;
    }

    return res;
}

double mm(double a[], int m, int flag){
    double res = *a;
    for (; m-- > 0; ++a){
        if (flag > 0 ? *a > res : *a < res) res = *a;
    }

    return res;
}

*/
