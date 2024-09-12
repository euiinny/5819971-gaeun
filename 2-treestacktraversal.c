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

void InsertNode(TreeNode** node, int* list, int index, int size) {
    if (index >= size) return;

    *node = createNode(list[index]);

    InsertNode(&(*node)->left, list, 2 * index + 1, size);
    InsertNode(&(*node)->right, list, 2 * index + 2, size);
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
    int arr[15] = {1, 2, 9, 3, 5, 10, 13, 4, 6, 7, 8, 11, 12, 14, 15};

    TreeNode* root = NULL;
    InsertNode(&root, arr, 0, 15);

    LinkOrders(root);

    return 0;
}
