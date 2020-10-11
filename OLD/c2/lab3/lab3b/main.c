#include <stdio.h>
#include <stdlib.h>
#include <string.h>

const char *msgs[] = {"0. Quit", "1. Add","2. Find", "3. Delete", "4. Show"};
const int NMsgs = sizeof(msgs) / sizeof(msgs[0]);
const int DEBUG = 1;

typedef struct item {
    int busy;       // Флаг что у эл. с этим ключем есть данные
    int key;        // Ключ по которому забираются данные
    int size;
    int offset;
} Item;

typedef struct table {
    int size;       // Размер таблицы
    Item **first;   // Первый эл. таблицы
    char *filename;
    FILE *file;
} Table;

// dialog
int     dialog(const char *msgs[], int);
int     D_Add(Table *);     // Добавление эл. в таблицу
int     D_Find(Table *);    // Поиск в таб
int     D_Delete(Table *);  // Удаление по ключу
int     D_Show(Table *);    // Вывод таблицы на экран

// table
int     insert(Table *, int, char *);
int     printTable(Table *);
char    *find(Table *, int);
int     delElem(Table *, int);
int     delTable(Table *);

// support
int     getInt(int *);
char    *getStr();
int     getHashKey(int, int);

// file
char    *add_extension(char *, char *);
char    *read_data(FILE *, Item *, char *);
int     write_data(FILE *, char *, int);
void    open(Table *);
void    load(Table *);
void    close(Table *);

// DELETE
void init(Table *);

int main() {
    // Table table = { ptab->size, (Item **) calloc(ptab->size, sizeof(Item *)) };
    Table table = {0, NULL, NULL, NULL};
    int rc;
    int (*fptr[])(Table *) = {NULL, D_Add, D_Find, D_Delete, D_Show};
    
    open(&table);
    // init(&table);

    while (rc = dialog(msgs, NMsgs)) {
        printf("selected: %d\n", rc);
        if (!fptr[rc](&table)) {
            break;
        }
    }

    printf("See you next time...\n");

    close(&table);
    // delTable(&table);
    return 0;
}

void close(Table *ptab){
    int i = 0, count = 0, offset = 0;
    Item *current = NULL, *p = NULL;
    fclose(ptab->file);

    ptab->file = fopen(ptab->filename,"w+b");
    fwrite(&ptab->size, sizeof(int), 1, ptab->file);

    for (i = 0; i < ptab->size; count = 0, i++){
        p = ptab->first[i];
    
        fseek(ptab->file, 0, SEEK_END);
        offset = ftell(ptab->file);
        fwrite(&count, sizeof(int), 1, ptab->file);

        if (p){
            count = count + 1;
            fwrite(&p->key, sizeof(int), 1, ptab->file);
            fwrite(&p->busy, sizeof(int), 1, ptab->file);
            fwrite(&p->size, sizeof(int), 1, ptab->file);
            fwrite(&p->offset, sizeof(int), 1, ptab->file);

            free(p);
        }

        fseek(ptab->file, offset, SEEK_SET);
        fwrite(&count, sizeof(int), 1, ptab->file);
    }
    fclose(ptab->file);

    free(ptab->filename);
    free(ptab->first);
}

void open(Table *ptab){
    char *filename_data = NULL;
    //system("cls");
    printf("Enter file name: ");

    ptab->filename = getStr();

    filename_data = add_extension(ptab->filename, ".data");
    if (ptab->file = fopen(ptab->filename, "r+b")){
        load(ptab);
        fclose(ptab->file);
        printf("File is loaded!\n");
        ptab->file = fopen(filename_data, "r+b");
    } else{ 
        printf("Enter size of table: ");
        getInt(&ptab->size);
        ptab->first = (Item **) calloc(ptab->size, sizeof(Item *));
        
        printf("File is created!\n");
        ptab->file = fopen(filename_data,"w+b");
    }

    free(filename_data);
}

void load(Table *ptab){
    int i = 0, count = 0;
    Item *current = NULL;
    
    fread(&ptab->size, sizeof(int), 1, ptab->file);
    ptab->first = (Item **) calloc(ptab->size, sizeof(Item *));

    for (i = 0; i < ptab->size; count = 0, i++){
        fread(&count, sizeof(int), 1, ptab->file);
        while (--count >= 0){
            current = (Item *) calloc(1, sizeof(Item));

            fread(&current->key, sizeof(int), 1, ptab->file);
            fread(&current->busy, sizeof(int), 1, ptab->file);
            fread(&current->size, sizeof(int), 1, ptab->file);
            fread(&current->offset, sizeof(int), 1, ptab->file);
    
            if (ptab->first[i] == NULL) ptab->first[i] = current;
        }
    }
}

