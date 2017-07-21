#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>
#include <vector>
#include <deque>
#include <cmath>

using namespace std;

const double eps = 1e-10;
const int N = 1505;

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
    double len2() {
        return sqr(x) + sqr(y);
    }
    double len() {
        return sqrt(len2());
    }
    void init() {
        scanf("%lf%lf", &x, &y);
    }
    void print() {
        printf("(%.0lf,%.0lf)\n", x, y);
    }
    int quad() const {
        return sgn(y) == 1 || (sgn(y) == 0 && sgn(x) >= 0);
    }
};
P operator-(P a, P b) {
    return P(a.x - b.x, a.y - b.y);
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
double operator ^(P a, P b){
	return a.x * b.x + a.y * b.y;
}
double det(P a, P b, P c) {
    return (b - a) * (c - a);
}
double dis(P a, P b) {
    return (b - a).len();
}
double Area(vector<P> poly) {
    double ans = 0.0;
    for (int i = 1; i < poly.size(); i++) {
        ans += (poly[i] - poly[0]) * (poly[(i + 1) % poly.size()] - poly[0]);
    }
    return fabs(ans) / 2;
}

struct L {
    P a, b;
    L() {}
    L(P _a, P _b) : a(_a), b(_b) {}
    P v() { return b - a; }
    bool onLeft(const P &p) const {
        return sgn((b - a) * (p - a)) > 0;
    }
};
P intersect(L l1, L l2) {
    double s1 = det(l1.a, l1.b, l2.a);
    double s2 = det(l1.a, l1.b, l2.b);
    return (l2.a * s2 - l2.b * s1) / (s2 - s1);
}
bool parallel(L l1, L l2) {
    return sgn(l1.v() * l2.v()) == 0;
}
bool sameDir(const L &l0, const L &l1) {
    return parallel(l0, l1) && sgn((l0.b - l0.a) ^ (l1.b - l1.a)) == 1;
}
bool operator < (const P &a, const P &b) {
    if (a.quad() != b.quad())
        return a.quad() < b.quad();
    else
        return sgn((a * b)) > 0;
}
bool operator < (const L &l0, const L &l1) {
    if (sameDir(l0, l1))
        return l1.onLeft(l0.a);
    else
        return (l0.b - l0.a) < (l1.b - l1.a);
}
bool check(const L &u, const L &v, const L &w) {
    return w.onLeft(intersect(u, v));
}
vector<P> intersection(vector<L> &l) {
    sort(l.begin(), l.end());
    deque<L> q;
    for (int i = 0; i < l.size(); i++) {
        if (i && sameDir(l[i], l[i - 1])) {
            continue;
        }
        while (q.size() > 1 && !check(q[q.size() - 2], q[q.size() - 1], l[i])) {
            q.pop_back();
        }
        while (q.size() > 1 && !check(q[1], q[0], l[i])) {
            q.pop_front();
        }
        q.push_back(l[i]);
    }
    while (q.size() > 2 && !check(q[q.size() - 2], q[q.size() - 1], q[0])) {
        q.pop_back();
    }
    while (q.size() > 2 && !check(q[1], q[0], q[q.size() - 1])) {
        q.pop_front();
    }
    vector<P> ret;
    for (int i = 0; i < q.size(); i++)
        ret.push_back(intersect(q[i], q[(i + 1) % q.size()]));
    return ret;
}

int T, n;
P a[N];
vector<L> lines;

int main() {
    scanf("%d", &T);
    for (int ii = 1; ii <= T; ii++) {
        scanf("%d", &n);
        lines.clear();
        for (int i = 0; i < n; i++) {
            a[i].init();
        }
        for (int i = n - 1; i >= 0; i--) {
            lines.push_back(L(a[i], a[(i - 1 + n) % n]));
        }
        double ans = Area(intersection(lines));
        printf("%.2lf\n", ans);
    }
    return 0;
}
