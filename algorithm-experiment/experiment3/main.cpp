#include <iostream>
#include <cstdlib>
#include <vector>
#include <ctime>
#include <set>
#include <unordered_set>
#include <fstream>

#define NUMS 20
#define eps 1e-10
using namespace std;

struct hashSet{
    size_t operator() (const unordered_set<int>& s) const {
        size_t res = 0;
        for (auto& r : s)   res += r;
        return res;
    }
};

unordered_set<unordered_set<int>, hashSet> dataGenerate(int sz){
    srand((unsigned)time(0));
    unordered_set<int> rested;
    unordered_set<int> selected;
    for (int i = 1; i <= sz; i++) rested.insert(i);
    unordered_set<unordered_set<int>, hashSet> res;
    unordered_set<int> s;
    while (s.size() < NUMS){
        int r = rand() % sz + 1;
        s.insert(r);
    }
    for(auto& r : s) {
        rested.erase(r);
        selected.insert(r);
    }
    res.insert(s);
    while (rested.size() >= NUMS){
        unordered_set<int> s;
        size_t n = rand() % NUMS + 1;
        size_t x = rand() % n + 1;
        while (s.size() < x){
            int r = rand() % sz + 1;
            if (rested.find(r) != rested.end()){
                s.insert(r);
                rested.erase(r);
            }
        }
        while (s.size() < n){
            int r = rand() % sz + 1;
            if (selected.find(r) != selected.end()){
                s.insert(r);
            }
        }
        res.insert(s);
        for (auto& r : s)   selected.insert(r);
    }
    if (rested.size() > 0)  res.insert(rested);
    while (res.size() < (size_t)sz){
        s.clear();
        int n = rand() % NUMS + 1;
        for (int i = 0; i < n; i++){
            int r = rand() % sz + 1;
            s.insert(r);
        }
        res.insert(s);
    }
    return res;
}

unordered_set<unordered_set<int>, hashSet>
greedySetCover(unordered_set<unordered_set<int>, hashSet> F, int sz){
    unordered_set<int> A;
    unordered_set<unordered_set<int>, hashSet> C;
    while (A.size() != (size_t)sz){
        int maxCnt = 0;
        unordered_set<unordered_set<int>, hashSet>::iterator maxIt = F.end();
        for (auto it = F.begin(); it!= F.end(); ++it){
            int cnt = 0;
            for (auto r : *it){
                if (A.find(r) == A.end()) cnt++;
            }
            if (cnt > maxCnt){
                maxCnt = cnt;
                maxIt = it;
            }
        }
        C.insert(*maxIt);
        for (auto r : *maxIt)   A.insert(r);
        F.erase(maxIt);
    }
    return C;
}

vector<vector<int>> preworkLP(vector<unordered_set<int>>& F, int sz, int& f){
    ofstream outData;
    outData.open("input.txt", ios::out);
    vector<vector<int>> res(sz, vector<int>());
    vector<int> cnt(sz, 0);
    for (int i = 0; i < sz; i++){
        for (auto r : F[i]){
            res[r-1].push_back(i+1);
            cnt[r-1]++;
        }
    }
    clock_t begin_time, end_time;
    begin_time = clock();
    for (int i = 0; i < sz; i++){
        for (auto r : res[i]){
            outData << r << " ";
        }
        outData << endl;
    }
    outData.close();
    end_time = clock();
    clock_t cost_time = end_time - begin_time;
    cout << "pre time = " << cost_time << endl;
    int maxCnt =0;
    for (auto r : cnt){
        if (r > maxCnt) maxCnt = r;
    }
    f = maxCnt;
    return res;
}

void greedy(unordered_set<unordered_set<int>, hashSet> F,int sz){
//    clock_t begin_time, end_time;
//    begin_time = clock();
    unordered_set<unordered_set<int>, hashSet> C = greedySetCover(F, sz);
    int cnt = 0;
    unordered_set<int> ss;
    vector<int> vec(sz + 1, 0);
    for (auto& s : C){
        for (auto r : s){
            ss.insert(r);
            vec[r] = 1;
            cnt++;
        }
    }
//    end_time = clock();
//    clock_t cost_time = end_time - begin_time;

    cout << "-----GREEDY-----" << endl;
    cout << "C.size     : " << C.size() << endl;
    cout << "total cnt  : " << cnt << endl;
    cout << "valid cnt  : " << ss.size() << endl;
    //cout << "cost time  : " << cost_time << " ms" << endl;


//    for (int i = 1; i <= sz; i++){
//        if (vec[i] != 1){
//            cout << "error!!" << endl;
//            break;
//        }
//    }

    if (sz <= 100){
        for (auto& s : C){
            for (auto r : s){
                cout << r << " ";
            }
            cout << endl;
        }
        cout << endl;
    }
}

