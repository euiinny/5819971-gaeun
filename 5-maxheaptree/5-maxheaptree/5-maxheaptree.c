#include <stdio.h>
#include <stdlib.h>

#define MAX_SIZE 100

typedef struct {
    int data[MAX_SIZE];
    int size;
} MaxHeap;


void InitMaxHeap(MaxHeap* root) {
    root->size = 0;
}

// 힙의 요소를 출력하는 함수
void PrintHeap(MaxHeap* root) {
    for (int i = 0; i < root->size; i++) {
        printf("%d ", root->data[i]); // 각 요소를 출력
    }
    printf("\n");
}

// 최대 힙에 새로운 값을 삽입하는 함수
int InsertMaxHeap(MaxHeap* root, int value, int showSteps) {
    if (root->size >= MAX_SIZE) {
        printf("힙이 가득 찼습니다 \n");
        return 0; // 0 반환
    }

    int index = root->size;
    root->data[index] = value;
    root->size++;

    int moves = 0;
    if (showSteps) {
        PrintHeap(root);
    }

    while (index > 0) {
        int parent = (index - 1) / 2;
        if (root->data[parent] < root->data[index]) {
            int temp = root->data[parent];
            root->data[parent] = root->data[index];
            root->data[index] = temp;
            index = parent;
            moves++;

            if (showSteps) {
                PrintHeap(root);
            }
        }
        else {
            break;
        }
    }
    if (showSteps) {
        PrintHeap(root); // 최종 상태 출력
    }

    return moves; // 이동 횟수 반환
}

// 최대 힙에서 최대 요소(루트)를 삭제하는 함수
int DeleteMaxHeap(MaxHeap* root) {
    if (root->size == 0) {
        printf("힙이 비어있습니다!\n"); // 힙이 비어 있으면 경고
        return 0; // 0 반환
    }

    root->data[0] = root->data[root->size - 1]; // 마지막 요소를 루트에 대입
    root->size--;

    int index = 0;
    int moves = 0;
    PrintHeap(root);

    // 루트를 아래로 내려가며 힙 속성 유지
    while (index * 2 + 1 < root->size) {
        int leftChild = index * 2 + 1;
        int rightChild = index * 2 + 2;
        int largerChild = leftChild;

        if (rightChild < root->size && root->data[rightChild] > root->data[leftChild]) {
            largerChild = rightChild;
        }
        
        if (root->data[index] < root->data[largerChild]) {
            int temp = root->data[index];
            root->data[index] = root->data[largerChild];
            root->data[largerChild] = temp;

            index = largerChild;
            moves++;
            
            PrintHeap(root);
        }
        else {
            break;
        }
    }

    PrintHeap(root);

    return moves;
}

// 힙의 레벨 순서로 출력하는 함수
void PrintHeapLevelOrder(MaxHeap* root) {
    if (root->size == 0) {
        printf("힙이 비어 있습니다.\n");
        return; // 함수 종료
    }

    int level = 0;
    int count = 1;
    int index = 0;

    printf("트리 레벨별 출력:\n");
    while (index < root->size) {
        printf("[%d] ", level + 1); // 현재 레벨 출력

        for (int i = 0; i < count && index < root->size; i++) {
            printf("%d ", root->data[index]); // 현재 레벨의 요소 출력
            index++; // 인덱스 증가
        }
        printf("\n"); // 레벨 출력 후 줄 바꿈

        level++; // 다음 레벨로 이동
        count *= 2; // 출력할 노드 수 두 배로 증가
    }
}

// 사용자 인터페이스를 실행하는 함수
void RunUserInterface(MaxHeap* root) {
    char choice; // 사용자 선택
    int value, moves; // 입력 값 및 이동 횟수

    while (1) {
        // 메뉴 출력
        printf(" i : 노드 추가\n");
        printf(" d : 노드 삭제\n");
        printf(" p : 레벨별 출력\n");
        printf(" c : 종료\n");

        printf("메뉴 입력: ");
        scanf(" %c", &choice);

        switch (choice) {
        case 'i': // 노드 추가
            printf("추가할 값 입력: ");
            scanf("%d", &value);
            moves = InsertMaxHeap(root, value, 1);
            printf("노드 이동 횟수: %d\n", moves);
            break;

        case 'd': // 노드 삭제
            moves = DeleteMaxHeap(root);
            printf("노드 이동 횟수: %d\n", moves);
            break;

        case 'p': // 레벨별 출력
            PrintHeapLevelOrder(root);
            break;

        case 'c': // 종료
            printf("프로그램을 종료합니다.\n");
            return; 

        default: // 잘못된 입력 처리
            printf("잘못된 입력입니다. 다시 시도해주세요.\n"); // 경고 메시지
        }
    }
}

int main() {
    MaxHeap root;  // 힙을 root로 이름 변경
    InitMaxHeap(&root); // 힙 초기화

    // 초기 데이터 배열
    int inputData[] = { 90, 89, 70, 36, 75, 63, 65, 21, 18, 13 };
    int size = sizeof(inputData) / sizeof(inputData[0]); // 배열 크기 계산

    // 초기 데이터를 힙에 삽입
    for (int i = 0; i < size; i++) {
        InsertMaxHeap(&root, inputData[i], 0); // 삽입 함수 호출
    }

    RunUserInterface(&root); // 사용자 인터페이스 실행

    return 0; // 프로그램 종료
}
