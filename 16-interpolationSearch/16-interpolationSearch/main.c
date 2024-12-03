#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// 배열 크기와 테스트 횟수를 정의
#define SIZE 10000       // 정렬 및 검색에 사용할 배열의 크기
#define TEST_COUNT 1000  // 평균 비교 횟수를 계산하기 위한 테스트 반복 횟수

// Quick Sort 함수
void QuickSort(int arr[], int left, int right) {
    // 배열을 재귀적으로 정렬
    if (left < right) {
        // 피벗을 배열의 마지막 요소로 설정
        int pivot = arr[right];
        int i = left - 1;

        // 피벗을 기준으로 배열을 분할
        for (int j = left; j < right; j++) {
            if (arr[j] <= pivot) {
                i++;
                // 두 요소를 교환
                int temp = arr[i];
                arr[i] = arr[j];
                arr[j] = temp;
            }
        }

        // 피벗 요소를 올바른 위치로 이동
        int temp = arr[i + 1];
        arr[i + 1] = arr[right];
        arr[right] = temp;

        // 분할된 두 부분에 대해 재귀 호출
        QuickSort(arr, left, i);
        QuickSort(arr, i + 2, right);
    }
}

// 배열의 일부를 출력하는 함수
void printArray(int* array) {
    // 배열의 정렬 결과를 출력
    printf("Array Sorting Result:\n");

    // 배열의 처음 20개 요소 출력
    for (int i = 0; i < 20; i++)
        printf("%4d ", array[i]);
    printf("\n");

    // 배열의 마지막 20개 요소 출력
    for (int i = SIZE - 20; i < SIZE; i++)
        printf("%4d ", array[i]);
    printf("\n\n");
}

// Binary Search 구현
int BinarySearch(int* array, int size, int target) {
    // 이진 탐색으로 배열에서 target을 찾음
    int left = 0, right = size - 1, compareCount = 0;

    while (left <= right) {
        // 중간 인덱스를 계산
        int mid = left + (right - left) / 2;
        compareCount++;

        // 타겟 값을 찾은 경우
        if (array[mid] == target)
            return compareCount;

        // 타겟이 중간값보다 큰 경우 오른쪽 탐색
        if (array[mid] < target)
            left = mid + 1;
        else // 타겟이 중간값보다 작은 경우 왼쪽 탐색
            right = mid - 1;
    }
    return compareCount; // 찾지 못한 경우 비교 횟수 반환
}

// Interpolation Search 구현
int InterpolationSearch(int* array, int size, int target) {
    // 보간 탐색으로 배열에서 target을 찾음
    int left = 0, right = size - 1, compareCount = 0;

    while (left <= right && target >= array[left] && target <= array[right]) {
        compareCount++;

        // left와 right가 같으면 마지막 위치 확인
        if (left == right) {
            if (array[left] == target) return compareCount;
            break;
        }

        // 보간 위치 계산
        int pos = left + ((double)(right - left) / (array[right] - array[left]) * (target - array[left]));

        // 계산된 위치가 유효한 범위 내인지 확인
        if (pos < left || pos > right) break;

        // 타겟 값을 찾은 경우
        if (array[pos] == target)
            return compareCount;

        // 타겟이 보간 위치 값보다 큰 경우 오른쪽 탐색
        if (array[pos] < target)
            left = pos + 1;
        else // 타겟이 보간 위치 값보다 작은 경우 왼쪽 탐색
            right = pos - 1;
    }
    return compareCount; // 찾지 못한 경우 비교 횟수 반환
}

// 평균 비교 횟수 계산 함수 (Binary Search)
double getAverageBinarySearchCompareCount(int* array) {
    double totalCompareCount = 0;

    // 무작위 타겟 선택 후 Binary Search 수행
    for (int i = 0; i < TEST_COUNT; i++) {
        int target = array[rand() % SIZE];
        totalCompareCount += BinarySearch(array, SIZE, target);
    }

    // 평균 비교 횟수 반환
    return totalCompareCount / TEST_COUNT;
}

// 평균 비교 횟수 계산 함수 (Interpolation Search)
double getAverageInterpolationSearchCompareCount(int* array) {
    double totalCompareCount = 0;

    // 무작위 타겟 선택 후 Interpolation Search 수행
    for (int i = 0; i < TEST_COUNT; i++) {
        int target = array[rand() % SIZE];
        totalCompareCount += InterpolationSearch(array, SIZE, target);
    }

    // 평균 비교 횟수 반환
    return totalCompareCount / TEST_COUNT;
}

// 임의 배열 생성 함수
void generateRandomArray(int* array) {
    // 배열에 0에서 9999 사이의 랜덤 값을 삽입
    for (int i = 0; i < SIZE; i++)
        array[i] = rand() % 10000;
}

// 메인 함수
int main(int argc, char* argv[]) {
    srand(time(NULL)); // 랜덤 시드 초기화
    int array[SIZE];   // 정렬 및 탐색에 사용할 배열 생성

    generateRandomArray(array);  // 임의의 값으로 배열 초기화

    QuickSort(array, 0, SIZE - 1); // 배열 정렬
    printArray(array);             // 정렬된 배열 출력

    // Binary Search와 Interpolation Search의 평균 비교 횟수 출력
    printf("Average Compare Count of Binary Search: %.2f\n",
        getAverageBinarySearchCompareCount(array));
    printf("Average Compare Count of Interpolation Search: %.2f\n",
        getAverageInterpolationSearchCompareCount(array));

    return 0; // 프로그램 종료
}
