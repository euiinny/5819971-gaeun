#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h> // for bool type
#define MAX_ELEMENT 200

typedef struct TreeNode {
    int weight;
    char ch;
    struct TreeNode *left;
    struct TreeNode *right;
} TreeNode;

typedef struct {
    TreeNode* ptree;
    char ch;
    int key;
} element;

typedef struct {
    element heap[MAX_ELEMENT];
    int heap_size;
} HeapType;

HeapType* create() {
    return (HeapType*)malloc(sizeof(HeapType));
}

void init(HeapType* h) {
    h->heap_size = 0;
}

void print_heap(HeapType* h) {
    for (int i = 1; i <= h->heap_size; i++) {
        printf("%d ", h->heap[i].key);
    }
    printf("\n");
}

void insert_min_heap(HeapType* h, element item) {
    int i;
    i = ++(h->heap_size);
    
    while ((i != 1) && (item.key < h->heap[i / 2].key)) {
        h->heap[i] = h->heap[i / 2];
        i /= 2;
    }
    h->heap[i] = item;
}

element delete_min_heap(HeapType* h) {
    int parent, child;
    element item, temp;
    
    item = h->heap[1];
    temp = h->heap[(h->heap_size)--];
    parent = 1;
    child = 2;
    while (child <= h->heap_size) {
        if ((child < h->heap_size) && (h->heap[child].key > h->heap[child + 1].key))
            child++;
        if (temp.key < h->heap[child].key) break;
        h->heap[parent] = h->heap[child];
        parent = child;
        child *= 2;
    }
    h->heap[parent] = temp;

    return item;
}

TreeNode* make_tree(TreeNode* left, TreeNode* right) {
    TreeNode* node = (TreeNode*)malloc(sizeof(TreeNode));
    node->left = left;
    node->right = right;
    return node;
}

void destroy_tree(TreeNode* root) {
    if (root == NULL) return;
    destroy_tree(root->left);  // 왼쪽 자식부터 먼저 파괴
    destroy_tree(root->right); // 오른쪽 자식 파괴
    free(root); // 현재 노드 해제
}

int is_leaf(TreeNode* root) {
    return !(root->left) && !(root->right);
}

void print_array(int codes[], int n) {
    for (int i = 0; i < n; i++)
        printf("%d", codes[i]);
    printf("\n");
}

void print_codes(TreeNode* root, int codes[], int top) {
    if (root->left) {
        codes[top] = 1;
        print_codes(root->left, codes, top + 1);
    }
    if (root->right) {
        codes[top] = 0;
        print_codes(root->right, codes, top + 1);
    }
    
    if (is_leaf(root)) {
        printf("%c: ", root->ch);
        print_array(codes, top);
    }
}

void GenerateHuffmanCodes(char ch_list[], int freq[], int n) {
    int i;
    TreeNode *node, *x;
    HeapType* heap;
    element e, e1, e2;
    int codes[100];
    int top = 0;

    // 중복 출력을 방지하기 위한 변수
    bool first_print = true;
    
    heap = create();
    init(heap);
    for (i = 0; i < n; i++) {
        node = make_tree(NULL, NULL);
        e.ch = node->ch = ch_list[i];
        e.key = node->weight = freq[i];
        e.ptree = node;
        insert_min_heap(heap, e);
        
        // 각 삽입 후 힙 상태 출력
        print_heap(heap);
    }
    
    for (i = 1; i < n; i++) {
        e1 = delete_min_heap(heap);
        e2 = delete_min_heap(heap);
        x = make_tree(e1.ptree, e2.ptree);
        e.key = x->weight = e1.key + e2.key;
        e.ptree = x;

        // 노드 결합 출력
        printf("///%d + %d -> %d\n", e1.key, e2.key, e.key);
        insert_min_heap(heap, e);
        
        // 힙 상태 출력 (중복 체크)
        if (first_print || heap->heap_size != 6) { // 원하는 크기만큼 출력
            print_heap(heap);
            first_print = false; // 다음 출력은 방지
        }
    }
    
    e = delete_min_heap(heap);
    print_codes(e.ptree, codes, top);
    destroy_tree(e.ptree);
    free(heap);
}

int main(void) {
    char characters[] = {'a', 'e', 'i', 'o', 'u', 's', 't'};
    int frequencies[] = {10, 15, 12, 3, 4, 13, 1};
    int size = sizeof(characters) / sizeof(characters[0]);
    
    GenerateHuffmanCodes(characters, frequencies, size);
    
    return 0;
}
