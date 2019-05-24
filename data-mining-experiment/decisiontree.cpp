#include <iostream>
#include <map>
#include <cmath>
#include "include/decisiontree.h"
using namespace std;

void MapAttribute(Attribute_Type attr){
    switch(attr){
        case Buy: cout << "Buy" << endl;break;
        case Maint: cout << "Maint" << endl;break;
        case Doors: cout << "Doors" << endl;break;
        case Persons: cout << "Persons" << endl;break;
        case Lug_boot: cout << "Lug_boot" << endl;break;
        case Safety: cout << "Safety" << endl;break;
        default :
            cout << "no this value!! exit(1)";
            exit(1);
    }
}

void MapNode(Node_Type node){
    switch (node){
        case Label: cout << "Label" << endl;break;
        case TestCond: cout << "TestCond" << endl;break;
        default :
            cout << "no this value!! exit(1)";
            exit(1);
    }
}

void MapLabel(Label_Type label){
    switch (label){
        case Unacc: cout << "Unacc" << endl;break;
        case Acc: cout << "Acc" << endl;break;
        case Good: cout << "Good" << endl;break;
        case Vgood: cout << "Vgood" << endl;break;
        //case NVALID:cout << "NVALID" << endl;break;
        default :
            cout << "no this value!! exit(1)";
            exit(1);
    }
}

bool Stopping_Cond(DecisionTreeNode& DT, Data& Train){
    if (DT.DataSet.size() == 0)    return true;
    if (DT.AttributeSet.size() == 0)   return true;
    if (DT.DataSet.size() < 7)  return true;//优化终止条件，当该节点的数据集较小时，不再划分
    set<int>::const_iterator it = DT.DataSet.begin();
    int first = *it;
    for ( ++it; it != DT.DataSet.end(); ++it){
        if (Train.CarSet[*it].Clas != Train.CarSet[first].Clas){
            return false;
        }
    }
    return true;
}

void PartByAttr(vector<set<int>>& AttrDataSet, set<int>& DataSet, Attribute_Type attr, Data& Train){
    vector<set<int>>().swap(AttrDataSet);
    if (attr == Buy){
        AttrDataSet.resize(BuyAttrSize);
        for (auto ch : DataSet){
            AttrDataSet[Train.CarSet[ch].Buying-1].insert(ch);
        }
    }
    else if (attr == Maint){
        AttrDataSet.resize(MaintAttrSize);
        for (auto ch : DataSet){
            AttrDataSet[Train.CarSet[ch].Maint-1].insert(ch);
        }
    }else if (attr == Doors){
        AttrDataSet.resize(DoorsAttrSize);
        for (auto ch : DataSet){
            AttrDataSet[Train.CarSet[ch].Doors-2].insert(ch);
        }
    }else if (attr == Persons){
        AttrDataSet.resize(PersonsAttrSize);
        for (auto ch : DataSet){
                AttrDataSet[Train.CarSet[ch].Persons/2-1].insert(ch);
        }
    }else if (attr == Lug_boot){
        AttrDataSet.resize(Lug_bootAttrSize);
        for (auto ch : DataSet){
            AttrDataSet[Train.CarSet[ch].Lug_boot-1].insert(ch);
        }
    }else if (attr == Safety){
        AttrDataSet.resize(SafetyAttrSize);
        for (auto ch : DataSet){
                AttrDataSet[Train.CarSet[ch].Safety-1].insert(ch);
        }
    }else{
        cout << "no this attribute!! exit!" << endl;
        exit(1);
    }
}

