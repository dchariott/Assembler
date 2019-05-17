//
// Created by Dylan Chariott on 2019-03-19.
//

#ifndef ASSEMBLER_BINARY_CONVERT_H
#define ASSEMBLER_BINARY_CONVERT_H
#include <string>
#include <iostream>
#include <sstream>
#include <map>
#include <vector>
#include <utility>
using namespace std;

int parseRType(string opcode_str, vector<string>& tokens);
int parseIType(string opcode_str, vector<string>& tokens, int address);
int parseJType(string opcode_str, vector<string>& tokens, int address);
int parse(string line, const map<string, int>& labels, int address);

#endif //ASSEMBLER_BINARY_CONVERT_H
