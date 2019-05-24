#ifndef POINT_H_INCLUDED
#define POINT_H_INCLUDED
#include <vector>

#define eps 1e-8
const double Pi=3.14159265358979;

class Point{
public:
    Point(double px, double py):x(px),y(py){};
    double x;
    double y;
};

class Vector{
public:
    Vector(double px, double py):x(px),y(py){};
    double x;
    double y;
};

struct PointHash{
    std::size_t operator() (const Point& p) const {
        return p.x + p.y;
    }
};

std::size_t hash_value(const Point& p);
Vector operator-(const Point& pl, const Point& pr);
bool operator==(const Point& pl, const Point& pr);
Vector operator*(double r, const Vector& v);
double operator*(const Vector& vl, const Vector& vr);
Vector operator+(const Vector& vl, const Vector& vr);
double operator^(const Vector& vl, const Vector& vr);
bool operator==(const Vector& vl, const Vector& vr);
bool operator!=(const Vector& vl, const Vector& vr);
double length(const Vector& v);
Point operator+(const Point& p, const Vector& v);
double distance(const Point& pa, const Point& pb);
bool isLine(const Point& pa, const Point& pb, const Point& pc);
bool isInTriangle(const Point& pa, const Point& pb, const Point& pc, const Point& ps);
double oneSide(const Point& pa, const Point& pb, const Point& pc);
double cosAngle(const Point& pa, const Point& pb);
double sinAngle(const Point& po, const Point& pa, const Point& pb);
double cosAngle(const Point& po, const Point& pa, const Point& pb);
double getPolarAngle(const Point& po, const Point& pa, const Point& pb);
int getMinYIndex(std::vector<Point>& points);
void swap(std::vector<Point>& points, int i, int j);
std::vector<Point> merge3(const std::vector<std::pair<Point, double>>& , const std::vector<std::pair<Point, double>>& , const std::vector<std::pair<Point, double>>& points3);
std::vector<Point> outputCHPoints(const std::vector<Point>& chPoint);
#endif // POINT_H_INCLUDED
