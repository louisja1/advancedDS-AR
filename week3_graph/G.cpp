#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

const int N = 1000005;

int n, m, q, dfc;
int dfn[N], low[N], stack[N], dep[N], block, cnt;
int col[N];
int fa[N][20];

struct edge {
    int adj, id;
    edge() {}
    edge(int _adj, int _id) {
        adj = _adj;
        id = _id;
    }
};

vector<edge> G[N];
vector<int> E[N];

void Tarjan(int x, int lst) {
    dfn[x] = ++ dfc;
	low[x] = dfn[x];
	for (int i = 0; i < G[x].size(); i++) {
        if (G[x][i].id == lst) continue;
        int y = G[x][i].adj;
		if (!dfn[y]){
            stack[++ cnt] = y;
			Tarjan(y, G[x][i].id);
			low[x] = min(low[x], low[y]);
            if (low[y] == dfn[x]) {
                ++ block;
                E[x].push_back(block + n);
                E[block + n].push_back(x);
                for ( ;; cnt --) {
                    E[block + n].push_back(stack[cnt]);
                    E[stack[cnt]].push_back(block + n);
                    if (stack[cnt] == y) {cnt --; break;}
                }
            } else if (low[y] > dfn[x]) {
                E[x].push_back(y);
                E[y].push_back(x);
                cnt --;
            }
		}
		else low[x] = min(low[x], dfn[y]);
	}
}

void prep(int x, int _col) {
    col[x] = _col;
    for (int i = 1; i <= 19; i++) {
        fa[x][i] = fa[fa[x][i - 1]][i - 1];
    }
    for (int i = 0; i < E[x].size(); i++) {
        int y = E[x][i];
        if (y == fa[x][0]) continue;
        fa[y][0] = x;
        dep[y] = dep[x] + 1;
        prep(y, _col);
    }
}

int lca(int x, int y) {
    if (dep[y] > dep[x]) swap(x, y);
    for (int i = 19; i >= 0; i--) {
        if (dep[fa[x][i]] >= dep[y]) {
            x = fa[x][i];
        }
    }
    if (x == y) return x;
    for (int i = 19; i >= 0; i--) {
        if (fa[x][i] != fa[y][i]) {
            x = fa[x][i];
            y = fa[y][i];
        }
    }
    return fa[x][0];
}

int main() {
    scanf("%d%d%d", &n, &m, &q);
    for (int i = 1; i <= n; i++) {
        G[i].clear();
        E[i].clear();
        dfn[i] = low[i] = col[i] = 0;
    }
    for (int i = 1; i <= m; i++) {
        int x, y;
        scanf("%d%d", &x, &y);
        G[x].push_back(edge(y, i));
        G[y].push_back(edge(x, i));
    }
    block = 0; cnt = 0;
    for (int i = 1; i <= n; i++)
        if (!dfn[i]) {
            Tarjan(i, 0);
        }
    int cols = 0;
    for (int i = 1; i <= n; i++) {
        if (col[i]) continue;
        ++ cols;
        dep[i] = 1;
        prep(i, cols);
    }
    for (int i = 1; i <= q; i++) {
        int x, y, z;
        scanf("%d%d%d", &x, &y, &z);
        if (col[x] != col[y] || col[x] != col[z]) {
            cout << "NO" << endl;
            continue;
        }
        int oth = lca(x, y) ^ lca(y, z) ^ lca(x, z);
        if (oth == z) {
            cout << "YES" << endl;
            continue;
        }
        if (oth > n && (fa[oth][0] == z || fa[z][0] == oth)) {
            cout << "YES" << endl;
            continue;
        }
        cout << "NO" << endl;
    }
    return 0;
}
