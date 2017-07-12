#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

const int N = 10005;
const int M = 100005;

vector<int> G[N];
int n, m;
int dfn[N], low[N], comp[N], stack[N];
int stamp, comps, top;

void Tarjan(int x) {
    dfn[x] = low[x] = ++ stamp;
    stack[++ top] = x;
    for (int i = 0; i < G[x].size(); i++) {
        int y = G[x][i];
        if (!dfn[y]) {
            Tarjan(y);
            low[x] = min(low[x], low[y]);
        } else if (!comp[y]) {
            low[x] = min(low[x], dfn[y]);
        }
    }
    if (dfn[x] == low[x]) {
        comps ++;
        while (1) {
            int y = stack[top --];
            comp[y] = comps;
            if (y == x) break;
        }
    }
}

int main() {
    while (scanf("%d%d", &n, &m) == 2) {
        if (!n && !m) break;
        stamp = comps = top = 0;
        for (int i = 1; i <= n; i++) {
            G[i].clear();
            dfn[i] = comp[i] = 0;
        }
        for (int i = 1; i <= m; i++) {
            int x, y;
            scanf("%d%d", &x, &y);
            G[x].push_back(y);
        }
        for (int i = 1; i <= n; i++)
            if (!dfn[i]) {
                Tarjan(i);
            }
        if (comps == 1) puts("Yes");
        else puts("No");
    }
    return 0;
}
