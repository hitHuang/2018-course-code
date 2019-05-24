#ifndef KNN_H_INCLUDED
#define KNN_H_INCLUDED
#include "data.h"
#include <vector>
#include <utility>
#include <iostream>
using namespace std;

#include <queue>
#include <cmath>
#include <array>

struct Num_Distance{
    int number;
    double distance;
    Num_Distance(int pn, double pd) : number(pn), distance(pd){}
};

bool operator> (const Num_Distance& a, const Num_Distance& b);

double Distance(Car& car1, Car& car2);
void TestKNN(Data& Train, Data& Test, int KValue);
void TestKNN(Data& Train, Data& Test, int KValue, double& ErrorRate, int& BestK);
void TrainTestKNN(int KValue);
void MultiTestKNN();
#endif // KNN_H_INCLUDED
