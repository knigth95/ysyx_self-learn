class Solution:
    def countGoodNodes(self, n: int, m: int, redEdges: List[List[int]], whiteEdges: List[List[int]]) -> int:
        g = [defaultdict(int) for _ in range(n)]
        for u, v in redEdges:
            g[u][v] = g[v][u] = 1
        for u, v in whiteEdges:
            g[u][v] = g[v][u] = 0
        cnt = [0] * n
        for u in range(n):
            for v in g[u]:
                cnt[u] += g[u][v]
        return sum(cnt[u] == len(g[u]) for u in range(n))
