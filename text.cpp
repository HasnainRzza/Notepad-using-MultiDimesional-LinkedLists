#include <iostream>
#include<conio.h>
#include <fstream>
#include <string>

using namespace std;
        int rowCounter = 0;
        int maxCharCount = 0;
class FileAnalyzer {
public:
    FileAnalyzer(const string& filename) : filename(filename) {
    }

    void analyze() {
        ifstream file(filename);

        if (!file) {
            cerr << "Failed to open the file." << endl;
            return;
        }

        string maxCharRow;

        string line;
        while (getline(file, line)) {
            rowCounter++;
            int currentCharCount = line.length();
            if (currentCharCount > maxCharCount) {
                maxCharCount = currentCharCount;
                maxCharRow = line;
            }
        }
        file.close();
    }

private:
    string filename;
};

