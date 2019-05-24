#ifndef DECISIONTREE_H_INCLUDED
#define DECISIONTREE_H_INCLUDED

#include <set>

#include "data.h"
#include <iostream>
using namespace std;

//set<Buy_Type> BAttrSet = {BLow, BMed, BHigh, BVhigh};
//set<Maint_Type> MAttrSet = {MLow, MMed, MHigh, MVhigh};
//set<Doors_Type> DAttrSet = {DTwo, DThree, DFour, DMore};
//set<Persons_Type> PAttrSet = {PTwo, PFour, PMore};
//set<Lug_boot_Type> LAttrSet = {LSmall, LMed, LBig};
//set<Safety_Type> SAttrSet = {SLow, SMed, SHigh};
//set<Label_Type> CAttrSet = {Unacc, Acc, Good, Vgood};

//�������Ľڵ�
struct DecisionTreeNode{
    Node_Type       Node_Value;             //����Ҷ���Ͳ����������
    Label_Type      Label_Value;            //Ҷ�ڵ�����
    Attribute_Type  TestCond_Value;         //���Խ��Ĳ�������
    set<int>        DataSet;                //����ý������ݼ�
    set<int>        AttributeSet;           //�ý����ò������Լ�
    vector<set<int>>    AttrDataSet;        //���䵽���ӽ������ݼ�
    vector<DecisionTreeNode*>    Child;     //�ӽ��ָ��
    DecisionTreeNode() {}
    DecisionTreeNode(Node_Type pn) : Node_Value(pn) {}
    DecisionTreeNode(set<int>& pds, set<int>& pas) : DataSet(pds), AttributeSet(pas){}
};

bool Stopping_Cond(DecisionTreeNode& DT, Data& Train);
void CreateNode(DecisionTreeNode& DT, Data& Train);
void Find_Best_Split(DecisionTreeNode& DT, Data& Train);
void Classify(DecisionTreeNode& DT, Data& Train);
void PartByAttr(vector<set<int>>& AttrDataSet, set<int>& DataSet, Attribute_Type attr, Data& Train);
double Impurity_Measure(set<int>& DataSet, Data& Train);
double Impurity_Measure(set<int>& DataSet, Data& Train, int);
double Impurity_Measure(set<int>& DataSet, Data& Train, float);
double Information_Gain(set<int>& DataSet, vector<set<int>>& AttrDataSet, Data& Train);
void TreeGrowth(DecisionTreeNode& DT, Data& Train);
void TestData(DecisionTreeNode& DT, Car& car, int& YesNum, int& NoNum);
void TestDecisionTree(DecisionTreeNode& DT, Data& Test);
void TestDecisionTree(DecisionTreeNode& DT, Data& Test, double& ErrorRate);
void DecisionTree_Init(DecisionTreeNode& DT, Data& Train);
void Data_Classify_Log(Label_Type label, set<int>& DataSet, Data& D);
void TrainTestDecision();
void MultiTestDecTree();
void BaggingDecTree();
#endif // DECISIONTREE_H_INCLUDED
