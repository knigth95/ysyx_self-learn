from typing import List
from collections import defaultdict

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

# 输入描述
# 第一行输入两个正整数n,m，代表节点的数量和边的数量。
# 接下来的m行，每行输入两个正整数u,v和一个字符chr，代表节点u和节点v有一条边连接。如果 chr 为'R'，代表这条边被染红；'W'代表未被染色。

# 1<=n,m<=10^5
# 1<=u,v<=n
