/* Задача
Из входного потока вводится произвольное число строк. Длина строки не ограничена. Каждая строка содержит последовательность слов, разделенных пробелами и/или знаками табуляции. Строка представлена списком (первое поле элемента списка - символ строкиж второе - указатель на следующий элемент списка или NULL в конце списка). Конец ввода определяется концом файла.

---1. Для каждой строки сформировать новую строку, поместив в нее каждое второе слово исходной последовательности. Слова в новой строке должны быть разделены только одним пробелом. Полученную строку вывести в выходной поток.

########################################################
2. Для каждой строки сформировать новую строку, поместив в нее группу символов исходной строки, расположенных между двумя заданными символами, первый их которых является первым символом строки, вторым - последний символ. Пробелы в исходной строке игнорировать. Выделенные группы разделить одним пробелом. Полученную строку вывести на экран.
########################################################

# Примечания

a. Каждая строка представлена списком; первое поле элемента списка - символ строки: второе - указатель на следующий эл. списка или NULL в конце списка; список результата формировать, модифицируя исходный список.

b. Ввод строк должен быть организован с помощью функции scanf() со спецификациями для ввода строк. Функцию getchar() или спецификацию %c в scanf() не использовать!

c. Логически законченные части алгоритма решения задачи должны быть оформлены отдельными функциями с параметрами (например, пропуск разделителей, создание списка, вывод списка и т.п.)

d. Целесообразно обработку строк оформить соответствующей функцией, тогда в функции main должны быть ввод строки, вызов функции обработки, вывод результата - в цикле, пока не закончиться ввод, конец цикла - по достижению конца файла.

e. Все функции должны работать со списком; при вводе строки следует сразу создавать список.

*/

#include <stdio.h>
#include <malloc.h>
#include <string.h>

typedef struct item {
    char c;
    struct item *next;
} Item;

int get_list(Item **);
void put_list(const char *, Item *);
Item *delete_list(Item *);
Item *new_str(Item *);
Item *del_space(Item *);
Item *skip_word(Item *);
Item *del_word(Item *);
int get_char(char *c);
void put_char(const char *, char c);
Item *work(Item *, char, char);

int main(){
    Item *ptr = NULL;
    char first_char, last_char;

    while ( puts("\nEnter string"), get_list(&ptr) ){

//        puts("Enter first character");
//        get_char(&first_char);

//        puts("Enter last character");
//        get_char(&last_char);

//        put_char("Entered first char", first_char);
//        put_char("Entered last char", last_char);

//        put_list("Entered string", ptr);
          put_list("Entered string", ptr);

//        ptr = work(ptr, first_char, last_char);
//        // ptr = new_str(ptr);
//        // put_list("Result string", ptr);
//        ptr = delete_list(ptr);

    }

    printf("See you next time...\n");
    return 0;
}

Item *work(Item *ptr, char f, char l){

/*
   Item head = {'*', ptr}, *cur = &head;
    int fl = 0;

    while (cur && (cur->next = del_space(cur->next))){
        if ( cur->c == f ){

        } else {
            cur = cur->next;
        }
    }

    if (prev->next){
        free(prev->next);
        prev->next = NULL;
    }
*/
    
//    return head.next;
}

Item *new_str(Item *p){
    Item head = {'*', p};
    Item *cur = &head, *prev = &head;
    int fl = 0;
    while(cur && (cur->next = del_space(cur->next))){
        if (fl){
            cur = skip_word(cur->next);
            prev = cur;
            cur = cur->next;
            if (cur){
                cur->c = ' ';
            }
        } else {
            cur->next = del_word(cur->next);
        }

        fl = !fl;
    }

    if(prev->next){
        free(prev->next);
        prev->next = NULL;
    }
    return head.next;
}

int get_char(char *c){
    int n;
    char enter;

    do {
        n = scanf("%c", c);
        if ( n < 0 ) return 0;

        if ( n == 0 ){
            printf("Error: Repeat input: ");
            n = scanf("%*c");
        }
    } while ( n == 0 );
    
    scanf("%c", &enter);
    return 1;
}


void put_char(const char *msg, char c){
    printf("%s: %c\n", msg, c);
}

int get_list(Item **pptr){
    char buf[21], *str;
    Item head = {'*', NULL};
    Item *last = &head;
    int n, rc = 1;
    do {
        n = scanf("%20[^\n]", buf);

        if (n < 0) {
            delete_list(head.next);
            head.next = NULL;
            rc = 0;
            continue;
        }

        if (n > 0) {
            for(str = buf; *str != '\0'; ++str){
                last->next = (Item *) malloc(sizeof(Item));
                last = last->next;
                last->c = *str;
            }
            last->next = NULL;
        } else {
            scanf("%*c");
        }
    } while (n > 0);

    *pptr = head.next;
    return rc;
}

void put_list(const char *msg, Item *ptr){
    printf("%s: \"", msg);
    for (; ptr != NULL; ptr = ptr->next){
        printf("%c", ptr->c);
    }

    printf("\"\n");
}

Item *delete_list(Item *ptr){
    Item *tmp = NULL;
    while (ptr != NULL){
        tmp = ptr;
        ptr = ptr->next;
        free(tmp);
    }
    return ptr;
}


Item *del_space(Item *p){
    Item *tmp;
    while(p && (p->c == ' ' || p->c == '\t')){
        tmp = p;
        p = p->next;
        free(tmp);
    }
    return p;
}

Item *skip_word(Item *p){
    while(p->next && p->next->c != ' ' && p->next->c != '\t'){
        p = p->next;
    }
    return p;
}

Item *del_word(Item *p){
    Item *tmp;
    while(p && p->c != ' ' && p->c != '\t'){
        tmp = p;
        p = p->next;
        free(tmp);
    }
    return p;
}

