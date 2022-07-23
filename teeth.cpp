#include "FileHandler.hpp"
#include "ExtensibleTeeth.hpp"
using namespace std;

int main() {
    int n, m;
    list<int> A, B;
    string fileName = "input.txt";
    FileHandler fh = FileHandler();
    ExtensibleTeeth extensibleTeeth = ExtensibleTeeth();

    fh.openFile(fileName);
    fh.readSizes(&n, &m);
    fh.readList(n, &A);
    fh.readList(n, &B);
    fh.closeFile();

    int optimalHeight = extensibleTeeth.Wrapper(n, m, &A, &B); // call T() and extendT()
    fh.writeOutput(A, B, optimalHeight, "output.txt");
}