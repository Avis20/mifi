#include <stdio.h>
#include <malloc.h>
#include <string.h>
#include <time.h>
#include <stdlib.h>
#include <limits.h>

typedef struct Tree { // структура для представления узлов дерева
    int key;
    char height;
    struct Tree* left;
    struct Tree* right;
    char* info;
} Tree;

int Exit(Tree**);       // функция выхода
int Menu(Tree**);       // меню
int Random(Tree**);     // генерация рандомных значений в дереве
int Input(Tree**);      // ввод строк
int Deletion(Tree**);   // удаление элемента из дерева
int Print(Tree**);      // вывод дерева в виде дерева
int Find(Tree**);       // поиск элемента в дереве
int FindMax(Tree**);    // поиск ближайшего элемента дерева
int Save(Tree**);       // запись в файл

//функции работы с деревом
Tree *Create();                                // создание дерева
Tree *TreeCreate();                            // функция создания пустого дерева
void TreePrint(Tree* T);                       // вывод дерева
void TreeDelete(Tree* T);                      // удаление текста
int TreeAddKey(Tree** T, int key, char* info); // добавление элемента с ключом в дерево
Tree *TreeFindKey(Tree* T, int key);                      //поиск ключа, возвращает указатель на дерево с ключом
Tree *TreeFindMaxKey(Tree* T);                        //поиск ключа, возвращает указатель на дерево с ключом
char *TreeFindKeyStr(Tree* T, int key);                   //поиск ключа, возвращает указатель на строку информации
int TreeDeleteKey(Tree** T, int key);                   //удаление ключа из дерева
void TreeDeleteItem(Tree* T, int);                       //удаление узла из дерева
Tree *TreeRead(FILE* F);                                  //чтение дерева
void TreeSave(Tree*, FILE* F);                           //запись в файл
void NodePrint(Tree* T, int sp); // вывод узла


//функции балансировки
char    height(Tree* p);
int     bfactor(Tree* p);
void    fixheight(Tree* p);
Tree*   rotateright(Tree* p);
Tree*   rotateleft(Tree* q);
Tree*   balance(Tree* p);
Tree*   insert(Tree* p, int k, char* info);
Tree*   findmin(Tree* p);
Tree*   removemin(Tree* p);
Tree*   removekey(Tree* p, int k);

//другие функции
int getInt(int* num);
int getStr(char** str);
int getStrF(FILE* F, char** s);
char *copyStr(char* s);

char *msgs[] = {
    "Exit",
    "Print menu",
    "Print tree",
    "Input item",
    "Delete item",
    "Find item",
};

int main() {
    srand((unsigned int)time(NULL));

    Tree* T = NULL;
    int ex = 0;
    int choice = 0;                                         //далее до конца - вывод меню

    const int amount = sizeof(msgs) / sizeof(msgs[0]);          //количество функций
    for (int i = 0;i<amount;++i)
        printf("%d %s\n", i, msgs[i]);
    int(*func[]) (Tree**) = {Exit, Menu, Print, Input, Deletion, Find};

    while (!ex)
    {                                                       //цикл выбора пукнта
        printf("\nMake your choice:  ");
        getInt(&choice);
        while (choice < 0 || choice >= sizeof(msgs) / sizeof(msgs[0]))      //пока не ввели корректный номер пункта
            getInt(&choice);
        ex = (*func[choice])(&T);                           //смотрим значение, которое вернула фукнкция
    }
    return 0;
}

int Exit(Tree** T){
    TreeDelete(*T);
    return 1;
}

int Print(Tree** T){
    puts("Tree:");
    TreePrint(*T);
    return 0;
}

int Menu(Tree** T){
    const int amount = sizeof(msgs) / sizeof(msgs[0]);
    puts("Menu:");
    for (int i = 0; i<amount; ++i)
        printf("%d %s\n", i, msgs[i]);
    return 0;
}

