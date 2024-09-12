#include <stdio.h>
#include <stdlib.h>

typedef struct TreeNode {
    int data;
    struct TreeNode* left;
    struct TreeNode* right;
} TreeNode;

typedef struct StackNode {
    TreeNode* data;
    struct StackNode* link;
} StackNode;

typedef struct {
    StackNode* top;
} LinkedStackType;

void init(LinkedStackType* s) {
    s->top = NULL;
}

int is_empty(LinkedStackType* s) {
    return (s->top == NULL);
}

void push(LinkedStackType* s, TreeNode* item) {
    StackNode* temp = (StackNode*)malloc(sizeof(StackNode));
    temp->data = item;
    temp->link = s->top;
    s->top = temp;
    printf("push(%d) ", item->data);
}

TreeNode* pop(LinkedStackType* s) {
    if (is_empty(s)) return NULL;

    StackNode* temp = s->top;
    TreeNode* data = temp->data;
    s->top = temp->link;
    free(temp);
    printf("pop(%d) ", data->data);
    return data;
}

TreeNode* createNode(int data) {
    TreeNode* newNode = (TreeNode*)malloc(sizeof(TreeNode));
    newNode->data = data;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}

void PlaceNode(TreeNode* node, int direction, int data) {
    TreeNode* newNode = createNode(data);
    if (direction == 0) {
        // 왼쪽에 배치
        node->left = newNode;
    } else {
        // 오른쪽에 배치
        node->right = newNode;
    }
}

void GenerateLinkTree(TreeNode** root) {
    // 루트 노드를 생성
    *root = createNode(1);  // 루트는 1

    // 각 노드를 수동으로 배치
    PlaceNode(*root, 0, 2);   // 1의 왼쪽에 2
    PlaceNode(*root, 1, 9);   // 1의 오른쪽에 9
    PlaceNode((*root)->left, 0, 3);  // 2의 왼쪽에 3
    PlaceNode((*root)->left, 1, 5);  // 2의 오른쪽에 5
    PlaceNode((*root)->right, 0, 10); // 9의 왼쪽에 10
    PlaceNode((*root)->right, 1, 13); // 9의 오른쪽에 13
    PlaceNode((*root)->left->left, 0, 4);  // 3의 왼쪽에 4
    PlaceNode((*root)->left->left, 1, 6);  // 3의 오른쪽에 6
    PlaceNode((*root)->left->right, 0, 7); // 5의 왼쪽에 7
    PlaceNode((*root)->left->right, 1, 8); // 5의 오른쪽에 8
    PlaceNode((*root)->right->left, 0, 11); // 10의 왼쪽에 11
    PlaceNode((*root)->right->left, 1, 12); // 10의 오른쪽에 12
    PlaceNode((*root)->right->right, 0, 14); // 13의 왼쪽에 14
    PlaceNode((*root)->right->right, 1, 15); // 13의 오른쪽에 15
}

void StackInOrder(TreeNode* root) {
    LinkedStackType s;
    init(&s);
    TreeNode* current = root;

    printf("LinkedInOrder: \n");

    while (current != NULL || !is_empty(&s)) {
        while (current != NULL) {
            push(&s, current);
            current = current->left;
        }
        current = pop(&s);
        printf("visit(%d) ", current->data);
        current = current->right;
    }
    printf("\n");
}

void StackPreOrder(TreeNode* root) {
    LinkedStackType s;
    init(&s);
    TreeNode* current = root;

    printf("LinkedPreOrder: \n");

    while (current != NULL || !is_empty(&s)) {
        while (current != NULL) {
            printf("visit(%d) ", current->data);
            push(&s, current);
            current = current->left;
        }
        current = pop(&s);
        current = current->right;
    }
    printf("\n");
}

void StackPostOrder(TreeNode* root) {
    LinkedStackType s;
    init(&s);
    TreeNode* current = root;
    TreeNode* lastVisited = NULL;

    printf("LinkedPostOrder:\n");

    while (current != NULL || !is_empty(&s)) {
        if (current != NULL) {
            push(&s, current);
            current = current->left;
        } else {
            TreeNode* peekNode = s.top->data;
            if (peekNode->right != NULL && lastVisited != peekNode->right) {
                current = peekNode->right;
            } else {
                pop(&s);
                printf("visit(%d) ", peekNode->data);
                lastVisited = peekNode;
            }
        }
    }
    printf("\n");
}

void LinkOrders(TreeNode* root) {
    StackInOrder(root);
    StackPreOrder(root);
    StackPostOrder(root);
}

int main() {
    TreeNode* root = NULL;

    GenerateLinkTree(&root);

    LinkOrders(root);

    return 0;
}
