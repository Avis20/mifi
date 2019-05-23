#include <stdlib.h>
#include <malloc.h>

typedef struct item {
    int busy;       // Флаг что у эл. с этим ключем есть данные
    int key;        // Ключ по которому забираются данные
    int release;    // Версия эл.
    char *info;     // Сами данные
} Item;

typedef struct table {
    int SZ;         // Размер вектора (?)
    int n;          // Размер таблицы
    Item *first;    // Первый эл. (?)
    FILE *fd;       // Файл (?)
} Table;

int     D_Add(Table *);     // Добавление эл. в таблицу
int     D_Find(Table *);    // Поиск в таб
int     D_Delete(Table *);  // Удаление по ключу (?)
int     D_Show(Table *);    // Вывод таблицы на экран

int     dialog(const char *msgs[], int);
int     get_int(int *);

const char *msgs[] = {"0. Quit", "1. Add", "2. Find", "3. Delete", "4. Show"};
const int NMsgs = sizeof(msgs) / sizeof(msgs[0]);

int (*fptr[])(Table *) = {NULL, D_Add, D_Find, D_Delete, D_Show};

int main(){
    Table table = {0, 0, NULL, NULL};
    int rc;

    while(rc = dialog(msgs, NMsgs))
        if(!fptr[rc](&table))
            break;

    printf("See you next time...\n");

    return 0;
}

int dialog(const char *msgs[ ], int N){
    char *errmsg = "";
    int rc;
    int i, n;

    do {
        puts(errmsg);
        errmsg = "You are wrong. Repeat, please!";
        for (i = 0; i < N; ++i)
            puts(msgs[i]);
        
        puts("Make your choice: --> ");
        n = get_int(&rc);
        if (n == 0) rc = 0;
    } while(rc < 0 || rc >= N);

    return rc;
}


int get_int(int *number){
    int n;

    do {
        n = scanf("%d", number);
        if ( n < 0 ) return 0;

        if ( n == 0 ){
            printf("Error: Repeat input: ");
            scanf("%*[^\n]");
        }

    } while ( n == 0 );

    return 1;
}

int D_Add(Table *t){return 1;};
int D_Find(Table *t){return 1;};
int D_Delete(Table *t){return 1;};
int D_Show(Table *t){return 1;};
