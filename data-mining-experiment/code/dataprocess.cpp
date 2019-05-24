#include <iostream>
#include <array>
#include <ctime>
#include "include/data.h"

void Data_Input(Data& D){
    FILE* op;
    if ((op = fopen("data.txt","r")) == NULL){
        cout << "open file failed and exit!!" << endl;
        exit(1);
    }
    int buying, maint, doors, persons, lug_boot, safety, clas;
    int number = 0;
    while ((fscanf(op,"%d %d %d %d %d %d %d",&buying,&maint,&doors,&persons,&lug_boot,&safety,&clas)!=EOF)){
        Car car(number,buying,maint,doors,persons,lug_boot,safety,clas);
        D.addItem(car);
        ++number;
    }
    fclose(op);
    //cout << "Data Input Over. Data size : " << D.getSize() << endl;
}

void Data_Partition(Data& D, Data& Train, Data& Test){
    array<bool,DATASIZE> isSelected = {0};
    static unsigned seed;
    seed += 111;
    srand((unsigned)time(0)+seed);
    for(int i = 0,cnt = 0; i < DATASIZE; i++){
        int ch = rand()%DATASIZE;
        //自助法，有放回采样
        isSelected[ch] = true;
        Train.addItem(D.CarSet[ch]);
        Train.CarSet[i].Original_Number = Train.CarSet[i].Number;
        Train.CarSet[i].Number = i;

//        if (isSelected[ch] == false){
//            isSelected[ch] = true;
//            Train.addItem(D.CarSet[ch]);
//            Train.CarSet[cnt].Original_Number = Train.CarSet[cnt].Number;
//            Train.CarSet[cnt].Number = cnt;
//        }
    }
    for(int i = 0, cnt = 0; i < DATASIZE; i++){
        if (isSelected[i] == false){
            Test.addItem(D.CarSet[i]);
            Test.CarSet[cnt].Original_Number = Test.CarSet[cnt].Number;
            Test.CarSet[cnt].Number = cnt;
            ++cnt;
        }
    }
    //cout << "Data Partition Over. " << "TrainSet size : " << Train.getSize() << "  TestSet size : " << Test.getSize() << endl;
}

void Data_Print(Data& D){
    for (int i = 0; i < D.getSize(); i++){
        printf("%4d %d  %d  %d  %d  %d  %d  %d\n",D.CarSet[i].Number,D.CarSet[i].Buying,D.CarSet[i].Maint,D.CarSet[i].Doors,
               D.CarSet[i].Persons,D.CarSet[i].Lug_boot,D.CarSet[i].Safety,D.CarSet[i].Clas);
    }
}

void Data_Print(set<int>& DataSet, Data& D){
    int cnt = 0;
    for (auto i : DataSet){
        cnt++;
        printf("%4d %d  %d  %d  %d  %d  %d  %d\n",D.CarSet[i].Number,D.CarSet[i].Buying,D.CarSet[i].Maint,D.CarSet[i].Doors,
               D.CarSet[i].Persons,D.CarSet[i].Lug_boot,D.CarSet[i].Safety,D.CarSet[i].Clas);
    }
    cout << "cnt = " << cnt << endl;
}

void Data_Output(Data& Train, Data& Test){
    FILE* op_train;
    FILE* op_test;
    if ((op_train = fopen("trainset.txt","w")) == NULL){
        cout << "open file failed and exit!!" << endl;
        exit(1);
    }
    if ((op_test = fopen("testset.txt","w")) == NULL){
        cout << "open file failed and exit!!" << endl;
        exit(1);
    }
    for(int i = 0; i < Train.getSize(); i++){
        fprintf(op_train,"%-4d %-4d %d %d %d %d %d %d %d\n",Train.CarSet[i].Number,Train.CarSet[i].Original_Number,
                Train.CarSet[i].Buying,Train.CarSet[i].Maint,Train.CarSet[i].Doors,
               Train.CarSet[i].Persons,Train.CarSet[i].Lug_boot,Train.CarSet[i].Safety,Train.CarSet[i].Clas);
    }
    for(int i = 0; i < Test.getSize(); i++){
        fprintf(op_test,"%-4d %-4d %d %d %d %d %d %d %d\n",Test.CarSet[i].Number,Test.CarSet[i].Original_Number,
                Test.CarSet[i].Buying,Test.CarSet[i].Maint,Test.CarSet[i].Doors,
               Test.CarSet[i].Persons,Test.CarSet[i].Lug_boot,Test.CarSet[i].Safety,Test.CarSet[i].Clas);
    }
    fclose(op_train);
    fclose(op_test);
}

void Data_Init(Data& D, Data& Train, Data& Test){
    Data_Input(D);
    Data_Partition(D, Train, Test);
    Data_Output(Train, Test);
}
