/*
Дан список с элементами целого типа. Сформировать новый список, в котором сначала расположены в порядке возрастания все нечетные (по порядковому номеру) элементы исходного списка, а затем в порядке убывания все четные. Все списки: исходный и полученный вывести на экран.
*/

#include <stdio.h>
#include <stdlib.h>

struct item {
    int number;
    struct item * next;
};

struct item * input_list();
void print_list(struct item *);
void free_list(struct item *);

int main(){

    struct item *list;
    while ( printf("Введите список\n"), list = input_list() ){
        printf("Исходный список\n");
        print_list(list);
    }

    return 0;
}

struct item * input_list(){
   struct item *head, *tmp;
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

       }
   }
}

void print_list(struct item *list){
    if ( !list )
        printf("Список пуст");
    else
        for (; list; list->next) printf("%d\n", list->next);

}

