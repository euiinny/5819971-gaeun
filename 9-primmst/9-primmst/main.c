#include <stdio.h>
#include <stdlib.h>

#define TRUE 1
#define FALSE 0
#define MAX_VERTICES 100
#define INF 1000L  // 무한대를 나타내기 위한 값

// 그래프 구조체 정의
typedef struct GraphType {
    int n;  // 정점의 개수
    int weight[MAX_VERTICES][MAX_VERTICES];  // 간선 가중치 저장 배열
} GraphType;

int selected[MAX_VERTICES];  // 선택된 정점 여부를 저장하는 배열
int distance[MAX_VERTICES];  // 최소 거리를 저장하는 배열

// Prim 알고리즘에서 최소 거리의 정점을 찾는 함수
int FindPrimMST(int n) {
    int v = -1;  // 선택할 정점 초기화
    for (int i = 0; i < n; i++) {
        if (!selected[i] && (v == -1 || distance[i] < distance[v])) {
            v = i;
        }
    }
    return v;
}

// 그래프 초기화 함수
void graph_init(GraphType* g) {
    g->n = 0;
    for (int i = 0; i < MAX_VERTICES; i++) {
        for (int j = 0; j < MAX_VERTICES; j++) {
            g->weight[i][j] = INF;  // 모든 간선 가중치를 무한대로 초기화
        }
        selected[i] = FALSE;  // 모든 정점을 선택되지 않은 상태로 초기화
        distance[i] = INF;  // 거리도 무한대로 초기화
    }
}

// Prim 알고리즘을 이용하여 최소 신장 트리를 생성하는 함수
void prim(GraphType* g, int s) {
    int u, v;

    // 시작 정점으로부터의 거리 초기화
    for (u = 0; u < g->n; u++)
        distance[u] = INF;
    distance[s] = 0;

    printf("Prim MST Algorithm\n");

    // 모든 정점에 대해 최소 신장 트리를 확장
    for (int i = 0; i < g->n; i++) {
        u = FindPrimMST(g->n);  // 최소 거리의 정점 선택
        if (u == -1 || distance[u] == INF) return;  // 선택된 정점이 없거나, 모든 정점이 연결되지 않은 경우 종료

        selected[u] = TRUE;  // 선택된 정점을 MST에 추가
        printf("정점 %d 추가\n", u + 1);  // 정점 번호를 1부터 시작하도록 출력

        // 선택된 정점의 인접 정점의 거리 갱신
        for (v = 0; v < g->n; v++) {
            if (g->weight[u][v] != INF && !selected[v] && g->weight[u][v] < distance[v]) {
                distance[v] = g->weight[u][v];
            }
        }
    }
}

// 그래프의 간선 가중치 초기화 함수
void GenerateGraph(GraphType* g) {
    g->n = 10;  // 그래프에 있는 정점의 수

    // 간선 가중치 배열 정의
    int weights[10][10] = {
        // 1    2    3    4    5    6    7    8    9    10
        {  0,   3, INF, INF, INF,  11,  12, INF, INF, INF }, // 1
        {  3,   0,   5,   4,   1,   7,   8, INF, INF, INF }, // 2
        {INF,   5,   0,   2, INF, INF,   6,   5, INF, INF }, // 3
        {INF,   4,   2,   0,   5, INF, INF,  14, INF,  16 }, // 4
        {INF,   1, INF,   5,   0,   9, INF, INF,  18,  17 }, // 5
        { 11,   7, INF, INF,   9,   0, INF, INF, INF, INF }, // 6
        { 12,   8,   6, INF, INF, INF,   0,  13, INF, INF }, // 7
        {INF, INF,   5,  14, INF, INF,  13,   0, INF,  15 }, // 8
        {INF, INF, INF, INF,  18, INF, INF, INF,   0,  10 }, // 9
        {INF, INF, INF,  16,  17, INF, INF,  15,  10,   0 }  // 10
    };

    // 가중치 배열을 그래프에 복사
    for (int i = 0; i < g->n; i++) {
        for (int j = 0; j < g->n; j++) {
            g->weight[i][j] = weights[i][j];
        }
    }
}

int main(void) {
    GraphType* g;
    g = (GraphType*)malloc(sizeof(GraphType));  // 그래프 동적 메모리 할당
    graph_init(g);  // 그래프 초기화

    GenerateGraph(g);  // 그래프 생성

    prim(g, 0);  // Prim 알고리즘 실행, 시작 정점은 0 (정점 1에 해당)

    free(g);  // 메모리 해제
    return 0;
}
