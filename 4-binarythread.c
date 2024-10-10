#include <stdio.h>
#include <stdlib.h>

// 이진 트리 노드 정의
typedef struct TreeNode {
    int data;
    struct TreeNode *left, *right;
} TreeNode;

// 스레드 이진 트리 노드 정의
typedef struct ThreadNode {
    int data;
    struct ThreadNode *left, *right;
    int ltag, rtag; // ltag: 왼쪽이 자식(0)인지 스레드(1)인지, rtag: 오른쪽이 자식(0)인지 스레드(1)인지
} ThreadNode;

// 이진 트리 노드 생성 함수
TreeNode* createTreeNode(int data) {
    TreeNode* newNode = (TreeNode*)malloc(sizeof(TreeNode));
    newNode->data = data;
    newNode->left = newNode->right = NULL;
    return newNode;
}

// 스레드 이진 트리 노드 생성 함수
ThreadNode* createThreadNode(int data) {
    ThreadNode* newNode = (ThreadNode*)malloc(sizeof(ThreadNode));
    newNode->data = data;
    newNode->left = newNode->right = NULL;
    newNode->ltag = newNode->rtag = 0; // 자식이면 0, 스레드면 1
    return newNode;
}

// 이진 탐색 트리에 데이터 삽입 (재귀 방식)
TreeNode* insertIntoBinaryTree(TreeNode* root, int data) {
    if (root == NULL)
        return createTreeNode(data);
    if (data < root->data)
        root->left = insertIntoBinaryTree(root->left, data);
    else
        root->right = insertIntoBinaryTree(root->right, data);
    return root;
}

// GenerateBinaryTree 함수 - 주어진 배열로 이진 탐색 트리 생성
TreeNode* GenerateBinaryTree(int inputData[]) {
    TreeNode* root = NULL;
    for (int i = 0; i < 15; i++) {
        root = insertIntoBinaryTree(root, inputData[i]);
    }
    return root;
}

// 중위 순회 (재귀 방식) - 이진 탐색 트리
void BinaryTreeInOrder(TreeNode* root) {
    if (root == NULL) return;
    BinaryTreeInOrder(root->left);
    printf("%d ", root->data);
    BinaryTreeInOrder(root->right);
}

// 이진 탐색 트리에서 스레드 이진 트리 생성 (재귀 방식)
void createThreadTree(ThreadNode* root, ThreadNode** prev) {
    if (root == NULL) return;

    // 왼쪽 서브트리 순회
    if (root->ltag == 0)
        createThreadTree(root->left, prev);

    // 현재 노드에 스레드 설정
    if (root->left == NULL) {
        root->left = *prev;
        root->ltag = 1; // 왼쪽에 스레드 설정
    }
    if (*prev != NULL && (*prev)->right == NULL) {
        (*prev)->right = root;
        (*prev)->rtag = 1; // 이전 노드의 오른쪽에 스레드 설정
    }

    *prev = root;

    // 오른쪽 서브트리 순회
    if (root->rtag == 0)
        createThreadTree(root->right, prev);
}

// GenerateThreadTree 함수 - 이진 탐색 트리로부터 스레드 이진 트리 생성
ThreadNode* GenerateThreadTree(int inputData[]) {
    TreeNode* bstRoot = GenerateBinaryTree(inputData);  // 이진 탐색 트리 생성
    ThreadNode* troot = (ThreadNode*)bstRoot;  // 변환된 스레드 이진 트리의 루트
    ThreadNode* prev = NULL;
    createThreadTree(troot, &prev);  // 스레드 트리로 변환
    return troot;
}

// 스레드 이진 트리 중위 순회 (반복 방식, 스택 미사용)
void ThreadTreeInOrder(ThreadNode* root) {
    ThreadNode* current = root;

    // 중위 순회를 시작하기 위해 가장 왼쪽 노드로 이동
    while (current->ltag == 0)
        current = current->left;

    // 중위 순회
    while (current != NULL) {
        printf("%d ", current->data);

        if (current->rtag == 1) {
            current = current->right;  // 스레드를 따라 이동
        } else {
            // 오른쪽 서브트리로 이동한 후, 가장 왼쪽 자식으로 이동
            current = current->right;
            while (current != NULL && current->ltag == 0)
                current = current->left;
        }
    }
}

// 메모리 해제 함수 (이진 트리)
void FreeBinaryTree(TreeNode* root) {
    if (root == NULL) return;
    FreeBinaryTree(root->left);
    FreeBinaryTree(root->right);
    free(root);
}

// 메모리 해제 함수 (스레드 이진 트리)
void FreeThreadTree(ThreadNode* root) {
    if (root == NULL) return;
    if (root->ltag == 0) FreeThreadTree(root->left);  // 자식 노드가 있을 때만 해제
    if (root->rtag == 0) FreeThreadTree(root->right);
    free(root);
}

// main 함수는 주어졌으므로 수정하지 않음
int main() {
    int inputData[] = {4, 1, 9, 13, 15, 3, 6, 14, 7, 10, 12, 2, 5, 8, 11};
    
    // 이진 탐색 트리 생성
    TreeNode* root = GenerateBinaryTree(inputData);
    printf("Binary tree inorder: ");
    BinaryTreeInOrder(root);
    printf("\n");

    // 스레드 이진 트리 생성
    ThreadNode* troot = GenerateThreadTree(inputData);
    printf("Thread tree inorder: ");
    ThreadTreeInOrder(troot);
    printf("\n");

    // 메모리 해제
    FreeBinaryTree(root);
    FreeThreadTree(troot);

    return 0;
}
