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
        printf("%.0lf %.0lf\n", x, y);
    }
    P Rev() {
        return P(-y, x);
    }
};
bool operator ==(P a, P b){
	return !sgn(a.x - b.x) and !sgn(a.y - b.y);
}
P operator +(P a, P b) {
    return P(a.x + b.x, a.y + b.y);
}
P operator -(P a, P b) {
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

struct line {
    P p, v;
};
P operator *(line A, line B){
	P u = B.p - A.p;
	double t = (B.v * u) / (B.v * A.v);
	return A.p + A.v * t;
}
P get(P a, P b) {
    return (a + b) / 2;
}
P get(P a, P b, P c) {
    if (a == b) return get(a, c);
    if (a == c) return get(a, b);
    if (b == c) return get(a, b);
    line ABO = (line){(a + b) / 2, (a - b).Rev()};
    line BCO = (line){(c + b) / 2, (b - c).Rev()};
    return ABO * BCO;
}

int n;
P a[N];
P O;
double r;

int main() {
    while (scanf("%d", &n) == 1 && n) {
        for (int i = 0; i < n; i++) {
            a[i].init();
        }
        random_shuffle(a, a + n);
        O = a[0]; r = 0.0;
        for (int i = 1; i < n; i++) {
            if (dis(a[i], O) < r + eps) continue;
            O = get(a[0], a[i]);
            r = dis(O, a[i]);
            for (int j = 0; j < i; j++) {
                if (dis(a[j], O) < r + eps) continue;
                O = get(a[i], a[j]);
                r = dis(O, a[i]);
                for (int k = 0; k < j; k++) {
                    if (dis(a[k], O) < r + eps) continue;
                    O = get(a[i], a[j], a[k]);
                    r = dis(O, a[i]);
                }
            }
        }
        printf("%.2lf %.2lf %.2lf\n", O.x, O.y, r);
    }
    return 0;
}
