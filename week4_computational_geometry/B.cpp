#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

const double eps = 1e-9;
const double pi = 3.141592653;

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

int n, m;

int main() {
    int T;
    scanf("%d", &T);
    puts("INTERSECTING LINES OUTPUT");
    for (int ii = 1; ii <= T; ii++) {
        double a, b, c, d;
        scanf("%lf%lf%lf%lf", &a, &b, &c, &d);
        L l1 = L(P(a, b), P(c, d));
        scanf("%lf%lf%lf%lf", &a, &b, &c, &d);
        L l2 = L(P(a, b), P(c, d));
        if (collinear(l1, l2)) puts("LINE"); else
        if (parallel(l1, l2)) puts("NONE"); else
        intersect(l1, l2).print();
    }
    puts("END OF OUTPUT");
    return 0;
}