int Random(Tree** T)
{                                                           //добавление случайных элементов
    puts("Enter amount:");
    int amount = 0;                                         //количество добавляемых элементов
    getInt(&amount);
    int count = 0;
    for (int i = 0;i < amount; i++)                         //цикл добавления
    {
        int length = rand() % 10 + 1;
        char* str = (char*)calloc(length + 1, sizeof(char));
        for (int j = 0; j < length; ++j)                    //генерируем случайную строку
            str[j] = 'a' + rand() % 26;
        if (TreeAddKey(T, rand() % 40, str))                //при неудачном не учитываем
            free(str);
        else
            ++count;
    }
    printf("Added %d keys\n", count);
    return 0;
}

int Input(Tree** T)                                             //добавление ключа
{
    puts("Enter key:");
    int key = 0;
    getInt(&key);
    puts("Enter info: ");
    char* info = NULL;
    getStr(&info);
    if (TreeAddKey(T, key, info)){
        free(info);
        puts("Key exist.");
    } else {
        puts("Key added.");
    }
    return 0;
}

int Deletion(Tree** T){
    puts("Enter key:");
    int key = 0;
    getInt(&key);
    if (TreeDeleteKey(T, key))
        puts("Item deleted.");
    else
        puts("Item not found.");                            //если не успешно
    return 0;
}


int Find(Tree** T){
    puts("Enter key:        ");
    int key = 0;
    getInt(&key);                                               //чтение ключа из входного потока
    char* str;
    if (str = TreeFindKeyStr(*T, key))
    {                           //если поиск успешен
        printf("key: %d info: %s.\n", key, str);
        free(str);
    }
    else
        puts("Item not found.");
    return 0;
}

int FindMax(Tree** T){
    Tree* R;
    if (R = TreeFindMaxKey(*T)){
        printf("key: %d info: %s\n", R->key, R->info);
        free(R->info);
        free(R);
    } else {
        puts("Key not found.");
    }
    return 0;
}

Tree* Create(){
    puts("Enter 1 to read from file, else to create new tree"); //просим ввести 1, чтобы считать из файла, иначе - чтение из входного потока
    int f = 1;
    getInt(&f);
    Tree* T;
    if (f)
    {
        FILE* F = NULL;
        char* FilePath;
        puts("Enter path to file:");                                //попытка открыть файл
        getStr(&FilePath);
        F = fopen(FilePath, "r");
        if (F == NULL)
        {
            puts("File not found");                         //если файл не нашли, то срздадим пустое дерево
            T = NULL;                               //основное дерево
        }
        else
        {
            T = TreeRead(F);                                //если файл нашли - считали из файла
            fclose(F);
            puts("File read");
        }
    }
    else
        T = NULL;                               //пустое дерево
    return T;
}


int Save(Tree** T)
{
    FILE* F = NULL;
    char* FilePath;
    puts("Enter path to file:");
    getStr(&FilePath);
    F = fopen(FilePath, "w+");                              //создаём файл в режиме запись + чтение
    puts("New file created.");
    TreeSave(*T, F);                                            //сохранение
    fclose(F);
    puts("File saved.");
    return 0;
}



//работа с деревом/////////////////////////////////////////

//создаие дерева. В корне лежит элемент с INT_MIN далее все элементы добавляются в правое поддерево
//это сделано для того, чтобы добавление и удаление корневого элемента не отличалось от удаления/добавлния элемнта
//из листьев

Tree* TreeCreate(int key, char* info)
{
    Tree* T = (Tree*)calloc(1, sizeof(Tree));                   //выделяем память под корень
    if (T)
    {
        T->key = key;                                       //заполняем поля
        T->left = T->right = NULL;
        T->info = info;
    }
    return T;
}

//добавление ключа
int TreeAddKey(Tree** T, int key, char* info)
{
    Tree* T2 = TreeFindKey(*T, key);
    if (T2 != NULL)
    {
        return 1;
    }
    *T = insert(*T, key, info);
    return 0;
}


char height(Tree* p)
{
    return p ? p->height : 0;
}

int bfactor(Tree* p)
{
    return height(p->right) - height(p->left);
}

