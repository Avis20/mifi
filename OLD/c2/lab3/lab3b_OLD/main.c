#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <malloc.h>

const char *msgs[] = {"0. Quit", "1. Add", "2. Find", "3. Delete", "4. Random", "5. Show"};
const int NMsgs = sizeof(msgs) / sizeof(msgs[0]);
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
    close(&table);
    // delTable(&table);
    return 0;
}

void open(Table *pTab){
    printf("Enter file name: ");

    pTab->filename = getStr();
    char *filenameData = addExtension(pTab->filename, ".data");

    printf("%s; ", pTab->filename);
    if ( pTab->file = fopen(pTab->filename, "r+b") ){
        printf("File is loaded!\n");
        load(pTab);
        fclose(pTab->file);
        pTab->file = fopen(filenameData,"r+b");
    } else {
        printf("Enter size of table: ");
        getInt(&pTab->size);
        pTab->list = (Item **) calloc(pTab->size, sizeof(Item *));
        
        printf("File is created!\n");
        pTab->file = fopen(filenameData,"w+b");
    }

    free(filenameData);
}

void load(Table *pTab){
    int count = 0;
    Item *current = NULL, *last = NULL;  
    
    fread(&pTab->size, sizeof(int), 1, pTab->file);
    
    pTab->list = (Item **) calloc(pTab->size, sizeof(Item *));

    for (int i = 0; i < pTab->size; count = 0,  i++){
        fread(&count, sizeof(int), 1, pTab->file);
        
        while (--count >= 0){
            current = (Item *) calloc(1, sizeof(Item));

            fread(&current->key, sizeof(int), 1, pTab->file);
            fread(&current->size, sizeof(int), 1, pTab->file);
            fread(&current->offset, sizeof(int), 1, pTab->file);
    
            if (pTab->list[i] == NULL){
                pTab->list[i] = current;
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

int D_Add(Table *pTab) {
    int k, rc, n;
    char *info = NULL;
    
    printf("Enter key: -->\n");
    n = getInt(&k);

    if (n == 0) return 0;

    printf("Enter info:\n");
    info = getStr();

    if (DEBUG) printf("[DEBUG] after enter string\n");
    if (info == NULL) return 0;

    rc = insert(pTab, k, info);
    printf("add status: %d", rc);
    
    return 1;
}

int D_Find(Table *pTab){
    return 1;
};

int D_Delete(Table *pTab){
    return 1;
}

int D_Random(Table *pTab){
    return 1;
};

int D_Show(Table *pTab) {
    printTable(pTab);
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

int insert (Table *pTab, int key, char *str) {
    int hashKey = getHashKey(key, pTab->size);
    Item *newItem = NULL, *tmp = NULL;

    newItem = (Item *) calloc(1, sizeof(Item));
    newItem->key = key;
    newItem->size = strlen(str) + 1;
    newItem->offset = writeData(pTab->file, str, newItem->size);
    newItem->next = pTab->list[hashKey];
    pTab->list[hashKey] = newItem;
    
    (pTab->size)++;
    return 0;
}

int getHashKey(int key, int size) {
    return key % size;
}

int find(Table *pTab, int k, int hashKey) {
    return 0;
}

int printTable(Table *pTab){
    int i = 0, f = -1;
    char *data = NULL;
    Item *tmp = NULL;
    
    printf("Key:\tRelease:\tInfo:\n");
    for (i = 0; i < pTab->size; i++){
        if ( (tmp = pTab->list[i]) != NULL ){
            f = 0;
            printf("-----------------------------\n");
            while (tmp){
                data = (char *) calloc(tmp->size, sizeof(char));
                data = readData(pTab->file, tmp, data);

                printf("%d\t%d\t%s\n", i, tmp->key, data);
                tmp = tmp->next;        
                free(data);
            }
        } else {
            printf("-----------------------------\n");
            printf("%d\tNULL\n", i);
        }
    }
    return f;
}

char * getInfoByKey(Table *pTab, int key) {
    return "Element not Found";
}

int writeData(FILE *file, char *data, int size){
    int offset = 0;
    fseek(file, 0, SEEK_END);
    offset = ftell(file);
    fwrite(data, sizeof(char), size, file);
    return offset;
}

char * readData(FILE *file, Item *node, char *data){
    fseek(file, node->offset, SEEK_SET);
    fread(data, sizeof(char), node->size, file);
    return data;
}


void close(Table *pTab){
    int i = 0, count = 0, offset = 0;
    Item *del = NULL, *p = NULL;
    fclose(pTab->file);
    
    pTab->file = fopen(pTab->filename,"w+b");
    fwrite(&pTab->size, sizeof(int), 1, pTab->file);

    for(i = 0; i < pTab->size; count = 0, i++){
        p = pTab->list[i];
    
        fseek(pTab->file, 0, SEEK_END);
        offset = ftell(pTab->file);
        fwrite(&count, sizeof(int), 1, pTab->file);

        while(p){
            count = count + 1;
            fwrite(&p->key, sizeof(int), 1, pTab->file);
            fwrite(&p->size, sizeof(int), 1, pTab->file);
            fwrite(&p->offset, sizeof(int), 1, pTab->file);

            del = p;
            p = del->next;
            free(del);
        }

        fseek(pTab->file, offset, SEEK_SET);
        fwrite(&count, sizeof(int), 1, pTab->file);
    }
    fclose(pTab->file);

    free(pTab->filename);
    free(pTab->list);
}   
