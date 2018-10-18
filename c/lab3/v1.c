/*
Дана последовательность из n целых элементов. Сформировать две новых последовательности, состоящих соответственно из положительных и отрицательных элементов исходной последовательности. Элементы в результирующих последовательностях должны быть отсортированы по убыванию. Все последовательности: исходную и полученные вывести на экран.
*/

#include <stdio.h>
#define N 100

int input(int[], int);
void output(int[], int);
void sort(int[], int);
int make(int[], int[], int, int);

int main(){

    int arr[N], n, input_count;
    int pos[N], neg[N], count_pos, count_neg;
    // int arr[5] = {-1,2,-3,4,-5}, input_count = 5;

    while (1){
    input_count = input( arr, N );
    if ( input_count <= 0 ) break;
        output(arr, input_count);
        sort(arr, input_count);
        count_pos = make(arr, pos, input_count, 1);
        if ( count_pos > 0 ) output(pos, count_pos);
        count_neg = make(arr, neg, input_count, 0);
        if ( count_neg > 0 ) output(neg, count_neg);
    }

    return 0;
}

int input(int arr[], int len){
    int i, count;

    printf("Введите кол-во элементов: ");
    scanf("%d", &count);

    for (i = 0; i < count; i++){
        printf("%d элемент = ", i);
        scanf("%d", &arr[i]);
    }

    return count;
}

void output(int arr[], int count){
    int i;
    
    printf("Массив:\n");
    for (i = 0; i < count; i++){
        printf(" %d", arr[i]);
    }
    printf("\n");
}

void sort(int arr[], int count){
    int i, j, tmp;
    for(i = 1; i < count; i++){
        for(j = 0; j < count - 1; j++){
            if ( arr[j] > arr[j+1] ){
                tmp = arr[j];
                arr[j] = arr[j+1];
                arr[j+1] = tmp;
            }
        }
    }
}

int make(int arr[], int arr2[], int count, int param){
    int i, count2 = 0;

    for(i = 0; i < count; i++){
        if ( arr[i] > 0 == param){
            arr2[count2++] = arr[i];
        }
    }

    return count2;
}