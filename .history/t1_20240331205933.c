#include <stdio.h>
#include <stdlib.h>

int countGoodNodes(int n, int m, int** redEdges, int redEdgesSize, int* redEdgesColSize, int** whiteEdges, int whiteEdgesSize, int* whiteEdgesColSize) {
    int **g = (int **)malloc(sizeof(int *) * n);
    for (int i = 0; i < n; i++) {
        g[i] = (int *)malloc(sizeof(int) * n);
        for (int j = 0; j < n; j++) {
            g[i][j] = 0;
        }
    }

    for (int i = 0; i < m; i++) {
        int u = redEdges[i][0], v = redEdges[i][1];
        g[u][v] = g[v][u] = 1;
    }

    for (int i = 0; i < m; i++) {
        int u = whiteEdges[i][0], v = whiteEdges[i][1];
        g[u][v] = g[v][u] = 0;
    }

    int *cnt = (int *)malloc(sizeof(int) * n);
    for (int i = 0; i < n; i++) {
        cnt[i] = 0;
        for (int j = 0; j < n; j++) {
            cnt[i] += g[i][j];
        }
    }

    int ans = 0;
    for (int i = 0; i < n; i++) {
        if (cnt[i] == 0) {
            ans++;
        } else {
            int all_red = 1;
            for (int j = 0; j < n; j++) {
                if (g[i][j] == 0) {
                    all_red = 0;
                    break;
                }
            }
            if (all_red) {
                ans++;
            }
        }
    }

    for (int i = 0; i < n; i++) {
        free(g[i]);
    }
    free(g);
    free(cnt);

    return ans;
}

int main() {
    int n, m;
    scanf("%d %d", &n, &m);

    int **redEdges = (int **)malloc(sizeof(int *) * m);
    int *redEdgesColSize = (int *)malloc(sizeof(int) * m);
    for (int i = 0; i < m; i++) {
        redEdges[i] = (int *)malloc(sizeof(int) * 2);
        scanf("%d %d", &redEdges[i][0], &redEdges[i][1]);
        redEdgesColSize[i] = 2;
    }

    int **whiteEdges = (int **)malloc(sizeof(int *) * m);
    int *whiteEdgesColSize = (int *)malloc(sizeof(int) * m);
    for (int i = 0; i < m; i++) {
        whiteEdges[i] = (int *)malloc(sizeof(int) * 2);
        scanf("%d %d", &whiteEdges[i][0], &whiteEdges[i][1]);
        whiteEdgesColSize[i] = 2;
    }

    int ans = countGoodNodes(n, m, redEdges, m, redEdgesColSize, whiteEdges, m, whiteEdgesColSize);
    printf("%d\n", ans);

    for (int i = 0; i < m; i++) {
        free(redEdges[i]);
    }
    free(redEdges);
    free(redEdgesColSize);

    for (int i = 0; i < m; i++) {
        free(whiteEdges[i]);
    }
    free(whiteEdges);
    free(whiteEdgesColSize);

    return 0;
}