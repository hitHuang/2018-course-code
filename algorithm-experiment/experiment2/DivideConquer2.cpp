#include <vector>
#include <ctime>
#include <iostream>
#include <algorithm>
#include "Point.h"
using namespace std;

extern vector<Point> scan(vector<Point>& points);

template<typename T>
void exchange(vector<T>& A, int p, int r){
    T tmp = A[p];
    A[p] = A[r];
    A[r] = tmp;
}

template<typename T>
int Partition(vector<T>& A, int p, int r){
    T key = A[r];
    int i = p - 1;
    for (size_t j = p; j < A.size(); j++){
        if (A[j] < key){
            exchange(A, ++i, j);
        }
    }
    exchange(A, ++i, r);
    return i;
}

template <typename T>
int RandomizedPartiton(vector<T>& A, int p, int r){
    srand((unsigned)time(NULL));
    int i = rand() % (r - p + 1) + p;
    exchange(A, i, r);
    return Partition(A, p, r);
}

template<typename T>
T RandomizedSelect(vector<T>& A, int p, int r, int mid){
    if (p == r)
        return A[p];
    int q = RandomizedPartiton(A, p, r);
    int k = q - p + 1;
    if (mid == k) return A[q];
    else if (mid < k)
        return RandomizedSelect(A, p, q - 1, mid);
    return RandomizedSelect(A, q + 1, r, mid - k);
}

double getMiddleX(vector<Point>& points){
    vector<double> A;
    for (auto& p : points){
        A.push_back(p.x);
    }
    int mid = A.size() >> 1;
    return RandomizedSelect(A, 0, A.size()-1, mid);
}

Point randomGeneratePointInConvexHull(vector<Point>& points){
    if (points.size() == 2){
        return Point((points[0].x+points[1].x)/2,(points[0].y+points[1].y)/2);
    }
    int i,j,k;
    i = rand() % points.size();
    j = rand() % points.size();
    while (j == i)  j = rand() % points.size();
    k = rand() % points.size();
    while (k == i || k == j) k = rand() % points.size();
    Point pi = points[i];
    Point pj = points[j];
    Point pk = points[k];
    Vector v0 = pj - pi;
    Vector v1 = pk - pi;
    double u = (double)rand() / RAND_MAX;
    double v = (double)rand() / RAND_MAX;
    if (u + v >= 1){
        u = 1 - u;
        v = 1 - v;
    }
    Point p = pi + (u*v0 + v*v1);
    return p;
}

vector<Point> convexHull(vector<Point>& points){
    if (points.size() <= 2) return points;
    if (points.size() <= 3) return outputCHPoints(points);
    double midX = getMiddleX(points);
    vector<Point> pL, pR;
    for (auto& p : points){
        if (p.x <= midX)    pL.push_back(p);
        else pR.push_back(p);
    }
    vector<Point> qL = convexHull(pL);
    vector<Point> qR = convexHull(pR);
    Point minYP = qL[0];
    int minYIndex = 0;
    for (size_t i = 1; i < qL.size(); i++){
        if (qL[i].y < minYP.y) {
            minYP = qL[i];
            minYIndex = i;
        }
    }
    Point p = randomGeneratePointInConvexHull(qL);
    vector<pair<Point, double>> sortPointsl;
    for (size_t i = minYIndex; i < qL.size(); i++){
        double angle = getPolarAngle(p, minYP, qL[i]);
        sortPointsl.push_back({qL[i], angle});
    }
    for (int i = 0; i < minYIndex; i++){
        double angle = getPolarAngle(p, minYP, qL[i]);
        sortPointsl.push_back({qL[i], angle});
    }
    vector<pair<Point, double>> sortPointsr, sortPointsr1, sortPointsr2;
    for (size_t i = 0; i < qR.size(); i++){
        double angle = getPolarAngle(p, minYP, qR[i]);
        sortPointsr.push_back({qR[i], angle});
    }
    int minAngleIndex = 0, maxAngleIndex = 0;
    double minAngle = sortPointsr[0].second;
    double maxAngle = sortPointsr[0].second;
    for (size_t i = 0; i < sortPointsr.size(); i++){
        if(sortPointsr[i].second < minAngle){
            minAngleIndex = i;
            minAngle = sortPointsr[i].second;
        }
        if(sortPointsr[i].second > maxAngle){
            maxAngleIndex = i;
            maxAngle = sortPointsr[i].second;
        }
    }
    for (int i = minAngleIndex; i != maxAngleIndex; i = (i + 1)%sortPointsr.size()){
        sortPointsr1.push_back(sortPointsr[i]);
    }
    sortPointsr1.push_back(sortPointsr[maxAngleIndex]);
    for (int i = (maxAngleIndex+1)%sortPointsr.size(); i != minAngleIndex; i = (i + 1)%sortPointsr.size()){
        sortPointsr2.push_back(sortPointsr[i]);
    }
    reverse(sortPointsr2.begin(), sortPointsr2.end());
    vector<Point> res = merge3(sortPointsl, sortPointsr1, sortPointsr2);
    return outputCHPoints(scan(res));
}
