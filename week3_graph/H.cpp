#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>

using namespace std;

const int T = 2005;
const int M = T * T * 4;
const int INF = 999999999;

int n, m, s, t, ans, tot;
int g[T], adj[M * 2], nxt[M * 2], f[M * 2];
int cnt[T], dist[T], cur[T], fa[T], dat[T];
int pre[T], pig[T];

void add(int x, int y, int ff, int rf) {
    adj[++tot] = y; nxt[tot] = g[x]; g[x] = tot; f[tot] = ff;
    adj[++tot] = x; nxt[tot] = g[y]; g[y] = tot; f[tot] = rf;
}

int sap(int s, int t) {
    int x, sum;
    for (int i = 1; i <= t; i++) {
        dist[i] = 1;
        cur[i] = g[i];
        fa[i] = dat[i] = cnt[i] = 0;
    }
    cnt[0] = 1; cnt[1] = t - 1;
    dist[t] = 0;
    dat[s] = INF;
    x = s;
    sum = 0;
    while (1) {
        int p;
        for (p = cur[x]; p; p = nxt[p]) {
            if (f[p] > 0 && dist[adj[p]] == dist[x] - 1) break;
        }
        if (p > 0) {
            cur[x] = p;
            fa[adj[p]] = p;
            dat[adj[p]] = min(dat[x], f[p]);
            x = adj[p];
            if (x == t) {
                sum += dat[x];
                while (x != s) {
                    f[fa[x]] -= dat[t];
                    f[fa[x] ^ 1] += dat[t];
                    x = adj[fa[x] ^ 1];
                }
            }
        } else {
            cnt[dist[x]] --;
            if (cnt[dist[x]] == 0) return sum;
            dist[x] = t + 1;
            for (int p = g[x]; p; p = nxt[p]) {
                if (f[p] > 0 && dist[adj[p]] + 1 < dist[x]) {
                    dist[x] = dist[adj[p]] + 1;
                    cur[x] = p;
                }
            }
            cnt[dist[x]] ++;
            if (dist[s] > t) return sum;
            if (x != s) x = adj[fa[x] ^ 1];
        }
    }
}

int main() {
    ans = 0; tot = 1;
    scanf("%d%d", &n, &m);
    s = m + 1; t = m + 2;
    for (int i = 1; i <= n; i++) {
        scanf("%d", &pig[i]);
    }
    for (int i = 1; i <= t; i++) {
        g[i] = 0;
    }
    for (int i = 1; i <= n; i++) {
        pre[i] = s;
    }
    for (int i = 1; i <= m; i++) {
        int size;
        scanf("%d", &size);
        for (int j = 1; j <= size; j++) {
            int type;
            scanf("%d", &type);
            add(pre[type], i, (pre[type] == s) ? pig[type] : INF, 0);
            pre[type] = i;
        }
        int req;
        scanf("%d", &req);
        add(i, t, req, 0);
    }
    cout << sap(s, t) << endl;
    return 0;
}
