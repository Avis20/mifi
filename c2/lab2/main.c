#include <stdio.h>
#include <malloc.h>
#include <string.h>

typedef struct Item {
    char c;
    struct Item *next;
} Item;

int get_list(Item **);
void put_list(const char *, Item *);
Item *delete_list(Item *);
Item *new_str(Item *);
Item *del_space(Item *);
Item *skip_word(Item *);
Item *del_word(Item *);
void put_char(const char *msg, char *c);

int main(){
    Item *ptr = NULL;

    while ( puts("Enter string"), get_list(&ptr) ){
        put_list("Entered string", ptr);
        ptr = new_str(ptr);
        put_list("Result string", ptr);
        ptr = delete_list(ptr);
    }
    return 0;
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
    } while(n > 0);

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

