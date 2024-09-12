#include <stdio.h>
#include <stdlib.h>

typedef struct TreeNode {
    int data;
    struct TreeNode* left;
    struct TreeNode* right;
} TreeNode;

void GenerateArrayTree(int* tree) {
    int list[] = {1, 2, 9, 3, 5, 10, 13, 4, 6, 7, 8, 11, 12, 14, 15};
    for(int i = 0; i < 15; i++) {
        tree[i] = list[i];
    }
    for(int i = 0; i < 15; i++) {
        printf("%d ", tree[i]);
    }
    printf("\n\n");
}

void ArrayPreOrder(int* tree, int index, int size) {
    if (index >= size || tree[index] == -1) return;

    printf("%d ", tree[index]);
    ArrayPreOrder(tree, 2 * index + 1, size);
    ArrayPreOrder(tree, 2 * index + 2, size);
}

void ArrayInOrder(int* tree, int index, int size) {
    if (index >= size || tree[index] == -1) return;

    ArrayInOrder(tree, 2 * index + 1, size);
    printf("%d ", tree[index]);
    ArrayInOrder(tree, 2 * index + 2, size);
}

void ArrayPostOrder(int* tree, int index, int size) {
    if (index >= size || tree[index] == -1) return;

    ArrayPostOrder(tree, 2 * index + 1, size);
    ArrayPostOrder(tree, 2 * index + 2, size);
    printf("%d ", tree[index]);
}

void ArrayOrders(int* tree, int size) {
    ArrayPreOrder(tree, 0, size);
    printf("\n");
    ArrayInOrder(tree, 0, size);
    printf("\n");
    ArrayPostOrder(tree, 0, size);
    printf("\n\n");
}

void LinkPreOrder(TreeNode* node) {
    if (node != NULL) {
        printf("%d ", node->data);
        LinkPreOrder(node->left);
        LinkPreOrder(node->right);
    }
}

void LinkInOrder(TreeNode* node) {
    if (node != NULL) {
        LinkInOrder(node->left);
        printf("%d ", node->data);
        LinkInOrder(node->right);
    }
}

void LinkPostOrder(TreeNode* node) {
    if (node != NULL) {
        LinkPostOrder(node->left);
        LinkPostOrder(node->right);
        printf("%d ", node->data);
    }
}

void LinkOrders(TreeNode* root) {
    LinkPreOrder(root);
    printf("\n");
    LinkInOrder(root);
    printf("\n");
    LinkPostOrder(root);
    printf("\n\n");
}

TreeNode* createNode(int data) {
    TreeNode* newNode = (TreeNode*)malloc(sizeof(TreeNode));
    newNode->data = data;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}

void InsertNode(TreeNode** node, int* list, int index, int size) {
    if (index >= size || list[index] == -1) return;

    if (*node == NULL) {
        *node = createNode(list[index]);
    }
    InsertNode(&(*node)->left, list, 2 * index + 1, size);
    InsertNode(&(*node)->right, list, 2 * index + 2, size);
}

int main() {
    int arr[15];
    GenerateArrayTree(arr);
        
    TreeNode* root = NULL;
    InsertNode(&root, arr, 0, 15);
    
    root->data;
    ArrayOrders(arr, 15);
    LinkOrders(root);
        
    return 0;
}
