#include <bits/stdc++.h>
#define MAXN 1000005

using namespace std;

int n_points;
struct Point {
    int x;
    int y;
    int id;
};

bool point_cmp (const Point &a, const Point &b) {
    return a.x < b.x || (a.x == b.x && a.y < b.y);
}
Point points[MAXN];
bool in_ch[MAXN];

long long cross_prod (const Point &a, const Point &b, const Point &c) {
	return ((long long) b.x - a.x) * (c.y - a.y) - (long long) (b.y - a.y) * (c.x - a.x);
}

vector<Point> convex_hull () {
    sort(points, points + n_points, point_cmp);
    // find the bottom half
    vector<Point> ch(2 * n_points);
    int ch_s = 0;
    for (int i = 0; i < n_points; i++) {
        while (ch_s > 1 && cross_prod(ch[ch_s - 2], ch[ch_s - 1], points[i]) <= 0) {
            ch_s--;
        }
        ch[ch_s++] = points[i];
    }
    // find the top half
    int low_s = ch_s;
    for (int i = n_points - 2; i >= 0; i--) {
        while (ch_s >= low_s + 1 && cross_prod(ch[ch_s - 2], ch[ch_s - 1], points[i]) <= 0) {
            ch_s--;
        }
        ch[ch_s++] = points[i];
    }
    ch.resize(ch_s - 1);
    return ch;
}

vector<int> trovacerchi(int N, vector<int> X, vector<int> Y) {
    ::n_points = N;
    for (int i = 0; i < N; i++) {
        points[i] = { X[i], Y[i], i };
    }
    points[n_points++] = { 0, 0, -1 };
    auto ch = convex_hull();
    for (auto point: ch) {
        if (point.id != -1) {
            in_ch[point.id] = true;
        }
    }
    vector<int> res;
    for (int i = 0; i < n_points; i++) {
        if (in_ch[i]) {
            res.push_back(i);
        }
    }
    return res;
}
