#include <iostream>
#include <cstdlib>
#include <ctime>
#include <random>
std::mt19937 rnd(time(0));

using namespace std;

void dataGenerate(int Array[], int l, int r){
    for (int i = l; i < r; i++){
        Array[i] = rnd();
    }
}

void exchange(int A[], int p, int r){
    int tmp = A[p];
    A[p] = A[r];
    A[r] = tmp;
}

int Rand_Partition(int A[], int p, int r){
    int i = rand()%(r-p+1) + p;
    exchange(A, r, i);
    int x = A[r];
    i = p - 1;
    for (int j = p; j < r; j++){
        if (A[j] < x){
            i++;
            exchange(A, i, j);
        }
    }
    exchange(A, i + 1, r);
    return i + 1;
}

void QuickSort(int A[], int p, int r){
    if (p < r){
        int q = Rand_Partition(A, p, r);
        QuickSort(A, p, q - 1);
        QuickSort(A, q + 1, r);
    }
}

void InsertSort(int A[], int p, int r){
    for (int i = p; i <= r; i++){
        int key = A[i];
        int j = i - 1;
        for ( ; j >= p; j--){
            if (A[j] > key){
                A[j+1] = A[j];
            }else{
                break;
            }
        }
        A[j+1] = key;
    }
}

void QuickSort2(int A[], int p, int r){
    if(p >= r)  return ;
    if (r - p <= 20){
        InsertSort(A, p, r);
    }
    else {
        int i = rand()%(r-p+1) + p;
        exchange(A, r, i);
        int x = A[r];
        int lt = p;
        i  = p;
        int gt = r - 1;
        while (i <= gt){
            if (A[i] < x){
                exchange(A, i++, lt++);
            }
            else if (A[i] > x){
                exchange(A, i, gt--);
            }
            else    i++;
        }
        exchange(A, gt+1, r);
        QuickSort2(A, p, lt-1);
        QuickSort2(A, gt+1, r);
    }
}

void QuickSort3(int A[], int p, int r){
    if(p >= r)  return ;
    if (r - p <= 20){
        InsertSort(A, p, r);
    }
    else {
        int q = Rand_Partition(A, p, r);
        QuickSort(A, p, q - 1);
        QuickSort(A, q + 1, r);
    }
}

int cmp(const void* a, const void* b){
    return *(int*)a - *(int*)b;
}

int Array[1000000];

void run(int Size){
    clock_t begin_time, end_time;
    double cost_time = 0.0;
    begin_time = clock();
    QuickSort(Array, 0, Size - 1);
    end_time = clock();
    cost_time += (double)(end_time - begin_time);
    cout << "cost_time: " << cost_time << endl;
}

void test(){
    for (int i = 0; i < 1000; i++){
        Array[i] = i;
    }
    for (int i = 999; i > 0; i--){
        int n = rand() % i;
        exchange(Array, i, n);
    }
    QuickSort2(Array, 0, 1000 - 1);
    for (int i = 0; i < 1000; i++){
        cout << Array[i] << "  ";
    }
}

//  实验指导输入1
void test1(){
    dataGenerate(Array, 0, 1000000);
    run(1000000);
}

//  实验指导输入2
void test2(){
    for (int i = 0; i < 1000000; i++)
        Array[i] = 1;
    run(1000000);
}

//  实验指导输入3
void test3(int n){
    for (int i = 0; i < n; i++) Array[i] = 1;
    dataGenerate(Array, n, 10000);
    run(10000);
}

void test4_1(int n){
    for (int i = 0; i < n; i++) Array[i] = 1;
    dataGenerate(Array, n, 1000);
    run(1000);
}

void test4_2(int n){
    for (int i = 0; i < n; i++) Array[i] = 1;
    dataGenerate(Array, n, 5000);
    run(5000);
}

int main()
{
//  验证算法正确性的基本数据
//    int A[] = {1,3,0,4,6,9,7,2,5,8};
//    InsertSort(A, 0, 9);
    //int A[] = {1,1,1,1,1,1,1,1,1,1};
    //QuickSort(A, 0, 9);
    //QuickSort2(A, 0, 9);
    //qsort(A, 10, sizeof(A[0]), cmp);
//    for (auto r : A)
//        cout << r << " ";
//    cout << endl;

    srand((unsigned)time(0));

    //test();

    test1();

    //test2();

    //test3(10000);

    //test4_1(1000);

    //test4_2(5000);

    return 0;
}
