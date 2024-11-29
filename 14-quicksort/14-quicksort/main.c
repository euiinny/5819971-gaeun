#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define SIZE 100 // 배열의 크기 정의

// 전역 변수 선언
int comparisonCount = 0; // 비교 연산 횟수 저장
int moveCount = 0; // 데이터 이동 횟수 저장
int rounds = 0; // 분할 과정의 라운드 수를 저장
int isFirst = 0; // 첫 번째 실행 여부를 나타내는 플래그 변수

// 배열의 내용을 출력하는 함수
void printArray(int array[], int size) {
    for (int i = 0; i < size; i++) {
        printf("%d ", array[i]);
    }
    printf("\n");
}

// 배열을 랜덤 값으로 초기화하는 함수
void generateRandomArray(int array[]) {
    for (int i = 0; i < SIZE; i++) {
        array[i] = rand() % 1000; // 0~999 범위의 랜덤 값 생성
    }
}

// Quick Sort를 스택을 이용하여 비재귀적으로 구현한 함수
void doQuickSort(int array[], int left, int right) {
    // 스택 초기화
    int stack[SIZE];
    int top = -1;

    // 초기 정렬 범위를 스택에 추가
    stack[++top] = left;
    stack[++top] = right;

    while (top >= 0) { // 스택이 비어있지 않은 동안 반복
        // 스택에서 정렬 범위를 꺼냄
        int right = stack[top--];
        int left = stack[top--];

        if (left >= right) continue; // 정렬 범위가 유효하지 않으면 건너뜀

        int pivot = array[left]; // 피벗 값 설정
        int low = left + 1;
        int high = right;

        // 분할 과정
        while (low <= high) {
            comparisonCount++; // 비교 횟수 증가
            while (low <= right && array[low] <= pivot) { // 왼쪽에서 피벗보다 큰 값을 찾음
                low++;
                comparisonCount++;
            }
            while (high > left && array[high] >= pivot) { // 오른쪽에서 피벗보다 작은 값을 찾음
                high--;
                comparisonCount++;
            }
            if (low < high) { // low와 high를 교환
                int temp = array[low];
                array[low] = array[high];
                array[high] = temp;
                moveCount += 3; // 값 교환 횟수 증가
            }
        }

        // 피벗과 high 위치의 값을 교환
        if (left != high) {
            int temp = array[left];
            array[left] = array[high];
            array[high] = temp;
            moveCount += 3; // 값 교환 횟수 증가
        }

        // 첫 번째 실행 시, 특정 구간의 배열 상태를 출력
        if (rounds % 10 == 0 && isFirst == 0) {
            for (int i = 20; i < 40; i++) { // 배열의 20~39번 요소 출력
                printf("%d ", array[i]);
            }
            printf("\n");
            for (int i = 40; i < 60; i++) { // 배열의 40~59번 요소 출력
                printf("%d ", array[i]);
            }
            printf("\n");
        }
        rounds++; // 라운드 증가

        // 새로운 정렬 범위를 스택에 추가
        if (left < high - 1) {
            stack[++top] = left;
            stack[++top] = high - 1;
        }
        if (high + 1 < right) {
            stack[++top] = high + 1;
            stack[++top] = right;
        }
    }
}

// 프로그램의 메인 함수
int main() {
    srand(time(NULL)); // 랜덤 시드 초기화
    int array[SIZE]; // 정렬할 배열 선언
    int totalComparisons = 0; // 전체 비교 횟수 합산
    int totalMoveCount = 0; // 전체 이동 횟수 합산

    for (int i = 0; i < 20; i++) { // 20번 정렬 실행
        generateRandomArray(array); // 랜덤 배열 생성

        // 비교 횟수와 이동 횟수 초기화
        comparisonCount = 0;
        moveCount = 0;
        rounds = 0; // 라운드 초기화

        if (i == 0) { // 첫 번째 실행일 경우
            printf("Quick Sort Run\n");
            doQuickSort(array, 0, SIZE - 1); // Quick Sort 실행
            printf("Result:\n");
            printArray(array, SIZE); // 정렬 결과 출력
            isFirst++; // 첫 번째 실행 여부 플래그 증가
        } else { // 첫 번째 실행이 아닌 경우
            doQuickSort(array, 0, SIZE - 1); // Quick Sort 실행
        }

        // 비교 횟수와 이동 횟수 누적
        totalComparisons += comparisonCount;
        totalMoveCount += moveCount;
    }

    // 평균 비교 횟수와 이동 횟수 출력
    printf("\nAverage Comparisons: %.2f\n", totalComparisons / 20.0);
    printf("Average Moves: %.2f\n", totalMoveCount / 20.0);

    return 0; // 프로그램 종료
}
