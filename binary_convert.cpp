//
// Created by Dylan Chariott on 2019-03-19.
//

#include "binary_convert.h"

map<string, int> rType = {
        {"sll", 4}, {"srl", 6}, {"sra", 7}, {"sltu", 18}, {"sgtu", 19}, {"sleu", 20},
        {"sgeu", 21}, {"add", 32}, {"addu", 33}, {"sub", 34}, {"subu", 35}, {"and", 36}, {"or", 37},
        {"xor", 38}, {"seq", 40}, {"sne", 41}, {"slt", 42}, {"sgt", 43}, {"sle", 44}, {"sge", 45}
};

map<string, int> iType = {
        {"beqz", 4}, {"bnez", 5}, {"addi", 8}, {"addui", 9}, {"subi", 10}, {"subui", 11}, {"andi", 12}, {"ori", 13}, {"xori", 14},
        {"lhi", 15}, {"jr", 18}, {"jalr", 19}, {"seqi", 24}, {"snei", 25}, {"slti", 26}, {"sgti", 27}, {"slei", 28}, {"sgei", 29},
        {"lb", 32}, {"lh", 33}, {"lw", 35}, {"lbu", 36}, {"lhu", 37}, {"sb", 40}, {"sh", 41},
        {"sw", 43}, {"sequi", 48}, {"senui", 49}, {"sltui", 50}, {"sgtui", 51}, {"sleui", 52}, {"sgeui", 53},
        {"slli", 54}, {"srli", 55}, {"srai", 56}
};

map<string, int> jType = {
        {"j", 2}, {"jal", 3}
};


map<string, int> addresses;

int parseRType(string opcode_str, vector<string>& tokens){
    int opcode = 0, rs1 = 0, rs2 = 0, rd = 0, funct = 0;
    string rd_str = "", rs1_str = "", rs2_str = "";
    rd_str = tokens[0];
    rs1_str = tokens[1];
    rs2_str = tokens[2];
    funct = rType.at(opcode_str);


    string::size_type pos = rd_str.find('r');
    rd_str = rd_str.substr(pos + 1, string::npos);
    rd = stoi(rd_str, nullptr);
    rd <<= 11;

    pos = rs1_str.find('r');
    rs1_str = rs1_str.substr(pos + 1, string::npos);
    rs1 = stoi(rs1_str, nullptr);
    rs1 <<= 21;

    pos = rs2_str.find('r');
    rs2_str = rs2_str.substr(pos + 1, string::npos);
    rs2 = stoi(rs2_str, nullptr);
    rs2 <<= 16;

    return opcode | rs1 | rs2 | rd | funct;
}

int parseIType(string opcode_str, vector<string>& tokens, int address){
    int opcode = 0, rs1 = 0, rs2 = 0, imm = 0;
    string rs1_str = "", rs2_str = "", imm_str = "";
    opcode = iType.at(opcode_str);
    opcode <<= 26;

    if (opcode_str == "lhi"){
        rs2_str = tokens[0];
        string::size_type pos = rs2_str.find('r');
        rs2_str = rs2_str.substr(pos + 1, string::npos);
        rs2 = stoi(rs2_str, nullptr);
        imm_str = tokens[1];
        if (imm_str.find(' ') != string::npos){
            imm_str = imm_str.substr(1, string::npos);
        }
        imm = stoi(imm_str, nullptr);
    }
    else if (tokens[0].find('(') != string::npos && tokens[0].find(')') != string::npos){
        string::size_type beginPos = tokens[0].find("(");
        string::size_type endPos = tokens[0].find(")");
        imm_str = tokens[0].substr(0, beginPos);
        imm = stoi(imm_str, nullptr);
        rs1_str = tokens[0].substr(beginPos + 2, endPos);
        rs1 = stoi(rs1_str, nullptr);
        rs2_str = tokens[1];
        beginPos = rs2_str.find('r');
        rs2_str = rs2_str.substr(beginPos + 1, string::npos);
        rs2 = stoi(rs2_str, nullptr);
    }
    else if (tokens[1].find('(') != string::npos && tokens[1].find(')') != string::npos){
        string::size_type beginPos = tokens[1].find("(");
        string::size_type endPos = tokens[1].find(")");
        imm_str = tokens[1].substr(0, beginPos);
        if (imm_str.find(' ') != string::npos){
            imm_str = imm_str.substr(1, string::npos);
        }
        imm = stoi(imm_str, nullptr);
        rs1_str = tokens[1].substr(beginPos + 2, endPos);
        rs1 = stoi(rs1_str, nullptr);
        rs2_str = tokens[0].substr(1, string::npos);
        rs2 = stoi(rs2_str, nullptr);
    }
    else if (opcode_str == "beqz" || opcode_str == "bnez"){
        rs1_str = tokens[0].substr(1, string::npos);
        rs1 = stoi(rs1_str, nullptr);
        imm_str = tokens[1];
        if (imm_str.find(' ') != string::npos){
            imm_str = imm_str.substr(1, string::npos);
        }
        imm = addresses.at(imm_str);
        imm -= (address + 4);
    }
    else if (opcode_str.find("j") != string::npos){
        string rs1_str = tokens[0].substr(1, string::npos);
        rs1 = stoi(rs1_str, nullptr);
    }
    else{
        string rs2_str = tokens[0].substr(1, string::npos);
        rs2 = stoi(rs2_str, nullptr);
        string::size_type pos = tokens[1].find('r');
        string rs1_str = tokens[1].substr(pos + 1, string::npos);
        rs1 = stoi(rs1_str, nullptr);
        string imm_str = tokens[2];
        if (imm_str.find(' ') != string::npos){
            imm_str = imm_str.substr(1, string::npos);
        }
        imm = stoi(imm_str, nullptr);
    }

    rs1 <<= 21;
    rs2 <<= 16;

    if (imm < 0){
        int mask = 0b00000000000000001111111111111111;
        imm &= mask;
    }

    return opcode | rs1 | rs2 | imm;
}

int parseJType(string opcode_str, vector<string>& tokens, int address){
    int opcode = 0, offset = 0;

    opcode = jType.at(opcode_str);
    opcode <<= 26;
    string offset_str = tokens[0];
    offset = addresses.at(offset_str);
    offset -= (address + 4);
    if (offset < 0){
        int mask = 0b00000011111111111111111111111111;
        offset &= mask;
    }

    return opcode | offset;
}

int parse(string line,  const map<string, int>& labels, int address){
    vector<string> tokens;
    stringstream lineS(line);
    string opcode_str = "";
    if (line.find(':') != string::npos){
        string temp = "";
        getline(lineS, temp, ' ');
    }
    getline(lineS, opcode_str, ' ');

    string temp;
    while(getline(lineS, temp, ',')){
        tokens.push_back(temp);
    }

    if (addresses.empty()){
        addresses = labels;
    }
    if (rType.find(opcode_str) != rType.end()){
        return parseRType(opcode_str, tokens);
    }
    else if (iType.find(opcode_str) != iType.end()){
        return parseIType(opcode_str, tokens, address);
    }
    else if (jType.find(opcode_str) != jType.end()){
        return parseJType(opcode_str, tokens, address);
    }
    else{
        return 0;
    }
}