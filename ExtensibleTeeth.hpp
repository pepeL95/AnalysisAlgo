#ifndef EXTENSIBLE_TEETH
#define EXTENSIBLE_TEETH
#include "ExtensibleTeeth.hpp"
#include <iostream>
#include <algorithm>
#include <string>
#include <list>
#include <iterator>
#include <map>
#include <vector>
using namespace std;

class ExtensibleTeeth {
public:
    ExtensibleTeeth(){};
    void extendT(list<int> *A, list<int> *B, map<pair<int, int>, pair<int, int> > E, int N, int M);
    int T(int n, int m, int N, int M, std::list<int> *A, std::list<int> *B, vector<vector<int>> *memo, map<pair<int, int>, pair<int, int> > *E);
    int Wrapper(int n, int m, list<int> *A, list<int> *B);
};


#endif