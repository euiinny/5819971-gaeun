#include <stdio.h>
#include <stdlib.h>

#define MAX_VERTICES 100
#define INF 1000

// 엣지 구조체: 시작 정점, 끝 정점, 가중치를 저장
typedef struct {
    int start, end, weight;
} Edge;

// 그래프 구조체: 정점의 개수와 엣지 배열을 포함
typedef struct {
    int n;
    Edge edges[MAX_VERTICES];
} GraphType;

// 최소 힙 구조체: 엣지 배열과 힙의 크기를 저장
typedef struct {
    Edge heap[MAX_VERTICES];
    int size;
} MinHeap;

// 그래프 초기화 함수
void graph_init(GraphType* g) {
    g->n = 0;
}

// 그래프에 엣지 추가 함수
void insert_edge(GraphType* g, int start, int end, int w) {
    g->edges[g->n].start = start;
    g->edges[g->n].end = end;
    g->edges[g->n].weight = w;
    g->n++;
}

// 미리 정의된 엣지 집합을 그래프에 추가하는 함수
void GenerateGraph(GraphType* g) {
    insert_edge(g, 1, 2, 3);
    insert_edge(g, 2, 3, 5);
    insert_edge(g, 1, 6, 11);
    insert_edge(g, 2, 6, 7);
    insert_edge(g, 5, 6, 9);
    insert_edge(g, 2, 5, 1);
    insert_edge(g, 2, 4, 4);
    insert_edge(g, 4, 5, 13);
    insert_edge(g, 5, 9, 18);
    insert_edge(g, 1, 7, 12);
    insert_edge(g, 3, 7, 6);
    insert_edge(g, 7, 8, 13);
    insert_edge(g, 3, 8, 5);
    insert_edge(g, 4, 8, 14);
    insert_edge(g, 8, 10, 15);
    insert_edge(g, 9, 10, 10);
    insert_edge(g, 4, 10, 16);
    insert_edge(g, 5, 10, 17);
    insert_edge(g, 3, 4, 2);
    insert_edge(g, 2, 7, 8);
}

// 엣지를 가중치 기준으로 비교하는 함수 (qsort용)
int compare(const void* a, const void* b) {
    Edge* x = (Edge*)a;
    Edge* y = (Edge*)b;
    return x->weight - y->weight;
}

int parent[MAX_VERTICES];

// 집합 초기화 함수: 모든 정점을 서로소 집합으로 초기화
void set_init(int n) {
    for (int i = 0; i < n; i++)
        parent[i] = -1;
}

// 루트 정점을 찾는 함수 (경로 압축 기법 사용)
int set_find(int curr) {
    if (parent[curr] == -1)
        return curr;
    return parent[curr] = set_find(parent[curr]);
}

// 두 집합을 합치는 함수
void set_union(int a, int b) {
    int root1 = set_find(a);
    int root2 = set_find(b);
    if (root1 != root2)
        parent[root1] = root2;
}

// Kruskal 알고리즘 (qsort 기반) 함수
void QuickKruskal(GraphType* g) {
    int edge_accepted = 0;
    int uset, vset;

    qsort(g->edges, g->n, sizeof(Edge), compare); // 엣지를 가중치 기준으로 정렬

    printf("Quick Based Kruskal \n");
    set_init(MAX_VERTICES);

    for (int i = 0; i < g->n; i++) {
        uset = set_find(g->edges[i].start);
        vset = set_find(g->edges[i].end);
        if (uset != vset) {
            // 선택된 엣지 출력
            printf("Edge (%d, %d) select %d\n", g->edges[i].start, g->edges[i].end, g->edges[i].weight);
            set_union(uset, vset);
            edge_accepted++;
        }
        if (edge_accepted == g->n - 1)
            break;
    }
}

// 최소 힙 초기화 함수
void minHeapInit(MinHeap* h) {
    h->size = 0;
}

// 최소 힙에 엣지를 삽입하는 함수
void minHeapInsert(MinHeap* h, Edge e) {
    int i = h->size++;
    while (i > 0) {
        int parent = (i - 1) / 2;
        if (h->heap[parent].weight <= e.weight)
            break;
        h->heap[i] = h->heap[parent];
        i = parent;
    }
    h->heap[i] = e;
}

// 최소 힙에서 최소 가중치 엣지를 삭제하고 반환하는 함수
Edge minHeapDelete(MinHeap* h) {
    Edge minEdge = h->heap[0];
    Edge lastEdge = h->heap[--h->size];

    int parent = 0;
    int child = 1;
    while (child < h->size) {
        if (child + 1 < h->size && h->heap[child + 1].weight < h->heap[child].weight)
            child++;
        if (lastEdge.weight <= h->heap[child].weight)
            break;
        h->heap[parent] = h->heap[child];
        parent = child;
        child = 2 * parent + 1;
    }
    h->heap[parent] = lastEdge;
    return minEdge;
}

// Kruskal 알고리즘 (MinHeap 기반) 함수
void MinHeapKruskal(GraphType* g) {
    MinHeap heap;
    minHeapInit(&heap);
    int edge_accepted = 0;
    int uset, vset;

    // 모든 엣지를 최소 힙에 삽입
    for (int i = 0; i < g->n; i++) {
        minHeapInsert(&heap, g->edges[i]);
    }

    printf("MinHeap Based Kruskal\n");
    set_init(MAX_VERTICES);

    while (heap.size > 0) {
        Edge edge = minHeapDelete(&heap);
        uset = set_find(edge.start);
        vset = set_find(edge.end);
        if (uset != vset) {
            // 선택된 엣지 출력
            printf("Edge (%d, %d) select %d\n", edge.start, edge.end, edge.weight);
            set_union(uset, vset);
            edge_accepted++;
        }
        if (edge_accepted == g->n - 1)
            break;
    }
}

int main(void) {
    GraphType* g;
    g = (GraphType*)malloc(sizeof(GraphType));
    graph_init(g); // 그래프 초기화
    GenerateGraph(g); // 그래프 생성
    QuickKruskal(g); // Qsort 기반 Kruskal 알고리즘 실행
    MinHeapKruskal(g); // MinHeap 기반 Kruskal 알고리즘 실행
    free(g); // 메모리 해제
    return 0;
}