void fixheight(Tree* p)
{
    char hl = height(p->left);
    char hr = height(p->right);
    p->height = (hl>hr ? hl : hr) + 1;
}

Tree* rotateright(Tree* p) // правый поворот вокруг p
{
    Tree* q = p->left;
    p->left = q->right;
    q->right = p;
    fixheight(p);
    fixheight(q);
    return q;
}

Tree* rotateleft(Tree* q) // левый поворот вокруг q
{
    Tree* p = q->right;
    q->right = p->left;
    p->left = q;
    fixheight(q);
    fixheight(p);
    return p;
}

Tree* balance(Tree* p) // балансировка узла p
{
    fixheight(p);
    if (bfactor(p) == 2){
        if (bfactor(p->right) < 0)
            p->right = rotateright(p->right);
        return rotateleft(p);
    }

    if (bfactor(p) == -2){
        if (bfactor(p->left) > 0)
            p->left = rotateleft(p->left);
        return rotateright(p);
    }
    return p; // балансировка не нужна
}

Tree* insert(Tree* p, int k, char* info) // вставка ключа k в дерево с корнем p
{
    if (!p) return TreeCreate(k, info);
    if (k<p->key)
        p->left = insert(p->left, k, info);
    else
        p->right = insert(p->right, k, info);
    return balance(p);
}

Tree* findmin(Tree* p) // поиск узла с минимальным ключом в дереве p
{
    return p->left ? findmin(p->left) : p;
}

Tree* removemin(Tree* p) // удаление узла с минимальным ключом из дерева p
{
    if (p->left == 0)
        return p->right;
    p->left = removemin(p->left);
    return balance(p);
}

Tree* removekey(Tree* p, int k) // удаление ключа k из дерева p
{
    if (!p) return 0;
    if (k < p->key)
        p->left = removekey(p->left, k);
    else if (k > p->key)
        p->right = removekey(p->right, k);
    else //  k == p->key
    {
        Tree* q = p->left;
        Tree* r = p->right;
        free(p->info);
        free(p);
        if (!r) return q;
        Tree* min = findmin(r);
        min->right = removemin(r);
        min->left = q;
        return balance(min);
    }
    return balance(p);
}


//поиск ключа, возвращает значение указателя на узел дерева, к которому прикреплён лист с ключом
//или должен быть прикреплен лист с таки ключом
//это сделано для удобной вставки и удаления
Tree *TreeFindKey(Tree* T, int key){
    while (T)
        if (key > T->key)
            T = T->right;
        else if (key < T->key)
            T = T->left;
        else
            return T;
    return NULL;
}

//поиск возвращает список
char* TreeFindKeyStr(Tree* T, int key){
    T = TreeFindKey(T, key);
    if (T == NULL) return NULL;
    return copyStr(T->info);
}

Tree* TreeFindMaxKey(Tree* T){
    for (;T->right; T = T->right);
    Tree* R = (Tree*)calloc(1, sizeof(Tree));
    R->key = T->key;
    R->info = copyStr(T->info);
    return R;
}

//выводит дерево с помощью рекурсивной функции вывода
void TreePrint(Tree* T){
    if (T) NodePrint(T, 0);
}

//вывода узла дерева, помимо указателя на поддерево передаётс и значение sp - количество пробелов
//для отступа, чтобы при выводе дерево напоминало дерево
void NodePrint(Tree* T, int sp){
    if (T->right)
        NodePrint(T->right, sp + 2);            //рекурсивнй вызов вывода правого поддерева
    char* s = (char*)calloc(sp + 1, sizeof(char));
    memset(s, ' ', sp);
    printf("\n%s%d %s", s, T->key, T->info);
    free(s);
    if (T->left)
        NodePrint(T->left, sp + 2);         //и левого поддерева
}


//удаление ключа
int TreeDeleteKey(Tree** T, int key){
    Tree* T2 = TreeFindKey(*T, key);
    if (T2 == NULL) return 0;
    *T = removekey(*T, key);
    return 1;
}

void TreeDelete(Tree* T){
    if (T){
        TreeDelete(T->left);
        TreeDelete(T->right);
        free(T->info);
        free(T);
    }
}


