#include "ExtensibleTeeth.hpp"
using namespace std;

int ExtensibleTeeth::T(int n, int m, int N, int M, std::list<int> *A, std::list<int> *B, vector<vector<int>> *memo, map<pair<int, int>, pair<int, int> > *E) {
    /* This is the driver which calls itself recursively and returns optimal height */
    pair<int, int> v1, v2; // will store winning vertices and make winning edges to keep track of right teeth heights
    auto leftEndpointA = next((*A).begin(), N - n);
    auto leftEndpointB = next((*B).begin(), M - m);
    if ((*memo)[n - 1][m - 1] != -1)
        return (*memo)[n - 1][m - 1];

    if (n == 1 && m == 1)
        return *leftEndpointA + *leftEndpointB;

    else if (n == 1)
        return *max_element(leftEndpointB, (*B).end()) + *leftEndpointA;

    else if (m == 1)
        return *max_element(leftEndpointA, (*A).end()) + *leftEndpointB; 

    else {
        int extendA = T(n, m - 1, N, M, A, B, memo, E);
        int keepAB = T(n - 1, m - 1, N, M, A, B, memo, E);
        int extendB = T(n - 1, m, N, M, A, B, memo, E);
        (*memo)[n - 1][m - 1] = min(extendA, min(keepAB, extendB));
        if ((*memo)[n - 1][m - 1] == keepAB) {
            // puts("Keep same length");
            v1 = make_pair(n, m);
            v2 = make_pair(n-1, m-1);
            (*E)[v1] = v2; // this is a map to a winner edge
        }
        else if ((*memo)[n - 1][m - 1] == extendA) {
            // puts("Extend A"); 
            v1 = make_pair(n, m);
            v2 = make_pair(n, m-1);
            (*E)[v1] = v2; // this is a map to a winner edge
        }
        else {
            // puts("extend B");
            v1 = make_pair(n, m);
            v2 = make_pair(n-1, m);
            (*E)[v1] = v2; // this is a map to a winner edge
        }
        int leftmost_sum = *leftEndpointA + *leftEndpointB;
        if (leftmost_sum > (*memo)[n - 1][m - 1])
            (*memo)[n - 1][m - 1] = leftmost_sum;
        return (*memo)[n - 1][m - 1];
    }
}

void ExtensibleTeeth::extendT(list<int> *A, list<int> *B, map<pair<int, int>, pair<int, int> > E, int N, int M) {
    for (auto e : E) {
        if (e.first.first - e.second.first == 1 && e.first.second - e.second.second == 1)
            continue;

        else if (e.first.first - e.second.first == 1) {
            // extend B
            auto leftEndpointB = next(B->begin(), M - e.first.second);
            B->insert(leftEndpointB, *leftEndpointB);
        }
        else {
            // extend A
            auto leftEndpointA = next(A->begin(), N - e.first.first);
            A->insert(leftEndpointA, *leftEndpointA);
        }
    }

    while (A->size() < B->size()) // pad right endpoint if needed...
        A->push_back(A->back());
    while (B->size() < A->size()) // pad right endpoint if needed...
        B->push_back(B->back());
}

int ExtensibleTeeth::Wrapper(int n, int m, list<int> *A, list<int> *B) {
    int N = n, M = m;
    // memo table
    vector<vector<int> > memo(n, std::vector<int>(m, -1));
    // this will store the edges that are enabled
    map<pair<int, int>, pair<int, int> > E;
    // this will store the winner path of recursion tree that contains the right teeth heights
    map<pair<int, int>, pair<int, int> > characterPath; 
    int optimalHeight = T(n, m, N, M, A, B, &memo, &E); // recursive calls
    
   pair<int, int> root(N, M); // starts on the root of recursion tree   
   while(true){ // do some prunning to get the winning path
        if (E.find(root) == E.end())
            break;
        characterPath[root] = E[root];
        root = E[root]; 
    }
    extendT(A, B, characterPath, N, M); // extends the teeth accordingly

    return optimalHeight;
}