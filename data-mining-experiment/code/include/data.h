#ifndef DATA_H_INCLUDED
#define DATA_H_INCLUDED
#include <vector>
#include <set>
#define DATASIZE 1728
#define TRAINSIZE   1728
#define BuyAttrSize 4
#define MaintAttrSize 4
#define DoorsAttrSize 4
#define PersonsAttrSize 3
#define Lug_bootAttrSize 3
#define SafetyAttrSize 3
#define LabelAttrSize 4
using namespace std;

typedef enum {Label, TestCond}                              Node_Type;
typedef enum {Unacc, Acc, Good, Vgood, NVALID}              Label_Type;
typedef enum {Buy, Maint, Doors, Persons, Lug_boot, Safety} Attribute_Type;
typedef enum {BLow, BMed, BHigh, BVhigh}                    Buy_Type;
typedef enum {MLow, MMed, MHigh, MVhigh}                    Maint_Type;
typedef enum {DTwo, DThree, DFour, DMore}                   Doors_Type;
typedef enum {PTwo, PFour, PMore}                           Persons_Type;
typedef enum {LSmall, LMed, LBig}                           Lug_boot_Type;
typedef enum {SLow, SMed, SHigh}                            Safety_Type;

struct Car{
    int     Number;
    int     Original_Number = 0;
    int     Buying;
    int     Maint;
    int     Doors;
    int     Persons;
    int     Lug_boot;
    int     Safety;
    int     Clas;
    Car(int number, int buying, int maint, int doors, int persons, int lug_boot, int safety, int clas) :
        Number(number),Buying(buying),Maint(maint),Doors(doors),Persons(persons),Lug_boot(lug_boot),Safety(safety),Clas(clas){}
};

struct Data{
    Data(){}
    void addItem(Car car){CarSet.push_back(car);size++;}
    int getSize(){return size;}
    vector<Car> CarSet;
    int size = 0;
};

//将数据从文本文件读入D中
void Data_Input(Data& D);
//将数据划分为训练集和检验集
void Data_Partition(Data& D, Data& Train, Data& Test);
void Data_Print(Data& D);
void Data_Print(set<int>& DataSet, Data& D);
void Data_Output(Data& Train, Data& Test);
//初始化，包括读入、划分
void Data_Init(Data& D, Data& Train, Data& Test);
#endif // DATA_H_INCLUDED
