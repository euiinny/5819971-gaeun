#include <stdio.h>

// 두 숫자를 교환하는 함수
void swap(int* a, int* b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

// 특정 노드를 기준으로 최대 힙 성질을 유지하는 함수
void heapify(int inputData[], int n, int i) {
    int largest = i;  // 현재 노드를 루트로 설정
    int left = 2 * i + 1;  // 왼쪽 자식 노드의 인덱스
    int right = 2 * i + 2; // 오른쪽 자식 노드의 인덱스

    // 왼쪽 자식 노드가 더 크면 largest를 갱신
    if (left < n && inputData[left] > inputData[largest])
        largest = left;

    // 오른쪽 자식 노드가 더 크면 largest를 갱신
    if (right < n && inputData[right] > inputData[largest])
        largest = right;

    // 가장 큰 값이 현재 노드가 아니면 교환 후 재귀 호출로 힙 성질 유지
    if (largest != i) {
        swap(&inputData[i], &inputData[largest]);
        heapify(inputData, n, largest);
    }
}

// 주어진 배열을 최대 힙으로 만드는 함수
void BuildMaxHeap(int inputData[], int n) {
    for (int i = 0; i < n; i++) {
        int currentIndex = i;

        // 삽입된 노드를 부모와 비교하여 최대 힙 성질을 유지
        while (currentIndex > 0) {
            int parentIndex = (currentIndex - 1) / 2;
            if (inputData[currentIndex] > inputData[parentIndex]) {
                swap(&inputData[currentIndex], &inputData[parentIndex]);
                currentIndex = parentIndex;  // 부모로 이동하여 다시 비교
            } else {
                break;  // 부모가 더 크면 종료
            }
        }

        // 힙이 생성되는 중간 과정을 출력
        for (int j = 0; j <= i; j++) {
            printf("%d ", inputData[j]);
        }
        printf("\n");
    }
}

// 최대 힙을 생성하고 정렬하는 함수
void BuildMaxHeapAndSort(int inputData[], int n) {
    // 최대 힙 생성
    BuildMaxHeap(inputData, n);

    // 힙 정렬 실행
    for (int i = n - 1; i > 0; i--) {
        swap(&inputData[0], &inputData[i]);  // 루트(최대값)를 배열 끝으로 이동
        heapify(inputData, i, 0);  // 나머지 부분에 대해 힙 성질 유지

        // 힙 상태 출력 (정렬 후 중간 결과)
        for (int j = 0; j <= i - 1; j++) {
            printf("%d ", inputData[j]);
        }
        printf("\n");
    }
}

int main() {
    int inputData[] = { 34, 12, 76, 59, 32, 55, 88, 26, 16, 79, 35, 85, 29, 78, 41, 56, 86 };
    int size = sizeof(inputData) / sizeof(inputData[0]);

    // 힙 정렬 실행
    printf("<Sort>\n");
    BuildMaxHeapAndSort(inputData, size);

    // 최종적으로 정렬된 배열 출력
    printf("\nSorted Array:\n");
    for (int i = 0; i < size; i++) {
        printf("%d ", inputData[i]);
    }
    printf("\n");

    return 0;
}
