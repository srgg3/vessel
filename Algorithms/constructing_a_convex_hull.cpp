// Построение выпуклой оболочки
// Дан набор точек. Построить выпуклую оболочку, 
// которая содержит все данные точки (вывести  все точки многоугольника подряд против часовой стрелки).

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

struct Point {
    long long x, y;
};

long long cross(Point a, Point b, Point c){
    return (b.x - a.x) * (c.y - a.y) - (b.y - a.y) * (c.x - a.x);
}

bool cmp(Point a, Point b) {
    if (a.x == b.x){
        return a.y < b.y;
    }
    return a.x < b.x;
}

vector<Point> convex_hull(vector<Point> p){
    int n = p.size();
    if (n <= 1){
        return p;
    }

    sort(p.begin(), p.end(), cmp);

    vector<Point> hull;

    for (auto &pt : p){
        while (hull.size() >= 2 &&
               cross(hull[hull.size()-2], hull[hull.size()-1], pt) <= 0) {
            hull.pop_back();
        }
        hull.push_back(pt);
    }

    int t = hull.size();
    for (int i = n - 2; i >= 0; i--){
        auto pt = p[i];
        while ((int)hull.size() > t && cross(hull[hull.size()-2], hull[hull.size()-1], pt) <= 0){
            hull.pop_back();
        }
        hull.push_back(pt);
    }

    hull.pop_back();
    return hull;
}

int main() {
    int n;
    cin >> n;

    vector<Point> p(n);
    for (int i = 0; i < n; i++) {
        cin >> p[i].x >> p[i].y;
    }
    vector<Point> h = convex_hull(p);
    for (auto &pt : h) {
        cout << pt.x << " " << pt.y << endl;
    }

    return 0;
}