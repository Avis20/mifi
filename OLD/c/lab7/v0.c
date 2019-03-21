/*
Дан список с элементами целого типа. Сформировать новый список, в котором сначала расположены в порядке возрастания все нечетные (по порядковому номеру) элементы исходного списка, а затем в порядке убывания все четные. Все списки: исходный и полученный вывести на экран.
*/

#include <stdio.h>
#include <stdlib.h>

struct item {
    int number;
    struct item *next;
};

struct item * input_list();
struct item * sort_list(struct item *);
void print_list(struct item *);
void free_list(struct item *);
void work_list(struct item *, struct item **, struct item **);

int main(){

    struct item *list, *odd, *even, *result, **tmp;
    while ( printf("Введите список\n"), list = input_list() ){
        printf("Исходный список\n");
        print_list(list);
        work_list(list, &odd, &even);
        printf("Нечетный список\n");
        print_list(odd);
        printf("Четный список\n");
        print_list(even);
        odd = sort_list(odd);
        even = sort_list(even);
        printf("Сортированный нечетный список\n");
        print_list(odd);
        printf("Сортированный четный список\n");
        print_list(even);

        result = odd;
        *tmp = result;
        while ( (*tmp)->next != NULL ){
            *tmp = (*tmp)->next;
        }
        (*tmp)->next = even;

        printf("Итоговый список\n");
        print_list(result);
        free_list(result);
        free_list(list);
        free_list(odd);
        free_list(even);
    }

    return 0;
}

struct item * input_list(){
   struct item *head, *tmp, *current;
   int n;
   do {
       printf("Введите кол-во элементов\n");
       scanf("%d", &n);
   } while ( n < 0 );

   head = NULL;
   while ( n-- > 0 ){
       tmp = malloc( sizeof(struct item) );
       if (!tmp){
           free_list(head);
           head = NULL;
           break;
       }
       printf("Введите элемент списка\n");
       scanf("%d", &tmp->number);
       tmp->next = NULL;
       if (!head){
           head = tmp;
       } else {
           current->next = tmp;
       }
       current = tmp;
   }
   return head;
}

void print_list(struct item *list){
    if ( !list ){
        printf("Список пуст");
    } else {
        for (; list; list = list->next) printf("%d\n", list->number);
    }
}

void free_list (struct item *list){
    if (list){
        free_list(list->next);
        free(list);
    }
}

void work_list(struct item *list, struct item **odd, struct item **even){
    if ( !odd || !even ) return;
    *odd = *even = NULL;
    for (; list; list = list->next ){
        if ( list->number % 2 ){
            *odd = malloc(sizeof(struct item));
            (*odd)->number = list->number;
            (*odd)->next = NULL;
            odd = &(*odd)->next;
        } else {
            *even = malloc(sizeof(struct item));
            (*even)->number = list->number;
            (*even)->next = NULL;
            even = &(*even)->next;
        }
    }
}

struct item * sort_list(struct item *list){
    struct item *result = NULL;
    while ( list != NULL ){
        struct item *tmp = list;
        list = list->next;
        if ( result == NULL || tmp->number > result->number ){
            tmp->next = result;
            result = tmp;
        } else {
            struct item *current = result;
            while (current->next != NULL && !( tmp->number > current->next->number )){
                current = current->next;
            }
            tmp->next = current->next;
            current->next = tmp;
        }
    }
    return result;
}


/*
struct item * split_list(struct item *, struct item *);

struct item *split_list(struct item *odd, struct item *even){
    struct item *result, **tmp;
    result = odd;
    *tmp = result;
    while ( (*tmp)->next != NULL ){
        *tmp = (*tmp)->next;
    }
    (*tmp)->next = even;
    return result;
}
*/