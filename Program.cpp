
#include <iostream>
#include <algorithm>
#include <fstream>
#include <string>
#include <list>
#include <iterator>
using namespace std;


int T(int n, int m, std::list<int> A, std::list<int> B){
    
    if(n == 1 && m == 1)
    {
        //memo[n][m] = A.front() + B.front();
    }
    else if(n == 1)
    {
        int j = A.front();
        //extend A until n = m
        for(int i = 1; i < m; i++){
            A.push_back(j);
        }
        //maxsum across pairs
        int maxSum = A.front() + B.front();
        
        std::list<int>::iterator it1;
        std::list<int>::iterator it2;
        
        for(it1 = A.begin(), it2 = B.begin(); it1 != A.end() || it2 != B.end(); it1++, it2++)
        {
            maxSum = std::max(maxSum, *it1 + *it2);
        }
    }
    else if(m == 1){
        //extend B until m = n
        int j = B.front();
        for(int i = 0; i < n; i++){
            B.push_back(j);
        }
        
        int maxSum = A.front() + B.front();
        std::list<int>::iterator it1;
        std::list<int>::iterator it2;
        
        for(it1 = A.begin(), it2 = B.begin(); it1 != A.end() || it2 != B.end(); it1++, it2++)
        {
            maxSum = std::max(maxSum, *it1 + *it2);
        }
        
    }
    else{
        //memo[n][m] = std::min(T(n, m-1, A, B.pop_front),std::min(T(n-1, m, A.pop_front, B), T(n-1, m-1, A.pop_front, B.pop_front)))
    }
    
    int leftmost_sum = A.front() + B.front();   //what is .value?
    /*if(leftmost_sum > memo[n][m]){
        memo[n][m] = leftmost_sum;
    }*/
    
    return 1; //memo[n][m]
    
}

//get size input
void getInput(int *size1, int *size2, fstream *mFile){

    *mFile >> *size1 >> *size2;
    
    
}

//get array input
void getInput(int size, std::list<int> *mList, fstream *mFile){
    for(int i = 0; i <= size; i++)
    {
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


