#include <stdio.h>

/* Примеры вопросов
*/

// 1.
// Элемент списка имеет след. структуру
struct Item {
    int k;
    struct Item *next;
};

int main(){
    struct Item a[5] = {
        {12, a + 3},
        {25, NULL},
        {38, a + 2},
        {47, a + 4},
        {20, a + 1}
    };

    struct Item *ptr = a;
    int n = 3;

    while ( n-- > 0 ){
        printf("%d; ", n);
        ptr = ptr->next;
    }

    printf("%d\n", ptr->k);
    return 0;
}
