#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// 트리의 노드 구조체 정의
typedef struct Node {
    int key;                    // 노드의 값
    struct Node *left, *right;  // 왼쪽 및 오른쪽 자식 노드
    int height;                 // AVL 트리에서 높이 정보
} Node;

// 전역 변수: 비교 횟수 및 탐색 횟수를 저장
int compareCount = 0;
int searchCount = 0;

// 유틸리티 함수들
// 두 값 중 큰 값을 반환
int max(int a, int b) {
    return (a > b) ? a : b;
}

// 노드의 높이를 반환
int height(Node *node) {
    return (node == NULL) ? 0 : node->height;
}

// 새로운 노드를 생성
Node *createNode(int key) {
    Node *node = (Node *)malloc(sizeof(Node));
    node->key = key;
    node->left = node->right = NULL;
    node->height = 1; // 새 노드의 높이는 1
    return node;
}

// 트리를 후위 순회하며 메모리를 해제
void freeTree(Node *root) {
    if (root == NULL) return;
    freeTree(root->left);  // 왼쪽 서브트리 해제
    freeTree(root->right); // 오른쪽 서브트리 해제
    free(root);            // 현재 노드 해제
}

// AVL 트리 관련 함수들
// 노드의 균형 계수를 계산
int getBalance(Node *node) {
    return (node == NULL) ? 0 : height(node->left) - height(node->right);
}

// 오른쪽 회전 (Right Rotation)
Node *rotateRight(Node *y) {
    Node *x = y->left;         // 회전의 축이 되는 노드
    Node *T = x->right;        // x의 오른쪽 서브트리

    // 회전 수행
    x->right = y;
    y->left = T;

    // 높이 갱신
    y->height = max(height(y->left), height(y->right)) + 1;
    x->height = max(height(x->left), height(x->right)) + 1;

    return x; // 새로운 루트 반환
}

// 왼쪽 회전 (Left Rotation)
Node *rotateLeft(Node *x) {
    Node *y = x->right;        // 회전의 축이 되는 노드
    Node *T = y->left;         // y의 왼쪽 서브트리

    // 회전 수행
    y->left = x;
    x->right = T;

    // 높이 갱신
    x->height = max(height(x->left), height(x->right)) + 1;
    y->height = max(height(y->left), height(y->right)) + 1;

    return y; // 새로운 루트 반환
}

// AVL 트리에 삽입
Node *insertAVL(Node *node, int key) {
    // 기본 BST 삽입 로직
    if (node == NULL) return createNode(key); // 새 노드 생성

    compareCount++; // 비교 횟수 증가
    if (key < node->key) // 왼쪽 서브트리에 삽입
        node->left = insertAVL(node->left, key);
    else if (key > node->key) // 오른쪽 서브트리에 삽입
        node->right = insertAVL(node->right, key);
    else
        return node; // 중복 키는 삽입하지 않음

    // 높이 갱신
    node->height = 1 + max(height(node->left), height(node->right));

    // 균형 계수 계산
    int balance = getBalance(node);

    // 불균형 처리
    if (balance > 1 && key < node->left->key) // LL 케이스
        return rotateRight(node);
    if (balance < -1 && key > node->right->key) // RR 케이스
        return rotateLeft(node);
    if (balance > 1 && key > node->left->key) { // LR 케이스
        node->left = rotateLeft(node->left);
        return rotateRight(node);
    }
    if (balance < -1 && key < node->right->key) { // RL 케이스
        node->right = rotateRight(node->right);
        return rotateLeft(node);
    }

    return node; // 루트 반환
}

// 트리에서 최소값 노드를 반환
Node *minValueNode(Node *node) {
    Node *current = node;
    while (current->left != NULL) // 왼쪽으로 계속 이동
        current = current->left;
    return current;
}

// AVL 트리에서 노드 삭제
Node *deleteAVL(Node *root, int key) {
    if (root == NULL) return root; // 빈 트리

    compareCount++; // 비교 횟수 증가
    if (key < root->key) // 왼쪽 서브트리에서 삭제
        root->left = deleteAVL(root->left, key);
    else if (key > root->key) // 오른쪽 서브트리에서 삭제
        root->right = deleteAVL(root->right, key);
    else {
        // 삭제할 노드 찾음
        if ((root->left == NULL) || (root->right == NULL)) { // 하나 이하의 자식
            Node *temp = root->left ? root->left : root->right;
            if (temp == NULL) { // 자식이 없는 경우
                temp = root;
                root = NULL;
            } else // 자식이 하나인 경우
                *root = *temp;
            free(temp); // 메모리 해제
        } else {
            // 두 자식을 가진 경우
            Node *temp = minValueNode(root->right); // 오른쪽 서브트리에서 최소값
            root->key = temp->key; // 최소값 복사
            root->right = deleteAVL(root->right, temp->key); // 오른쪽 서브트리에서 최소값 삭제
        }
    }

    if (root == NULL) return root; // 루트가 NULL인 경우 반환

    // 높이 갱신
    root->height = 1 + max(height(root->left), height(root->right));

    // 균형 계수 계산
    int balance = getBalance(root);

    // 불균형 처리
    if (balance > 1 && getBalance(root->left) >= 0) // LL 케이스
        return rotateRight(root);
    if (balance > 1 && getBalance(root->left) < 0) { // LR 케이스
        root->left = rotateLeft(root->left);
        return rotateRight(root);
    }
    if (balance < -1 && getBalance(root->right) <= 0) // RR 케이스
        return rotateLeft(root);
    if (balance < -1 && getBalance(root->right) > 0) { // RL 케이스
        root->right = rotateRight(root->right);
        return rotateLeft(root);
    }

    return root; // 루트 반환
}

