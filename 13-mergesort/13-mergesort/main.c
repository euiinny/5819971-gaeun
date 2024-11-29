#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define SIZE 100 // 배열 크기 정의
int rounds = 0; // 합병 정렬에서 현재 단계의 반복 횟수를 저장
int comparisonCount = 0; // 비교 횟수 카운트
int moveCount = 0; // 이동 횟수 카운트
int totalComparisons = 0; // 총 비교 횟수 누적
int totalMoves = 0; // 총 이동 횟수 누적
int isFirst = 0; // 첫 번째 실행 여부 확인 변수

// 랜덤 배열 생성 함수
// 0부터 999 사이의 랜덤 값을 갖는 배열을 생성
void generateRandomArray(int array[]) {
    for (int i = 0; i < SIZE; i++) {
        array[i] = rand() % 1000; // 0-999 범위의 랜덤 값 생성
    }
}

// 배열 출력 함수
// 배열의 내용을 출력
void printArray(int array[], int size) {
    for (int i = 0; i < size; i++) {
        printf("%d ", array[i]); // 배열 원소 출력
    }
    printf("\n");
}

// 반복적 합병 정렬 함수
void doMergeSort(int array[]) {
    int temp[SIZE]; // 정렬 과정에서 사용할 임시 배열

    // 배열의 크기를 1, 2, 4, 8...씩 늘려가며 합병 정렬 수행
    for (int width = 1; width < SIZE; width *= 2) {
        // 배열을 부분 배열 단위로 나누고 합병
        for (int i = 0; i < SIZE; i += 2 * width) {
            int left = i; // 왼쪽 부분 배열의 시작 인덱스
            int mid = i + width < SIZE ? i + width : SIZE; // 중간 지점
            int right = i + 2 * width < SIZE ? i + 2 * width : SIZE; // 오른쪽 끝 인덱스

            int l = left, r = mid, k = left; // 부분 배열의 인덱스 초기화

            // 왼쪽과 오른쪽 부분 배열 비교하며 병합
            while (l < mid && r < right) {
                comparisonCount++; // 비교 횟수 증가
                if (array[l] <= array[r]) {
                    temp[k++] = array[l++]; // 왼쪽 배열 값 삽입
                    moveCount++; // 이동 횟수 증가
                } else {
                    temp[k++] = array[r++]; // 오른쪽 배열 값 삽입
                    moveCount++; // 이동 횟수 증가
                }
            }

            // 왼쪽 부분 배열의 남은 값 병합
            while (l < mid) {
                temp[k++] = array[l++];
                moveCount++;
            }

            // 오른쪽 부분 배열의 남은 값 병합
            while (r < right) {
                temp[k++] = array[r++];
                moveCount++;
            }

            // 병합된 결과를 원래 배열에 복사
            for (int j = left; j < right; j++) {
                array[j] = temp[j];
                moveCount++;
            }

            // 중간 상태 출력 (10번마다 수행)
            if (rounds % 10 == 0 && isFirst == 0) {
                for (int j = 0; j < 10; j++) { // 배열의 첫 10개 요소 출력
                    printf("%3d ", array[j]);
                }
                printf("| ");
                for (int j = SIZE / 2 - 1; j < SIZE / 2 + 10; j++) { // 중간 10개 요소 출력
                    printf("%3d ", array[j]);
                }
                printf("\n");
            }
            rounds++; // 반복 횟수 증가
        }
    }
}

// 메인 함수
int main() {
    int array[SIZE]; // 정렬에 사용할 배열
    srand((unsigned int)time(NULL)); // 난수 생성을 위한 초기화

    for (int i = 0; i < 20; i++) { // 20번 실행
        generateRandomArray(array); // 랜덤 배열 생성
        comparisonCount = 0; // 비교 횟수 초기화
        moveCount = 0; // 이동 횟수 초기화

        if (i == 0) { // 첫 번째 실행일 경우
            printf("Merge Sort Run\n"); // 정렬 시작 알림
            doMergeSort(array); // 합병 정렬 수행

            printf("Result\n");
            printArray(array, SIZE); // 정렬된 배열 출력
            isFirst++; // 첫 실행 완료 플래그 설정
        } else {
            doMergeSort(array); // 이후 실행은 상태 출력 없이 정렬 수행
        }

        totalComparisons += comparisonCount; // 총 비교 횟수 누적
        totalMoves += moveCount; // 총 이동 횟수 누적
    }

    // 평균 비교 횟수와 이동 횟수 출력
    printf("\nAverage Comparisons: %.2f\n", totalComparisons / 20.0);
    printf("Average Moves: %.2f\n", totalMoves / 20.0);

    return 0; // 프로그램 종료
}
