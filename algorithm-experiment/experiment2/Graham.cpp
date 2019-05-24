#include <iostream>
#include <vector>
#include <set>
#include <stack>
#include <utility>
#include <algorithm>
#include "Point.h"
using namespace std;

static bool cmp(pair<Point,double>& pa, pair<Point,double>& pb){
    return pa.second > pb.second;
}

vector<Point> preProcess(vector<Point>& points){
    int minYIndex = getMinYIndex(points);
    swap(points, 0, minYIndex);
    vector<pair<Point, double>> sortPoint;
    Point p0 = points[0];
    sortPoint.push_back({p0,0});
    set<double> Set;
    for (size_t i = 1; i < points.size(); i++){
        double dis = distance(p0, points[i]);
        double angle = cosAngle(p0, points[i]);
        if (Set.find(angle) == Set.end()){
            Set.insert(angle);
            sortPoint.push_back({points[i], angle});
        }else{
            vector<pair<Point, double>>::iterator it = sortPoint.begin();
            for (; it != sortPoint.end(); ++it){
                if ((*it).second == angle){
                    break;
                }
            }
            if (dis > distance(p0, (*it).first)){
                sortPoint.erase(it);
                sortPoint.push_back({points[i], angle});
            }
        }
    }
    sort(++sortPoint.begin(), sortPoint.end(), cmp);
    vector<Point> res;
    for (auto& p : sortPoint)
        res.push_back(p.first);
    return res;
}

vector<Point> scan(vector<Point>& points){
    vector<Point> res;
    stack<Point> Stack;
    if (points.size() < 3)   return points;
    Stack.push(points[0]);
    Stack.push(points[1]);
    Stack.push(points[2]);
    Point p0 = points[0];
    for(size_t i = 3; i < points.size(); i++){
        Point pi = points[i];
        while (Stack.size() > 2){
            Point ptop = Stack.top();
            Stack.pop();
            Point pnext = Stack.top();
            Stack.push(ptop);
            if (oneSide(p0,pnext,ptop)*oneSide(p0,pnext,pi) >= 0 &&
                oneSide(p0,pi,ptop)*oneSide(p0,pi,pnext) >= 0 &&
                oneSide(pi,pnext,ptop)*oneSide(pi,pnext,p0) >= 0){
                Stack.pop();
            }else{
                Stack.push(pi);
                break;
            }
        }
        if (Stack.size() <= 2){
            Stack.push(pi);
        }
    }
    while (!Stack.empty()){
        res.push_back(Stack.top());
        Stack.pop();
    }
    return res;
}

vector<Point> grahamScan(vector<Point>& points){
    vector<Point> sortPoints = preProcess(points);
    vector<Point> res = outputCHPoints(scan(sortPoints));
//    cout << "-------GrahamScan-------" << endl;
//    for (auto &p : res)
//    cout << p.x << "  " << p.y << endl;
    return res;
}
