#include <stdio.h>
#include <stdlib.h>

#define MAX_NODES 11

int graph[MAX_NODES][MAX_NODES] = {
    {0, 0, 1, 0, 0, 1, 0, 0, 0, 1},
    {0, 0, 0, 0, 1, 1, 0, 1, 0, 0},
    {1, 0, 0, 1, 1, 0, 0, 0, 0, 0},
    {0, 0, 1, 0, 1, 1, 0, 0, 0, 0},
    {1, 1, 1, 1, 0, 1, 1, 1, 0, 0},
    {1, 1, 0, 1, 1, 0, 0, 0, 0, 0},
    {1, 0, 0, 0, 1, 0, 0, 1, 1, 0},
    {0, 1, 0, 0, 1, 0, 1, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 1, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 1, 0},
    {0, 1, 0, 0, 0, 0, 0, 1, 1, 0}
};

void depth_first_search(int start, int goal) {
    int stack[MAX_NODES], top = -1;
    int visited[MAX_NODES] = {0};
    int visited_count = 0;
    int search_path[MAX_NODES]; // 경로 저장을 위한 배열
    int path_index = 0; // 경로 인덱스

    stack[++top] = start;

    while (top != -1) {
        int node = stack[top--];

        // 노드가 이미 방문되었는지 확인
        if (visited[node]) {
            continue;
        }

        visited[node] = 1;
        search_path[path_index++] = node; // 경로에 노드 추가
        visited_count++;

        // 방문한 노드 출력
        printf("%d ", node);

        // 목표 노드에 도달한 경우
        if (node == goal) {
            printf("\n탐색 성공: %d\n", goal);
            printf("방문한 노드의 수: %d\n", visited_count);
            return;
        }

        // 인접 노드를 스택에 추가
        for (int i = MAX_NODES - 1; i >= 0; i--) {
            if (graph[node][i] == 1 && !visited[i]) {
                stack[++top] = i;
            }
        }

        // 백트래킹 노드 출력
        if (path_index > 0) {
            path_index--; // 현재 노드를 경로에서 제거 (백트래킹)
        }
    }

    printf("\n탐색 실패\n");
    printf("방문한 노드의 수: %d\n", visited_count);
}

void breadth_first_search(int start, int goal) {
    int queue[MAX_NODES], front = -1, rear = -1;
    int visited[MAX_NODES] = {0};
    int visited_count = 0;

    queue[++rear] = start;

    while (front < rear) {
        front++;
        int node = queue[front];

        // 노드가 이미 방문되었는지 확인
        if (visited[node]) {
            continue;
        }

        visited[node] = 1;
        visited_count++;
        printf("%d ", node);

        // 목표 노드에 도달한 경우
        if (node == goal) {
            printf("\n탐색 성공: %d\n", goal);
            printf("방문한 노드의 수: %d\n", visited_count);
            return;
        }

        // 인접 노드를 큐에 추가
        for (int i = 0; i < MAX_NODES; i++) {
            if (graph[node][i] == 1 && !visited[i]) {
                queue[++rear] = i;
            }
        }
    }

    printf("\n탐색 실패\n");
    printf("방문한 노드의 수: %d\n", visited_count);
}

int main() {
    while (1) {
        int menu_input;
        printf("\n1: 깊이 우선 탐색\n");
        printf("2: 너비 우선 탐색\n");
        printf("3: 종료\n");
        printf("메뉴 입력: ");
        scanf("%d", &menu_input);

        if (menu_input == 1) {
            int start, goal;
            printf("시작 번호와 탐색할 값 입력: ");
            scanf("%d %d", &start, &goal);
            depth_first_search(start, goal);
        } else if (menu_input == 2) {
            int start, goal;
            printf("시작 번호와 탐색할 값 입력: ");
            scanf("%d %d", &start, &goal);
            breadth_first_search(start, goal);
        } else if (menu_input == 3) {
            printf("프로그램 종료\n");
            break;
        } else {
            printf("잘못된 입력입니다. 다시 시도하세요.\n");
        }
    }

    return 0;
}
