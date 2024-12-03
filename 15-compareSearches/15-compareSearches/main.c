#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define SIZE 1000  // 배열의 크기를 1000으로 정의합니다.

// 전역 변수로 Quick Sort의 비교 횟수를 저장합니다.
int compareCount = 0;

// 배열을 랜덤한 값으로 초기화합니다.
void generateRandomArray(int* array) {
    for (int i = 0; i < SIZE; i++) {
        array[i] = rand() % 1000;  // 0부터 999까지의 난수를 배열에 저장합니다.
    }
}

// 배열에서 목표값을 선형 탐색하며 비교 횟수를 반환합니다.
int linearSearch(int* array, int target) {
    int count = 0;  // 비교 횟수를 초기화합니다.
    for (int i = 0; i < SIZE; i++) {
        count++;  // 비교가 수행될 때마다 증가시킵니다.
        if (array[i] == target) {  // 목표값을 찾으면 비교 횟수를 반환합니다.
            return count;
        }
    }
    return count;  // 목표값이 없을 경우 전체 비교 횟수를 반환합니다.
}

// 100번의 선형 탐색을 수행하고 평균 비교 횟수를 계산합니다.
double getAverageLinearSearchCompareCount(int* array) {
    int totalComparisons = 0;  // 총 비교 횟수를 저장합니다.
    for (int i = 0; i < 100; i++) {
        int target = array[rand() % SIZE];  // 배열에서 임의의 목표값을 선택합니다.
        totalComparisons += linearSearch(array, target);
    }
    return totalComparisons / 100.0;  // 평균 비교 횟수를 반환합니다.
}

// Quick Sort에서 Partition 작업을 수행하며 비교 횟수를 기록합니다.
int partition(int* array, int low, int high) {
    int pivot = array[high];  // 피벗을 마지막 요소로 설정합니다.
    int i = low - 1;  // 작은 요소를 추적하는 인덱스
    for (int j = low; j < high; j++) {
        compareCount++;  // 비교 횟수를 증가시킵니다.
        if (array[j] < pivot) {  // 피벗보다 작은 경우
            i++;
            // 요소를 교환하여 작은 값이 앞쪽으로 이동하게 만듭니다.
            int temp = array[i];
            array[i] = array[j];
            array[j] = temp;
        }
    }
    // 피벗을 정렬된 위치에 놓습니다.
    int temp = array[i + 1];
    array[i + 1] = array[high];
    array[high] = temp;
    return i + 1;  // 피벗의 최종 위치를 반환합니다.
}

// 재귀적으로 Quick Sort를 수행합니다.
void quickSort(int* array, int low, int high) {
    if (low < high) {  // 유효한 범위인지 확인합니다.
        int pi = partition(array, low, high);  // Partition 작업 수행
        quickSort(array, low, pi - 1);  // 피벗보다 작은 부분을 정렬합니다.
        quickSort(array, pi + 1, high);  // 피벗보다 큰 부분을 정렬합니다.
    }
}

// Quick Sort를 수행하고 비교 횟수를 측정합니다.
void getQuickSortCompareCount(int* array) {
    compareCount = 0;  // 비교 횟수를 초기화합니다.
    quickSort(array, 0, SIZE - 1);
}

// 배열에서 이진 탐색을 수행하며 비교 횟수를 반환합니다.
int binarySearch(int* array, int target) {
    int low = 0, high = SIZE - 1;
    int count = 0;  // 비교 횟수를 초기화합니다.
    while (low <= high) {  // 탐색 범위가 유효한 동안 반복합니다.
        int mid = low + (high - low) / 2;  // 중간 위치 계산
        count++;  // 비교 횟수를 증가시킵니다.
        if (array[mid] == target) {  // 목표값을 찾은 경우
            return count;
        }
        if (array[mid] < target) {  // 목표값이 더 크면 오른쪽 탐색
            low = mid + 1;
        } else {  // 목표값이 더 작으면 왼쪽 탐색
            high = mid - 1;
        }
    }
    return count;  // 목표값이 없는 경우 비교 횟수를 반환합니다.
}

// 100번의 이진 탐색을 수행하고 평균 비교 횟수를 계산합니다.
double getAverageBinarySearchCompareCount(int* array) {
    int totalComparisons = 0;  // 총 비교 횟수를 저장합니다.
    for (int i = 0; i < 100; i++) {
        int target = array[rand() % SIZE];  // 배열에서 무작위 목표값을 선택합니다.
        totalComparisons += binarySearch(array, target);
    }
    return totalComparisons / 100.0;  // 평균 비교 횟수를 반환합니다.
}

// 배열의 앞부분과 뒷부분을 출력합니다.
void printArray(int* array) {
    printf("Array Sorting Result:\n");
    for (int i = 0; i < 20; i++)  // 배열의 앞부분 20개 요소 출력
        printf("%3d ", array[i]);
    printf("\n");
    for (int i = SIZE - 20; i < SIZE; i++)  // 배열의 뒷부분 20개 요소 출력
        printf("%3d ", array[i]);
    printf("\n");
}

// 메인 함수: 프로그램 실행 시작점
int main(int argc, char* argv[]) {
    srand(time(NULL));  // 랜덤 시드 초기화
    int array[SIZE];  // 배열 선언
    generateRandomArray(array);  // 배열을 난수로 초기화

    // 선형 탐색의 평균 비교 횟수를 계산하여 출력
    printf("Average Linear Search Compare Count: %.2f\n",
        getAverageLinearSearchCompareCount(array));

    // Quick Sort를 수행하고 비교 횟수를 출력
    getQuickSortCompareCount(array);
    printf("Quick Sort Compare Count: %d\n", compareCount);

    // 이진 탐색의 평균 비교 횟수를 계산하여 출력
    printf("Average Binary Search Compare Count: %.2f\n\n",
        getAverageBinarySearchCompareCount(array));

    // 배열의 앞부분과 뒷부분 출력
    printArray(array);

    return 0;  
}
