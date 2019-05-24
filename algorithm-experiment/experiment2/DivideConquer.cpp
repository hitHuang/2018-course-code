#include <iostream>
#include <cstdlib>
#include <algorithm>
#include <unordered_set>
#include <functional>
#include <cmath>
#include <vector>
#include "Point.h"

using namespace std;

void divide(vector<Point>& points, Point p1, Point p2, unordered_set<Point, PointHash>& res){
    if (res.find(p1) == res.end())  res.insert(p1);
    if (res.find(p2) == res.end())  res.insert(p2);
    if (points.size() == 0) return ;
    Point pMax = points[0];
    if (points.size() == 1) {
        if (res.find(pMax) == res.end()){
            res.insert(pMax);
        }
        return ;
    }
    double maxArea = oneSide(p1, p2, pMax);
    for (size_t i = 1; i < points.size(); i++){
        double area = oneSide(p1, p2, points[i]);
        if (area - maxArea > eps){
            maxArea = area; pMax = points[i];
        }
    }
    vector<Point> points1, points2;
    for (auto& p : points){
        if (p == p1 || p == p2) continue;
        if (oneSide(p1, pMax, p) > 0)   points1.push_back(p);
        if (oneSide(pMax, p2, p) > 0)   points2.push_back(p);
    }
    divide(points1, p1, pMax, res);
    divide(points2, pMax, p2, res);
}

vector<Point> divideConquer(vector<Point>& points){
    double minX = points[0].x;
    double maxX = points[0].x;
    size_t minIndex = 0, maxIndex = 0;
    for (size_t i = 0; i < points.size(); i++){
        if (points[i].x - minX < -eps){ minX = points[i].x; minIndex = i;}
        if (points[i].x - maxX > eps){ maxX = points[i].x; maxIndex = i;}
    }
    Point pl = points[minIndex];
    Point pr = points[maxIndex];
    vector<Point> points1, points2;
    for (auto& p : points){
        double r = oneSide(pl,pr,p);
        if (fabs(r) < eps) continue;
        if (r > 0){ points1.push_back(p);}
        if (r < 0){ points2.push_back(p);}
    }
    unordered_set<Point, PointHash> s;
    divide(points1,pl,pr,s);
    divide(points2,pr,pl,s);
    vector<Point> res;
    for (auto& p : s)   res.push_back(p);
    res = outputCHPoints(res);
//    cout << "-------DivideConquer-------" << endl;
//    for (auto &p : res)
//    cout << p.x << "  " << p.y << endl;
    return res;
}
