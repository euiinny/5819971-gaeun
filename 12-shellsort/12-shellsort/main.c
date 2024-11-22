#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define ARRAY_SIZE 100

// 랜덤 숫자를 배열에 생성하는 함수
void generateRandomNumbers(int arr[]) {
    for (int i = 0; i < ARRAY_SIZE; i++) {
        arr[i] = rand() % 1000; // 0과 999 사이의 랜덤 숫자 생성
    }
}

// 배열을 출력하는 함수 (최대 20개 항목만 출력)
void printTruncatedArray(int arr[], int size) {
    for (int i = 0; i < 20 && i < size; i++) {
        printf("%d ", arr[i]);
    }
    if (size > 20) {
        printf("..."); // 20개 초과시 생략 표시
    }
    printf("\n\n");
}

// 배열을 모두 출력하는 함수
void printFullArray(int arr[], int size) {
    for (int i = 0; i < size; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n\n");
}

// 배열을 복사하는 함수
void copyArray(int source[], int destination[]) {
    for (int i = 0; i < ARRAY_SIZE; i++) {
        destination[i] = source[i]; // source 배열을 destination 배열에 복사
    }
}

// 쉘 정렬을 수행하는 함수
void doShellSort(int arr[], int gapType, int *compCount, int *moveCount) {
    int gap, i, j, temp;
    *compCount = 0; // 비교 횟수 초기화
    *moveCount = 0; // 이동 횟수 초기화

    // 배열을 복사하여 arrCopy에 저장
    int arrCopy[ARRAY_SIZE];
    copyArray(arr, arrCopy);  // 배열 복사

    if (gapType == 2) { // n/2 갭 시퀀스
        gap = ARRAY_SIZE / 2; // 처음 갭 값 설정
        while (gap > 0) { // 갭이 0보다 클 때까지 반복
            printf("Sorting with gap = %d: \n", gap);
            for (i = gap; i < ARRAY_SIZE; i++) {
                temp = arrCopy[i]; // 현재 값 저장
                j = i;

                // 비교 및 이동을 처리
                while (j >= gap) {
                    (*compCount)++; // 비교 횟수 증가
                    if (arrCopy[j - gap] > temp) {
                        arrCopy[j] = arrCopy[j - gap]; // 값 이동
                        j -= gap; // 갭만큼 이동
                        (*moveCount)++; // 이동 횟수 증가
                    } else {
                        break; // 비교 결과가 만족되면 종료
                    }
                }
                arrCopy[j] = temp; // 최종 위치에 값 배치
                (*moveCount)++; // 최종 배치 이동 횟수 증가
            }
            printTruncatedArray(arrCopy, ARRAY_SIZE); // 중간 상태 출력
            gap /= 2; // 갭을 반으로 나누어 감소
        }
    } else if (gapType == 3) { // n/3 갭 시퀀스
        gap = ARRAY_SIZE / 3; // 처음 갭 값 설정
        while (gap > 0) { // 갭이 0보다 클 때까지 반복
            printf("Sorting with gap = %d: \n", gap);
            for (i = gap; i < ARRAY_SIZE; i++) {
                temp = arrCopy[i]; // 현재 값 저장
                j = i;

                // 비교 및 이동을 처리
                while (j >= gap) {
                    (*compCount)++; // 비교 횟수 증가
                    if (arrCopy[j - gap] > temp) {
                        arrCopy[j] = arrCopy[j - gap]; // 값 이동
                        j -= gap; // 갭만큼 이동
                        (*moveCount)++; // 이동 횟수 증가
                    } else {
                        break; // 비교 결과가 만족되면 종료
                    }
                }
                arrCopy[j] = temp; // 최종 위치에 값 배치
                (*moveCount)++; // 최종 배치 이동 횟수 증가
            }
            printTruncatedArray(arrCopy, ARRAY_SIZE); // 중간 상태 출력
            gap /= 3; // 갭을 3으로 나누어 감소
        }
    }
    printf("Sorted shellArray (gap = %d):\n", gapType);
    printFullArray(arrCopy, ARRAY_SIZE); // 최종 정렬된 배열 출력
}

// 삽입 정렬을 수행하는 함수
void doInsertionSort(int arr[], int *compCount, int *moveCount) {
    int i, j, temp;
    *compCount = 0; // 비교 횟수 초기화
    *moveCount = 0; // 이동 횟수 초기화

    // 배열을 복사하여 arrCopy에 저장
    int arrCopy[ARRAY_SIZE];
    copyArray(arr, arrCopy);  // 배열 복사

    for (i = 1; i < ARRAY_SIZE; i++) {
        temp = arrCopy[i]; // 현재 값 저장
        j = i - 1;

        // 현재 값보다 큰 값을 오른쪽으로 밀기
        while (j >= 0 && arrCopy[j] > temp) {
            arrCopy[j + 1] = arrCopy[j]; // 값 이동
            j--;
            (*compCount)++; // 비교 횟수 증가
            (*moveCount)++; // 이동 횟수 증가
        }
        arrCopy[j + 1] = temp; // 현재 값을 적절한 위치에 배치
        (*moveCount)++; // 최종 배치 이동 횟수 증가
        if (j >= 0) {
            (*compCount)++; // 마지막 비교 증가
        }
    }
    printf("Sorted insertionArray:\n");
    printFullArray(arrCopy, ARRAY_SIZE); // 최종 정렬된 배열 출력
}

int main() {
    srand(time(NULL)); // 랜덤 숫자 생성을 위한 시드 설정

    int array[ARRAY_SIZE];
    int comparisonCount, moveCount;

    // 랜덤 숫자를 배열에 생성
    generateRandomNumbers(array);

    // 쉘 정렬 (n/2)
    printf("Shell Sort (n/2):\n");
    doShellSort(array, 2, &comparisonCount, &moveCount);
    printf("Shell Sort (n/2) - Comparisons: %d, Moves: %d\n\n", comparisonCount, moveCount);

    // 쉘 정렬 (n/3)
    printf("Shell Sort (n/3):\n");
    doShellSort(array, 3, &comparisonCount, &moveCount);
    printf("Shell Sort (n/3) - Comparisons: %d, Moves: %d\n\n", comparisonCount, moveCount);

    // 삽입 정렬
    printf("\nInsertion Sort:\n");
    doInsertionSort(array, &comparisonCount, &moveCount);
    printf("Insertion Sort - Comparisons: %d, Moves: %d\n", comparisonCount, moveCount);

    return 0;
}
