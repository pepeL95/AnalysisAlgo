#include <iostream>
#include <algorithm>
#include <fstream>
#include <string>
#include <list>
#include <iterator>
#include <stdlib.h>
#include <string_view>
#include <map>
#include <vector>
using namespace std;



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

void extendT(list<int> *A, list<int> *B, map<pair<int, int>, pair<int, int> > E, int N, int M) {
    
    for (auto e : E) {
        if (e.first.first - e.second.first == 1 && e.first.second - e.second.second == 1) {
            // keep
            continue;
        }
        else if (e.first.first - e.second.first == 1) {
            // extend B
            auto leftEndpointB = next((*B).begin(), M - e.first.second);
            B->insert(leftEndpointB, *leftEndpointB);
        }
        else {
            // extend A
            auto leftEndpointA = next((*A).begin(), N - e.first.first);
            A->insert(leftEndpointA, *leftEndpointA);
        }
    }

    while (A->size() < B->size())
        A->push_back(A->back());
    while (B->size() < A->size())
        B->push_back(B->back());

    // printOutput(*A, *B);
    
}

int T(int n, int m, int N, int M, std::list<int> *A, std::list<int> *B, vector<vector<int>> *memo, map<pair<int, int>, pair<int, int> > *E)
{
    pair<int, int> v1, v2; 
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
        cout << "BASE CASE: n == 1" << endl;
        cout << *max_element(leftEndpointB, (*B).end()) + *leftEndpointA << endl;
        return *max_element(leftEndpointB, (*B).end()) + *leftEndpointA;
    }
    else if (m == 1)
    {
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
            v1 = make_pair(n, m);
            v2 = make_pair(n-1, m-1);
            (*E)[v1] = v2;
        }
        else if ((*memo)[n - 1][m - 1] == extendA)
        {
            //(*A).insert(leftEndpointA, *leftEndpointA);
            puts("Extend A"); 
            v1 = make_pair(n, m);
            v2 = make_pair(n, m-1);
            (*E)[v1] = v2;
        }
        else
        {
            //(*B).insert(leftEndpointB, *leftEndpointB);
            puts("extend B");
            v1 = make_pair(n, m);
            v2 = make_pair(n-1, m);
            (*E)[v1] = v2;
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
    vector<vector<int> > memo(n, std::vector<int>(m, -1));
    map<pair<int, int>, pair<int, int> > E;
    map<pair<int, int>, pair<int, int> > E_prime;
    int optimalHeight = T(n, m, N, M, &A, &B, &memo, &E);
    
    cout << "Optimal Height: " << optimalHeight << endl;

   pair<int, int> root(N, M);    
   for (auto e : E) {
        if (E.find(root) == E.end())
            break;
        E_prime[root] = E[root];
        root = E[root];
    }

    extendT(&A, &B, E_prime, N, M);

    printOutput(A, B);
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
}
