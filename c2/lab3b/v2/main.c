#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <malloc.h>

const char *msgs[] = {"0. Quit", "1. Add", "2. Find", "3. Delete", "4. Random", "5. Show"};
const int NMsgs = sizeof(msgs) / sizeof(msgs[0]);
const int SIZE = 10;
const int DEBUG = 1;

typedef struct item {
    int key;        // Ключ по которому забираются данные
    int release;    // Версия эл.
    int size;       // Размер строки
    char *info;     // Сами данные
    int offset;     // Смещение в файле
    struct item *next;
} Item;

typedef struct table {
    int size;           // Размер таблицы
    Item **list;        // Список эл. таблицы
    FILE *file;         // Файловый дескриптор
    char *filename;     // путь до файла
} Table;

int     D_Add(Table *);     // Добавление эл. в таблицу
int     D_Find(Table *);    // Поиск в таб
int     D_Delete(Table *);  // Удаление по ключу (?)
int     D_Show(Table *);    // Вывод таблицы на экран
int     D_Random(Table *);  // Наполнение рандомными данными

int     dialog(const char *msgs[], int);
int     getInt(int *);
char *  getStr();
char *  addExtension(char *, char *);

int     insert(Table *, int, char *);
int     getHashKey(int, int);

int     printTable(Table *);

void    open(Table *);
void    load(Table *);
void    close(Table *);
char *  readData(FILE *, Item *, char *);
int     writeData(FILE *, char *, int);

int (*fptr[])(Table *) = {NULL, D_Add, D_Find, D_Delete, D_Random, D_Show};

int main(){
    Table table = {0, NULL, NULL, NULL};
    int rc;

    open(&table);

    while ( rc = dialog(msgs, NMsgs) )
        if ( !fptr[rc](&table) )
            break;

    printf("See you next time...\n");
    // delTable(&table);
    return 0;
}

void open(Table *ptab){
    printf("Enter file name: ");

    ptab->filename = getStr();
    char *filenameData = addExtension(ptab->filename, ".data");

    if ( ptab->file = fopen(ptab->filename, "r+b") ){
        printf("File is loaded!\n");
        load(ptab);
        fclose(ptab->file);
        ptab->file = fopen(filenameData,"r+b");
    } else {
        printf("Enter size of table: ");
        getInt(&ptab->size);
        ptab->list = (Item **) calloc(ptab->size, sizeof(Item *));
        
        printf("File is created!\n");
        ptab->file = fopen(filenameData,"w+b");
    }

    free(filenameData);
}

void load(Table *ptab){
    int count = 0;
    Item *current = NULL, *last = NULL;  
    
    fread(&ptab->size, sizeof(int), 1, ptab->file);
    
    ptab->list = (Item **) calloc(ptab->size, sizeof(Item *));   

    for (int i = 0; i < ptab->size; count = 0,  i++){
        fread(&count, sizeof(int), 1, ptab->file);
        
        while (--count >= 0){
            current = (Item *) calloc(1, sizeof(Item));

            fread(&current->key, sizeof(int), 1, ptab->file);
            fread(&current->size, sizeof(int), 1, ptab->file);
            fread(&current->offset, sizeof(int), 1, ptab->file);
    
            if (ptab->list[i] == NULL){
                ptab->list[i] = current;
            } else {
                last->next = current;
            }
    
            last = current;
        }
    }
}

char * addExtension(char *filename, char *extension){
    char *tmp = (char *) calloc( strlen(filename) + strlen(extension) + 1, sizeof(char) );
    strcpy(tmp, filename);
    strcat(tmp, extension);
    return tmp;
}

int dialog(const char *msgs[], int N){
    char *errmsg = "";
    int rc;
    int i, n;

    do {
        puts(errmsg);
        errmsg = "You are wrong. Repeat, please!";
        for (i = 0; i < N; ++i)
            puts(msgs[i]);
        
        puts("Make your choice: --> ");
        n = getInt(&rc);
        if (n == 0) rc = 0;
    } while (rc < 0 || rc >= N);

    return rc;
}

int D_Add(Table *ptab) {
    int k, rc, n;
    char *info = NULL;
    
    printf("Enter key: -->\n");
    n = getInt(&k);

    if (n == 0) return 0;

    printf("Enter info:\n");
    info = getStr();

    if (DEBUG) printf("[DEBUG] after enter string\n");
    if (info == NULL) return 0;

    rc = insert(ptab, k, info);
    printf("add status: %d", rc);
    
    return 1;
}

int D_Find(Table *ptab){
    return 1;
};

int D_Delete(Table *ptab){
    return 1;
}

int D_Random(Table *ptab){
    return 1;
};

int D_Show(Table *ptab) {
    return 1;
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
    char buf[21], *s = NULL;
    int i = 0, n;

    do {
        while ( scanf("%24[^\n]",buf) == EOF ){
            printf("Error: repeat input: ");
        }

        if ( !i++ ){
            s = (char *) calloc(sizeof(buf),sizeof(char));
        } else{
            s = (char *) realloc(s, i * sizeof(buf));
        }

        strcat(s, buf);
    } while( !scanf("%1[\n]",buf) );
    
    return s;
}

int insert (Table *ptab, int key, char *str) {

    if (ptab->size >= SIZE) {
        printf("Error: The table has reached a certain size: %d elements", SIZE);
        return 2;
    }

    int hashKey = getHashKey(key, ptab->size);
    Item *newItem = NULL, *tmp = NULL;

    newItem = (Item *) calloc(1, sizeof(Item));
    newItem->key = key;
    newItem->size = strlen(str) + 1;
    newItem->offset = writeData(ptab->file, str, newItem->size);
    newItem->next = ptab->list[hashKey];
    ptab->list[hashKey] = newItem;
    
    (ptab->size)++;
    return 0;
}

int getHashKey(int key, int size) {
    return key % size;
}

int find(Table *ptab, int k, int hashKey) {
    return 0;
}

int printTable(Table *pTab){
    int i = 0, f = -1;
    char *data = NULL;
    Item *p = NULL;
    
    printf("Item:\tKey:\tValue:\n");
    for (i = 0; i < pTab->size; i++){
        if ( (p = pTab->list[i]) != NULL ){
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

char *getInfoByKey(Table *ptab, int key) {
    return "Element not Found";
}

int writeData(FILE *file, char *data, int size){
    int offset = 0;
    fseek(file, 0, SEEK_END);
    offset = ftell(file);
    fwrite(data, sizeof(char), size, file);
    return offset;
}