void CreateNode(DecisionTreeNode& DT, Data& Train){
    vector<DecisionTreeNode*>().swap(DT.Child);
    DecisionTreeNode* s;
    set<int> TmpAttrSet = DT.AttributeSet;
    TmpAttrSet.erase(static_cast<int>(DT.TestCond_Value));
    PartByAttr(DT.AttrDataSet, DT.DataSet, DT.TestCond_Value, Train);
    switch(DT.TestCond_Value){
        case Buy:
            for (int i = 0; i < BuyAttrSize; i++){
                s = new DecisionTreeNode(DT.AttrDataSet[i], TmpAttrSet);
                DT.Child.push_back(s);
            }
            break;
        case Maint:
            for (int i = 0; i < MaintAttrSize; i++){
                s = new DecisionTreeNode(DT.AttrDataSet[i], TmpAttrSet);
                DT.Child.push_back(s);
            }
            break;
        case Doors:
            for (int i = 0; i < DoorsAttrSize; i++){
                s = new DecisionTreeNode(DT.AttrDataSet[i], TmpAttrSet);
                DT.Child.push_back(s);
            }
            break;
        case Persons:
            for (int i = 0; i < PersonsAttrSize; i++){
                s = new DecisionTreeNode(DT.AttrDataSet[i], TmpAttrSet);
                DT.Child.push_back(s);
            }
            break;
        case Lug_boot:
            for (int i = 0; i < Lug_bootAttrSize; i++){
                s = new DecisionTreeNode(DT.AttrDataSet[i], TmpAttrSet);
                DT.Child.push_back(s);
            }
            break;
        case Safety:
            for (int i = 0; i < SafetyAttrSize; i++){
                s = new DecisionTreeNode(DT.AttrDataSet[i], TmpAttrSet);
                DT.Child.push_back(s);
            }
            break;
        default:
            cout << "no this attr!! exit!";
            exit(1);
    }
}

//不纯性度量————熵
double Impurity_Measure(set<int>& DataSet, Data& Train){
    map<int, int> LabelSet;
    int Size = DataSet.size();
    for (auto i : DataSet){
        int label = Train.CarSet[i].Clas;
        ++LabelSet[label];
    }
    double res = 0;

    for (auto element : LabelSet){
        double p = element.second * 1.0 / Size;
        res -= p * (log(p) / log(2));
    }
    return res;
}

//不纯性度量————Gini系数
double Impurity_Measure(set<int>& DataSet, Data& Train, int){
    map<int, int> LabelSet;
    int Size = DataSet.size();
    for (auto i : DataSet){
        int label = Train.CarSet[i].Clas;
        ++LabelSet[label];
    }
    double res = 0;

    for (auto element : LabelSet){
        double p = element.second * 1.0 / Size;
        res += p * p;
    }
    return 1 - res;
}

//不纯性度量————分类误差
double Impurity_Measure(set<int>& DataSet, Data& Train, double){
    map<int, int> LabelSet;
    int Size = DataSet.size();
    for (auto i : DataSet){
        int label = Train.CarSet[i].Clas;
        ++LabelSet[label];
    }

    double maxp = 0;
    for (auto element : LabelSet){
        double p = element.second * 1.0 / Size;
        if (p > maxp)
            maxp = p;
    }
    return 1 - maxp;
}

double Information_Gain(set<int>& DataSet, vector<set<int>>& AttrDataSet, Data& Train){
    double Parent_Measure = Impurity_Measure(DataSet, Train);
    double Son_Measure = 0;
    for (unsigned i = 0; i < AttrDataSet.size(); i++){
        double pn = AttrDataSet[i].size() * 1.0 / DataSet.size();     //该子结点所占比例
        double tmp = Impurity_Measure(AttrDataSet[i], Train);         //每个子结点的度量
        Son_Measure += pn * tmp;
    }
    return Parent_Measure - Son_Measure;
}

double Information_Gain(set<int>& DataSet, vector<set<int>>& AttrDataSet, Data& Train, int){
    double Parent_Measure = Impurity_Measure(DataSet, Train, 1);
    double Son_Measure = 0;
    for (unsigned i = 0; i < AttrDataSet.size(); i++){
        double pn = AttrDataSet[i].size() * 1.0 / DataSet.size();     //该子结点所占比例
        double tmp = Impurity_Measure(AttrDataSet[i], Train, 1);         //每个子结点的度量
        Son_Measure += pn * tmp;
    }
    return (Parent_Measure - Son_Measure) / Son_Measure;
}

