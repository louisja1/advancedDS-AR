#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

typedef long long LL;

const int N = 100005;
const int M = 200005;

int n, m, tot, dfc, blocks;
int dfn[N], low[N], col[N], rep[N];
LL ans[N];
bool bridge[M];

struct edge {
    int adj, len, id;
    edge() {}
    edge(int _adj, int _len, int _id) {
        len = _len;
        adj = _adj;
        id = _id;
    }
};

struct best {
    int x;
    LL val;
    best() {}
    best(int _x, LL _val) {
        x = _x;
        val = _val;
    }
    bool operator < (const best& oth) const {
        return val < oth.val;
    }
};

vector<edge> G[N];
vector<edge> E[N];
best H[N][2];

void Tarjan(int x, int lst) {
    dfn[x] = low[x] = ++dfc;
    for (int i = 0; i < G[x].size(); i++) {
        int y = G[x][i].adj;
        if (!dfn[y]) {
            Tarjan(y, G[x][i].id);
            low[x] = min(low[x], low[y]);
            if (low[y] > dfn[x]) {
                bridge[G[x][i].id] = true;
            }
        } else if (dfn[y] < dfn[x] && G[x][i].id != lst) {
            low[x] = min(low[x], dfn[y]);
        }
    }
}

void paint(int x, int _col) {
    col[x] = _col;
    for (int i = 0; i < G[x].size(); i++) {
        if (bridge[G[x][i].id]) continue;
        int y = G[x][i].adj;
        if (col[y]) continue;
        paint(y, _col);
    }
}

void prep(int x, int lst) {
    H[x][0] = H[x][1] = best(0, 0);
    for (int i = 0; i < E[x].size(); i++) {
        int y = E[x][i].adj;
        if (y == lst) continue;
        prep(y, x);
        best tmp = best(y, H[y][0].val + E[x][i].len);
        if (H[x][1] < tmp) {
            H[x][1] = tmp;
            if (H[x][0] < H[x][1]) {
                swap(H[x][0], H[x][1]);
            }
        }
    }
}

void calc(int x, int lst, LL up) {
    ans[x] = max(up, H[x][0].val);
    for (int i = 0; i < E[x].size(); i++) {
        int y = E[x][i].adj;
        if (y == lst) continue;
        LL tmp;
        if (y == H[x][0].x) {
            tmp = H[x][1].val;
        } else {
            tmp = H[x][0].val;
        }
        tmp += E[x][i].len;
        calc(y, x, max(tmp, up + E[x][i].len));
    }
}

int main() {
    int Case;
    scanf("%d", &Case);
    for (int ii = 1; ii <= Case; ii++) {
        scanf("%d%d", &n, &m);
        for (int i = 1; i <= n; i++) {
            G[i].clear();
            E[i].clear();
        }
        for (int i = 1; i <= m; i++) {
            int x, y, z;
            scanf("%d%d%d", &x, &y, &z);
            G[x].push_back(edge(y, z, i));
            G[y].push_back(edge(x, z, i));
        }
        dfc = 0;
        for (int i = 1; i <= n; i++) {
            dfn[i] = low[i] = col[i] = 0;
        }
        for (int i = 1; i <= m; i++) {
            bridge[i] = false;
        }
        for (int i = 1; i <= n; i++)
            if (!dfn[i]) {
                Tarjan(i, 0);
            }
        blocks = 0;
        for (int i = 1; i <= n; i++)
            if (!col[i]) {
                ++ blocks;
                rep[blocks] = i;
                paint(i, blocks);
            }
        for (int i = 1; i <= n; i++)
            for (int j = 0; j < G[i].size(); j++)
                if (bridge[G[i][j].id]) {
                    int t = G[i][j].adj;
                    E[col[i]].push_back(edge(col[t], G[i][j].len, 0));
                }
        prep(1, 0);
        calc(1, 0, 0);
        int pos = -1;
        for (int i = 1; i <= blocks; i++) {
            if (pos == -1 || ans[i] < ans[pos] || (ans[i] == ans[pos] && rep[i] < rep[pos])) {
                pos = i;
            }
        }
        cout << rep[pos] << " " << ans[pos] << endl;
    }
    return 0;
}
