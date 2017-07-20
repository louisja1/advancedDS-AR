#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

const double eps = 1e-9;
const int N = 100005;

int sgn(double x) {
    return (x > eps) - (x < -eps);
}
int sgn(double a, double b) {
    return sgn(a - b);
}

double sqr(double x) {
    return x * x;
}
struct P {
    double x, y;
    P() {}
    P(double _x, double _y) : x(_x), y(_y) {}
    void print() {
        printf("POINT %.2lf %.2lf\n", x, y);
    }
};
P operator -(P a, P b) {
    return P(a.x - b.x, a.y - b.y);
}
double operator ^(P a, P b){
	return a.x * b.x + a.y * b.y;
}
double operator *(P a, P b) {
    return a.x * b.y - a.y * b.x;
}
P operator *(P a, double b) {
    return P(a.x * b, a.y * b);
}
P operator /(P a, double b) {
    return P(a.x / b, a.y / b);
}
double det(P a, P b, P c) {
    return (b - a) * (c - a);
}

struct L {
    P a, b;
    L() {}
    L(P _a, P _b) : a(_a), b(_b) {}
    P v() { return b - a; }
};
bool collinear(L l1, L l2) {
    return sgn(det(l1.a, l1.b, l2.a)) == 0 && sgn(det(l1.a, l1.b, l2.b)) == 0;
}
bool parallel(L l1, L l2) {
    return sgn(l1.v() * l2.v()) == 0;
}
P intersect(L l1, L l2) {
    double s1 = det(l1.a, l1.b, l2.a);
    double s2 = det(l1.a, l1.b, l2.b);
    return (l2.a * s2 - l2.b * s1) / (s2 - s1);
}
bool onLine(P p, L l){
	return sgn((l.a - p) * (l.b - p)) == 0;
}
bool onSeg(P p, L s){
	return onLine(p,s) && (sgn((s.b - s.a) ^ (p - s.a)) >= 0) && (sgn((s.a - s.b) ^ (p - s.b)) >= 0);
}

vector<L> Lines;

int n, m;
bool vis[N];

bool check(L l1, L l2) {
    if (collinear(l1, l2)) return true;
    if (parallel(l1, l2)) return false;
    P p = intersect(l1, l2);
    if (onSeg(p, l1) && onSeg(p, l2)) return true;
    return false;
}

vector<int> ans;

int main() {
    while (scanf("%d", &n) == 1 && n) {
        Lines.clear();
        for (int i = 0; i < n; i++) {
            vis[i] = 1;
        }
        for (int i = 1; i <= n; i++) {
            double a, b, c, d;
            scanf("%lf%lf%lf%lf", &a, &b, &c, &d);
            Lines.push_back(L(P(a, b), P(c, d)));
        }
        ans.clear();
        for (int i = 0; i < n; i++) {
            if (!vis[i]) continue;
            for (int j = i + 1; j < n; j++) {
                if (check(Lines[i], Lines[j])) {
                    vis[i] = false;
                    break;
                }
            }
            if (vis[i]) {
                ans.push_back(i + 1);
            }
        }
        printf("Top sticks:");
        for (int i = 0; i < ans.size(); i++) {
            printf(" %d%c", ans[i], ",."[i == (int)ans.size() - 1]);
        }
        printf("\n");
    }
    return 0;
}
