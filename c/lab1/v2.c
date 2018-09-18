#include <stdoi.h>
// Попарно поменять местами цифры, начиная с верхнего порядка. Если пары нет, поменять на ноль.

int main(){
    int n, tmp;
    while (1){
		printf("Введите натуральное число n\n");
		scanf("%d", &n);
		//if ( n <= 0) break;
		while ( n > 0){
			tmp = n % 10;
			printf("%d", tmp);
			n /= 10;
		}
    }
    return 0;
}