void Find_Best_Split(DecisionTreeNode& DT, Data& Train){
    auto it = DT.AttributeSet.begin();
    Attribute_Type BestAttribute = static_cast<Attribute_Type>(*it);
    PartByAttr(DT.AttrDataSet, DT.DataSet, BestAttribute, Train);
    double BestInfoGain = Information_Gain(DT.DataSet, DT.AttrDataSet, Train, 1);
    for (auto ch : DT.AttributeSet){
        PartByAttr(DT.AttrDataSet, DT.DataSet, static_cast<Attribute_Type>(ch), Train);
        double tmpInfoGain = Information_Gain(DT.DataSet, DT.AttrDataSet, Train, 1);
        if (tmpInfoGain > BestInfoGain){
            BestInfoGain = tmpInfoGain;
            BestAttribute = static_cast<Attribute_Type>(ch);
        }
    }
    DT.TestCond_Value = BestAttribute;
    return ;
}

void Classify(DecisionTreeNode& DT, Data& Train){
    int LabelArray[LabelAttrSize] = {0};
    DT.Node_Value = Label;
    if(DT.DataSet.size() == 0) {
        DT.Label_Value = static_cast<Label_Type>(NVALID);
        return ;
    }
    for (auto i : DT.DataSet){
        int tmp = Train.CarSet[i].Clas - 1;
        LabelArray[tmp]++;
    }
    int MaxNum = 0;
    int label = NVALID;
    for (int i = 0; i < LabelAttrSize; i++){
        if (LabelArray[i] > MaxNum){
            MaxNum = LabelArray[i];
            label = i;
        }
    }
    DT.Label_Value = static_cast<Label_Type>(label);
}

void TreeGrowth(DecisionTreeNode& DT, Data& Train){
    if (Stopping_Cond(DT, Train) == true){
        DT.Node_Value = Label;
        Classify(DT, Train);
        return ;
    }else{
        DT.Node_Value = TestCond;
        Find_Best_Split(DT, Train);
        CreateNode(DT, Train);
        for (unsigned i = 0; i < DT.Child.size(); i++){
            TreeGrowth(*(DT.Child[i]), Train);
        }
    }
    return ;
}

//vector<int> ErrorNum_DT;

static int TP = 0;
static int FP = 0;
static int FN = 0;
static int TN = 0;

void TestData(DecisionTreeNode& DT, Car& car, int& YesNum, int& NoNum){
    if (DT.Node_Value == Label){
        if (car.Clas-1 == static_cast<int>(DT.Label_Value)){
            YesNum++;

            if (car.Clas-1 == Unacc)    TP++;
            else TN++;

        }else{
            //ErrorNum_DT.push_back(car.Original_Number);
            NoNum++;

            if (car.Clas-1 == Unacc)    FN++;
            else if (static_cast<int>(DT.Label_Value) == Unacc) FP++;
            else    TN++;
        }

    }else{
        DecisionTreeNode T;
        switch (DT.TestCond_Value){
            case Buy:
                T = *(DT.Child[car.Buying-1]);
                TestData(T, car, YesNum, NoNum);
                break;
            case Maint:
                T = *(DT.Child[car.Maint-1]);
                TestData(T, car, YesNum, NoNum);
                break;
            case Doors:
                T = *(DT.Child[car.Doors-2]);
                TestData(T, car, YesNum, NoNum);
                break;
            case Persons:
                T = *(DT.Child[car.Persons/2-1]);
                TestData(T, car, YesNum, NoNum);
                break;
            case Lug_boot:
                T = *(DT.Child[car.Lug_boot-1]);
                TestData(T, car, YesNum, NoNum);
                break;
            case Safety:
                T = *(DT.Child[car.Safety-1]);
                TestData(T, car, YesNum, NoNum);
                break;
            default:
                cout << "error!! exit!" << endl;
                exit(1);
        }
    }
}

