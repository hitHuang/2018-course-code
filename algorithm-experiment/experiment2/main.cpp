#include <iostream>
#include <cstdlib>
#include <ctime>
#include <unordered_set>
#include <set>
#include <ctime>
#include <fstream>
#include "Point.h"
using namespace std;

vector<Point> bruteForce(vector<Point>& points);

//vector<Point> preProcess(vector<Point>& points);
//vector<Point> scan(vector<Point>& points);
vector<Point> grahamScan(vector<Point>& points);

//void divide(vector<Point>& points, Point p1, Point p2,
//            unordered_set<Point, PointHash>& res);
vector<Point> divideConquer(vector<Point>& points);

vector<Point> convexHull(vector<Point>& points);

void dataGenerate(vector<Point>& points,int sz){
    srand((unsigned)time(0));
    for (int i = 0; i < 10; i++){
        for (int j = 0; j < 10; j++){
            for (int k = 0; k < sz / 100; k++){
                double x = (double)rand()/RAND_MAX * 10 + i * 1.0 * 10;
                double y = (double)rand()/RAND_MAX * 10 + j * 1.0 * 10;
                points.push_back(Point(x,y));
            }
        }
    }

    // for (int i = 0; i < sz; i++){
    //     double x = (double)rand()/RAND_MAX * 100;
    //     double y = (double)rand()/RAND_MAX * 100;
    //     points.push_back(Point(x,y));
    // }
}

void outFile(vector<Point>& points, int ch){
    ofstream dataOut;
    if (ch == 0){
        dataOut.open("dataSet.txt", ios::out);
    }
    else dataOut.open("dataRes.txt", ios::out);
    for (int i = 0; i < points.size(); i++){
        dataOut << points[i].x << " " << points[i].y << endl;
    }
    dataOut.close();
}

int main(int argc, char* argv[])
{
    //for (int sz = 1000; sz <= 100000; sz += 1000){
	int sz = 1000;
    if (argc == 2){
        sscanf(argv[1], "%d", &sz);
    }

    vector<Point> points;
    dataGenerate(points, sz);


    outFile(points, 0);
    vector<Point> res1 = bruteForce(points);
    vector<Point> res2 = grahamScan(points);
	vector<Point> res3 = divideConquer(points);

	//vector<Point> res4 = convexHull(points);

    if (!(res1 == res2 && res2 == res3)) {
            cerr << "error!" << endl;
            exit(0);
    }
	outFile(res3, 1);
    system("python plot.py");

//        clock_t begin_time1, end_time1;
//        clock_t begin_time2, end_time2;
//        clock_t begin_time3, end_time3;
//        double cost_time1, cost_time2, cost_time3;
//        begin_time1 = clock();
//        vector<Point> res1 = bruteForce(points);
//        end_time1 = clock();
//        begin_time2 = clock();
//        vector<Point> res2 = grahamScan(points);
//        end_time2 = clock();
//        begin_time3 = clock();
//        vector<Point> res3 = divideConquer(points);
//        end_time3 = clock();
//        if (res1 == res2 && res2 == res3)   cout << "the same" << endl;
//        cost_time1 = (double)(end_time1 - begin_time1);
//        cost_time2 = (double)(end_time2 - begin_time2);
//        cost_time3 = (double)(end_time3 - begin_time3);
//        cout << "cost_time1 = " << cost_time1 << "  cost_time2 = "
//        << cost_time2 << "  cost_time3 = " << cost_time3 << endl;

    //}
    return 0;
}