void init(Table *ptab){

    int arr[] = {12, 48, 3, 5, 7, 63, 15, 202, 130};
    int size = sizeof(arr) / sizeof(arr[0]);
    for (int i = 0; i < size; ++i){
        insert(ptab, arr[i], "test");
    }
}

int dialog(const char *msgs[ ], int N){
    char *errmsg = "";
    int rc;
    int i, n;
    do {
        puts(errmsg);
        errmsg = "You are wrong. Repeat, please!";

        for(i = 0; i < N; ++i) {
            puts(msgs[i]);
        }
        puts("Make your choice: --> ");
        n = getInt(&rc);
        if (n == 0) {
            rc = 0;
        }
    } while (rc < 0 || rc >= N);
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

int D_Find(Table *ptab) {
    int key;
    char *info;
    printf("Enter key: --> ");
    getInt(&key);

    info = find(ptab, key);
    printf("Result: %s\n", info);
    return 1;
}

int D_Delete(Table *ptab){
    int key;
    printf("Enter key: -->\n");
    getInt(&key);
    
    if ( delElem(ptab, key) ) {
        printf("Delete successful\n");
    } else {
        printf("Delete not soccessful\n");
    }

    return 1;
}

int D_Show(Table *ptab) {
    printTable(ptab);
    return 1;
}

// ############ SUPPORT

int getHashKey(int key, int size) {
    return key % size;
}

int getInt(int *a){
    int n;
    do {
       n = scanf("%i", a);
       if (n < 0) return 0;

       if (n == 0){
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

char *find(Table *ptab, int key) {
    int hashKey = getHashKey(key, ptab->size);
    Item *p = NULL;
    char *data = NULL;
    int n = 0;

    while ( ( p = ptab->first[hashKey] ) && p->busy != -1 && n < ptab->size ){
        if ( p && p->key == key ){
            data = (char *) calloc(p->size, sizeof(char));
            data = read_data(ptab->file, p, data);
            return data;
        }
        hashKey = ( hashKey + 1 ) % ptab->size;
        n++;
    };
    return "Element not Found";
}

char *read_data(FILE *file, Item *node, char *data){
    fseek(file, node->offset, SEEK_SET);
    fread(data, sizeof(char), node->size, file);
    return data;
}

int printTable(Table *ptab){
    int i = 0;
    char *data = NULL;
    Item *p = NULL;

    if (DEBUG) printf("[DEBUG] ptab->size = %d\n", ptab->size);

    printf("Item:\tKey:\tBusy:\tValue:\n");
    for (i = 0; i < ptab->size; i++){
        if ( (p = ptab->first[i]) != NULL ){
            data = (char *) calloc(p->size, sizeof(char));
            data = read_data(ptab->file, p, data);
            printf("-----------------------------\n");
            printf("%d\t%d\t%d\t%s\n", i, p->key, p->busy, data);
            free(data);
        } else {
            printf("-----------------------------\n");
            printf("%d\t\tNULL\n", i);
        }
    }
    return 1;
}

int write_data(FILE *file, char *data, int size){
    int offset = 0;
    fseek(file, 0, SEEK_END);
    offset = ftell(file);
    fwrite(data, sizeof(char), size, file);
    return offset;
}

int insert (Table *ptab, int key, char *str) {
    int hashKey = getHashKey(key, ptab->size);
    Item *p = NULL;
    int n = 0;

    while ( ( p = ptab->first[hashKey] ) && p->busy != -1 && n < ptab->size ){
        hashKey = ( hashKey + 1 ) % ptab->size;
        n++;
    };

    if ( n < ptab->size ){
        Item *newItem = NULL;
        newItem = (Item *) calloc(1, sizeof(Item));
        newItem->key = key;
        newItem->busy = 1;
        newItem->size = strlen(str) + 1;
        newItem->offset = write_data(ptab->file, str, newItem->size);
        ptab->first[hashKey] = newItem;
    } else {
        printf("Error: The table has reached a certain size: %d elements\n", ptab->size);
        return 2;
    }

    return 0;
}

int delElem(Table *ptab, int key) {
    int hashKey = getHashKey(key, ptab->size);
    Item *p = NULL;
    int n = 0;

    while ( ( p = ptab->first[hashKey] ) && n < ptab->size ){
        if ( p && p->key == key ){
            p->busy = -1;
            return 1;
        }
        hashKey = ( hashKey + 1 ) % ptab->size;
        n++;
    };    
    return 0;
}

int delTable(Table *ptab){
    Item *p = NULL;

    for (int i = 0; i < ptab->size; i++){
        if ( (p = ptab->first[i]) != NULL ){
            free(p);
        }
    }
    return 1;
}

char *add_extension(char *filename, char *extension){
    char *tmp = (char *) calloc( strlen(filename) + strlen(extension) + 1, sizeof(char));
    strcpy(tmp, filename);
    strcat(tmp, extension);
    return tmp;
}
