#include "include/knn.h"

//vector<int> ErrorNum_KNN;

bool operator> (const Num_Distance& a, const Num_Distance& b){
    return a.distance > b.distance;
}

double Distance(Car& car1, Car& car2){
    double dist = 0;
    dist += (car1.Buying - car2.Buying)*(car1.Buying - car2.Buying);
    dist += (car1.Maint - car2.Maint)*(car1.Maint - car2.Maint);
    dist += (car1.Doors - car2.Doors)*(car1.Doors - car2.Doors);
    dist += (car1.Persons/2 - car2.Persons/2)*(car1.Persons/2 - car2.Persons/2);
    dist += (car1.Lug_boot - car2.Lug_boot)*(car1.Lug_boot - car2.Lug_boot);
    dist += (car1.Safety - car2.Safety)*(car1.Safety - car2.Safety);
    return dist;
}

void PrintTestKNN(int KValue, int YesNum, int NoNum){
    cout << "---------KNN with K = " << KValue << "----------" << endl;
    cout << "Total : " << YesNum + NoNum << endl;
    cout << "Yes   : " << YesNum << "  ";
    cout << "No : " << NoNum << endl;
    cout << "error rate : " << NoNum * 1.0 / (YesNum + NoNum) << endl;
}
static int TP = 0;
static int FP = 0;
static int FN = 0;
static int TN = 0;
void TestKNN(Data& Train, Data& Test, int KValue){
    priority_queue<Num_Distance, vector<Num_Distance>, greater<Num_Distance>> PQ;
    int YesNum = 0;
    int NoNum = 0;
    for (int i = 0; i < Test.size; i++){
        Car car = Test.CarSet[i];
        priority_queue<Num_Distance, vector<Num_Distance>, greater<Num_Distance>>().swap(PQ);
        for (int i = 0; i < Train.size; i++){
            double dist = Distance(Train.CarSet[i], car);
            Num_Distance nd(i, dist);
            PQ.push(nd);
        }
        vector<Num_Distance> Neighbors;
        for (int i = 0; i < KValue; i++){
            Neighbors.push_back(PQ.top());
            PQ.pop();
        }
        array<int, LabelAttrSize> LabelArray = {0};
        for (int i = 0; i < KValue; i++){
            LabelArray[Train.CarSet[Neighbors[i].number].Clas-1]++;
        }
        int MaxNum = 0;
        Label_Type label;
        for (int i = 0; i < LabelAttrSize; i++){
            if (LabelArray[i] > MaxNum){
                MaxNum = LabelArray[i];
                label = static_cast<Label_Type>(i);
            }
        }
        if (label == static_cast<int>(car.Clas-1)){
            YesNum++;

            if (car.Clas-1 == Unacc)    TP++;
            else TN++;
        }
        else{
            NoNum++;

            if (car.Clas-1 == Unacc)    FN++;
            else if (static_cast<int>(label) == Unacc) FP++;
            else    TN++;
        }
    }
    PrintTestKNN(KValue, YesNum, NoNum);
    cout << "TP : " << TP << "  FP : " << FP << "  FN : " << FN << "  TN : " << TN << endl;
    cout << "accuracy : " << (TP + TN) * 1.0 / Test.size << "  ";
    cout << "precision : " << TP * 1.0 / (TP + FP) << "  ";
    cout << "recall : " << TP * 1.0 / (TP + FN) << endl << endl;
}

void TestKNN(Data& Train, Data& Test, int KValue, double& ErrorRate, int& BestK){
    priority_queue<Num_Distance, vector<Num_Distance>, greater<Num_Distance>> PQ;
    int YesNum = 0;
    int NoNum = 0;
    //vector<int>().swap(ErrorNum_KNN);
    for (int i = 0; i < Test.size; i++){
        Car car = Test.CarSet[i];
        priority_queue<Num_Distance, vector<Num_Distance>, greater<Num_Distance>>().swap(PQ);
        for (int i = 0; i < Train.size; i++){
            double dist = Distance(Train.CarSet[i], car);
            Num_Distance nd(i, dist);
            PQ.push(nd);
        }
        vector<Num_Distance> Neighbors;
        for (int i = 0; i < KValue; i++){
            Neighbors.push_back(PQ.top());
            PQ.pop();
        }
        array<int, LabelAttrSize> LabelArray = {0};
        for (int i = 0; i < KValue; i++){
            LabelArray[Train.CarSet[Neighbors[i].number].Clas-1]++;
        }
        int MaxNum = 0;

//        array<double, LabelAttrSize> LabelArray = {0};
//        for (int i = 0; i < KValue; i++){
//            LabelArray[Train.CarSet[Neighbors[i].number].Clas-1] += 1.0 / Neighbors[i].distance;
//        }
//        double MaxNum = 0;

        Label_Type label;
        for (int i = 0; i < LabelAttrSize; i++){
            if (LabelArray[i] > MaxNum){
                MaxNum = LabelArray[i];
                label = static_cast<Label_Type>(i);
            }
        }
        if (label == static_cast<int>(car.Clas-1)){
            YesNum++;
        }
        else{
            //ErrorNum_KNN.push_back(car.Original_Number);
            NoNum++;
        }
    }
    PrintTestKNN(KValue, YesNum, NoNum);
    if (NoNum * 1.0 / (YesNum + NoNum) < ErrorRate){
        ErrorRate = NoNum * 1.0 / (YesNum + NoNum);
        BestK = KValue;
    }
}

void TrainTestKNN(int KValue){
    Data D, Train, Test;
    Data_Init(D, Train, Test);
    TestKNN(Train, Test, KValue);
    cout << "TP : " << TP << "  FP : " << FP << "  FN : " << FN << "  TN : " << TN << endl;
}

void MultiTestKNN(){
    static double ErrorRate = 1;
    int num = 50;
    int BestK;
    Data D, Train, Test;
    Data_Init(D, Train, Test);
    for (int i = 1; i <= num; i++){
        TestKNN(Train, Test, i, ErrorRate, BestK);
    }
    cout << "Best K value = " << BestK << endl;
    cout << "Best Error Rate = " << ErrorRate << endl;
}
