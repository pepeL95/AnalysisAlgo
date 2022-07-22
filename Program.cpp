#include <iostream>
#include <algorithm>
#include <fstream>
#include <string>
#include <list>
#include <iterator>
#include <stdlib.h>
#include <map>
#include <vector>
using namespace std;

int T(int n, int m, int N, int M, std::list<int> *A, std::list<int> *B, vector<vector<int>> *memo, map<string, string> *E)
{
    auto leftEndpointB = next((*B).begin(), M - m);
    auto leftEndpointA = next((*A).begin(), N - n);
    if ((*memo)[n - 1][m - 1] != -1)
    {
        cout << "At [" << n - 1 << "]"
             << "[" << m - 1 << "] = " << (*memo)[n - 1][m - 1] << endl;
        return (*memo)[n - 1][m - 1];
    }
    if (n == 1 && m == 1)
    {
        cout << "BASE CASE: n == 1 and m == 1" << endl;
        // cout << "current value A = " << *leftEndpointA << endl;
        // cout << "current value B = " << *leftEndpointB << endl;
        cout << *leftEndpointA + *leftEndpointB << endl;
        return *leftEndpointA + *leftEndpointB;
    }
    else if (n == 1)
    {
        // //extend A until n = m
        // for(int i = 1; i < m; i++)
        //     A.push_back(A.front());
        // maxsum across pairs
        cout << "BASE CASE: n == 1" << endl;
        cout << *max_element(leftEndpointB, (*B).end()) + *leftEndpointA << endl;
        return *max_element(leftEndpointB, (*B).end()) + *leftEndpointA;
    }
    else if (m == 1)
    {
        // //extend B until m = n
        // int j = (*B).front();
        // for(int i = 0; i < n; i++){
        //     (*B).push_back(j);
        // }
        // maxsum across pairs
        cout << "BASE CASE: m == 1" << endl;
        cout << *max_element(leftEndpointA, (*A).end()) + *leftEndpointB << endl;
        // cout << "n = " << *leftEndpointA << "right ep = " << *max_element(leftEndpointA, (*A).end()) << endl;
        return *max_element(leftEndpointA, (*A).end()) + *leftEndpointB; //*max_element((*A).begin(), next((*A).begin(), n)) + (*B).front();
    }
    else
    {
        int extendA = T(n, m - 1, N, M, A, B, memo, E);
        int keepAB = T(n - 1, m - 1, N, M, A, B, memo, E);
        int extendB = T(n - 1, m, N, M, A, B, memo, E);
        (*memo)[n - 1][m - 1] = min(extendA, min(keepAB, extendB));
        if ((*memo)[n - 1][m - 1] == keepAB)
        {
            puts("Keep same length");
        }
        else if ((*memo)[n - 1][m - 1] == extendA)
        {
            //(*A).insert(leftEndpointA, *leftEndpointA);

            puts("Extend A");
        }
        else
        {
            //(*B).insert(leftEndpointB, *leftEndpointB);

            puts("extend B");
        }
        int leftmost_sum = *leftEndpointA + *leftEndpointB;
        if (leftmost_sum > (*memo)[n - 1][m - 1])
            (*memo)[n - 1][m - 1] = leftmost_sum;
        return (*memo)[n - 1][m - 1];
    }
}

void Wrapper(int n, int m, list<int> A, list<int> B)
{
    int N = n, M = m;
    vector<vector<int>> memo(n, std::vector<int>(m, -1));
    map<string, string> E;
    int optimalHeight = T(n, m, N, M, &A, &B, &memo, &E);
    cout << "Optimal Height: " << optimalHeight << endl;
}
// get size input (line 1 of input file)
void getInput(int *size1, int *size2, fstream *mFile)
{
    *mFile >> *size1 >> *size2;
}

// get array input (lines 2 nd 3 of input file)
void getInput(int size, std::list<int> *mList, fstream *mFile)
{
    for (int i = 0; i < size; i++)
    {
        int j;
        *mFile >> j;
        mList->push_back(j);
    }
}

void printOutput(std::list<int> A, std::list<int> B)
{
    cout << endl
         << "A: ";
    for (int a_value : A)
    {
        cout << a_value << " ";
    }
    cout << endl
         << "B: ";
    for (int b_value : B)
    {
        cout << b_value << " ";
    }
    cout << endl
         << endl;
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
    Wrapper(n, m, A, B);
    printOutput(A, B);
    printOutput(A, B);
}
