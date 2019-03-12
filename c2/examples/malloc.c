#include <stdlib.h>
#include <stdio.h>

struct User {
    char name[9];
    int age;
};

struct User *init_user(){
    return (struct User)malloc(sizeof(User));
};

int main(){
    User *user = init_user();
    return 0;
}

