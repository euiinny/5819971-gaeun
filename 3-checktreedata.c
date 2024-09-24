#include <stdio.h>
#include <stdlib.h>

typedef struct TreeNode {
    int data;
    struct TreeNode* left;
    struct TreeNode* right;
} TreeNode;

typedef struct QueueNode {
    TreeNode* data;
    struct QueueNode* next;
} QueueNode;

typedef struct {
    QueueNode* front;
    QueueNode* rear;
} Queue;

void initQueue(Queue* q) {
    q->front = NULL;
    q->rear = NULL;
}

int isEmpty(Queue* q) {
    return (q->front == NULL);
}

void enqueue(Queue* q, TreeNode* node) {
    QueueNode* temp = (QueueNode*)malloc(sizeof(QueueNode));
    temp->data = node;
    temp->next = NULL;
    if (q->rear != NULL) {
        q->rear->next = temp;
    }
    q->rear = temp;
    if (q->front == NULL) {
        q->front = temp;
    }
}

TreeNode* dequeue(Queue* q) {
    if (isEmpty(q)) return NULL;
    QueueNode* temp = q->front;
    TreeNode* node = temp->data;
    q->front = q->front->next;
    if (q->front == NULL) {
        q->rear = NULL;
    }
    free(temp);
    return node;
}

TreeNode* createNode(int data) {
    TreeNode* newNode = (TreeNode*)malloc(sizeof(TreeNode));
    newNode->data = data;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}

void PlaceNode(TreeNode *node, int direction, int data) {
    TreeNode* newNode = createNode(data);
    if (direction == 0) {
        node->left = newNode;
    } else {
        node->right = newNode;
    }
}

void GenerateLinkTree(TreeNode *root) {
    PlaceNode(root, 0, 2);
    PlaceNode(root, 1, 9);
    PlaceNode((root)->left, 0, 3);
    PlaceNode((root)->left, 1, 5);
    PlaceNode((root)->right, 0, 10);
    PlaceNode((root)->right, 1, 13);
    PlaceNode((root)->left->left, 0, 4);
    PlaceNode((root)->left->left, 1, 6);
    PlaceNode((root)->left->right, 0, 7);
    PlaceNode((root)->left->right, 1, 8);
    PlaceNode((root)->right->left, 0, 11);
    PlaceNode((root)->right->left, 1, 12);
    PlaceNode((root)->right->right, 0, 14);
    PlaceNode((root)->right->right, 1, 15);
}

int GetSumOfNodes(TreeNode* root) {
    if (root == NULL) return 0;
    
    Queue q;
    initQueue(&q);
    enqueue(&q, root);
    
    int sum = 0;
    
    while (!isEmpty(&q)) {
        TreeNode* current = dequeue(&q);
        sum += current->data;
        
        if (current->left != NULL) enqueue(&q, current->left);
        if (current->right != NULL) enqueue(&q, current->right);
    }
    
    return sum;
}

int GetNumberOfNodes(TreeNode* root) {
    if (root == NULL) return 0;
    
    Queue q;
    initQueue(&q);
    enqueue(&q, root);
    
    int count = 0;
    
    while (!isEmpty(&q)) {
        TreeNode* current = dequeue(&q);
        count++;
        
        if (current->left != NULL) enqueue(&q, current->left);
        if (current->right != NULL) enqueue(&q, current->right);
    }
    
    return count;
}

int GetHeightOfTree(TreeNode* root) {
    if (root == NULL) return 0;
    
    Queue q;
    initQueue(&q);
    enqueue(&q, root);
    
    int height = 0;
    
    while (!isEmpty(&q)) {
        int nodeCount = 0;
        QueueNode* front = q.front;
        
        while (front != NULL) {
            nodeCount++;
            front = front->next;
        }
        
        if (nodeCount == 0) return height;
        height++;
        
        for (int i = 0; i < nodeCount; i++) {
            TreeNode* current = dequeue(&q);
            
            if (current->left != NULL) enqueue(&q, current->left);
            if (current->right != NULL) enqueue(&q, current->right);
        }
    }
    
    return height;
}

int GetNumberOfLeafNodes(TreeNode* root) {
    if (root == NULL) return 0;
    
    Queue q;
    initQueue(&q);
    enqueue(&q, root);
    
    int leafCount = 0;
    
    while (!isEmpty(&q)) {
        TreeNode* current = dequeue(&q);
        
        if (current->left == NULL && current->right == NULL) {
            leafCount++;
        }
        
        if (current->left != NULL) enqueue(&q, current->left);
        if (current->right != NULL) enqueue(&q, current->right);
    }
    
    return leafCount;
}

int main() {
    TreeNode *root = (TreeNode*)malloc(sizeof(TreeNode));
    root->data = 1;
    root->left = NULL;
    root->right = NULL;

    GenerateLinkTree(root);

    printf("Sum of nodes: %d\n", GetSumOfNodes(root));
    printf("Number of nodes: %d\n", GetNumberOfNodes(root));
    printf("Height of tree: %d\n", GetHeightOfTree(root));
    printf("Number of leaf nodes: %d\n", GetNumberOfLeafNodes(root));

    return 0;
}