void lp(vector<unordered_set<int>> F, int sz){
    int f = 0;
    preworkLP(F, sz, f);
    double p = 1.0 / f;
    char cmd[20];
    clock_t begin_time, end_time;
    begin_time = clock();
    sprintf(cmd, "python lp.py %d", sz);
    system(cmd);
    end_time = clock();
    clock_t cost_time = end_time - begin_time;
    cout << "lp.py " << cost_time << endl;
    vector<double> isSelect;
    fstream inData;
    inData.open("output.txt", ios::in);
    double r;
    while (inData >> r){
        if (r - p > eps)    isSelect.push_back(1);
        else isSelect.push_back(0);
    }
    inData.close();
    unordered_set<int> s;
    int cnt1 = 0, cnt2 = 0;
    for (size_t i = 0; i < isSelect.size(); i++){
        if (isSelect[i] == 0)   continue;
        cnt1++;
        for (auto r : F[i]){
            cnt2++;
            s.insert(r);
        }
    }

    cout << "--------LP------" << endl;
    cout << "C.size     : " << cnt1 << endl;
    cout << "total cnt  : " << cnt2 << endl;
    cout << "vaild cnt  : " << s.size() << endl;

//    vector<int> vec(sz + 1, 0);
//    for (size_t i = 0; i < isSelect.size(); i++){
//        if (isSelect[i] == 0)   continue;
//        for (auto r : F[i]){
//            vec[r] = 1;
//        }
//    }
//    for (int i = 1; i <= sz; i++){
//        if (vec[i] != 1){
//            cout << "error!!" << endl;
//            break;
//        }
//    }

    if (sz <= 100){
        for (size_t i = 0; i < isSelect.size(); i++){
            if (isSelect[i] == 0)   continue;
            for (auto r : F[i]){
                cout << r << " ";
            }
            cout << endl;
        }
    }
}

void lp2(vector<unordered_set<int>> F, int sz){
    srand((unsigned)time(0));
    char cmd[20];
    sprintf(cmd, "python lp.py %d", sz);
    system(cmd);
    vector<double> isSelect;
    fstream inData;
    inData.open("output.txt", ios::in);
    double r;
    unsigned int offSet;
    while (inData >> r){
        offSet = r * RAND_MAX;
        if (rand() < offSet)    isSelect.push_back(1);
        else isSelect.push_back(0);
    }
    inData.close();
    unordered_set<int> s;
    int cnt1 = 0, cnt2 = 0;
    for (size_t i = 0; i < isSelect.size(); i++){
        if (isSelect[i] == 0)   continue;
        cnt1++;
        for (auto r : F[i]){
            cnt2++;
            s.insert(r);
        }
    }
    cout << "--------LP2------" << endl;
    cout << "C.size     : " << cnt1 << endl;
    cout << "total cnt  : " << cnt2 << endl;
    cout << "valid cnt  : " << s.size() << endl;

//    vector<int> vec(sz + 1, 0);
//    for (size_t i = 0; i < isSelect.size(); i++){
//        if (isSelect[i] == 0)   continue;
//        for (auto r : F[i]){
//            vec[r] = 1;
//        }
//    }
//    for (int i = 1; i <= sz; i++){
//        if (vec[i] != 1){
//            cout << "error!!" << endl;
//            break;
//        }
//    }

//    if (sz <= 100){
//        for (size_t i = 0; i < isSelect.size(); i++){
//            if (isSelect[i] == 0)   continue;
//            for (auto r : F[i]){
//                cout << r << " ";
//            }
//            cout << endl;
//        }
//    }
}

int main(int argc, char* argv[])
{
    int sz = 5000;
    if (argc == 2)  sscanf(argv[1], "%d", &sz);
    unordered_set<unordered_set<int>, hashSet> F = dataGenerate(sz);
    vector<unordered_set<int>> F2;
    for (auto& s : F)   F2.push_back(s);

    clock_t begin_time1, end_time1;
    clock_t begin_time2, end_time2;
    clock_t begin_time3, end_time3;
    double cost_time1;
    double cost_time2;
    double cost_time3;
    begin_time1 = clock();
    greedy(F,sz);
    end_time1 = clock();
    begin_time2 = clock();
    lp(F2, sz);
    end_time2 = clock();
    begin_time3 = clock();
    //lp2(F2, sz);
    end_time3 = clock();
    cost_time1 = end_time1 - begin_time1;
    cost_time2 = end_time2 - begin_time2;
    cost_time3 = end_time3 - begin_time3;
    cout << "-------time------" << endl;
    cout << "greedy time : " << cost_time1 << endl;
    cout << "LP     time : " << cost_time2 << endl;
    cout << "LP2    time : " << cost_time3 << endl;
    return 0;
}
