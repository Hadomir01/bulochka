#include <stdio.h>

int main() {
	int a;
	int count_0 = 0;
	int count_1 = 0;
	int i = 0;
	printf("Введите целое неотрицательное число: ");
	scanf("%d", &a);
	for (a, i, count_0, count_1; i != 32 ; i++) {
		if (((a>>i) & 1) == 0) {
			count_0 = count_0 + 1;
		} else {
			count_1 = count_1 + 1;
		}
	}
	printf("Нулевых битов: %d\n", count_0);
	printf("Единичных битов: %d\n", count_1);
}

int main() {
	int a;
	int i;
	printf("Введите целое неотрицательное число: ");
	scanf("%d", &a);

	printf("Биты на четных позициях: ");
	for (i=30, a; i >= 0; i=i-2) {
		if (((a>>i) & 1) == 0) {
			printf("0");
		} else {
			printf("1");
		}
		
	}
	printf("\n");
	printf("Биты на нечетных позициях: ");
	for (i = 31, a; i >= 1; i=i-2) {
		if (((a>>i) & 1) == 0) {
			printf("0");
		} else {
			printf("1");
		}
	}
	printf("\n");
}
