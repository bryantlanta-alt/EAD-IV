#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define SIZE 10

void bubbleSort(int arr[], int n) {
    int i, j, temp;
    for (i = 0; i < n - 1; i++) {
        for (j = 0; j < n - i - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
}

void selectionSort(int arr[], int n) {
    int i, j, min_idx, temp;
    for (i = 0; i < n - 1; i++) {
        min_idx = i;
        for (j = i + 1; j < n; j++) {
            if (arr[j] < arr[min_idx]) {
                min_idx = j;
            }
        }
        temp = arr[min_idx];
        arr[min_idx] = arr[i];
        arr[i] = temp;
    }
}

void insertionSort(int arr[], int n) {
    int i, key, j;
    for (i = 1; i < n; i++) {
        key = arr[i];
        j = i - 1;
        while (j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j];
            j = j - 1;
        }
        arr[j + 1] = key;
    }
}

void printArray(int arr[], int size) {
    for (int i = 0; i < size; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

int main() {
    int original[SIZE];
    int arr[SIZE];
    int i;

    srand(time(NULL));
    for (i = 0; i < SIZE; i++) {
        original[i] = rand() % 100;
    }

    printf("Original: ");
    printArray(original, SIZE);

    for (i = 0; i < SIZE; i++) arr[i] = original[i];
    bubbleSort(arr, SIZE);
    printf("Bubble Sort: ");
    printArray(arr, SIZE);

    for (i = 0; i < SIZE; i++) arr[i] = original[i];
    selectionSort(arr, SIZE);
    printf("Selection Sort: ");
    printArray(arr, SIZE);

    for (i = 0; i < SIZE; i++) arr[i] = original[i];
    insertionSort(arr, SIZE);
    printf("Insertion Sort: ");
    printArray(arr, SIZE);

    return 0;
}