#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

const double eps = 1e-10;
const double inf = 1e12;

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
};
P operator-(P a, P b) {
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
double dis(P p, L l) {
    return abs((p - l.a) * l.v()) / l.v().len();
}

bool check(L l1, L l2) {
    if (collinear(l1, l2)) return true;
    if (parallel(l1, l2)) return false;
    P p = intersect(l1, l2);
    if (onSeg(p, l1) && onSeg(p, l2)) return true;
    return false;
}

int n;
double r, x, y;
vector<P> poly;

bool convex() {
    int vis[3] = {0};
    for (int i = 0; i < n; i++) {
        P fir = poly[i];
        P sec = poly[(i + 1) % n];
        P thi = poly[(i + 2) % n];
        int val = sgn(det(fir, sec, thi));
        val += 1;
        vis[val] ++;
        if (vis[0] && vis[2]) {
            return false;
        }
    }
    return true;
}

bool pointInPoly(P c) {
    L ray(P(-inf, c.y), c);
    int cnt = 0;
    for (int i = 0; i < n; i++) {
        L seg(poly[i], poly[(i + 1) % n]);
        if (onSeg(c, seg)) { // on the border
            return true;
        }
        if (onSeg(poly[i], ray)) {
            if (sgn(poly[(i + 1) % n].y, poly[i].y) > 0) {
                cnt ++;
            }
        } else if (onSeg(poly[(i + 1) % n], ray)) {
            if (sgn(poly[(i + 1) % n].y, poly[i].y) < 0) {
                cnt ++;
            }
        } else if (check(seg, ray)) {
            cnt ++;
        }
    }
    if (cnt % 2) return true;
    return false;
}

bool fit() {
    P c = P(x, y);
    if (!pointInPoly(c)) {
        return false;
    }
    for (int i = 0; i < n; i++) {
        L seg(poly[i], poly[(i + 1) % n]);
        double len = dis(c, seg);
        if (sgn(len, r) < 0) return false;
    }
    return true;
}

int main() {
    while (scanf("%d", &n) == 1 && n > 2) {
        scanf("%lf%lf%lf", &r, &x, &y);
        poly.clear();
        for (int i = 0; i < n; i++) {
            P p;
            p.init();
            poly.push_back(p);
        }
        if (!convex()) {
            puts("HOLE IS ILL-FORMED");
        } else if (fit()) {
            puts("PEG WILL FIT");
        } else {
            puts("PEG WILL NOT FIT");
        }
    }
    return 0;
}