void TreeSave(Tree* T, FILE* F){
    if (T){
        TreeSave(T->left, F);
        TreeSave(T->right, F);
        if (T->key != INT_MIN)
            fprintf(F, "%d\n%s\n", T->key, T->info);
    }
}

Tree* TreeRead(FILE* F){
    Tree* T = NULL;
    int key;
    fscanf(F, "%d", &key);
    char* info;
    getStrF(F, &info);
    while (!feof(F)){
        T = insert(T, key, info);
        fscanf(F, "%d", &key);
        getStrF(F, &info);

    }
    return T;
}

//прочие функции

int getInt(int *a){
    int n = scanf("%d", a); //считаем по адресу а - значение символа. сама функция вернёт -1, если конец файла, 0 если символ не корректный
    if (!n)                                                     // обнаружен некорректный символ - ошибка
        printf("%s\n", "Error! All incorrect symbols will be skiped.");
    while (n <= 0)
    {
        scanf("%*c");
        n = scanf("%d", a);
    }
    return 1;
}


int getStr(char** s)                                    //получаем строку из входного потока
{
    char buf[21];                                       //считываем из входного потока строку с помощью этого буфера, кусками по 20 сиволов
    int n;                                              //сюда будет записываться результат scanf
    int len = 0;                                        //сюда длина результирующей строки
    *s = (char *)malloc(1);                             //указатель на результирующую сткроу
    **s = '\0';                                         //ноль байт, пока строка имеет только конец строки
    do {
        n = scanf("%20[^\n]", buf);                     //считываем буфер
        if (n < 0)
        {                                               //если ввели конец файла (ctrl+Z), то будет -1
            free(*s);                                   //очищаем память, возвращаем пустой указатель
            return -1;
        }
        if (n > 0) {                                    //если буфер не пустой
            len += strlen(buf);                         //увеличиваем результирующую длину
            *s = (char *)realloc(*s, len + 1);          //добавляем память
            if (*s)                                     //если память выделилась
                strcat(*s, buf);                        //копируем строку из буфера в конец нашей строки
            else
            {                                           //если память не выделилась
                free(*s);                               //очищаем память
                return -2;
            }
        }
        else
            scanf("%*c");                               //если перенос строки, то очищаем входной поток
    } while (n > 0 || strlen(*s) == 0);                                 //пока во входном потоке есть хоть один символ
    return 0;
}


//тоже самое, только из файла
int getStrF(FILE* F, char** s)
{
    char buf[21];                                       //считываем из входного потока строку с помощью этого буфера, кусками по 20 сиволов
    int n;                                              //сюда будет записываться результат scanf
    int len = 0;                                        //сюда длина результирующей строки
    *s = (char *)malloc(1);                             //указатель на результирующую сткроу
    **s = '\0';                                         //ноль байт, пока строка имеет только конец строки
    fscanf(F, "%*c");
    do {
        n = fscanf(F, "%20[^\n]", buf);                 //считываем буфер
        if (n < 0)
        {                                               //если ввели конец файла (ctrl+Z), то будет -1
            free(*s);                                   //очищаем память, возвращаем пустой указатель
            return -1;
        }
        if (n > 0) {                                    //если буфер не пустой
            len += strlen(buf);                         //увеличиваем результирующую длину
            *s = (char *)realloc(*s, len + 1);          //добавляем память
            if (*s)                                     //если память выделилась
                strcat(*s, buf);                        //копируем строку из буфера в конец нашей строки
            else
            {                                           //если память не выделилась
                free(*s);                               //очищаем память
                return -2;
            }
        }
        else
            fscanf(F, "%*c");                               //если перенос строки, то очищаем входной поток
    } while (n > 0);                                    //пока во входном потоке есть хоть один символ
    return 0;
}


char *copyStr(char* s){
    char* res = (char*)calloc(strlen(s) + 1, sizeof(char));//выделяем память и копируем строки
    if (res) memcpy(res, s, strlen(s) + 1);
    return res;
}

