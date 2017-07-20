#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

const double eps = 1e-10;

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
    void print() {
        printf("(%.0lf,%.0lf)\n", x, y);
    }
};
P operator-(P a, P b) {
    return P(a.x - b.x, a.y - b.y);
}
double operator *(P a, P b) {
    return a.x * b.y - a.y * b.x;
}
double det(P a, P b, P c) {
    return (b - a) * (c - a);
}
double dis(P a, P b) {
    return (b - a).len();
}

int n, m;
vector<P> p;

bool operator <(const P &a, const P &b) {
    int ret = sgn(det(p[0], a, b));
    if (ret == 0) {
        return dis(a, p[0]) < dis(b, p[0]);
    }
    return ret > 0;
}


int main() {
    double x, y;
    p.clear();
    while (scanf("%lf%lf", &x, &y) == 2) {
        p.push_back(P(x, y));
    }
    sort(p.begin() + 1, p.end());
    for (int i = 0; i < p.size(); i++)
        p[i].print();
    return 0;
}