// 이진 트리에서 노드 탐색
Node *search(Node *root, int key) {
    if (root == NULL || root->key == key) return root; // 키를 찾음

    compareCount++; // 비교 횟수 증가
    if (key < root->key) // 왼쪽 서브트리 탐색
        return search(root->left, key);
    return search(root->right, key); // 오른쪽 서브트리 탐색
}

// 이진 탐색 트리(BST) 삽입 함수
Node *insertBST(Node *node, int key) {
    if (node == NULL) return createNode(key); // 새 노드 생성

    compareCount++; // 비교 횟수 증가
    if (key < node->key) // 왼쪽 서브트리에 삽입
        node->left = insertBST(node->left, key);
    else if (key > node->key) // 오른쪽 서브트리에 삽입
        node->right = insertBST(node->right, key);

    return node;
}

// BST에서 노드 삭제
Node *deleteBST(Node *root, int key) {
    if (root == NULL) return root; // 빈 트리

    compareCount++; // 비교 횟수 증가
    if (key < root->key) // 왼쪽 서브트리에서 삭제
        root->left = deleteBST(root->left, key);
    else if (key > root->key) // 오른쪽 서브트리에서 삭제
        root->right = deleteBST(root->right, key);
    else {
        // 삭제할 노드 찾음
        if ((root->left == NULL) || (root->right == NULL)) { // 하나 이하의 자식
            Node *temp = root->left ? root->left : root->right;
            if (temp == NULL) { // 자식이 없는 경우
                temp = root;
                root = NULL;
            } else // 자식이 하나인 경우
                *root = *temp;
            free(temp); // 메모리 해제
        } else {
            // 두 자식을 가진 경우
            Node *temp = minValueNode(root->right); // 오른쪽 서브트리에서 최소값
            root->key = temp->key; // 최소값 복사
            root->right = deleteBST(root->right, temp->key); // 최소값 삭제
        }
    }

    return root; // 루트 반환
}

// AVL 트리에서 2000회의 배치 작업 수행
void doAVLBatch(Node *root) {
    for (int i = 0; i < 2000; i++) {
        int A = rand() % 3;     // 작업 타입 결정 (삽입, 삭제, 탐색)
        int B = rand() % 1000;  // 랜덤 키 값 생성
        if (A == 0) // 삽입 작업
            root = insertAVL(root, B);
        else if (A == 1) // 삭제 작업
            root = deleteAVL(root, B);
        else { // 탐색 작업
            searchCount++;
            search(root, B);
        }
    }
}

// BST에서 2000회의 배치 작업 수행
void doBinaryBatch(Node *root) {
    for (int i = 0; i < 2000; i++) {
        int A = rand() % 3;     // 작업 타입 결정 (삽입, 삭제, 탐색)
        int B = rand() % 1000;  // 랜덤 키 값 생성
        if (A == 0) // 삽입 작업
            root = insertBST(root, B);
        else if (A == 1) // 삭제 작업
            root = deleteBST(root, B);
        else { // 탐색 작업
            searchCount++;
            search(root, B);
        }
    }
}

// 메인 함수
int main(int argc, char *argv[]) {
    Node *root = NULL; // 트리 초기화
    srand(time(NULL)); // 랜덤 시드 설정
    float allCount = 0.0;

    // AVL 트리에서 2000회 배치 작업 수행
    doAVLBatch(root);
    allCount = (float)compareCount / searchCount; // 평균 비교 횟수 계산
    printf("average AVL compare count: %.2f\n", allCount);

    // AVL 트리 메모리 해제
    freeTree(root);
    root = NULL;
    compareCount = searchCount = 0;

    // BST에서 2000회 배치 작업 수행
    doBinaryBatch(root);
    allCount = (float)compareCount / searchCount; // 평균 비교 횟수 계산
    printf("average Bin compare count: %.2f\n", allCount);

    // BST 메모리 해제
    freeTree(root);
    return 0;
}