void TestData(DecisionTreeNode& DT, Car& car, Label_Type& label){
    if (DT.Node_Value == Label){
        label = static_cast<Label_Type>(DT.Node_Value);
    }else{
        //cout << "DT.TestCond_Value = "; MapAttribute(DT.TestCond_Value);
        DecisionTreeNode T;
        switch (DT.TestCond_Value){
            case Buy:
                T = *(DT.Child[car.Buying-1]);
                TestData(T, car, label);
                break;
            case Maint:
                T = *(DT.Child[car.Maint-1]);
                TestData(T, car, label);
                break;
            case Doors:
                T = *(DT.Child[car.Doors-2]);
                TestData(T, car, label);
                break;
            case Persons:
                T = *(DT.Child[car.Persons/2-1]);
                TestData(T, car, label);
                break;
            case Lug_boot:
                T = *(DT.Child[car.Lug_boot-1]);
                TestData(T, car, label);
                break;
            case Safety:
                T = *(DT.Child[car.Safety-1]);
                TestData(T, car, label);
                break;
            default:
                cout << "error!! exit!" << endl;
                exit(1);
        }
    }
}

void PrintTestResult(int YesNum, int NoNum){
    cout << "-------DecisionTree-------" << endl;
    cout << "Total : " << YesNum + NoNum << endl;
    cout << "Yes   : " << YesNum << "  ";
    cout << "No : " << NoNum << endl;
    cout << "error rate : " << NoNum * 1.0 / (YesNum + NoNum) << endl;
}

void TestDecisionTree(DecisionTreeNode& DT, Data& Test){
    int YesNum = 0;
    int NoNum = 0;
    //vector<int>().swap(ErrorNum_DT);
    for (int i = 0; i < Test.size; i++){
        TestData(DT, Test.CarSet[i], YesNum, NoNum);
    }
    PrintTestResult(YesNum, NoNum);
    cout << "TP : " << TP << "  FP : " << FP << "  FN : " << FN << "  TN : " << TN << endl;
    cout << "accuracy : " << (TP + TN) * 1.0 / Test.size << "  ";
    cout << "precision : " << TP * 1.0 / (TP + FP) << "  ";
    cout << "recall : " << TP * 1.0 / (TP + FN) << endl << endl;
}

void TestDecisionTree(DecisionTreeNode& DT, Data& Test, double& ErrorRate){
    int YesNum = 0;
    int NoNum = 0;
    //vector<int>().swap(ErrorNum_DT);
    for (int i = 0; i < Test.size; i++){
        TestData(DT, Test.CarSet[i], YesNum, NoNum);
    }
    PrintTestResult(YesNum, NoNum);
    ErrorRate += NoNum * 1.0 / (YesNum + NoNum);
}

void DecisionTree_Init(DecisionTreeNode& DT, Data& Train){
    DT.AttributeSet = {Buy, Maint, Doors, Persons, Lug_boot, Safety};
    for (int i = 0; i < Train.size; i++){
        DT.DataSet.insert(i);
    }
}

void Data_Classify_Log(Label_Type label, set<int>& DataSet, Data& D){
    FILE* op;
    if ((op = fopen("classify_log.txt","w+")) == NULL){
        cout << "open file failed!! exit!" << endl;
        exit(1);
    }
    fseek(op, 0, SEEK_END);
    int cnt = 0;
    fprintf(op, "Label = %d\n", static_cast<int>(label));
    for (auto i : DataSet){
        cnt++;
        fprintf(op, "%4d %d  %d  %d  %d  %d  %d  %d\n",D.CarSet[i].Number,D.CarSet[i].Buying,D.CarSet[i].Maint,D.CarSet[i].Doors,
               D.CarSet[i].Persons,D.CarSet[i].Lug_boot,D.CarSet[i].Safety,D.CarSet[i].Clas);
    }
    fprintf(op, "cnt = %d\n\n\n", cnt);
    fclose(op);
}

void TrainTestDecision(){
    Data D, Train, Test;
    Data_Init(D, Train, Test);
    DecisionTreeNode root;
    DecisionTree_Init(root, Train);
    TreeGrowth(root, Train);
    TestDecisionTree(root, Test);
}

void MultiTestDecTree(){
    static double ErrorRate = 0;
    double AvgErrorRate = 0;
    int num = 100;
    for (int i = 0; i < num; i++){
        Data D, Train, Test;
        Data_Init(D, Train, Test);
        DecisionTreeNode root;
        DecisionTree_Init(root, Train);
        TreeGrowth(root, Train);
        TestDecisionTree(root, Test, ErrorRate);
    }
    AvgErrorRate = ErrorRate / num;
    cout << "Average error rate : " << AvgErrorRate << endl;
}
