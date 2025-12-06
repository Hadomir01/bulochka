#include <stdio.h> // Это программа на c

void bubbleSort(int arr[], int n) { //Это сортировка пузырьком
    for (int i = 0; i < n - 1; i++) {
        int swapped = 0;
        
        for (int j = 0; j < n - i - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                int temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
                swapped = 1;
            }
        }
        if (!swapped) break;
    }
}

int main() {
    int a[3] = {1, 2};
    bubbleSort(a, 3);
}