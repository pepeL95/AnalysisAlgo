
#include <iostream>
#include <algorithm>
#include <fstream>
#include <string>
#include <list>
#include <iterator>
using namespace std;

// temporary for developing reasons
int memo[10][10];

int T(int n, int m, std::list<int> A, std::list<int> B){
    
    if(n == 1 && m == 1) {
        memo[n][m] = A.front() + B.front();
    }

    else if(n == 1) {
        // //extend A until n = m
        // for(int i = 1; i < m; i++)
        //     A.push_back(A.front());
        //maxsum across pairs
        return *std::max_element(B.begin(), std::next(B.begin(), m)) + A.front();

    }

    else if(m == 1) {
        // //extend B until m = n
        // int j = B.front();
        // for(int i = 0; i < n; i++){
        //     B.push_back(j);
        // }
        return *std::max_element(A.begin(), std::next(A.begin(), n)) + B.front();
    }

    else {
        memo[n][m] = std::min(T(n, m-1, A, B),std::min(T(n-1, m, A, B), T(n-1, m-1, A, B)));
        int leftmost_sum = A.front() + B.front();
        if (leftmost_sum > memo[n][m])
            memo[n][m] = leftmost_sum;
        }

    return memo[n][m];
}

//get size input
void getInput(int *size1, int *size2, fstream *mFile){
    *mFile >> *size1 >> *size2;
}

//get array input
void getInput(int size, std::list<int> *mList, fstream *mFile){
    for(int i = 0; i <= size; i++) {
        int j;
        *mFile >> j;
        mList->push_back(j);
    }   
}

int main()
{   
    fstream mFile; mFile.open("sample-input.txt");
    int n, m; std::list<int> A, B;
    getInput(&n, &m, &mFile);
    getInput(n, &A, &mFile);
    getInput(m, &B, &mFile);
    
}


