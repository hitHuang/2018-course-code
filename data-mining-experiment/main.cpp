#include "include/decisiontree.h"
#include "include/knn.h"

void CompareDecTreeAndKnn(){
    Data D, Train, Test;
    Data_Init(D, Train, Test);
    DecisionTreeNode root;
    DecisionTree_Init(root, Train);
    TreeGrowth(root, Train);
    TestDecisionTree(root, Test);

    TestKNN(Train, Test, 7);
}

int main()
{

    CompareDecTreeAndKnn();

    //train and test a decision tree
    //TrainTestDecision();

    //single exec KNN   the value of K is 7
    //TrainTestKNN(7);

    //MultiTestDecTree();

    //MultiTestKNN();

    return 0;
}
