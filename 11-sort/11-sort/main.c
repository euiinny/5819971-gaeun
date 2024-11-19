#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define SIZE 100
#define ATTEMPTS 20

// 배열 출력 함수
void printArray(int arr[], int size) {
    for (int i = 0; i < size; i++) {
        printf("%d ", arr[i]);
        if ((i + 1) % 10 == 0);
    }
    printf("\n");
}

// 랜덤 데이터 생성 함수
void generateRandomData(int arr[]) {
    for (int i = 0; i < SIZE; i++) {
        arr[i] = rand() % 1000; // 0~999 사이의 난수
    }
}

// 선택 정렬 함수
void doSelectionSort(int arr[]) {
    printf("Selection Sort Process:\n");
    int temp[SIZE];
    for (int i = 0; i < SIZE; i++) temp[i] = arr[i]; // 원본 데이터 복사
    int temp_val, min_idx;

    for (int i = 0; i < SIZE - 1; i++) {
        min_idx = i;
        for (int j = i + 1; j < SIZE; j++) {
            if (temp[j] < temp[min_idx]) {
                min_idx = j;
            }
        }
        temp_val = temp[i];
        temp[i] = temp[min_idx];
        temp[min_idx] = temp_val;

        // 10부터 20 단위 및 마지막(99번째) 출력
        if (i + 1 == 10 || (i + 1) % 20 == 10 || i + 1 == 99) {
            printf("\nAfter %d steps:", i + 1);
            printArray(temp, SIZE);
        }
    }
}

// 삽입 정렬 함수
void doInsertionSort(int arr[]) {
    int total_comparisons = 0;

    for (int t = 0; t < ATTEMPTS; t++) {
        int temp[SIZE];
        generateRandomData(temp); // 매번 새로운 데이터 생성
        int comparisons = 0;

        for (int i = 1; i < SIZE; i++) {
            int key = temp[i];
            int j = i - 1;
            while (j >= 0 && temp[j] > key) {
                temp[j + 1] = temp[j];
                j--;
                comparisons++;
            }
            comparisons++;
            temp[j + 1] = key;
        }
        total_comparisons += comparisons;
    }

    printf("\nInsertion Sort Compare Average: %.0f\n", (double)total_comparisons / ATTEMPTS);
    printf("Insertion Sort Result:\n");
    int final_data[SIZE];
    generateRandomData(final_data);
    for (int i = 1; i < SIZE; i++) {
        int key = final_data[i];
        int j = i - 1;
        while (j >= 0 && final_data[j] > key) {
            final_data[j + 1] = final_data[j];
            j--;
        }
        final_data[j + 1] = key;
    }
    printArray(final_data, SIZE);
}

// 버블 정렬 함수
void doBubbleSort(int arr[]) {
    int total_moves = 0;

    for (int t = 0; t < ATTEMPTS; t++) {
        int temp[SIZE];
        generateRandomData(temp); // 매번 새로운 데이터 생성

        for (int i = 0; i < SIZE - 1; i++) {
            for (int j = 0; j < SIZE - i - 1; j++) {
                if (temp[j] > temp[j + 1]) {
                    int temp_val = temp[j];
                    temp[j] = temp[j + 1];
                    temp[j + 1] = temp_val;
                    total_moves += 3; // swap당 3회 이동
                }
            }
        }
    }

    printf("\nBubble Sort Move Average: %.0f\n", (double)total_moves / ATTEMPTS);
    printf("Bubble Sort Result:\n");
    int final_data[SIZE];
    generateRandomData(final_data);
    for (int i = 0; i < SIZE - 1; i++) {
        for (int j = 0; j < SIZE - i - 1; j++) {
            if (final_data[j] > final_data[j + 1]) {
                int temp_val = final_data[j];
                final_data[j] = final_data[j + 1];
                final_data[j + 1] = temp_val;
            }
        }
    }
    printArray(final_data, SIZE);
}

// 메인 함수
int main() {
    int randomData[SIZE];
    srand(time(NULL));

    // 랜덤 데이터 생성
    generateRandomData(randomData);

    // 각 정렬 수행
    doSelectionSort(randomData);
    doInsertionSort(randomData);
    doBubbleSort(randomData);

    return 0;
}
