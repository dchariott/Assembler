#include <iostream>
#include "binary_convert.h"
#include <fstream>
#include <map>
#include <iomanip>
#include <algorithm>
using namespace std;

int main(int argc, char* argv[]) {
    int address = 0;
    map<string, int> labels;
    fstream fileToConvert;
    fileToConvert.open("input.txt");
    ifstream fileToRead;
    fileToRead.open(argv[1]);
    string line;

    if (fileToConvert.is_open()){
        ofstream fileToMake;
        fileToMake.open(argv[2]);
        while(getline(fileToRead, line)){
            transform(line.begin(), line.end(), line.begin(), ::tolower);
            fileToConvert << line << endl;
        }

        fileToConvert.seekg(0, ios::beg);
        while (getline(fileToConvert, line)){
           if (line.find(":") != string::npos){
               string::size_type endPos = line.find(":");
               string label = line.substr(0, endPos);
               labels.insert(pair<string, int>(label, address));
           }
           address += 4;
        }

        fileToConvert.clear();
        fileToConvert.seekg(0);
        address = 0;
        while (getline(fileToConvert, line)){
            cout << "0x" << hex << setfill('0') << setw(8) << parse(line, labels, address) << endl;
            fileToMake << "0x" << hex << setfill('0') << setw(8) << parse(line, labels, address) << endl;
            address += 4;
        }
        fileToMake.close();
    }
    fileToConvert.close();
    return 0;
}

