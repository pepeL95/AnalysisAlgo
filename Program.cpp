
#include <iostream>
#include <algorithm>
#include <fstream>
#include <string>
#include <list>
#include <iterator>
#include <stdlib.h>

using namespace std;

// temporary for developing
int memo[10][10];

int T(int n, int m, std::list<int> A, std::list<int> B){
    if(n == 1 && m == 1)
        return A.front() + B.front();
    else if(n == 1) {
        // //extend A until n = m
        // for(int i = 1; i < m; i++)
        //     A.push_back(A.front());
        //maxsum across pairs
        return *max_element(B.begin(), next(B.begin(), m)) + A.front();
    }
    else if(m == 1) {
        // //extend B until m = n
        // int j = B.front();
        // for(int i = 0; i < n; i++){
        //     B.push_back(j);
        // }
        //maxsum across pairs
        return *max_element(A.begin(), next(A.begin(), n)) + B.front();
    }
    else {
        int extendA = T(n, m-1, A, B);
        int keepAB = T(n-1, m-1, A, B);
        int extendB = T(n-1, m, A, B);
        memo[n][m] = min(extendA, min(keepAB, extendB));
        if (memo[n][m] == keepAB)
            puts("Keep same length");
        else if (memo[n][m] == extendA)
            puts("Extend A");
        else
            puts("extend B");
        int leftmost_sum = A.front() + B.front();
        if (leftmost_sum > memo[n][m])
            memo[n][m] = leftmost_sum;
    }
    return memo[n][m];
}

//get size input (line 1 of input file)
void getInput(int *size1, int *size2, fstream *mFile){
    *mFile >> *size1 >> *size2;
}

//get array input (lines 2 nd 3 of input file)
void getInput(int size, std::list<int> *mList, fstream *mFile){
    for(int i = 0; i < size; i++) {
        int j;
        *mFile >> j;
        mList->push_back(j);
    }   
}

int main()
{   
    int n, m;
    list<int> A, B;
    fstream mFile; 
    
    mFile.open("input.txt");
    getInput(&n, &m, &mFile);
    getInput(n, &A, &mFile);
    getInput(m, &B, &mFile);
    mFile.close();

    cout << T(n, m, A, B) << endl;
    // cout<< "n = " << n << "\nm = " << m << "\nA = " << A.back() << "\nB = " << B.back() << endl;


}