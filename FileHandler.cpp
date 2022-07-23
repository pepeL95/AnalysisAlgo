#include "FileHandler.hpp"
using namespace std;
//Read sizes from input file
void FileHandler::readSizes(int *size1, int *size2) {
    this->mFile >> *size1 >> *size2;
 }
//Read lists from input file
 void FileHandler::readList(int size, std::list<int>* mList) {
    for (int i = 0; i < size; i++) {
        int j; this->mFile >> j;
        mList->push_back(j);
    }
 }
//Write output file
void FileHandler::writeOutput(std::list<int> A, std::list<int> B, int minDist, string outputFileName) {
    ofstream mFile(outputFileName);
    mFile << minDist << endl;
    list<int>::iterator itr1 = A.begin();
    list<int>::iterator itr2 = B.begin();

    while (itr1 != A.end() && itr2 != B.end())
    {
        mFile << *itr1 << " " << *itr2 << endl;
        itr1++; itr2++;
    }
}
