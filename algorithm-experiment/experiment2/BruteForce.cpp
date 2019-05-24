#include <iostream>
#include <algorithm>
#include "Point.h"
using namespace std;

vector<Point> bruteForce(vector<Point>& points){
    int minYIndex = getMinYIndex(points);
    swap(points, 0, minYIndex);
    vector<Point> chPoint;
    Point p0 = points[0];
    vector<int> flag(points.size(), 1);
    for (size_t i = 1; i < points.size() - 2; i++){
        if (flag[i] == 0) continue;
        Point pi = points[i];
        for (size_t j = i + 1; j < points.size() - 1; j++){
            if (flag[i] == 0 || flag[j] == 0) continue;
            Point pj = points[j];
            for (size_t k = j + 1; k < points.size(); k++){
                if (flag[i] == 0 || flag[j] == 0 || flag[k] == 0) continue;
                Point pk = points[k];
                if (oneSide(p0,pi,pj)*oneSide(p0,pi,pk) >= 0 &&
                    oneSide(p0,pj,pi)*oneSide(p0,pj,pk) >= 0 &&
                    oneSide(pi,pj,p0)*oneSide(pi,pj,pk) >= 0){
                    flag[k] = 0;
                    continue;
                }
                if (oneSide(p0,pi,pk)*oneSide(p0,pi,pj) >= 0 &&
                    oneSide(p0,pk,pi)*oneSide(p0,pk,pj) >= 0 &&
                    oneSide(pi,pk,p0)*oneSide(pi,pk,pj) >= 0){
                    flag[j] = 0;
                    continue;
                }
                if (oneSide(p0,pj,pk)*oneSide(p0,pj,pi) >= 0 &&
                    oneSide(p0,pk,pj)*oneSide(p0,pk,pi) >= 0 &&
                    oneSide(pj,pk,p0)*oneSide(pj,pk,pi) >= 0){
                    flag[i] = 0;
                    continue;
                }
            }
        }
    }
    vector<Point>().swap(chPoint);
    for (size_t i = 0; i < points.size(); i++){
        if (flag[i] == 1){
            chPoint.push_back(points[i]);
        }
    }
    vector<Point> res = outputCHPoints(chPoint);
//    cout << "-------BruteForce-------" << endl;
//    for (auto &p : res)
//    cout << p.x << "  " << p.y << endl;
    return res;
}



//std::vector<Point> bruteForce(vector<Point> points, int){
//    sort(points.begin(), points.end(), cmp);
//    vector<Point> chPoint;
//    Point p0 = points[0];
//    vector<int> flag(points.size(), 1);
//    for (size_t i = 1; i < points.size() - 2; i++){
//        if (flag[i] == 0) continue;
//        Point pi = points[i];
//        for (size_t j = i + 1; j < points.size() - 1; j++){
//            if (flag[i] == 0 || flag[j] == 0) continue;
//            Point pj = points[j];
//            if (isLine(p0,pi,pj)){
//                if (distance(p0,pi) > distance(p0,pj)) flag[j] = 0;
//                else flag[i] = 0;
//                continue;
//            }
//            for (size_t k = j + 1; k < points.size(); k++){
//                if (flag[i] == 0 || flag[j] == 0 || flag[k] == 0)   continue;
//                Point pk = points[k];
//                if (isLine(p0,pi,pk)){
//                    if (distance(p0,pi) > distance(p0,pk)) flag[k] = 0;
//                    else flag[i] = 0;
//                    continue;
//                }
//                if (isLine(p0,pk,pj)){
//                    if (distance(p0,pk) > distance(p0,pj)) flag[j] = 0;
//                    else flag[k] = 0;
//                    continue;
//                }
//                if (isLine(pi,pj,pk)){
//                    if (distance(pi,pk) > distance(pi,pj)) flag[j] = 0;
//                    else flag[k] = 0;
//                    continue;
//                }
//                if (isInTriangle(p0,pi,pj,pk)){flag[k] = 0; continue;}
//                if (isInTriangle(p0,pi,pk,pj)){flag[j] = 0; continue;}
//                if (isInTriangle(p0,pk,pj,pi)){flag[i] = 0; continue;}
//            }
//        }
//    }
//    vector<Point>().swap(chPoint);
//    for (size_t i = 0; i < points.size(); i++){
//        if (flag[i] == 1){
//            chPoint.push_back(points[i]);
//        }
//    }
//
//    sort(chPoint.begin(), chPoint.end(), cmp);
//    cout << "-------BruteForce-------" << endl;
//    for (auto &p : chPoint)
//        cout << p.x << "  " << p.y << endl;
//}
