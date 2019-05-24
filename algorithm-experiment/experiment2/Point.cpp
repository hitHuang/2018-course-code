#include "Point.h"
#include <cmath>
#include <algorithm>

using namespace std;

Vector operator-(const Point& pl, const Point& pr){
    return Vector(pl.x - pr.x, pl.y - pr.y);
}

bool operator==(const Point& pl, const Point& pr){
    return (pl.x == pr.x && pl.y == pr.y);
}

Vector operator*(double r, const Vector& v){
    return Vector(r*v.x, r*v.y);
}

Point operator+(const Point& p, const Vector& v){
    return Point(p.x+v.x, p.y+v.y);
}

double operator*(const Vector& vl,const  Vector& vr){
    return vl.x * vr.x + vl.y * vr.y;
}

double operator^(const Vector& vl, const Vector& vr){
    return vl.x*vr.y - vr.x*vl.y;
}

bool operator==(const Vector& vl, const Vector& vr){
    return (vl.x==vr.x) && (vl.y==vr.y);
}

bool operator!=(const Vector& vl, const Vector& vr){
    return !(vl==vr);
}

Vector operator+(const Vector& vl, const Vector& vr){
    return Vector(vl.x+vr.x, vl.y+vr.y);
}

double distance(const Point& pa, const Point& pb){
    return sqrt((pa.x-pb.x)*(pa.x-pb.x)+(pa.y-pb.y)*(pa.y-pb.y));
}

bool isLine(const Point& pa, const Point& pb, const Point& pc){
    Vector v0 = pc - pa;
    Vector v1 = pb - pa;
    if (v0.x*v1.y == v0.y*v1.x) return true;
    return false;
}

bool isInTriangle(const Point& pa, const Point& pb, const Point& pc, const Point& ps){
    Vector v0 = pc - pa;
    Vector v1 = pb - pa;
    Vector v2 = ps - pa;
    double d = ((v0*v0)*(v1*v1)-(v0*v1)*(v0*v1));
    double u = ((v1*v1)*(v2*v0)-(v1*v0)*(v2*v1)) / d;
    if (u <= 0 || u >= 1) return false;
    double v = ((v0*v0)*(v2*v1)-(v0*v1)*(v2*v0)) / d;
    if (v <= 0 || v >= 1) return false;
    return u + v <= 1;
}

double oneSide(const Point& pa, const Point& pb, const Point& pc){
    return pa.x*pb.y+pc.x*pa.y+pb.x*pc.y-pc.x*pb.y-pb.x*pa.y-pa.x*pc.y;
}

double cosAngle(const Point& pa, const Point& pb){
    double dis = distance(pa,pb);
    double r = pb.x - pa.x;
    return r / dis;
}

double length(const Vector& v){
    return sqrt(v.x*v.x+v.y*v.y);
}

double sinAngle(const Point& po, const Point& pa, const Point& pb){
    Vector va = pa - po;
    Vector vb = pb - po;
    double cross = va^vb;
    double mod = length(va)*length(vb);
    double angle = cross / mod;
    return angle;
}

double cosAngle(const Point& po, const Point& pa, const Point& pb){
    Vector va = pa - po;
    Vector vb = pb - po;
    double dot = va*vb;
    double mod = length(va)*length(vb);
    double angle = dot / mod;
    return angle;
}

double getPolarAngle(const Point& po, const Point& pa, const Point& pb){
    double sin = sinAngle(po, pa, pb);
    double cos = cosAngle(po, pa, pb);
    double angle = asin(sin);
    if (angle >= 0){
        if (cos < 0)    angle = Pi - angle;
    }
    else{
        if (cos >= 0)    angle += 2 * Pi;
        else    angle = Pi - angle;
    }
    return angle;
}

vector<Point> merge3(const vector<pair<Point, double>>& points1,
                     const vector<pair<Point, double>>& points2,
                     const vector<pair<Point, double>>& points3){
    vector<Point> res;
    size_t i = 0, j = 0, k = 0;
    double angle1, angle2, angle3;
    while (i < points1.size() || j < points2.size() || k < points3.size()){
        angle1 = 2 * Pi; angle2 = 2 * Pi; angle3 = 2 * Pi;
        if (i < points1.size()) angle1 = points1[i].second;
        if (j < points2.size()) angle2 = points2[j].second;
        if (k < points3.size()) angle3 = points3[k].second;
        double minAngle = angle1;
        int minAngleIndex = 1;
        if (angle2 < minAngle){ minAngle = angle2; minAngleIndex = 2;}
        if (angle3 < minAngle){ minAngle = angle3; minAngleIndex = 3;}
        if (minAngleIndex == 1) res.push_back(points1[i++].first);
        else if (minAngleIndex == 2) res.push_back(points2[j++].first);
        else if (minAngleIndex == 3) res.push_back(points3[k++].first);
        else break;
    }
    return res;
}

int getMinYIndex(vector<Point>& points){
    int res = 0;
    double minY = points[0].y;
    for (size_t i = 1; i < points.size(); i++){
        if (points[i].y < minY){
            minY = points[i].y;
            res = i;
        }
    }
    return res;
}

void swap(vector<Point>& points, int i, int j){
    Point tmp = points[i];
    points[i] = points[j];
    points[j] = tmp;
}

vector<Point> outputCHPoints(const vector<Point>& chPoint){
    double minX = chPoint[0].x;
    double maxX = chPoint[0].x;
    size_t minIndex = 0, maxIndex = 0;
    for (size_t i = 1; i < chPoint.size(); i++){
        if (chPoint[i].x < minX){ minX = chPoint[i].x; minIndex = i;}
        if (chPoint[i].x > maxX){ maxX = chPoint[i].x; maxIndex = i;}
    }
    Point pl = chPoint[minIndex];
    Point pr = chPoint[maxIndex];
    vector<Point> Su, Sd;
    for (size_t i = 0; i < chPoint.size(); i++){
        if (i == minIndex || i == maxIndex) continue;
        if (oneSide(pl,pr,chPoint[i]) > 0)  Su.push_back(chPoint[i]);
        else Sd.push_back(chPoint[i]);
    }
    Sd.push_back(pl);
    Sd.push_back(pr);
    sort(Su.begin(), Su.end(), [](Point& pa, Point& pb){return pa.x > pb.x;});
    sort(Sd.begin(), Sd.end(), [](Point& pa, Point& pb){return pa.x < pb.x;});
    vector<Point> res;
    for (auto p : Sd)   res.push_back(p);
    for (auto p : Su)   res.push_back(p);
    return res;
}
