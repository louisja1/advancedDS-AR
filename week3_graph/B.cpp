#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

const int N = 10005;
const int M = 100005;

int n, m, dfc, block, top;
int spare, clash;

struct edge {
    int to, id;
    edge() {}
    edge(int _to, int _id) {
        to = _to;
        id = _id;
    }
};

vector<edge> G[N];
vector<int> H[N];

int dfn[N], low[N], stack[N], belong[N];

void Tarjan(int x, int lst) {
    dfn[x] = low[x] = ++ dfc;
    stack[++ top] = x;
    for (int i = 0; i < G[x].size(); i++) {
        int y = G[x][i].to;
        if (!dfn[y]) {
            Tarjan(y, G[x][i].id);
            low[x] = min(low[x], low[y]);
            if (low[y] > dfn[x]) {
                spare ++;
            }
            if (low[y] >= dfn[x]) {
                ++ block;
                int p;
                H[block].push_back(x);
                do {
                    p = stack[top --];
                    H[block].push_back(p);
                } while (p != y);
            }
        } else if (G[x][i].id != lst) {
            low[x] = min(low[x], dfn[y]);
        }
    }
}

int main() {
    while (scanf("%d%d", &n, &m) == 2) {
        if (!n && !m) break;
        for (int i = 1; i <= n; i++) {
            dfn[i] = low[i] = belong[i] = 0;
            G[i].clear();
            H[i].clear();
        }
        dfc = block = top = spare = clash = 0;
        for (int i = 1; i <= m; i++) {
            int x, y;
            scanf("%d%d", &x, &y);
            ++ x; ++ y;
            G[x].push_back(edge(y, i));
            G[y].push_back(edge(x, i));
        }
        for (int i = 1; i <= n; i++) {
            if (!dfn[i]) {
                Tarjan(i, 0);
            }
        }
        for (int i = 1; i <= block; i++) {
            int edge_cnt = 0, vert_cnt = 0;
            for (int j = 0; j < H[i].size(); j++) {
                belong[H[i][j]] = i;
            }
            for (int j = 0; j < H[i].size(); j++) {
                vert_cnt ++;
                int p = H[i][j];
                for (int k = 0; k < G[p].size(); k++) {
                    int adj = G[p][k].to;
                    if (belong[adj] == i) {
                        edge_cnt ++;
                    }
                }
            }
            edge_cnt >>= 1;
            if (edge_cnt > vert_cnt) {
                clash += edge_cnt;
            }
        }
        cout << spare << " " << clash << endl;
    }
    return 0;
}
