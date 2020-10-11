#include <stdio.h>
#include <stdlib.h>
#include <string.h>

const char *msgs[] = {"0. Quit", "1. Add","2. Find", "3. Delete", "4. Show"};
const int NMsgs = sizeof(msgs) / sizeof(msgs[0]);
const int SIZE = 10, DEBUG = 1;

typedef struct item {
    int busy;       // Флаг что у эл. с этим ключем есть данные
    int key;        // Ключ по которому забираются данные
    char *info;     // Сами данные
} Item;

typedef struct table {
    int size;       // Размер таблицы
    Item **first;   // Первый эл. таблицы
} Table;

int     D_Add(Table *);     // Добавление эл. в таблицу
int     D_Find(Table *);    // Поиск в таб
int     D_Delete(Table *);  // Удаление по ключу
int     D_Show(Table *);    // Вывод таблицы на экран

int     dialog(const char *msgs[], int);
int     getInt(int *a);
char    *getStr();
int     getHaskKey(int key);

int     insert(Table *, int, char *);
int     find(Table *, int, int);
int     printTable(Table *);
int     delElem(Table *, int);
int     delTable(Table *);

int main() {
    Table table = { SIZE, (Item **) calloc(SIZE, sizeof(Item *)) };
    int rc;
    int (*fptr[])(Table *) = {NULL, D_Add, D_Find, D_Delete, D_Show};

    while (rc = dialog(msgs, NMsgs)) {
        printf("selected: %d\n", rc);
        if (!fptr[rc](&table)) {
            break;
        }
    }
    
    printf("See you next time...\n");
    // delTable(&table);
    return 0;
}


int dialog(const char *msgs[ ], int N){
    char *errmsg = "";
    int rc;
    int i, n;
    do{
      puts(errmsg);
      errmsg = "You are wrong. Repeat, please!";

      for(i = 0; i < N; ++i) {
          puts(msgs[i]);
      }
      puts("Make your choice: --> ");
      n = getInt(&rc);
      if(n == 0) {
          rc = 0;
      }
    } while(rc < 0 || rc >= N);
    return rc;
}


int D_Add(Table *ptab) {
    int k, rc, n;
    char *info = NULL;

    printf("Enter key: --> ");
    n = getInt(&k);
    if (n == 0) return 0;

    printf("Enter info:\n");
    info = getStr();

    printf("after enter string\n");
    if (info == NULL) return 0;

    rc = insert(ptab, k, info);
    printf("add status: %d", rc);
    return 1;
}

int D_Find(Table *ptab) { return 1; };
int D_Delete(Table *ptab) { return 1; };

int D_Show(Table *ptab) {
    printTable(ptab);
    return 1;
}

// ############ SUPPORT

int getHashKey(int key) {
    return key % SIZE;
}

int getInt(int *a) {
    int n;
    do {
       n = scanf("%i", a);
       if (n < 0) return 0;

       if (n == 0) {
            printf("%s\n", "Error! Repeat input");
            scanf("%*c");
       }
    } while (n == 0);
    scanf("%*c"); // возможно лишнее
    return 1;
}

char *getStr(){
    char buf[21];
    int i = 0, n;
    char *s = NULL;
    
    do {
       while (scanf("%24[^\n]", buf) == EOF){
            printf("Ошибка ввода! Повторите ввод: ");
       } 

       if (!i++){
            s = (char *)calloc(sizeof(buf),sizeof(char));
       } else {
            s = (char *)realloc(s, i * sizeof(buf));
       }

       strcat(s, buf);
    } while (!scanf("%1[\n]",buf));

    return s;
}

int insert (Table *ptab, int key, char *str) {
    int hashKey = getHashKey(key);

    Item *p = ptab->first[hashKey];

    if ( p == NULL ){
        Item *newItem = NULL;
        newItem = (Item *) calloc(1, sizeof(Item));
        newItem->key = key;
        newItem->info = str;
        newItem->busy = 1;
        ptab->first[hashKey] = newItem;
        // (ptab->size)++;
    } else {
        // for (i = 0, p++ = ; i < ptab->size; i++){
    }

    return 0;
}

int printTable(Table *ptab){
    int i = 0;
    char *data = NULL;
    Item *p = NULL;
    
    if (DEBUG) printf("[DEBUG] ptab->size = %d\n", ptab->size);

    printf("Item:\tKey:\tBusy:\tValue:\n");
    for (i = 0; i < ptab->size; i++){
        if ( (p = ptab->first[i]) != NULL ){
            printf("-----------------------------\n");
            printf("%d\t%d\t%d\t%s\n", i, p->key, p->busy, p->info);
        } else {
            printf("-----------------------------\n");
            printf("%d\t\tNULL\n", i);
        }
    }
    return 1;
}
