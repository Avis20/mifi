#include <stdlib.h>
#include <stdio.h>

struct addr {
    char name[40];
    char street[40];
    char city[40];
    char state[3];
    char zip[10];
};

struct addr *get_struct(void){
    struct addr *p;
    if (!(p=(struct addr *)malloc(sizeof(addr)))) {
        printf("Allocation error.");
        exit(0);
    }
    return p;
}

int main(){
    addr *test = get_struct();
    test->name[0] = 's';
}