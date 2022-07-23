#ifndef FILE_HANDLER_HPP
#define FILE_HANDLER_HPP
#include <fstream>
#include <string>
#include <list>
using namespace std;
class FileHandler {
public:
    FileHandler(){}    
    void readSizes(int *size1, int *size2);
    void readList(int size, std::list<int> *mList);
    void writeOutput(std::list<int> A, std::list<int> B, int minDist, string outputFileName);
    void openFile(string fileName) {this->mFile.open(fileName);}
    void closeFile() {this->mFile.close();}
private:
    fstream mFile;
};

#endif