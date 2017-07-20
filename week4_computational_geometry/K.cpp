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
    double len2() {
        return sqr(x) + sqr(y);
    }
    double len() {
        return sqrt(len2());
    }
};
bool operator <(const P &a, const P &b) {
    return sgn(a.x, b.x) < 0 || ((sgn(a.x, b.x) == 0) && (sgn(a.y, b.y) < 0));
}
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
vector<P> convex(vector<P> p) {
    sort(p.begin(), p.end());
    vector<P> ans, S;
    for (int i = 0; i < p.size(); i++) {
        while (S.size() >= 2 && sgn(det(S[S.size() - 2], S.back(), p[i])) <= 0) {
            S.pop_back();
        }
        S.push_back(p[i]);
    }
    ans = S;
    S.clear();
    for (int i = (int)p.size() - 1; i >= 0; i--) {
        while (S.size() >= 2 && sgn(det(S[S.size() - 2], S.back(), p[i])) <= 0) {
            S.pop_back();
        }
        S.push_back(p[i]);
    }
    for (int i = 1; i + 1 < S.size(); i++) {
        ans.push_back(S[i]);
    }
    return ans;
}

int n, m;
vector<P> A, C;

int main() {
    int T;
    scanf("%d", &T);
    for (int ii = 1; ii <= T; ii++) {
        scanf("%d%d", &n, &m);
        A.clear();
        for (int i = 1; i <= n; i++) {
            double x, y;
            scanf("%lf%lf", &x, &y);
            A.push_back(P(x, y));
        }
        C = convex(A);
        /*for (int i = 0; i < C.size(); i++) {
            printf("!!!!!!!!%.0lf %.0lf\n", C[i].x, C[i].y);
        }*/
        double ans = 0.0;
        for (int i = 0; i < C.size() - 1; i++) {
            ans += dis(C[i], C[i + 1]);
        }
        ans += dis(C[C.size() - 1], C[0]);
        ans += 2 * pi * m;
        printf("%.0lf\n", ans);
        if (ii < T) printf("\n");
    }
    return 0;
}
