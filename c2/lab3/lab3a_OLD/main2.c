#include <stdio.h>
#include<stdlib.h>
#include<string.h>

const char *msgs[] = {"0. Quit", "1. Add","2. Find", "3. Delete", "4. Show"};
const int NMsgs = sizeof(msgs) / sizeof(msgs[0]);
const int SIZE = 10;

typedef struct item {
    int busy;       // Флаг что у эл. с этим ключем есть данные
    int key;        // Ключ по которому забираются данные
    int release;    // Версия эл.
    char *info;     // Сами данные
    struct item *next; 
} Item;

typedef struct table {
    int size;       // Размер таблицы
    int curSize;    // Размер вектора (?)
    Item **first;   // Первый эл. таблицы
} Table;

int     D_Add(Table *);     // Добавление эл. в таблицу
int     D_Find(Table *);    // Поиск в таб
int     D_Delete(Table *);  // Удаление по ключу (?)
int     D_Show(Table *);    // Вывод таблицы на экран
int     D_Random(Table *);  // Наполнение рандомными данными

int     dialog(const char *msgs[], int);
int     getInt(int *a);
int     getHaskKey(int key);
char    *getInfoByKey(Table *ptab, int key);
char    *getStr();

int     insert(Table *ptab, int k, char *str);
int     find(Table *ptab, int k,    int hashKey);
int     printTable(Table *pTab);
int     delElem(Table *ptab, int key);
int     delTable(Table *ptab);

int main(void) {
    //Table table = {0, NULL}; // initialize table
    //Table table = {SIZE, 0, (Item *)calloc(SIZE, sizeof(Item))};
    Table table = {SIZE, 0, (Item **)calloc(SIZE, sizeof(Item *))};
    int rc;
    int (*fptr[])(Table *) = {NULL, D_Add, D_Find, D_Delete, D_Show};

    while (rc = dialog(msgs, NMsgs)) {
        printf("selected: %d\n", rc);
        if (!fptr[rc](&table)) {
            break;
        }
    }
    
    printf("See you next time...\n");
    delTable(&table);
    return 0;
}

int D_Add(Table *ptab) {
    int k, rc, n;
    char *info = NULL;

    printf("Enter key: -->");
    n = getInt(&k);
    if (n == 0) return 0;

    printf("Enter info:\n");
    info = getStr();

    printf("after enter string\n");
    if (info == NULL) return 0;

    rc = insert(ptab, k, info);
    printf("add status: %d", rc);
    //printf("%s: %d\n", errmsgs[rc], k);
    return 1;
}

int D_Find(Table *ptab) {
    int key;
    char *info;
    printf("Enter key: --> ");
    getInt(&key);

    info = getInfoByKey(ptab, key);
    printf("Result: %s\n", info);
    return 1;
}

int D_Delete(Table *ptab) {
    int key;
    printf("Enter key: -->");
    getInt(&key);
    if (delElem(ptab, key)) {
        printf("Delete successful\n");
    } else {
        printf("Delete not soccessful\n");
    }
    return 1;
}

int D_Show(Table *ptab) {
    // TODO Добавить описание что возвращается
    printTable(ptab);
    return 1;
}

int D_Random(Table *ptab){

    int max = 122, min = 97;
    for (int i = 0; i < SIZE; i++){
        int key = rand() % 20;

        char *val = (char *) malloc(sizeof(char) * 10);
        for (int j = 0; j < 10; j++){
            char v = rand() % (max - min + 1) + min;
            val[j] = v;
        }

        insert(ptab, key, val);
    }

    return 1;
};

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

int find(Table *ptab, int k, int hashKey) {
    Item *proc = ptab->first[hashKey];
    //printf("find proc: %d\t%s\n", proc->key, proc->info);
    while(proc) {
      //printf("key: %d value[0]: '%s'\n", proc->key, proc->info );
        if (proc->key == k) {
            return 1;
        }
        proc = proc->next;
    }

    return 0;
}

int getHashKey(int key) {
    return key % SIZE;
}

char *getStr(){
    char buf[21];
    int i = 0, n;
    char *s = NULL;
    do{
       while(EOF == scanf("%24[^\n]",buf)) 
         printf("Ошибка ввода! Повторите ввод: ");
       if(!i++) 
         s = (char *)calloc(sizeof(buf),sizeof(char));
       else
         s = (char *)realloc(s, i * sizeof(buf));
       strcat(s, buf);
    }while(!scanf("%1[\n]",buf));
    return s;
}

int printTable(Table *pTab){
    int i = 0, f = -1;
    char *data = NULL;
    Item *p = NULL;
    
    printf("Item:\tKey:\tValue:\n");
    for (i = 0; i < pTab->size; i++){
        if ( (p = pTab->first[i]) != NULL ){
            f = 0;
            printf("-----------------------------\n");
            while (p){
                printf("%d\t%d\t%s\n", i, p->key, p->info);
                p = p->next;        
            }
        } else {
            printf("-----------------------------\n");
            printf("%d\tNULL\n", i);
        }
    }
    return f;
}

int insert(Table *ptab, int k, char *str) {
    int hashKey = getHashKey(k);

    printf("find result: %d\n", find(ptab, k, hashKey));
    if (find(ptab, k, hashKey)) {
      printf("Error: Duplicate key: %d\n", k);
      return 1; // double key
    }
    if (ptab->curSize >= SIZE) {
      printf("Error: The table has reached a certain size: %d elements", SIZE);
      return 2;
    }

    Item *newItem = (Item *)malloc(sizeof(Item));
    newItem->key = k;
    newItem->info = str;

    if (ptab->first[hashKey]) {
      newItem->next = ptab->first[hashKey];
      ptab->first[hashKey] = newItem;
    } else {
      newItem->next = NULL;
      ptab->first[hashKey] = newItem;
    }
    (ptab->curSize)++;
    return 0;
}

char *getInfoByKey(Table *ptab, int key) {
    int hashKey = getHashKey(key);

    Item *proc = ptab->first[hashKey];
    //printf("find proc: %d\t%s\n", proc->key, proc->info);
    while(proc) {
      //printf("key: %d value[0]: '%s'\n", proc->key, proc->info );
      if (proc->key == key) {
          return proc->info;
      }
      proc = proc->next;
    }
    return "Element not Found";
}

int delElem(Table *ptab, int key) {
    int hashKey = getHashKey(key);
    Item **prev = NULL;
    Item *del, **tmp, *delItem;
    Item **list = &ptab->first[hashKey];

    while (*list) {
      printf("Key: %d\n", (*list)->key);
      if ((*list)->key != key) {
          list = &(*list)->next;
          continue;
      }
      if ((*list)->next) {
          tmp = &((*list)->next);
          del = &(**list);
          if (prev) {
            (*prev)->next = *tmp;
          } else {
            *list = *tmp;
          }
          free(del->info);
          free(del);
          return 1;
      } else {
          del = *list;
          free(del->info);
          free(del);
          if (prev) {
            (*list)->next = NULL;
          } else {
            *list = NULL;
          }
          return 1;
      }
      prev = &(*list);
      list = &(*list)->next;
    }
    return 0;
}

int delTable(Table *ptab) {
    Item *proc, *tmp, *del;
    for(int i=0; i < ptab->size; i++) {
      proc = ptab->first[i];
      //printf("del row %i\n", i);
      tmp = proc;
      while (tmp) {
          //printf("\tdelItem %i\n", tmp->key);
          del = tmp;
          tmp = del->next;
          free(del->info);
          free(del);
      }
    }
    return 0;
}